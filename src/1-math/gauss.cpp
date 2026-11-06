// Solve A x = b mod MOD (prime). a = n rows of m+1 numbers
// (last column = b). Returns -1 if no solution, else rank;
// x = one solution (free variables = 0). O(n m min(n,m)).
// #solutions = MOD^(m - rank). For GF(2) use bitset rows.
int gauss(vector<vector<ll>> a, vector<ll>& x) {
  int n = sz(a), m = sz(a[0]) - 1, r = 0;
  vi where(m, -1);
  for (int c = 0; c < m && r < n; c++) {
    int p = r;
    while (p < n && !a[p][c]) p++;
    if (p == n) continue;
    swap(a[p], a[r]); where[c] = r;
    ll iv = power(a[r][c], MOD - 2, MOD);
    for (ll& v : a[r]) v = v * iv % MOD;
    for (int i = 0; i < n; i++) if (i != r && a[i][c]) {
      ll f = a[i][c];
      for (int j = c; j <= m; j++)
        a[i][j] = ((a[i][j] - f * a[r][j]) % MOD + MOD) % MOD;
    }
    r++;
  }
  for (int i = r; i < n; i++) if (a[i][m]) return -1;
  x.assign(m, 0);
  for (int c = 0; c < m; c++)
    if (where[c] >= 0) x[c] = a[where[c]][m];
  return r; }
