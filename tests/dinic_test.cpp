#include "common.h"
#include "../src/3-graph/dinic.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 30000; iter++) {
    int n = rnd(2, 7), m = rnd(0, 12);
    bool und = iter % 3 == 0;
    Dinic d(n); vector<vector<ll>> c(n, vector<ll>(n));
    vi ids; vector<array<int,3>> es;
    for (int i = 0; i < m; i++) {
      int u = rnd(0, n-1), v = rnd(0, n-1); int w = rnd(0, 6);
      if (rnd(0, 5) == 0) w = rnd(1000000, 2000000);
      ids.push_back(d.addEdge(u, v, w, und ? w : 0));
      es.push_back({u, v, w});
      c[u][v] += w; if (und) c[v][u] += w; }
    int s = 0, t = n - 1;
    ll best = LLONG_MAX;
    for (int mask = 0; mask < 1 << n; mask++) {
      if (!(mask & 1) || (mask >> t & 1)) continue;
      ll cut = 0;
      for (int u = 0; u < n; u++) for (int v = 0; v < n; v++)
        if ((mask >> u & 1) && !(mask >> v & 1)) cut += c[u][v];
      best = min(best, cut); }
    ll f = d.maxflow(s, t);
    CHECK(f == best);
    // min cut from lvl
    ll cut = 0; ll S = 0;
    for (int u = 0; u < n; u++) for (int v = 0; v < n; v++)
      if (d.lvl[u] >= 0 && d.lvl[v] < 0) cut += c[u][v];
    CHECK(d.lvl[s] >= 0 && d.lvl[t] < 0);
    CHECK(cut == f); (void)S;
    if (!und) {
      // flow on edge, conservation
      vector<ll> bal(n);
      for (int i = 0; i < m; i++) {
        ll fl = d.e[ids[i] ^ 1].cap;
        CHECK(fl >= 0 && fl <= es[i][2]);
        bal[es[i][0]] -= fl; bal[es[i][1]] += fl; }
      for (int v = 0; v < n; v++)
        if (v != s && v != t) CHECK(bal[v] == 0);
      CHECK(bal[t] == f || (s == t));
    }
  }
  DONE();
}
