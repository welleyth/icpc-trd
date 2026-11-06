// Heavy-light decomposition. Path u-v = O(log n) ranges of
// positions [l, r); put values at pos[v] in a segment tree.
// Subtree of v = [pos[v], pos[v] + size[v]).
// Values on EDGES: store edge (par v, v) at pos[v] and skip
// the LCA: in the last step use pos[a] + 1.
struct HLD {
  vi par, dep, heavy, head, pos, size; int timer = 0;
  HLD(const vector<vi>& g, int root = 0) : par(sz(g), -1),
      dep(sz(g)), heavy(sz(g), -1), head(sz(g)), pos(sz(g)),
      size(sz(g), 1) {
    dfs(g, root); decompose(g, root, root); }
  void dfs(const vector<vi>& g, int u) {
    for (int v : g[u]) if (v != par[u]) {
      par[v] = u; dep[v] = dep[u] + 1; dfs(g, v);
      size[u] += size[v];
      if (heavy[u] < 0 || size[v] > size[heavy[u]])
        heavy[u] = v;
    } }
  void decompose(const vector<vi>& g, int u, int h) {
    head[u] = h; pos[u] = timer++;
    if (heavy[u] >= 0) decompose(g, heavy[u], h);
    for (int v : g[u])
      if (v != par[u] && v != heavy[u]) decompose(g, v, v); }
  template <class F> void path(int a, int b, F f) {
    for (; head[a] != head[b]; b = par[head[b]]) {
      if (dep[head[a]] > dep[head[b]]) swap(a, b);
      f(pos[head[b]], pos[b] + 1);
    }
    if (dep[a] > dep[b]) swap(a, b);
    f(pos[a], pos[b] + 1); }    // a = LCA here
  int lca(int a, int b) {
    for (; head[a] != head[b]; b = par[head[b]])
      if (dep[head[a]] > dep[head[b]]) swap(a, b);
    return dep[a] < dep[b] ? a : b; }
};
// usage: h.path(u, v, [&](int l, int r) {
//          ans += seg.query(l, r); });
