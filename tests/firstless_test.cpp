#include "t_util.h"
#include "../src/2-ds/lazyseg.cpp"
#include "lazy_shim.h"
int main() {
  for (int it = 0; it < 20000; it++) {
    int n = rnd(1, 25); Lazy z(n); vector<ll> a(n);
    ll mx = it % 3 == 0 ? 1000000000000LL : 6;
    for (int q = 0; q < 30; q++) {
      int l = rnd(0, n), r = rnd(l, n); ll v = rnd(-mx, mx); z.add(l, r, v); for (int k = l; k < r; k++) a[k] += v;
      for (int t = 0; t < 4; t++) {
        int ql = rnd(0, n); ll val = rnd(-mx * 2, mx * 2); if (t == 0) val = a[rnd(0, n-1)]; if (t == 1) val = LLONG_MIN;
        int br = n; for (int k = ql; k < n; k++) if (a[k] < val) { br = k; break; }
        CHECK(z.firstLess(ql, val) == br);
        if (t == 2) CHECK(z.firstLess(ql, LLONG_MAX) == (ql < n ? ql : n)); }
    }
  }
  puts("ok");
}
