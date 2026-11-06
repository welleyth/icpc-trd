#include "t_util.h"
#include "../src/1-math/modpow.cpp"
#include "../src/1-math/dlog.cpp"
ll fs(ll n, ll m, ll a, ll b) { ll s = 0; for (ll i = 0; i < n; i++) s += (a * i + b) / m; return s; }
int main() {
  for (ll m = 1; m <= 200; m++) for (ll a = 0; a <= m + 3; a++) {
    if (__gcd(a, m) != 1 && !(m == 1)) continue;
    for (ll b = 0; b <= m + 2; b++) {
      ll want = -1, cur = 1 % m;
      for (ll x = 0; x <= m + 1; x++) { if (cur == b % m) { want = x; break; } cur = cur * (a % m) % m; }
      ll got = dlog(a, b, m);
      if (got != want) { fprintf(stderr, "dlog(%lld,%lld,%lld) got %lld want %lld\n", a, b, m, got, want); exit(1); }
    }
  }
  // larger prime modulus
  for (int it = 0; it < 300; it++) {
    ll m = rnd(2, 1000000000), a = rnd(1, m - 1); if (__gcd(a, m) != 1) continue;
    ll x = rnd(0, 100000); ll b = power(a, x, m);
    ll got = dlog(a, b, m); CHECK(got >= 0 && got <= x && power(a, got, m) == b);
  }
  {ll m = 998244353; ll got = dlog(3, power(3, 123456789, m), m); CHECK(got == 123456789);}
  // floorSum
  for (int it = 0; it < 200000; it++) { ll n = rnd(1, 30), m = rnd(1, 30), a = rnd(0, 60), b = rnd(0, 60); CHECK(floorSum(n, m, a, b) == fs(n, m, a, b)); }
  for (int it = 0; it < 2000; it++) { ll n = rnd(1, 3000), m = rnd(1, 3000), a = rnd(0, 1e6), b = rnd(0, 1e6); CHECK(floorSum(n, m, a, b) == fs(n, m, a, b)); }
  // overflow check with __int128 reference (Euclid-like recursion in 128)
  auto ref = [&](ll n, ll m, ll a, ll b) { // exact via int128 same algorithm
    __int128 ans = 0, N = n, M = m, A = a, B = b;
    while (true) { if (A >= M) ans += N * (N - 1) / 2 * (A / M), A %= M; if (B >= M) ans += N * (B / M), B %= M;
      __int128 y = A * N + B; if (y < M) break; N = y / M; B = y % M; swap(M, A); }
    return ans; };
  for (int it = 0; it < 200000; it++) {
    ll n = it % 3 ? rnd(1, 1000000000) : 1000000000, m = it % 5 ? rnd(1, 1000000000) : 1000000000, a = rnd(0, m - 1), b = rnd(0, m - 1);
    if (it % 7 == 0) a = m - 1; if (it % 11 == 0) b = m - 1;
    __int128 r = ref(n, m, a, b); CHECK(r <= (__int128)LLONG_MAX); CHECK((__int128)floorSum(n, m, a, b) == r);
  }
  // sanity of the int128 reference vs brute formula at moderate sizes done above; extremes:
  CHECK(floorSum(1000000000, 1000000000, 999999999, 999999999) == (ll)ref(1000000000, 1000000000, 999999999, 999999999));
  puts("ok");
}
