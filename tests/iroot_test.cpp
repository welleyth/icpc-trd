#include "t_util.h"
#include "../src/1-math/iroot.cpp"
ll brute(ll x, int k) {
  ll lo = 0, hi = min<ll>(x, 4000000000LL) + 1; // lo^k<=x<hi^k
  auto pw = [&](ll r) { __int128 p = 1; for (int i = 0; i < k; i++) { p *= r; if (p > x) return false; } return true; };
  if (k == 1) return x;
  while (hi - lo > 1) { ll m = (lo + hi) / 2; if (pw(m)) lo = m; else hi = m; }
  return lo; }
int main() {
  const ll MX = LLONG_MAX;
  for (int k = 1; k <= 63; k++) {
    vector<ll> xs = {0, 1, 2, 3, MX, MX - 1, MX / 2};
    for (ll p = 1; p < 100000; p++) {
      __int128 q = 1; bool ok = true;
      for (int i = 0; i < k && ok; i++) { q *= p; if (q > MX) ok = false; }
      if (!ok) break;
      xs.push_back((ll)q); xs.push_back((ll)q - 1); if (q < MX) xs.push_back((ll)q + 1);
    }
    for (ll p : {1LL<<20, 3037000499LL, 3037000500LL, 2097151LL, 2097152LL, 1000000007LL, 3999999999LL}) {
      __int128 q = 1; bool ok = true;
      for (int i = 0; i < k && ok; i++) { q *= p; if (q > MX) ok = false; }
      if (ok) { xs.push_back((ll)q); xs.push_back((ll)q - 1); if (q < MX) xs.push_back((ll)q + 1); } }
    for (int i = 0; i < 300; i++) xs.push_back(rnd(0, MX - 1));
    for (int i = 0; i < 100; i++) xs.push_back(rnd(0, 1LL << rnd(1, 62)));
    for (ll x : xs) { if (x < 0) continue; CHECK(iroot(x, k) == brute(x, k)); }
  }
  for (ll b = 2; b < 70; b++) for (int it = 0; it < 300; it++) {
    ll x = it < 100 ? rnd(1, MX - 1) : rnd(1, 1LL << rnd(1, 62));
    int r = 0; __int128 p = 1; while (p * b <= x) p *= b, r++;
    CHECK(ilog(x, b) == r); }
  for (ll b : {MX, MX - 1, 1LL << 62, 3037000500LL, 2LL}) { CHECK(ilog(1, b) == 0); CHECK(ilog(MX, b) >= 0); }
  CHECK(ilog(MX, MX) == 1); CHECK(ilog(MX, 2) == 62); CHECK(ilog(MX-1, MX) == 0);
  puts("ok");
}
