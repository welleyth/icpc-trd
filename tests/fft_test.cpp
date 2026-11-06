#include "t_util.h"
#include "../src/1-math/fft.cpp"
vector<ll> naive(const vector<ll>& a, const vector<ll>& b) {
  if (a.empty() || b.empty()) return {};
  vector<ll> r(sz(a) + sz(b) - 1);
  for (int i = 0; i < sz(a); i++) for (int j = 0; j < sz(b); j++) r[i + j] += a[i] * b[j];
  return r; }
int main() {
  for (int it = 0; it < 4000; it++) {
    int n = rnd(1, it % 10 == 0 ? 130 : 20), m = rnd(1, it % 10 == 0 ? 130 : 20);
    if (it % 11 == 0) n = 1 << rnd(0, 7), m = 1 << rnd(0, 7);
    ll hi = it % 3 == 0 ? 100000 : 10;
    vector<ll> a(n), b(m); for (ll& x : a) x = rnd(0, hi); for (ll& x : b) x = rnd(0, hi);
    CHECK(convExact(a, b) == naive(a, b));
  }
  CHECK(convExact({}, {1}).empty()); CHECK(convExact({1}, {}).empty());
  CHECK(convExact({5}, {7}) == (vector<ll>{35}));
  CHECK(convExact({0}, {0}) == (vector<ll>{0}));
  // documented bound: n = 2e5, values <= 1e5
  { int n = 100000; vector<ll> a(n, 100000), b(n, 100000); auto r = convExact(a, b);
    CHECK(r[n - 1] == (ll)n * 100000 * 100000); CHECK(r[0] == 1e10); CHECK(r[2 * n - 2] == 1e10); }
  { int n = 1 << 17; vector<ll> a(n), b(n); for (ll& x : a) x = rnd(0, 100000); for (ll& x : b) x = rnd(0, 100000);
    auto r = convExact(a, b);
    for (int t = 0; t < 2000; t++) { int k = rnd(0, 2 * n - 2); ll s = 0; for (int i = max(0, k - n + 1); i <= min(k, n - 1); i++) s += a[i] * b[k - i]; CHECK(r[k] == s); } }
  // negative values (not promised, informational)
  puts("ok");
}
