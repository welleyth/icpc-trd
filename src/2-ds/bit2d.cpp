// 2D Fenwick: point "combine", query over [0, x) x [0, y).
// f commutative + associative: max with raise-only updates,
// or sum (+) with additions. O(log n log m), memory n*m.
//   BIT2D b(n, m, LLONG_MIN,
//           [](ll a, ll c) { return max(a, c); });
// Typical: DP over pairs sorted by one key, best over a
// dominated quadrant of the other two.
template <class T, class F> struct BIT2D {
  int n, m; T ID; F f; vector<vector<T>> t;
  BIT2D(int n, int m, T ID, F f)
    : n(n), m(m), ID(ID), f(f),
      t(n + 1, vector<T>(m + 1, ID)) {}
  void upd(int x, int y, T v) {
    for (int i = x + 1; i <= n; i += i & -i)
      for (int j = y + 1; j <= m; j += j & -j)
        t[i][j] = f(t[i][j], v); }
  T query(int x, int y) {
    T r = ID;
    for (int i = x; i > 0; i -= i & -i)
      for (int j = y; j > 0; j -= j & -j) r = f(r, t[i][j]);
    return r; }
};
