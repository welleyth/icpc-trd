// Max flow (Dinic, multi-push). O(V^2 E); unit caps:
// O(E sqrt V). 1e5 edges in well under a second.
struct Dinic {
  struct E { int to; ll cap; };
  vector<E> e; vector<vi> g; vi lvl, it;
  Dinic(int n) : g(n), lvl(n), it(n) {}
  // rc = capacity of the reverse edge (undirected: rc = c)
  int addEdge(int u, int v, ll c, ll rc = 0) {
    g[u].push_back(sz(e)); e.push_back({v, c});
    g[v].push_back(sz(e)); e.push_back({u, rc});
    return sz(e) - 2; }     // flow on edge id = e[id ^ 1].cap
  bool bfs(int s, int t) {
    fill(all(lvl), -1); lvl[s] = 0;
    vi q{s};
    for (int i = 0; i < sz(q); i++)
      for (int id : g[q[i]])
        if (e[id].cap > 0 && lvl[e[id].to] < 0) {
          lvl[e[id].to] = lvl[q[i]] + 1;
          q.push_back(e[id].to); }
    return lvl[t] >= 0; }
  ll dfs(int u, int t, ll f) {     // pushes up to f from u
    if (u == t) return f;
    ll pushed = 0;
    for (int& i = it[u]; i < sz(g[u]); i++) {
      E& x = e[g[u][i]];
      if (x.cap <= 0 || lvl[x.to] != lvl[u] + 1) continue;
      ll d = dfs(x.to, t, min(f - pushed, x.cap));
      x.cap -= d; e[g[u][i] ^ 1].cap += d; pushed += d;
      if (pushed == f) return f;  // edge may have cap left
    }
    lvl[u] = -1;                   // dead end: prune
    return pushed; }
  ll maxflow(int s, int t) {
    ll flow = 0;
    while (bfs(s, t)) { fill(all(it), 0);
                        flow += dfs(s, t, LLONG_MAX); }
    return flow; }
};
// Min cut after maxflow(): S side = {v : lvl[v] >= 0}.
// Bipartite matching: s->L, L->R, R->t, all caps 1.
