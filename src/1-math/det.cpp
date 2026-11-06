// Determinant mod MOD (prime), entries in [0, MOD). O(n^3)
// #spanning trees (Kirchhoff): det of the Laplacian D - A
// with one row and the same column removed.
ll det(vector<vector<ll>> a) {
  int n = sz(a); ll res = 1;
  for (int c = 0; c < n; c++) {
    int p = c;
    while (p < n && !a[p][c]) p++;
    if (p == n) return 0;
    if (p != c) swap(a[p], a[c]), res = MOD - res;
    res = res * a[c][c] % MOD;
    ll iv = power(a[c][c], MOD - 2, MOD);
    for (int i = c + 1; i < n; i++) if (a[i][c]) {
      ll f = a[i][c] * iv % MOD;
      for (int j = c; j < n; j++)
        a[i][j] = (a[i][j] + (MOD - f) * a[c][j]) % MOD;
    }
  }
  return res; }
