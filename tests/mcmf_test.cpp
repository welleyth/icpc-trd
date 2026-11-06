#include "common.h"
#include "../src/3-graph/mcmf.cpp"
#include "chk.h"
int main() {
  // assignment problem with negative costs
  for (int iter = 0; iter < 20000; iter++) {
    int n = rnd(1, 5);
    vector<vector<int>> c(n, vector<int>(n));
    MCMF M(2 * n + 2); int s = 2 * n, t = 2 * n + 1;
    for (int i = 0; i < n; i++) {
      M.addEdge(s, i, 1, 0); M.addEdge(n + i, t, 1, 0);
      for (int j = 0; j < n; j++) {
        c[i][j] = rnd(-10, 10); M.addEdge(i, n + j, 1, c[i][j]); } }
    vi p(n); iota(all(p), 0); ll best = LLONG_MAX;
    do { ll s2 = 0; for (int i = 0; i < n; i++) s2 += c[i][p[i]];
      best = min(best, s2); } while (next_permutation(all(p)));
    auto [f, cost] = M.run(s, t);
    CHECK(f == n && cost == best);
  }
  // general graphs with unit caps: brute over edge subsets
  for (int iter = 0; iter < 20000; iter++) {
    int n = rnd(2, 5), m = rnd(0, 9);
    bool dag = iter % 2;
    MCMF M(n); struct E { int u, v, w; }; vector<E> es;
    for (int i = 0; i < m; i++) {
      int u = rnd(0, n-1), v = rnd(0, n-1);
      if (dag) { if (u == v) continue; if (u > v) swap(u, v); }
      int w = dag ? rnd(-5, 5) : rnd(0, 5);
      int cap = rnd(1, 2);
      // expand cap by parallel unit edges for brute
      for (int k = 0; k < cap; k++) es.push_back({u, v, w});
      M.addEdge(u, v, cap, w); }
    int mm = sz(es); int s = 0, t = n - 1;
    int bf = -1; ll bc = 0;
    for (int mask = 0; mask < 1 << mm; mask++) {
      vi bal(n); ll cost = 0;
      for (int i = 0; i < mm; i++) if (mask >> i & 1) {
        bal[es[i].u]--; bal[es[i].v]++; cost += es[i].w; }
      bool ok = true;
      for (int v = 0; v < n; v++) if (v != s && v != t && bal[v]) ok = false;
      if (!ok) continue;
      int fl = bal[t]; if (s == t) continue;
      if (fl < 0) continue;
      // bal[s] == -fl? yes by conservation
      if (fl > bf || (fl == bf && cost < bc)) bf = fl, bc = cost;
    }
    auto [f, cost] = M.run(s, t);
    CHECK(f == bf && cost == bc);
    if (f != bf || cost != bc) { }
  }
  // lim
  { MCMF M(2); M.addEdge(0, 1, 5, 3); auto r = M.run(0, 1, 2);
    CHECK(r.first == 2 && r.second == 6); }
  { MCMF M(2); auto r = M.run(0, 1); CHECK(r.first == 0 && r.second == 0); }
  DONE();
}
