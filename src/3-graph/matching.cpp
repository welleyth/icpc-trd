// Bipartite matching (Kuhn), left 0..n-1 -> right 0..m-1.
// O(V E) worst, fast in practice. For big graphs use Dinic.
// Konig: min vertex cover = max matching;
// max independent set = n + m - matching.
struct Kuhn {
  int n, m; vector<vi> g; vi mt, vis; int stamp = 0;
  Kuhn(int n, int m) : n(n), m(m), g(n), mt(m, -1), vis(n) {}
  bool dfs(int u) {
    if (vis[u] == stamp) return false;
    vis[u] = stamp;
    for (int v : g[u])
      if (mt[v] < 0 || dfs(mt[v])) { mt[v] = u; return true; }
    return false; }
  int run() {
    int res = 0;
    for (int u = 0; u < n; u++) { stamp++; res += dfs(u); }
    return res; }       // mt[v] = left partner of right v
};
