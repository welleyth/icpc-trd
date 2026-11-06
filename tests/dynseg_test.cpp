#include "t_util.h"
#include "../src/2-ds/dynseg.cpp"
int main() {
  for (int it = 0; it < 6000; it++) {
    ll N = it % 5 == 0 ? 1 : it % 5 == 1 ? (1LL << 62) : it % 5 == 2 ? 2 : it % 5 == 3 ? rnd(1, 40) : rnd(1, 1LL << 40);
    bool nonneg = it % 2; DynSeg d(N); map<ll, ll> m;
    auto pick = [&]() { int t = rnd(0, 3); return t == 0 ? N - 1 : t == 1 ? max(0LL, N - 1 - (ll)rnd(0, 3)) : t == 2 ? rnd(0, N - 1) : (m.empty() ? 0 : next(m.begin(), rnd(0, sz(m) - 1))->first); };
    for (int q = 0; q < 40; q++) {
      ll i = pick(); ll v = nonneg ? rnd(0, 10) : rnd(-1000000000000LL, 1000000000000LL);
      if (it % 7 == 0) v = nonneg ? rnd(0, 1LL << 40) : v;
      d.add(i, v); m[i] += v;
      ll l = rnd(0, 1) ? pick() : rnd(0, N), r = rnd(0, 1) ? pick() + 1 : rnd(0, N); if (rnd(0, 5) == 0) l = 0, r = N; if (l > r) swap(l, r);
      ll s = 0; for (auto [k, x] : m) if (k >= l && k < r) s += x;
      CHECK(d.sum(l, r) == s); CHECK(d.sum(0, N) == [&]{ ll t = 0; for (auto [k, x] : m) t += x; return t; }());
      if (nonneg) {
        ll tot = d.sum(0, N); ll t = rnd(0, 1) ? rnd(1, tot + 2) : (rnd(0, 1) ? tot : 1);
        ll acc = 0, br = N; for (auto [k, x] : m) { acc += x; if (acc >= t) { br = k; break; } }
        if (t <= 0) continue;
        CHECK(d.lowerBound(t) == br);
      }
    }
  }
  puts("ok");
}
