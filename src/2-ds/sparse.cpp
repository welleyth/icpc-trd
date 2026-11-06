// Static range query [l, r) in O(1) after O(n log n) build,
// for IDEMPOTENT f (min, max, gcd, and, or).
//   Sparse sp(a, [](int x, int y) { return min(x, y); });
template <class T, class F> struct Sparse {
  vector<vector<T>> t; F f;
  Sparse(const vector<T>& a, F f) : t{a}, f(f) {
    for (int k = 1; (1 << k) <= sz(a); k++) {
      t.emplace_back(sz(a) - (1 << k) + 1);
      for (int i = 0; i < sz(t[k]); i++)
        t[k][i] = f(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
    }
  }
  T query(int l, int r) {            // requires l < r
    int k = __lg(r - l);
    return f(t[k][l], t[k][r - (1 << k)]); }
};
