// Knuth optimisation: dp[l][r] = min_{l <= m < r} dp[l][m] +
// dp[m+1][r] + w(l, r) (merge stones, optimal BST ...) when
// opt[l][r-1] <= opt[l][r] <= opt[l+1][r] (holds if w is
// monotone and satisfies the quadrangle inequality).
// O(n^2) instead of O(n^3). Here dp[i][i] = 0.
ll w(int l, int r);
ll knuth(int n) {
  vector<vector<ll>> dp(n, vector<ll>(n));
  vector<vi> opt(n, vi(n));
  for (int i = 0; i < n; i++) opt[i][i] = i;
  for (int len = 2; len <= n; len++)
    for (int l = 0; l + len - 1 < n; l++) {
      int r = l + len - 1; dp[l][r] = LLONG_MAX;
      int hiM = min(opt[l + 1][r], r - 1);
      for (int m = opt[l][r - 1]; m <= hiM; m++) {
        ll v = dp[l][m] + dp[m + 1][r] + w(l, r);
        if (v < dp[l][r]) dp[l][r] = v, opt[l][r] = m;
      }
    }
  return dp[0][n - 1]; }
