// LCA by binary lifting on a tree (adjacency list).
// O(n log n) build, O(log n) query. Iterative (no deep DFS).
struct LCA {
  int L; vector<vi> up; vi dep, order;
  LCA(const vector<vi>& g, int root = 0)
    : L(__lg(max(1, sz(g))) + 1),
      up(L, vi(sz(g), root)), dep(sz(g)) {
    order = {root};               // BFS order
    vector<bool> seen(sz(g)); seen[root] = true;
    for (int i = 0; i < sz(order); i++)
      for (int v : g[order[i]]) if (!seen[v]) {
        seen[v] = true; up[0][v] = order[i];
        dep[v] = dep[order[i]] + 1; order.push_back(v); }
    for (int k = 1; k < L; k++)
      for (int v = 0; v < sz(g); v++)
        up[k][v] = up[k - 1][up[k - 1][v]];
  }
  int kth(int v, int k) {         // k-th ancestor (k <= dep)
    for (int i = 0; i < L; i++) if (k >> i & 1) v = up[i][v];
    return v; }
  int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    a = kth(a, dep[a] - dep[b]);
    if (a == b) return a;
    for (int k = L - 1; k >= 0; k--)
      if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
    return up[0][a]; }
  int dist(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }
};
// Tree DP bottom-up without recursion: for v in reversed
// order: combine v into up[0][v].  Subtree as a range:
// Euler tour tin/tout; v is an ancestor of u
// <=> tin[v] <= tin[u] < tout[v].
