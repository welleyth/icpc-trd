#include "t_util.h"
#include "../src/1-math/modpow.cpp"
typedef array<array<ll,2>,2> M2;
M2 mul(const M2& a, const M2& b, ll m) { M2 c{}; for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) for (int k = 0; k < 2; k++) c[i][j] = (c[i][j] + (__int128)a[i][k] * b[k][j]) % m; return c; }
ll geoM(ll r, ll k, ll m) { // state (s, p): s' = s*r+1?  use [[r,1],[0,1]]^k applied to (0,1) -> sum
  M2 R{{{r % m, 1 % m}, {0, 1 % m}}}, I{{{1 % m, 0}, {0, 1 % m}}};
  for (; k; k >>= 1, R = mul(R, R, m)) if (k & 1) I = mul(I, R, m);
  return I[0][1] % m; }
int main() {
  for (ll m = 1; m <= 50; m++) for (ll r = 0; r < 3 * m + 3; r++) {
    ll s = 0;
    for (ll k = 0; k <= 70; k++) { CHECK(geo(r, k, m) == s); s = (s + power(r, k, m)) % m; }
  }
  for (int it = 0; it < 200000; it++) {
    ll m = it % 3 == 0 ? rnd(1, 3000000000LL) : it % 3 == 1 ? 3000000000LL - rnd(0, 5) : rnd(1, 1000);
    ll r = it % 5 == 0 ? 0 : it % 5 == 1 ? m * rnd(0, 3) : rnd(0, 4000000000LL);
    ll k = it % 4 == 0 ? rnd(0, 1000000000000000000LL) : it % 4 == 1 ? (1LL << rnd(0, 59)) - rnd(0, 1) : rnd(0, 100);
    CHECK(geo(r, k, m) == geoM(r, k, m));
  }
  puts("ok");
}
