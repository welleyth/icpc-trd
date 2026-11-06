#include "t_util.h"
#include "../src/2-ds/segtree.cpp"
int main() {
  for (int it = 0; it < 20000; it++) {
    int n = rnd(1, 20); Seg s(n); vector<ll> a(n, LLONG_MIN);
    for (int q = 0; q < 40; q++) {
      int i = rnd(0, n - 1); ll v = it % 2 ? rnd(-5, 5) : rnd(-4e18, 4e18);
      s.set(i, v); a[i] = v;
      int l = rnd(0, n), r = rnd(l, n); ll e = LLONG_MIN; for (int k = l; k < r; k++) e = max(e, a[k]);
      CHECK(s.query(l, r) == e);
    }
    for (int l = 0; l <= n; l++) for (int r = l; r <= n; r++) { ll e = LLONG_MIN; for (int k = l; k < r; k++) e = max(e, a[k]); CHECK(s.query(l, r) == e); }
  }
  { Seg s(0); CHECK(s.query(0, 0) == LLONG_MIN); }
  { Seg s(1); s.set(0, 3); CHECK(s.query(0, 1) == 3 && s.query(0, 0) == LLONG_MIN && s.query(1, 1) == LLONG_MIN); }
  puts("ok");
}
