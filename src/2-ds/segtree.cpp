// Point update, range query [l, r) for any associative f
// (need not be commutative). T is deduced from ID. O(log n)
//   Seg mx(n, LLONG_MIN,
//          [](ll a, ll b) { return max(a, b); });
//   Seg sm(n, 0LL, [](ll a, ll b) { return a + b; });  // 0LL!
template <class T, class F> struct Seg {
  int n; T ID; F f; vector<T> t;
  Seg(int n, T ID, F f) : n(n), ID(ID), f(f), t(2 * n, ID) {}
  void set(int i, T v) {
    for (t[i += n] = v; i >>= 1;)
      t[i] = f(t[2 * i], t[2 * i + 1]); }
  T get(int i) { return t[i + n]; }
  T query(int l, int r) {
    T a = ID, b = ID;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) a = f(a, t[l++]);
      if (r & 1) b = f(t[--r], b);
    }
    return f(a, b); }
};
