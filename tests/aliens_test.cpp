#include "t_util.h"
#include "../src/6-misc/aliens.cpp"
vector<ll> A; int cntCalls = 0;
ll CMODE = 0; // 0: squares; c>0: constant cost c per group (f linear)
pair<ll, int> solveLam(ll lam) {
  int n = sz(A); vector<ll> pre(n + 1); for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + A[i];
  vector<pair<ll, int>> dp(n + 1, {LLONG_MAX, 0}); dp[0] = {0, 0};
  for (int i = 1; i <= n; i++) for (int j = 0; j < i; j++) {
    ll s = pre[i] - pre[j]; pair<ll, int> c = {dp[j].first + (CMODE ? CMODE : s * s) + lam, dp[j].second + 1};
    if (c < dp[i]) dp[i] = c; }
  return dp[n]; }
int main() {
  for (int it = 0; it < 3000; it++) {
    int n = rnd(1, 14); A.assign(n, 0); for (ll& x : A) x = rnd(1, it % 3 ? 10 : 2);
    if (it % 7 == 0) fill(all(A), 3); // collinear-ish / ties
    ll S = accumulate(all(A), 0LL);
    // f(K) direct
    vector<vector<ll>> f(n + 1, vector<ll>(n + 1, LLONG_MAX / 4)); f[0][0] = 0;
    vector<ll> pre(n + 1); for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + A[i];
    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 0; j < i; j++) if (f[k - 1][j] < LLONG_MAX / 4) f[k][i] = min(f[k][i], f[k - 1][j] + (pre[i] - pre[j]) * (pre[i] - pre[j]));
    for (int K = 1; K <= n; K++) CHECK(aliens(K, -S * S - 1, S * S + 1) == f[K][n]);
    // minimal-range from the comment: -(max|slope|)-1 .. +1
    ll mx = 0; for (int k = 1; k < n; k++) mx = max(mx, llabs(f[k + 1][n] - f[k][n]));
    for (int K = 1; K <= n; K++) { CHECK(aliens(K, -mx - 1, mx + 1) == f[K][n]); CHECK(aliens(K, -mx - 1, mx + 1) == f[K][n]); }
  }
  // exercise ties: f(k) exactly linear is impossible for squares; check cnt(lam) monotone & claim smallest lam with cnt<=K
  // collinear f(k) = c*k (all ties): any K must work
  for (ll c : {1LL, 5LL, 100LL}) for (int n = 1; n <= 9; n++) { CMODE = c; A.assign(n, 1); for (int K = 1; K <= n; K++) CHECK(aliens(K, -c - 1, c + 1) == c * K); }
  // f(k) = k*(k-1)... mixed: constant cost plus square cost via CMODE=0 covered above
  CMODE = 0;
  puts("ok");
}
