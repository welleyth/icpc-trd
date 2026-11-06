#include "t_util.h"
const int MOD = 998244353;
#include "../src/1-math/modpow.cpp"
int main() {
  // power
  for (int it = 0; it < 100000; it++) {
    ll m = rnd(2, it % 2 ? 50 : 3000000000LL), b = rnd(-3e9, 3e9), e = rnd(0, 40);
    ll r = 1 % m; ll bb = ((b % m) + m) % m;
    for (int i = 0; i < e; i++) r = (__int128)r * bb % m;
    CHECK(power(b, e, m) == r);
  }
  CHECK(power(5, 0, 7) == 1); CHECK(power(0, 0, 7) == 1); CHECK(power(0, 5, 7) == 0);
  CHECK(power(3, 1LL << 60, 3000000000LL) == power(3, (1LL << 60), 3000000000LL));
  CHECK(power(2999999999LL, 3, 3000000000LL) == (ll)((__int128)(-1) * -1 * -1 % 3000000000LL + 3000000000LL) % 3000000000LL);
  // egcd
  for (int it = 0; it < 200000; it++) {
    ll a = rnd(0, it % 2 ? 30 : 1e18), b = rnd(0, it % 2 ? 30 : 1e18);
    if (!a && !b) continue;
    ll x, y, g = egcd(a, b, x, y);
    CHECK(g == std::gcd(a, b));
    CHECK((__int128)a * x + (__int128)b * y == g);
  }
  // inverse
  for (int it = 0; it < 200000; it++) {
    ll m = rnd(1, it % 2 ? 40 : 3000000000LL), a = rnd(-1e12, 1e12);
    if (std::gcd(((a % m) + m) % m, m) != 1 && m != 1) continue;
    ll i = inverse(a, m);
    CHECK(i >= 0 && i < m);
    CHECK((__int128)(((a % m) + m) % m) * i % m == 1 % m);
  }
  // crt small vs brute
  for (int m = 1; m <= 24; m++) for (int n = 1; n <= 24; n++)
    for (int a = 0; a < m; a++) for (int b = 0; b < n; b++) {
      ll l = (ll)m / std::gcd(m, n) * n, ans = -1;
      for (ll x = 0; x < l; x++) if (x % m == a && x % n == b) { ans = x; break; }
      auto [r, ll_] = crt(a, m, b, n);
      if (ans < 0) CHECK(r == -1 && ll_ == -1);
      else { CHECK(r == ans && ll_ == l); }
    }
  // crt large
  for (int it = 0; it < 300000; it++) {
    ll m = rnd(1, it % 3 ? 1000000000LL : 4000000000LL), n = rnd(1, it % 3 ? 1000000000LL : 4000000000LL);
    if (it % 5 == 0) { ll g = rnd(1, 1000); m = rnd(1, 1000000) * g; n = rnd(1, 1000000) * g; }
    ll g = std::gcd(m, n); __int128 l = (__int128)m / g * n;
    if (l > (__int128)4e18) continue;
    ll x = (ll)(trg() % (unsigned long long)l);
    auto [r, L2] = crt(x % m, m, x % n, n);
    CHECK(r == x && L2 == (ll)l);
    ll a = rnd(0, m - 1), b = rnd(0, n - 1);
    auto [r2, L3] = crt(a, m, b, n);
    if ((a - b) % g) CHECK(r2 == -1 && L3 == -1);
    else CHECK(r2 >= 0 && r2 < (ll)l && r2 % m == a && r2 % n == b && L3 == (ll)l);
  }
  puts("ok");
}
