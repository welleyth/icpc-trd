// Tarjan SCC. comp[v] in [0, ncomp); components are numbered
// in REVERSE topological order (comp 0 is a sink). O(n + m)
struct SCC {
  int n, timer = 0, ncomp = 0;
  vector<vi> g; vi tin, low, comp, st;
  SCC(int n) : n(n), g(n), tin(n, -1), low(n), comp(n, -1) {}
  void dfs(int u) {
    tin[u] = low[u] = timer++; st.push_back(u);
    for (int v : g[u]) {
      if (tin[v] < 0) dfs(v), low[u] = min(low[u], low[v]);
      else if (comp[v] < 0) low[u] = min(low[u], tin[v]);
    }
    if (low[u] == tin[u]) {
      int v;
      do { v = st.back(); st.pop_back(); comp[v] = ncomp; }
      while (v != u);
      ncomp++;
    } }
  void run() {
    for (int i = 0; i < n; i++) if (tin[i] < 0) dfs(i); }
};
// 2-SAT: variable x -> nodes 2x (x true), 2x+1 (x false).
struct TwoSat {
  int n; SCC s;
  TwoSat(int n) : n(n), s(2 * n) {}
  // clause (x == vx) OR (y == vy)
  void either(int x, bool vx, int y, bool vy) {
    int a = 2 * x + !vx, b = 2 * y + !vy;
    s.g[a ^ 1].push_back(b); s.g[b ^ 1].push_back(a); }
  void force(int x, bool v) { either(x, v, x, v); }
  bool solve(vector<bool>& val) {
    s.run(); val.assign(n, false);
    for (int i = 0; i < n; i++) {
      if (s.comp[2 * i] == s.comp[2 * i + 1]) return false;
      val[i] = s.comp[2 * i] < s.comp[2 * i + 1];
    }
    return true; }
};
