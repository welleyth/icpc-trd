#include "common.h"
#include "../src/3-graph/bridges.cpp"
#include "chk.h"
int comps(int n, vector<pii>& es, int skipE, int skipV) {
  vi p(n); iota(all(p), 0);
  function<int(int)> f = [&](int x) { return p[x]==x?x:p[x]=f(p[x]); };
  for (int i = 0; i < sz(es); i++) {
    if (i == skipE) continue;
    auto [u, v] = es[i];
    if (u == skipV || v == skipV) continue;
    p[f(u)] = f(v); }
  int c = 0;
  for (int i = 0; i < n; i++) if (i != skipV && f(i) == i) c++;
  return c; }
int main() {
  for (int iter = 0; iter < 30000; iter++) {
    int n = rnd(1, 8), m = rnd(0, 12);
    Bridges b(n, m); vector<pii> es;
    for (int i = 0; i < m; i++) {
      int u = rnd(0, n-1), v = rnd(0, n-1);
      b.addEdge(u, v, i); es.push_back({u, v}); }
    b.run();
    int c0 = comps(n, es, -1, -1);
    for (int i = 0; i < m; i++)
      CHECK((bool)b.isBridge[i] == (comps(n, es, i, -1) > c0));
    for (int v = 0; v < n; v++) {
      // size of v's component
      vi p(n); iota(all(p), 0);
      function<int(int)> f=[&](int x){return p[x]==x?x:p[x]=f(p[x]);};
      for (auto [x,y]: es) p[f(x)]=f(y);
      int cs = 0; for (int i=0;i<n;i++) cs += f(i)==f(v);
      int expect = c0 - (cs == 1);
      CHECK((bool)b.isCut[v] == (comps(n, es, -1, v) > expect));
    }
  }
  DONE();
}
