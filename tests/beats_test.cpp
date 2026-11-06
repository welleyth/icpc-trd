#include "t_util.h"
#include "../src/2-ds/lazyseg.cpp"
#include "../src/2-ds/beats.cpp"
#include "beats_shim.h"
int main() {
  for (int it = 0; it < 30000; it++) {
    int n = it % 10 == 0 ? 1 : rnd(1, 20);
    ll V = it % 3 == 0 ? 1000000000000LL : it % 3 == 1 ? 5 : 1000;
    vector<ll> a(n); for (ll& v : a) v = rnd(-V, V);
    bool neg = it % 4 == 0; // chmax through negation
    vector<ll> init = a; if (neg) for (ll& v : init) v = -v;
    Beats b(init);
    for (int q = 0; q < 60; q++) {
      int l = rnd(0, n - 1), r = rnd(l + 1, n); ll v = rnd(-V, V);
      if (q % 9 == 0) v = a[rnd(0, n - 1)];
      if (!neg) { b.chmin(l, r, v); for (int k = l; k < r; k++) a[k] = min(a[k], v); }
      else { b.chmin(l, r, -v); for (int k = l; k < r; k++) a[k] = max(a[k], v); }
      l = rnd(0, n - 1); r = rnd(l + 1, n);
      ll s = 0, m = LLONG_MIN, mn = LLONG_MAX; for (int k = l; k < r; k++) s += a[k], m = max(m, a[k]), mn = min(mn, a[k]);
      if (!neg) { CHECK(b.qsum(l, r) == s); CHECK(b.qmax(l, r) == m); }
      else { CHECK(b.qsum(l, r) == -s); CHECK(b.qmax(l, r) == -mn); }
      CHECK(b.qsum(l, l) == 0);
    }
  }
  puts("ok");
}
