#include "common.h"
const int MOD = 998244353;
#include "../src/4-string/prefcount.cpp"
#include "chk.h"
vi pf(const string& s) { int n = sz(s); vi p(n); for (int i = 1; i < n; i++) { int j = p[i-1]; while (j && s[i] != s[j]) j = p[j-1]; p[i] = j + (s[i] == s[j]); } return p; }
int main() {
  for (int k = 1; k <= 4; k++) for (int n = 1; n <= 9; n++) {
    if (pow(k, n) > 300000) continue;
    map<vi, ll> cnt; string s(n, 'a');
    for (ll x = 0; x < (ll)pow(k, n); x++) { ll y = x; for (int i = 0; i < n; i++) s[i] = 'a' + y % k, y /= k; cnt[pf(s)]++; }
    for (auto& [p, c] : cnt) CHECK(countByPrefix(p, k) == c % MOD);
    // valid p for larger alphabet, evaluated at k
    for (int K = k + 1; K <= 5 && pow(K, n) <= 300000; K++) {
      map<vi, ll> big; for (ll x = 0; x < (ll)pow(K, n); x++) { ll y = x; for (int i = 0; i < n; i++) s[i] = 'a' + y % K, y /= K; big[pf(s)]; }
      for (auto& [p, c] : big) { ll w = cnt.count(p) ? cnt[p] : 0; CHECK(countByPrefix(p, k) == w % MOD); (void)c; } }
  }
  // large k: modulo
  { vi p{0,0,0}; ll k = 1000000000000LL; ll e = k % MOD * ((k-1) % MOD) % MOD * ((k-1)%MOD) % MOD; CHECK(countByPrefix(p, k) == e); }
  DONE();
}
