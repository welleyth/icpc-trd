// Min-cost max-flow (SPFA augmenting paths); negative costs
// OK if no negative cycle. O(flow * V * E) worst case.
struct MCMF {
  struct E { int to; ll cap, cost; };
  vector<E> e; vector<vi> g; vector<ll> d; vi pe;
  MCMF(int n) : g(n), d(n), pe(n) {}
  void addEdge(int u, int v, ll cap, ll cost) {
    g[u].push_back(sz(e)); e.push_back({v, cap, cost});
    g[v].push_back(sz(e)); e.push_back({u, 0, -cost}); }
  pair<ll, ll> run(int s, int t, ll lim = LLONG_MAX) {
    ll flow = 0, cost = 0; vector<bool> inq(sz(g));
    while (flow < lim) {
      fill(all(d), LLONG_MAX); d[s] = 0;
      deque<int> q{s};
      while (!q.empty()) {
        int u = q.front(); q.pop_front(); inq[u] = false;
        for (int id : g[u]) {
          auto& x = e[id];
          if (x.cap > 0 && d[u] + x.cost < d[x.to]) {
            d[x.to] = d[u] + x.cost; pe[x.to] = id;
            if (!inq[x.to])
              inq[x.to] = true, q.push_back(x.to);
          }
        }
      }
      if (d[t] == LLONG_MAX) break;
      ll f = lim - flow;
      for (int v = t; v != s; v = e[pe[v] ^ 1].to)
        f = min(f, e[pe[v]].cap);
      for (int v = t; v != s; v = e[pe[v] ^ 1].to)
        e[pe[v]].cap -= f, e[pe[v] ^ 1].cap += f;
      flow += f; cost += f * d[t];
    }
    return {flow, cost}; }
};
// Assignment problem n x n: s->row (1,0), row->col (1,c),
// col->t (1,0). Max cost: negate costs.
