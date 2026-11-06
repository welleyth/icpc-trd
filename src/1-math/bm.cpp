// Berlekamp-Massey (mod prime MOD): from the first terms s,
// finds the shortest c with s[i] = sum_j c[j] * s[i-1-j].
// Needs 2L terms for a recurrence of order L. O(n^2)
vector<ll> berlekampMassey(const vector<ll>& s) {
  int n = sz(s), L = 0, m = 0;
  vector<ll> C(n), B(n), T;
  C[0] = B[0] = 1;
  ll b = 1;
  for (int i = 0; i < n; i++) {
    ++m;
    ll d = s[i] % MOD;
    for (int j = 1; j <= L; j++)
      d = (d + C[j] * s[i - j]) % MOD;
    if (!d) continue;
    T = C; ll coef = d * power(b, MOD - 2, MOD) % MOD;
    for (int j = m; j < n; j++)
      C[j] = (C[j] - coef * B[j - m]) % MOD;
    if (2 * L > i) continue;
    L = i + 1 - L; B = T; b = d; m = 0;
  }
  C.resize(L + 1); C.erase(C.begin());
  for (ll& x : C) x = (MOD - x) % MOD;
  return C; }
// k-th term (0-indexed) of s[i] = sum_j tr[j] * s[i-1-j]
// given the first sz(tr) terms S. O(L^2 log k)
ll linearRec(const vector<ll>& S, const vector<ll>& tr, ll k) {
  int n = sz(tr);
  auto combine = [&](const vector<ll>& a,
                     const vector<ll>& b) {
    vector<ll> res(2 * n + 1);
    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= n; j++)
        res[i + j] = (res[i + j] + a[i] * b[j]) % MOD;
    for (int i = 2 * n; i > n; i--)
      for (int j = 0; j < n; j++)
        res[i - 1 - j] =
            (res[i - 1 - j] + res[i] * tr[j]) % MOD;
    res.resize(n + 1);
    return res; };
  vector<ll> pol(n + 1), e(n + 1);
  pol[0] = e[1] = 1;
  for (k++; k; k /= 2) {
    if (k % 2) pol = combine(pol, e);
    e = combine(e, e);
  }
  ll res = 0;
  for (int i = 0; i < n; i++)
    res = (res + pol[i + 1] * S[i]) % MOD;
  return res; }
