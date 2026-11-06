#include "t_util.h"
#include "../src/6-misc/dp.cpp"
vector<ll> S;
ll cost(int j, int i) { return (S[i] - S[j]) * (S[i] - S[j]); }
int main() {
  for (int it = 0; it < 30000; it++) {
    int n = rnd(0, 12); vi a(n); int hi = it % 3 == 0 ? 2 : 1000000000; for (int& x : a) x = rnd(-hi, hi);
    // strict LIS O(n^2)
    vi dp(n, 1); int e = 0; for (int i = 0; i < n; i++) { for (int j = 0; j < i; j++) if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1); e = max(e, dp[i]); }
    CHECK(lis(a) == e);
  }
  CHECK(lis({}) == 0); CHECK(lis({5, 5, 5}) == 1); CHECK(lis({INT_MIN, INT_MAX}) == 2); CHECK(lis({3, 2, 1}) == 1);
  for (int it = 0; it < 30000; it++) {
    int n = rnd(1, 15); S.assign(n + 1, 0); int mx = it % 2 ? 2 : 20;
    for (int i = 1; i <= n; i++) S[i] = S[i - 1] + rnd(0, mx);
    dpOld.assign(n, 0); for (ll& x : dpOld) x = rnd(0, it % 3 ? 5 : 1000);
    dpNew.assign(n + 1, -1);
    solve(1, n, 0, n - 1);
    for (int i = 1; i <= n; i++) { ll b = LLONG_MAX; for (int j = 0; j < i; j++) b = min(b, dpOld[j] + cost(j, i)); CHECK(dpNew[i] == b); }
  }
  // layered use: k-partition into segments with squared sums
  for (int it = 0; it < 3000; it++) {
    int n = rnd(1, 12), k = rnd(1, n); S.assign(n + 1, 0); for (int i = 1; i <= n; i++) S[i] = S[i - 1] + rnd(0, 6);
    const ll INF = 1e15; vector<vector<ll>> f(k + 1, vector<ll>(n + 1, INF)); f[0][0] = 0;
    for (int t = 1; t <= k; t++) for (int i = 1; i <= n; i++) for (int j = 0; j < i; j++) f[t][i] = min(f[t][i], f[t - 1][j] + cost(j, i));
    vector<ll> cur(n + 1, INF); cur[0] = 0;
    for (int t = 1; t <= k; t++) { dpOld.assign(cur.begin(), cur.begin() + n); dpNew.assign(n + 1, INF); solve(1, n, 0, n - 1); cur = dpNew; cur[0] = INF; }
    CHECK(cur[n] == f[k][n]);
  }
  puts("ok");
}
