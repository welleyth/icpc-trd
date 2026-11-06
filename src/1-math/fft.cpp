// Exact convolution of non-negative ints with any modulus
// (here: plain ll result) via complex FFT; safe while every
// result < 1e15 (e.g. n = 2e5, values <= 1e5 is fine).
using cd = complex<double>;
void fft(vector<cd>& a) {
  int n = sz(a), L = __lg(n);
  static vector<complex<long double>> R(2, 1);
  static vector<cd> rt(2, 1);
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n); rt.resize(n);
    auto x = polar(1.0L, acosl(-1) / k);
    for (int i = k; i < 2 * k; i++)
      rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
  }
  vi rev(n);
  for (int i = 0; i < n; i++)
    rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k)
      for (int j = 0; j < k; j++) {
        cd z = rt[j + k] * a[i + j + k];
        a[i + j + k] = a[i + j] - z; a[i + j] += z;
      }
}
vector<ll> convExact(const vector<ll>& a,
                     const vector<ll>& b) {
  if (a.empty() || b.empty()) return {};
  vector<ll> res(sz(a) + sz(b) - 1);
  int n = 1; while (n < sz(res)) n <<= 1;
  vector<cd> in(n), out(n);
  for (int i = 0; i < sz(a); i++) in[i].real(a[i]);
  for (int i = 0; i < sz(b); i++) in[i].imag(b[i]);
  fft(in);
  for (cd& x : in) x *= x;
  for (int i = 0; i < n; i++)
    out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  for (int i = 0; i < sz(res); i++)
    res[i] = llround(imag(out[i]) / (4 * n));
  return res; }
