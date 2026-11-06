// Fenwick tree, 0-indexed: point add, prefix sum. O(log n)
struct BIT {
  int n; vector<ll> t;
  BIT(int n) : n(n), t(n + 1) {}
  void add(int i, ll v) {
    for (i++; i <= n; i += i & -i) t[i] += v; }
  ll sum(int i) {             // a[0] + ... + a[i-1]
    ll s = 0;
    for (; i > 0; i -= i & -i) s += t[i];
    return s; }
  ll sum(int l, int r) { return sum(r) - sum(l); }  // [l, r)
  // smallest i with a[0]+..+a[i] >= s (all a >= 0), n if none
  int lowerBound(ll s) {
    int pos = 0;
    for (int pw = 1 << __lg(n); pw; pw >>= 1)
      if (pos + pw <= n && t[pos + pw] < s)
        pos += pw, s -= t[pos];
    return pos; }
};
// Inversions: go left->right, ans += i - sum(a[i] + 1),
// add(a[i], 1)  (compress values to 0..n-1 first).
// Range add + point query: add(l, v), add(r, -v);
// then a[i] = sum(i + 1).
