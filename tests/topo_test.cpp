#include "common.h"
#include "../src/3-graph/topo.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 20000; iter++) {
    int n = rnd(1, 7), m = rnd(0, 10);
    vector<vi> g(n); vector<vector<bool>> r(n, vector<bool>(n));
    for (int i = 0; i < m; i++) {
      int u = rnd(0, n-1), v = rnd(0, n-1);
      g[u].push_back(v); r[u][v] = true; }
    for (int k = 0; k < n; k++) for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) if (r[i][k] && r[k][j]) r[i][j] = true;
    bool cyc = false;
    for (int i = 0; i < n; i++) cyc |= r[i][i];
    auto o = topo(g);
    CHECK((sz(o) < n) == cyc);
    if (!cyc) {
      vi pos(n, -1);
      for (int i = 0; i < n; i++) pos[o[i]] = i;
      for (int u = 0; u < n; u++) for (int v : g[u])
        CHECK(pos[u] < pos[v]);
    }
  }
  CHECK(topo(vector<vi>(0)).empty());
  DONE();
}
