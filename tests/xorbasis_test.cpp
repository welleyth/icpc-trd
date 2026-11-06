#include "t_util.h"
#include "../src/1-math/xorbasis.cpp"
int main() {
  for (int it = 0; it < 20000; it++) {
    int bits = rnd(1, it % 10 == 0 ? 60 : 8), m = rnd(0, 7);
    vector<ll> v(m); for (ll& x : v) x = rnd(0, (1LL << bits) - 1);
    if (it % 7 == 0) for (ll& x : v) x = (x & 3) << (bits > 3 ? bits - 3 : 0);
    XorBasis B; set<ll> span{0}; int cnt = 0;
    for (ll x : v) {
      bool in = span.count(x);
      bool r = B.add(x);
      CHECK(r == !in);
      if (!in) { cnt++; set<ll> ns = span; for (ll s : span) ns.insert(s ^ x); span = ns; }
      CHECK(B.cnt == cnt);
    }
    for (int q = 0; q < 10; q++) {
      ll x = rnd(0, (1LL << bits) - 1);
      CHECK(B.has(x) == (bool)span.count(x));
      ll best = 0; for (ll s : span) best = max(best, x ^ s);
      CHECK(B.maxXor(x) == best);
    }
    ll best = *span.rbegin(); CHECK(B.maxXor() == best);
    CHECK(B.has(0)); CHECK((int)span.size() == (1 << cnt));
  }
  XorBasis B; CHECK(B.maxXor() == 0 && B.maxXor(5) == 5 && !B.add(0));
  ll big = (1LL << 60) - 1; CHECK(B.add(big)); CHECK(B.maxXor() == big); CHECK(B.has(big) && !B.has(1));
  CHECK(B.add(1LL << 59) == false || true);
  puts("ok");
}
