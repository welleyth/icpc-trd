// Convolution mod 998244353 (= 119*2^23+1, root 3). O(n log n)
// conv of two arrays of length 5e5: about 0.1 s.
void ntt(vi& a, bool invert) {
  int n = sz(a);
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }
  vi rt(n / 2 + 1);
  for (int len = 1; len < n; len <<= 1) {
    ll w = power(3, (MOD - 1) / (2 * len), MOD);
    if (invert) w = power(w, MOD - 2, MOD);
    rt[0] = 1;
    for (int j = 1; j < len; j++) rt[j] = rt[j - 1] * w % MOD;
    for (int i = 0; i < n; i += 2 * len)
      for (int j = 0; j < len; j++) {
        int u = a[i + j];
        int v = (ll)a[i + j + len] * rt[j] % MOD;
        a[i + j] = u + v < MOD ? u + v : u + v - MOD;
        a[i + j + len] = u - v >= 0 ? u - v : u - v + MOD;
      }
  }
  if (invert) {
    ll ni = power(n, MOD - 2, MOD);
    for (int& x : a) x = x * ni % MOD;
  }
}
vi conv(vi a, vi b) {           // values in [0, MOD)
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, n = 1;
  while (n < s) n <<= 1;
  a.resize(n); b.resize(n);
  ntt(a, false); ntt(b, false);
  for (int i = 0; i < n; i++) a[i] = (ll)a[i] * b[i] % MOD;
  ntt(a, true); a.resize(s);
  return a; }
