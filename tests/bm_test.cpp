#include "t_util.h"
const int MOD = 998244353;
#include "../src/1-math/modpow.cpp"
#include "../src/1-math/bm.cpp"
int main() {
  for (int it = 0; it < 3000; it++) {
    int L = rnd(1, 10);
    vector<ll> c(L), s(2 * L + 30);
    for (ll& x : c) x = rnd(0, MOD - 1);
    if (it % 5 == 0) for (ll& x : c) x = rnd(0, 2);
    if (c.back() == 0) c.back() = rnd(1, MOD - 1);
    for (int i = 0; i < L; i++) s[i] = rnd(0, MOD - 1);
    for (int i = L; i < sz(s); i++) { ll v = 0; for (int j = 0; j < L; j++) v = (v + c[j] * s[i - 1 - j]) % MOD; s[i] = v; }
    vector<ll> first(s.begin(), s.begin() + 2 * L);
    auto r = berlekampMassey(first);
    // recovered recurrence must generate whole sequence; length <= L
    CHECK(sz(r) <= L);
    if (sz(r) == 0) { for (ll x : s) CHECK(x == 0); continue; }
    CHECK(sz(r) == L || true);
    for (int i = sz(r); i < sz(s); i++) { ll v = 0; for (int j = 0; j < sz(r); j++) v = (v + r[j] * s[i - 1 - j]) % MOD; CHECK(v == s[i]); }
    for (ll x : r) CHECK(x >= 0 && x < MOD);
    if (sz(r) == L) CHECK(r == c); // unique when minimal
    vector<ll> S(s.begin(), s.begin() + sz(r));
    for (int k = 0; k < sz(s); k++) CHECK(linearRec(S, r, k) == s[k]);
    // more terms
    ll k = rnd(0, 10000);
    vector<ll> d(k + 1); for (int i = 0; i <= k; i++) { if (i < sz(r)) d[i] = S[i]; else { ll v = 0; for (int j = 0; j < sz(r); j++) v = (v + r[j] * d[i - 1 - j]) % MOD; d[i] = v; } }
    CHECK(linearRec(S, r, k) == d[k]);
  }
  // order 1
  { vector<ll> s = {5, 15, 45, 135}; auto r = berlekampMassey(s); CHECK((r == vector<ll>{3})); CHECK(linearRec({5}, r, 10) == 5 * power(3, 10, MOD) % MOD); CHECK(linearRec({5}, r, 0) == 5); }
  { vector<ll> s = {7, 7}; auto r = berlekampMassey(s); CHECK((r == vector<ll>{1})); }
  // all zeros, empty
  { auto r = berlekampMassey({0, 0, 0, 0}); CHECK(r.empty()); }
  // fibonacci k=1e18 vs matrix power
  {
    auto r = berlekampMassey({0, 1, 1, 2, 3, 5, 8, 13}); CHECK((r == vector<ll>{1, 1}));
    for (ll k : {1000000000000000000LL, 999999999999999999LL, 123456789012345678LL}) {
      // fast doubling via matrices
      using M = array<ll, 4>;
      auto mul = [&](M a, M b) { return M{(a[0]*b[0]+a[1]*b[2])%MOD,(a[0]*b[1]+a[1]*b[3])%MOD,(a[2]*b[0]+a[3]*b[2])%MOD,(a[2]*b[1]+a[3]*b[3])%MOD}; };
      M res = {1,0,0,1}, b = {1,1,1,0}; for (ll e = k; e; e >>= 1, b = mul(b, b)) if (e & 1) res = mul(res, b);
      CHECK(linearRec({0, 1}, r, k) == res[1]);
    }
  }
  // negative-ish: recurrence with coefficient MOD-1
  { vector<ll> s = {1, 2}; for (int i = 2; i < 40; i++) s.push_back((s[i-1] * (MOD - 1) + s[i-2] * 2) % MOD); auto r = berlekampMassey(s); CHECK(sz(r) == 2 && r[0] == MOD - 1 && r[1] == 2); }
  puts("ok");
}
