// Bridges and articulation points (multi-edges OK). O(n + m)
// 2-edge-connected comps: DFS/DSU over non-bridge edges.
struct Bridges {
  int timer = 0;
  vector<vector<pii>> g;              // (to, edge id)
  vi tin, low; vector<bool> isBridge, isCut;
  Bridges(int n, int m)
    : g(n), tin(n, -1), low(n), isBridge(m), isCut(n) {}
  void addEdge(int u, int v, int id) {
    g[u].push_back({v, id}); g[v].push_back({u, id}); }
  void dfs(int u, int pe) {
    tin[u] = low[u] = timer++; int kids = 0;
    for (auto [v, id] : g[u]) {
      if (id == pe) continue;
      if (tin[v] >= 0) {
        low[u] = min(low[u], tin[v]); continue; }
      dfs(v, id); kids++;
      low[u] = min(low[u], low[v]);
      if (low[v] > tin[u]) isBridge[id] = true;
      if (pe >= 0 && low[v] >= tin[u]) isCut[u] = true;
    }
    if (pe < 0 && kids > 1) isCut[u] = true; }
  void run() {
    for (int i = 0; i < sz(g); i++)
      if (tin[i] < 0) dfs(i, -1); }
};
