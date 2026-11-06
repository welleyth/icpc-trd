// Range add, range min & sum on [l, r). All zeros initially
// (set a[i]: add(i, i + 1, a[i])). O(log n) per operation.
struct Lazy {
  int n; vector<ll> mn, sm, lz;
  Lazy(int n) : n(n), mn(4 * n), sm(4 * n), lz(4 * n) {}
  void apply(int x, int len, ll v) {
    mn[x] += v; sm[x] += v * len; lz[x] += v; }
  void push(int x, int l, int r) {
    if (!lz[x]) return;
    int m = (l + r) / 2;
    apply(2 * x, m - l, lz[x]); apply(2 * x + 1, r - m, lz[x]);
    lz[x] = 0; }
  void add(int ql, int qr, ll v, int x, int l, int r) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) return apply(x, r - l, v);
    push(x, l, r);
    int m = (l + r) / 2;
    add(ql, qr, v, 2 * x, l, m);
    add(ql, qr, v, 2 * x + 1, m, r);
    mn[x] = min(mn[2 * x], mn[2 * x + 1]);
    sm[x] = sm[2 * x] + sm[2 * x + 1]; }
  pair<ll, ll> get(int ql, int qr, int x, int l, int r) {
    if (qr <= l || r <= ql) return {LLONG_MAX, 0};
    if (ql <= l && r <= qr) return {mn[x], sm[x]};
    push(x, l, r);
    int m = (l + r) / 2;
    auto a = get(ql, qr, 2 * x, l, m);
    auto b = get(ql, qr, 2 * x + 1, m, r);
    return {min(a.first, b.first), a.second + b.second}; }
  void add(int l, int r, ll v) { add(l, r, v, 1, 0, n); }
  ll qmin(int l, int r) { return get(l, r, 1, 0, n).first; }
  ll qsum(int l, int r) { return get(l, r, 1, 0, n).second; }
};
