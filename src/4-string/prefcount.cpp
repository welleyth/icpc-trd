// Number of strings over k letters whose prefix function is
// exactly p (p must be a valid prefix function). O(n).
// D[b] = # distinct letters forbidden after border b.
ll countByPrefix(const vi& p, ll k) {
  int n = sz(p); vi D(n);
  D[0] = 1;
  for (int b = 1; b < n; b++) D[b] = D[p[b - 1]] + (p[b] == 0);
  ll r = k % MOD;                       // first letter: k ways
  for (int i = 1; i < n; i++) if (p[i] == 0)
    r = r * ((k - D[p[i - 1]]) % MOD + MOD) % MOD;
  return r; }
