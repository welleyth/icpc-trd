#include "t_util.h"
const int MOD = 998244353;
#include "../src/1-math/modpow.cpp"
#include "../src/1-math/ntt.cpp"
vi naive(const vi& a, const vi& b) {
  if (a.empty() || b.empty()) return {};
  vi r(sz(a) + sz(b) - 1);
  for (int i = 0; i < sz(a); i++) for (int j = 0; j < sz(b); j++) r[i + j] = (r[i + j] + (ll)a[i] * b[j]) % MOD;
  return r; }
int main() {
  for (int it = 0; it < 4000; it++) {
    int n = rnd(1, it % 10 == 0 ? 130 : 20), m = rnd(1, it % 10 == 0 ? 130 : 20);
    if (it % 11 == 0) n = 1 << rnd(0, 7), m = 1 << rnd(0, 7);
    vi a(n), b(m); for (int& x : a) x = rnd(0, MOD - 1); for (int& x : b) x = rnd(0, MOD - 1);
    if (it % 13 == 0) for (int& x : a) x = MOD - 1;
    CHECK(conv(a, b) == naive(a, b));
  }
  CHECK(conv({}, {1}).empty()); CHECK(conv({1}, {}).empty());
  CHECK(conv({5}, {7}) == (vi{35}));
  { vi a(1 << 12), b(1 << 12); for (int& x : a) x = rnd(0, MOD - 1); for (int& x : b) x = rnd(0, MOD - 1);
    CHECK(conv(a, b) == naive(a, b)); }
  // roundtrip
  for (int k = 0; k <= 10; k++) { vi a(1 << k); for (int& x : a) x = rnd(0, MOD - 1); auto b = a; ntt(b, false); ntt(b, true); CHECK(a == b); }
  puts("ok");
}
