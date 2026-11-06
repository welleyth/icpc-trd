// "Visible buildings": point update; count of records (i with
// a[i] > max of everything before it in the range) on [l, r).
// res[x] = records of the right child given the left's max.
// calc is O(log n), so update/query O(log^2 n). For the SUM of
// record values store sums in res the same way.
struct Records {
  int n; vector<ll> mx; vi res;
  Records(int n) : n(n), mx(4 * n, LLONG_MIN), res(4 * n) {}
  int calc(int x, int l, int r, ll m) {  // records after max m
    if (mx[x] <= m) return 0;
    if (r - l == 1) return 1;
    int md = (l + r) / 2;
    if (mx[2 * x] <= m) return calc(2 * x + 1, md, r, m);
    return calc(2 * x, l, md, m) + res[x]; }
  void set(int i, ll v, int x, int l, int r) {
    if (r - l == 1) { mx[x] = v; return; }
    int md = (l + r) / 2;
    if (i < md) set(i, v, 2 * x, l, md);
    else set(i, v, 2 * x + 1, md, r);
    mx[x] = max(mx[2 * x], mx[2 * x + 1]);
    res[x] = calc(2 * x + 1, md, r, mx[2 * x]); }
  int query(int ql, int qr, ll& m, int x, int l, int r) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) {
      int c = calc(x, l, r, m); m = max(m, mx[x]); return c; }
    int md = (l + r) / 2;
    int a = query(ql, qr, m, 2 * x, l, md);
    return a + query(ql, qr, m, 2 * x + 1, md, r); }
  void set(int i, ll v) { set(i, v, 1, 0, n); }
  int query(int l, int r) {
    ll m = LLONG_MIN; return query(l, r, m, 1, 0, n); }
};
