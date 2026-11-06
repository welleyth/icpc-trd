#include "t_util.h"
#include "../src/2-ds/monostack.cpp"
int main() {
  for (int it = 0; it < 30000; it++) {
    int n = rnd(0, 15); vector<ll> a(n); ll hi = it % 3 == 0 ? 1 : (it % 3 == 1 ? 4 : 1e18); for (ll& x : a) x = rnd(-hi, hi);
    vi L, R; nearestSmaller(a, L, R); CHECK(sz(L) == n && sz(R) == n);
    ll tot = 0, sub = 0;
    for (int i = 0; i < n; i++) {
      int l = -1; for (int j = i - 1; j >= 0; j--) if (a[j] < a[i]) { l = j; break; }
      int r = n; for (int j = i + 1; j < n; j++) if (a[j] <= a[i]) { r = j; break; }
      CHECK(L[i] == l && R[i] == r);
      if (hi < 100) tot += a[i] * (i - L[i]) * (R[i] - i);
    }
    if (hi < 100) { for (int l = 0; l < n; l++) { ll m = LLONG_MAX; for (int r = l; r < n; r++) { m = min(m, a[r]); sub += m; } } CHECK(sub == tot); }
  }
  puts("ok");
}
