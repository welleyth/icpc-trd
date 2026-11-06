#include "t_util.h"
#include "../src/6-misc/search.cpp"
int main() {
  for (int it = 0; it < 100000; it++) {
    ll lo = rnd(-20, 20), hi = rnd(lo, lo + 20), t = rnd(lo - 3, hi + 3);
    ll e = hi + 1; for (ll x = lo; x <= hi; x++) if (x >= t) { e = x; break; }
    int calls = 0; ll r = firstTrue(lo, hi, [&](ll x) { calls++; CHECK(x >= lo && x <= hi); return x >= t; });
    CHECK(r == e);
  }
  CHECK(firstTrue(5, 5, [](ll) { return true; }) == 5); CHECK(firstTrue(5, 5, [](ll) { return false; }) == 6);
  CHECK(firstTrue(-4000000000000000000LL, 4000000000000000000LL, [](ll x) { return x >= 3000000000000000000LL; }) == 3000000000000000000LL);
  CHECK(firstTrue(-4000000000000000000LL, 4000000000000000000LL, [](ll x) { return x >= -4000000000000000000LL; }) == -4000000000000000000LL);
  CHECK(firstTrue(-4000000000000000000LL, 4000000000000000000LL, [](ll) { return false; }) == 4000000000000000001LL);
  CHECK(firstTrue(0, 1000000000000000000LL, [](ll x) { return x * 2 >= 1000000000000000001LL; }) == 500000000000000001LL);
  CHECK(firstTrue(-7, -1, [](ll x) { return x >= -3; }) == -3);
  // ternary snippet (from comment) on strictly unimodal integer functions
  for (int it = 0; it < 50000; it++) {
    ll lo = rnd(-30, 30), hi = rnd(lo, lo + 30), pk = rnd(lo, hi);
    ll h = rnd(-5, 5), s1 = rnd(1, 4), s2 = rnd(1, 4);
    auto f = [&](ll x) { return x <= pk ? h - (pk - x) * s1 : h - (x - pk) * s2; };
    if (it % 2) { auto g = f; (void)g; }
    ll L = lo, H = hi;
    while (H - L > 2) { ll m1 = L + (H - L) / 3, m2 = H - (H - L) / 3; f(m1) < f(m2) ? L = m1 : H = m2; }
    ll best = LLONG_MIN; for (ll x = L; x <= H; x++) best = max(best, f(x));
    CHECK(best == h);
  }
  puts("ok");
}
