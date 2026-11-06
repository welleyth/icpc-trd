#include "t_util.h"
#include "../src/1-math/mint.cpp"
#include "../src/1-math/binom.cpp"
#include "../src/1-math/lagrange.cpp"
mint ev(const vector<mint>& c, ll x) { mint r = 0, X = x; for (int i = sz(c) - 1; i >= 0; i--) r = r * X + c[i]; return r; }
int main() {
  initFact();
  for (int it = 0; it < 3000; it++) {
    int n = rnd(1, 12);
    vector<mint> c(n); for (auto& v : c) v = rnd(0, MOD - 1);
    vector<mint> y(n); for (int i = 0; i < n; i++) y[i] = ev(c, i);
    vector<ll> xs = {0, 1, n - 1, n, n + 1, 1000000000000000000LL, rnd(0, 1000000000000000000LL), rnd(0, 20), MOD, MOD + 1, MOD + n, 2LL * MOD, (ll)MOD * 1000 + 3, MOD - 1, MOD - n, (ll)MOD * MOD, (ll)MOD * 7 + n - 1};
    for (ll x : xs) CHECK(lagrange(y, x) == ev(c, x));
  }
  { // n = 1 constant
    vector<mint> y = {42}; CHECK(lagrange(y, 1000000000000LL) == mint(42)); }
  // power sums
  for (int k = 0; k <= 12; k++) {
    vector<mint> y(k + 2); y[0] = 0; for (int i = 1; i < k + 2; i++) y[i] = y[i - 1] + mint(i).pow(k);
    for (ll m : {0LL, 1LL, 5LL, 100LL, 1000000LL, 1000000000000000000LL}) {
      if (m <= 200000) { mint s = 0; for (ll i = 1; i <= m; i++) s += mint(i).pow(k); CHECK(lagrange(y, m) == s); }
      else { // check periodic-in-poly: compare against second evaluation via more points
        vector<mint> y2(k + 5); y2[0] = 0; for (int i = 1; i < k + 5; i++) y2[i] = y2[i - 1] + mint(i).pow(k);
        CHECK(lagrange(y, m) == lagrange(y2, m)); }
    }
  }
  puts("ok");
}
