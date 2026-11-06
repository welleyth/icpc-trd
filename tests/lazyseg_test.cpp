#include "t_util.h"
#include "../src/2-ds/lazyseg.cpp"
int main() {
  for (int it = 0; it < 20000; it++) {
    int n = rnd(1, 20); Lazy z(n); vector<ll> a(n);
    ll mx = it % 5 == 0 ? 1e12 : 20;
    for (int q = 0; q < 40; q++) {
      int l = rnd(0, n), r = rnd(l, n);
      if (rnd(0, 1)) { ll v = rnd(-mx, mx); z.add(l, r, v); for (int k = l; k < r; k++) a[k] += v; }
      l = rnd(0, n - 1); r = rnd(l + 1, n);
      ll mn = LLONG_MAX, sm = 0; for (int k = l; k < r; k++) mn = min(mn, a[k]), sm += a[k];
      CHECK(z.qmin(l, r) == mn); CHECK(z.qsum(l, r) == sm);
      CHECK(z.qmin(l, l) == LLONG_MAX); CHECK(z.qsum(l, l) == 0);
    }
    for (int l = 0; l < n; l++) for (int r = l + 1; r <= n; r++) { ll mn = LLONG_MAX, sm = 0; for (int k = l; k < r; k++) mn = min(mn, a[k]), sm += a[k]; CHECK(z.qmin(l, r) == mn && z.qsum(l, r) == sm); }
  }
  { Lazy z(1); z.add(0, 1, 5); z.add(0, 1, -2); CHECK(z.qmin(0, 1) == 3 && z.qsum(0, 1) == 3); }
  { int n = 100000; Lazy z(n); vector<ll> a(n); for (int q = 0; q < 20000; q++) { int l = rnd(0, n - 1), r = rnd(l + 1, n); ll v = rnd(-9, 9); z.add(l, r, v); for (int k = l; k < r; k += 1) a[k] += v; if (q % 2000 == 0) { l = rnd(0, n - 1); r = rnd(l + 1, n); ll mn = LLONG_MAX, sm = 0; for (int k = l; k < r; k++) mn = min(mn, a[k]), sm += a[k]; CHECK(z.qmin(l, r) == mn && z.qsum(l, r) == sm); } } }
  puts("ok");
}
