#include "common.h"
#include "../src/3-graph/scc.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 20000; iter++) {
    int n = rnd(1, 8), m = rnd(0, 14);
    SCC s(n); vector<vector<bool>> r(n, vector<bool>(n));
    for (int i = 0; i < n; i++) r[i][i] = true;
    vector<pii> es;
    for (int i = 0; i < m; i++) {
      int u = rnd(0, n-1), v = rnd(0, n-1);
      s.g[u].push_back(v); r[u][v] = true; es.push_back({u, v}); }
    for (int k = 0; k < n; k++) for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) if (r[i][k] && r[k][j]) r[i][j] = true;
    s.run();
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
      CHECK((s.comp[i] == s.comp[j]) == (r[i][j] && r[j][i]));
    for (auto [u, v] : es) CHECK(s.comp[u] >= s.comp[v]);
    for (int i = 0; i < n; i++) CHECK(s.comp[i] >= 0 && s.comp[i] < s.ncomp);
  }
  // 2-SAT
  for (int iter = 0; iter < 30000; iter++) {
    int n = rnd(1, 6), m = rnd(0, 12);
    TwoSat ts(n); struct C { int x; bool vx; int y; bool vy; };
    vector<C> cl;
    for (int i = 0; i < m; i++) {
      C c{rnd(0, n-1), (bool)rnd(0, 1), rnd(0, n-1), (bool)rnd(0, 1)};
      if (rnd(0, 5) == 0) { c.y = c.x; c.vy = c.vx; }
      if (rnd(0, 7) == 0) { ts.force(c.x, c.vx); c.y = c.x; c.vy = c.vx; }
      else ts.either(c.x, c.vx, c.y, c.vy);
      cl.push_back(c);
    }
    auto sat = [&](int mask) {
      for (auto& c : cl)
        if (!(((mask >> c.x & 1) == c.vx) || ((mask >> c.y & 1) == c.vy)))
          return false;
      return true; };
    bool any = false;
    for (int mask = 0; mask < 1 << n; mask++) any |= sat(mask);
    vector<bool> val;
    bool ok = ts.solve(val);
    CHECK(ok == any);
    if (ok) {
      int mask = 0;
      for (int i = 0; i < n; i++) if (val[i]) mask |= 1 << i;
      CHECK(sat(mask));
    }
  }
  DONE();
}
