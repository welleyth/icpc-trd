// Functional graph v -> f[v] (out-degree 1): each component is
// one cycle with in-trees. Peel indegree-0 vertices (Kahn);
// what remains are cycles. O(n), no recursion.
// order = peeled vertices, leaves first: tree DP towards the
// cycle in this order (e.g. h[f[v]] = max(h[f[v]], h[v] + 1));
// distance to the cycle: dist[v] = dist[f[v]] + 1, going
// through order REVERSED.
// Cycle problems: work on the cycle doubled (length 2L) with
// prefix sums / sliding windows. k-th successor: binary
// lifting on f.
struct Functional {
  vi f, onCyc, cycId, order; vector<vi> cycles;
  Functional(const vi& f_) : f(f_) {
    int n = sz(f); vi indeg(n);
    onCyc.assign(n, 1); cycId.assign(n, -1);
    for (int v : f) indeg[v]++;
    for (int v = 0; v < n; v++)
      if (!indeg[v]) order.push_back(v);
    for (int i = 0; i < sz(order); i++) {
      int v = order[i]; onCyc[v] = 0;
      if (!--indeg[f[v]]) order.push_back(f[v]);
    }
    for (int v = 0; v < n; v++) if (onCyc[v] && cycId[v] < 0) {
      cycles.emplace_back();
      for (int u = v; cycId[u] < 0; u = f[u])
        cycId[u] = sz(cycles) - 1, cycles.back().push_back(u);
    }
  }
};
