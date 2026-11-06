#include "common.h"
#include "../src/3-graph/shortest.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 20000; iter++) {
    int n = rnd(1, 7), m = rnd(0, 14);
    int mode = iter % 3;  // 0: nonneg, 1: 0/1, 2: negative
    vector<array<ll,3>> e; Adj g(n);
    vector<vector<ll>> f(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) f[i][i] = 0;
    for (int i = 0; i < m; i++) {
      int u = rnd(0, n-1), v = rnd(0, n-1);
      ll w = mode == 0 ? rnd(0, 10) : mode == 1 ? rnd(0, 1)
           : rnd(-3, 10);
      if (mode == 2 && rnd(0, 3)) w = abs(w);
      e.push_back({u, v, w}); g[u].push_back({v, w});
      f[u][v] = min(f[u][v], w);
    }
    for (int k = 0; k < n; k++) for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (f[i][k] < INF && f[k][j] < INF)
          f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    int s = rnd(0, n-1);
    if (mode == 0) {
      auto d = dijkstra(g, s);
      for (int v = 0; v < n; v++) CHECK(d[v] == f[s][v]);
    } else if (mode == 1) {
      auto d = bfs01(g, s);
      for (int v = 0; v < n; v++) CHECK(d[v] == f[s][v]);
    } else {
      bool neg = false;
      for (int v = 0; v < n; v++)
        if (f[s][v] < INF && f[v][v] < 0) neg = true;
      vector<ll> d;
      bool ok = bellman(n, e, s, d);
      CHECK(ok == !neg);
      if (ok) for (int v = 0; v < n; v++) CHECK(d[v]==f[s][v]);
    }
  }
  // big weights
  Adj g(3); g[0].push_back({1, (ll)1e18}); g[1].push_back({2, (ll)1e18});
  auto d = dijkstra(g, 0); CHECK(d[2] == (ll)2e18);
  DONE();
}
