#include "t_util.h"
const int MOD = 998244353;
#include "../src/1-math/modpow.cpp"
#include "../src/1-math/gauss.cpp"
int main() {
  for (int it = 0; it < 30000; it++) {
    int P = it % 3 == 0 ? MOD : 3; // MOD fixed; small values stress zero pivots
    int n = rnd(1, 5), m = rnd(1, 5);
    vector<vector<ll>> a(n, vector<ll>(m + 1));
    int mode = it % 4;
    ll hi = (it % 2) ? 2 : MOD - 1;
    for (auto& r : a) for (ll& x : r) x = rnd(0, hi);
    if (mode == 0) { // consistent: pick x, set b
      vector<ll> x0(m); for (ll& v : x0) v = rnd(0, MOD - 1);
      for (auto& r : a) { __int128 s = 0; for (int j = 0; j < m; j++) s += (__int128)r[j] * x0[j]; r[m] = (ll)(s % MOD); }
    }
    if (mode == 1 && n > 1) for (int j = 0; j <= m; j++) a[n-1][j] = a[0][j] * 2 % MOD; // dependent row
    if (mode == 2 && n > 1) { for (int j = 0; j < m; j++) a[n-1][j] = a[0][j]; a[n-1][m] = (a[0][m] + 1) % MOD; } // inconsistent
    (void)P;
    vector<ll> x;
    int rk = gauss(a, x);
    // reference: brute force over small search is impossible for MOD; use independent elimination (fraction-free via mint style)
    // independent rank / consistency via simple row reduction on copy
    auto b = a; int r = 0; vi piv;
    for (int c = 0; c <= m && r < n; c++) {
      int p = -1; for (int i = r; i < n; i++) if (b[i][c]) { p = i; break; }
      if (p < 0) continue;
      swap(b[p], b[r]); ll iv = power(b[r][c], MOD - 2, MOD);
      for (ll& v : b[r]) v = v * iv % MOD;
      for (int i = r + 1; i < n; i++) { ll f = b[i][c]; for (int j = 0; j <= m; j++) b[i][j] = ((b[i][j] - f * b[r][j]) % MOD + MOD) % MOD; }
      piv.push_back(c); r++;
    }
    bool incons = !piv.empty() && piv.back() == m;
    if (incons) CHECK(rk == -1);
    else {
      CHECK(rk == r); CHECK(sz(x) == m);
      for (auto& row : a) { __int128 s = 0; for (int j = 0; j < m; j++) s += (__int128)row[j] * x[j]; CHECK((ll)(s % MOD) == row[m]); }
      for (ll v : x) CHECK(v >= 0 && v < MOD);
    }
  }
  // explicit
  { vector<vector<ll>> a = {{1, 0, 5}, {0, 1, 7}}; vector<ll> x; CHECK(gauss(a, x) == 2 && x == (vector<ll>{5, 7})); }
  { vector<vector<ll>> a = {{0, 0, 1}}; vector<ll> x; CHECK(gauss(a, x) == -1); }
  { vector<vector<ll>> a = {{0, 0, 0}}; vector<ll> x; CHECK(gauss(a, x) == 0 && x == (vector<ll>{0, 0})); }
  { vector<vector<ll>> a = {{1, 1, 2}}; vector<ll> x; CHECK(gauss(a, x) == 1 && (x[0] + x[1]) % MOD == 2); }
  { vector<vector<ll>> a = {{2, 3}, {4, 7}}; vector<ll> x; CHECK(gauss(a, x) == -1); }
  { vector<vector<ll>> a = {{2, 1}, {4, 2}, {6, 3}}; vector<ll> x; CHECK(gauss(a, x) == 1 && x[0] * 2 % MOD == 1); }
  puts("ok");
}
