#include "t_util.h"
const int MOD = 998244353;
#include "../src/1-math/modpow.cpp"
#include "../src/1-math/det.cpp"
ll brute(const vector<vector<ll>>& a) {
  int n = sz(a); vi p(n); iota(all(p), 0); ll tot = 0;
  do { ll t = 1; for (int i = 0; i < n; i++) t = t * a[i][p[i]] % MOD;
    int inv = 0; for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) inv += p[i] > p[j];
    tot = (tot + (inv & 1 ? MOD - t : t)) % MOD;
  } while (next_permutation(all(p)));
  return tot % MOD; }
int main() {
  for (int it = 0; it < 40000; it++) {
    int n = rnd(1, 6); vector<vector<ll>> a(n, vector<ll>(n));
    int mode = it % 5;
    for (auto& r : a) for (ll& x : r) { int z = rnd(0, 9); x = mode == 0 ? rnd(0, MOD - 1) : (z < 6 ? 0 : (mode == 1 ? rnd(0, 2) : rnd(0, MOD - 1))); }
    if (mode == 3 && n > 1) { int i = rnd(0, n - 1), j = rnd(0, n - 1); if (i != j) for (int k = 0; k < n; k++) a[i][k] = a[j][k] * 5 % MOD; }
    if (mode == 4 && n > 1) { int i = rnd(0, n - 1); for (int k = 0; k < n; k++) a[i][k] = 0; }
    CHECK(det(a) == brute(a));
  }
  CHECK(det({{7}}) == 7); CHECK(det({{0}}) == 0); CHECK(det({{0, 1}, {1, 0}}) == MOD - 1);
  // Kirchhoff
  for (int it = 0; it < 3000; it++) {
    int n = rnd(1, 6); vector<pii> E;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) { int mult = rnd(0, 2); if (rnd(0, 3) == 0) mult = 0; for (int k = 0; k < mult; k++) E.push_back({i, j}); }
    if (sz(E) > 14) continue;
    ll cnt = 0;
    for (int mask = 0; mask < (1 << sz(E)); mask++) {
      if (__builtin_popcount(mask) != n - 1) continue;
      vi p(n); iota(all(p), 0); function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
      bool ok = true;
      for (int e = 0; e < sz(E); e++) if (mask >> e & 1) { int a = f(E[e].first), b = f(E[e].second); if (a == b) ok = false; else p[a] = b; }
      cnt += ok;
    }
    vector<vector<ll>> L(n, vector<ll>(n));
    for (auto [u, v] : E) { L[u][u]++; L[v][v]++; L[u][v] += MOD - 1; L[v][u] += MOD - 1; }
    for (auto& r : L) for (ll& x : r) x %= MOD;
    L.pop_back(); for (auto& r : L) r.pop_back();
    CHECK(det(L) == cnt % MOD);
  }
  // K_n: n^(n-2)
  for (int n = 2; n <= 8; n++) { vector<vector<ll>> L(n - 1, vector<ll>(n - 1, MOD - 1)); for (int i = 0; i < n - 1; i++) L[i][i] = n - 1; CHECK(det(L) == power(n, n - 2, MOD)); }
  puts("ok");
}
