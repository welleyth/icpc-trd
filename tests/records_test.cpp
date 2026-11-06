#include "t_util.h"
#include "../src/2-ds/records.cpp"
int main() {
  for (int it = 0; it < 30000; it++) {
    int n = it % 10 == 0 ? 1 : rnd(1, 25); ll V = it % 2 ? 4 : 1000000000000LL;
    Records R(n); vector<ll> a(n, LLONG_MIN);
    for (int i = 0; i < n; i++) { ll v = rnd(-V, V); R.set(i, v); a[i] = v; }
    for (int q = 0; q < 50; q++) {
      if (rnd(0, 1)) { int i = rnd(0, n - 1); ll v = rnd(-V, V); R.set(i, v); a[i] = v; }
      int l = rnd(0, n), r = rnd(l, n); int c = 0; ll m = LLONG_MIN;
      for (int k = l; k < r; k++) if (a[k] > m) c++, m = a[k];
      CHECK(R.query(l, r) == c);
    }
  }
  puts("ok");
}
