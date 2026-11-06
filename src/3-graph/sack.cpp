// Small-to-large merging: always insert the smaller set into
// the larger one (swap is O(1)) -> every element moves
// O(log n) times. Example: # distinct colours in each subtree.
// Recursive: a path of 1e5 overflows an 8MB stack (see the
// checklist: bigger stack or iterative order).
vector<vi> g; vi col, ans;
set<int> dfs(int u, int p) {
  set<int> s{col[u]};
  for (int v : g[u]) if (v != p) {
    set<int> t = dfs(v, u);
    if (sz(t) > sz(s)) swap(s, t);
    s.insert(all(t));
  }
  ans[u] = sz(s);
  return s; }
