// Matrix power mod MOD: k x k matrix, O(k^3 log e).
// Linear recurrence f(n) = sum c_i f(n-i) -> companion matrix.
using Mat = vector<vector<ll>>;
Mat mul(const Mat& a, const Mat& b) {
  int n = sz(a), m = sz(b[0]), k = sz(b);
  Mat c(n, vector<ll>(m));
  for (int i = 0; i < n; i++)
    for (int t = 0; t < k; t++) if (a[i][t])
      for (int j = 0; j < m; j++)
        c[i][j] = (c[i][j] + a[i][t] * b[t][j]) % MOD;
  return c; }
Mat mpow(Mat a, ll e) {
  Mat r(sz(a), vector<ll>(sz(a)));
  for (int i = 0; i < sz(a); i++) r[i][i] = 1;
  for (; e; e >>= 1, a = mul(a, a)) if (e & 1) r = mul(r, a);
  return r; }
