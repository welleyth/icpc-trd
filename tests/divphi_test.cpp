#include "t_util.h"
#include "../src/1-math/sieve.cpp"
int main() {
  for (int it = 0; it < 3000; it++) {
    ll x = it < 2000 ? it + 1 : rnd(1, 1000000000000LL);
    if (it % 7 == 0) x = 1LL << rnd(0, 40);
    auto f = factorSlow(x);
    auto d = divPhi(f);
    set<ll> seen;
    for (auto [v, ph] : d) {
      CHECK(x % v == 0); CHECK(seen.insert(v).second);
      ll c = 0; if (v <= 2000000) { for (ll i = 1; i <= v; i++) if (__gcd(i, v) == 1) c++; CHECK(c == ph); }
      else { ll pp = v, r = v; for (auto [p, e] : factorSlow(v)) r = r / p * (p - 1); (void)pp; CHECK(r == ph); } }
    int cnt = 0; for (ll i = 1; i * i <= x; i++) if (x % i == 0) cnt += (i * i == x) ? 1 : 2;
    CHECK((int)d.size() == cnt);
    ll s = 0; for (auto [v, ph] : d) s += ph; CHECK(s == x);
  }
  // gcd-sum identity
  for (int it = 0; it < 2000; it++) {
    int n = rnd(1, 30); ll M = it % 2 ? 60 : 1000000;
    vector<ll> a(n); for (ll& v : a) v = rnd(1, M);
    ll x = rnd(1, M);
    ll br = 0; for (ll v : a) br += __gcd(x, v);
    ll s = 0;
    for (auto [d, ph] : divPhi(factorSlow(x))) { ll c = 0; for (ll v : a) c += v % d == 0; s += ph * c; }
    CHECK(s == br);
  }
  CHECK(divPhi({}).size() == 1 && divPhi({}) [0] == make_pair(1LL, 1LL));
  puts("ok");
}
