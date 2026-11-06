// Point update, range query [l, r) for any associative f.
// Change T, ID (identity) and f. O(log n)
struct Seg {
  using T = ll;
  const T ID = LLONG_MIN;
  T f(T a, T b) { return max(a, b); }
  int n; vector<T> t;
  Seg(int n) : n(n), t(2 * n, ID) {}
  void set(int i, T v) {
    for (t[i += n] = v; i >>= 1;)
      t[i] = f(t[2 * i], t[2 * i + 1]); }
  T query(int l, int r) {
    T a = ID, b = ID;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) a = f(a, t[l++]);
      if (r & 1) b = f(t[--r], b);
    }
    return f(a, b); }
};
