#include "common.h"
#include "../src/3-graph/linkcut.cpp"
#include "chk.h"
struct D { vi p; D(int n) : p(n+1) { iota(all(p), 0); } int f(int x) { return p[x]==x?x:p[x]=f(p[x]); } };
int main() {
  // unrooted
  for (int it = 0; it < 3000; it++) {
    int n = rnd(1, it % 100 == 0 ? 2000 : 12); LCT t(n); set<pii> es; int ops = it % 100 == 0 ? 20000 : 60;
    auto conn = [&](int a, int b) { D d(n); for (auto e : es) d.p[d.f(e.first)] = d.f(e.second); return d.f(a) == d.f(b); };
    for (int o = 0; o < ops; o++) {
      int ty = rnd(0, 2), a = rnd(1, n), b = rnd(1, n);
      bool big = n > 100;
      if (ty == 0) { if (a != b && !(big ? false : conn(a, b)) && (big ? !t.connected(a,b) : true)) { t.link(a, b); es.insert({min(a,b),max(a,b)}); } }
      else if (ty == 1) { if (!es.empty()) { auto it2 = es.begin(); advance(it2, rnd(0, sz(es)-1)); auto e = *it2; es.erase(it2); if (rnd(0,1)) t.cut(e.first, e.second); else t.cut(e.second, e.first); } }
      else { if (!big) CHECK(t.connected(a, b) == conn(a, b)); else if (o % 50 == 0) CHECK(t.connected(a, b) == conn(a, b)); }
    }
  }
  // rooted
  for (int it = 0; it < 3000; it++) {
    int n = rnd(1, it % 100 == 0 ? 2000 : 12); LCT t(n); vi par(n+1, 0); int ops = it % 100 == 0 ? 20000 : 60;
    auto root = [&](int x) { while (par[x]) x = par[x]; return x; };
    for (int o = 0; o < ops; o++) {
      int ty = rnd(0, 2), a = rnd(1, n), b = rnd(1, n);
      if (ty == 0) { if (!par[a] && root(b) != a) { t.linkRooted(a, b); par[a] = b; } }
      else if (ty == 1) { if (par[a]) { t.cutParent(a); par[a] = 0; } }
      else CHECK(t.findRoot(a) == root(a));
    }
    for (int a = 1; a <= n; a++) CHECK(t.findRoot(a) == root(a));
  }
  // speed 1e5: chain then random
  { int n = 100000; LCT t(n); for (int i = 2; i <= n; i++) t.linkRooted(i, i-1);
    CHECK(t.findRoot(n) == 1); for (int i = 0; i < 100000; i++) { int a = rnd(2, n); t.cutParent(a); CHECK(t.findRoot(a) == a); t.linkRooted(a, a-1); }
    LCT u(n); for (int i = 2; i <= n; i++) u.link(i, i-1); for (int i = 0; i < 100000; i++) { int a = rnd(2,n); u.cut(a, a-1); CHECK(!u.connected(a, a-1)); u.link(a-1, a); } }
  DONE();
}
