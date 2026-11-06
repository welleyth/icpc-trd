// Block-cut tree (vertex-biconnected components). Nodes 0..n-1
// are vertices, n.. are blocks; tree edges vertex - block.
// Cut vertices = vertices with >= 2 blocks. CACTUS: each cycle
// is one block and tree[b] lists it IN CYCLE ORDER, starting
// at the block's top vertex tree[b][0] (nearest to the root).
// Simple graph (multi-edges: skip the parent EDGE id instead).
struct BlockCut {
  int timer = 0; vector<vi> g, tree; vi tin, low, st;
  BlockCut(const vector<vi>& g_) : g(g_), tree(sz(g)),
      tin(sz(g), -1), low(sz(g)) {
    for (int v = 0; v < sz(g); v++)
      if (tin[v] < 0) dfs(v, -1); }
  void dfs(int u, int p) {
    tin[u] = low[u] = timer++; st.push_back(u);
    for (int v : g[u]) {
      if (v == p) continue;
      if (tin[v] >= 0) {
        low[u] = min(low[u], tin[v]); continue; }
      dfs(v, u); low[u] = min(low[u], low[v]);
      if (low[v] >= tin[u]) {            // u tops a new block
        int b = sz(tree);
        tree.push_back({u}); tree[u].push_back(b);
        int w;
        do {
          w = st.back(); st.pop_back();
          tree[b].push_back(w); tree[w].push_back(b);
        } while (w != v);
      }
    } }
};
