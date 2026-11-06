// P(x) for the polynomial of degree < n with P(i) = y[i],
// i = 0..n-1. O(n). Needs mint + fact/ifact (binom.cpp).
// Sum 1^k + ... + m^k is a polynomial of degree k+1 in m:
// compute it for m = 0..k+1 and interpolate at m.
mint lagrange(const vector<mint>& y, ll x) {   // x >= 0
  int n = sz(y);
  if (x < n) return y[x];
  vector<mint> pre(n + 1, 1), suf(n + 1, 1);
  for (int i = 0; i < n; i++) pre[i + 1] = pre[i] * (x - i);
  for (int i = n - 1; i >= 0; i--)
    suf[i] = suf[i + 1] * (x - i);
  mint res = 0;
  for (int i = 0; i < n; i++) {
    mint t = y[i] * pre[i] * suf[i + 1] * ifact[i]
             * ifact[n - 1 - i];
    if ((n - 1 - i) & 1) res -= t; else res += t;
  }
  return res; }
