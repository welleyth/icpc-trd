// GENERIC lazy segment tree (range update, range query).
//  S: node value; op(S, S) associative; e = neutral S
//  F: tag; mp(f, s) = s after applying f; comp(f, g) = "f
//     after g"; id = identity tag.
// BEATS: give S a field `bool fail`; mp sets s.fail = true
// when it cannot update the node exactly -> the tree pushes
// and recurses (mp on a leaf must never fail).
// findFirst(l, pred): first i >= l with !pred(op(a[l..i])),
// n if none; pred must be monotone and pred(e) = true.
template <class T, class = void>
struct HasFail : false_type {};
template <class T>
struct HasFail<T, void_t<decltype(declval<T>().fail)>>
    : true_type {};
template <class S, class F, class Op, class Mp, class Comp>
struct LazySeg {
  int n; S e; F id; Op op; Mp mp; Comp comp;
  vector<S> t; vector<F> lz;
  LazySeg(const vector<S>& a, S e, F id, Op op, Mp mp,
          Comp comp)
    : n(sz(a)), e(e), id(id), op(op), mp(mp), comp(comp),
      t(4 * n + 4, e), lz(4 * n + 4, id) {
    if (n) build(1, 0, n, a); }
  void build(int x, int l, int r, const vector<S>& a) {
    if (r - l == 1) { t[x] = a[l]; return; }
    int m = (l + r) / 2;
    build(2 * x, l, m, a); build(2 * x + 1, m, r, a);
    t[x] = op(t[2 * x], t[2 * x + 1]); }
  void put(int x, F f) {
    t[x] = mp(f, t[x]); lz[x] = comp(f, lz[x]); }
  void push(int x) {
    put(2 * x, lz[x]); put(2 * x + 1, lz[x]); lz[x] = id; }
  void update(int ql, int qr, F f, int x, int l, int r) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
      S s = mp(f, t[x]); bool bad = false;
      if constexpr (HasFail<S>::value) bad = s.fail;
      if (!bad) { t[x] = s; lz[x] = comp(f, lz[x]); return; }
    }
    push(x); int m = (l + r) / 2;
    update(ql, qr, f, 2 * x, l, m);
    update(ql, qr, f, 2 * x + 1, m, r);
    t[x] = op(t[2 * x], t[2 * x + 1]); }
  S query(int ql, int qr, int x, int l, int r) {
    if (qr <= l || r <= ql) return e;
    if (ql <= l && r <= qr) return t[x];
    push(x); int m = (l + r) / 2;
    return op(query(ql, qr, 2 * x, l, m),
              query(ql, qr, 2 * x + 1, m, r)); }
  template <class G>
  int find(int ql, G& pred, S& acc, int x, int l, int r) {
    if (r <= ql) return n;
    if (ql <= l && pred(op(acc, t[x]))) {
      acc = op(acc, t[x]); return n; }
    if (r - l == 1) return l;
    push(x); int m = (l + r) / 2;
    int i = find(ql, pred, acc, 2 * x, l, m);
    return i < n ? i : find(ql, pred, acc, 2 * x + 1, m, r); }
  void update(int l, int r, F f) { update(l, r, f, 1, 0, n); }
  S query(int l, int r) { return query(l, r, 1, 0, n); }
  template <class G> int findFirst(int l, G pred) {
    S acc = e; return find(l, pred, acc, 1, 0, n); }
};
// EXAMPLE: range add, range min + sum (len for the sum).
struct SN { ll mn, sm; int len; };
auto makeAddMinSum(const vector<ll>& a) {
  vector<SN> v;
  for (ll x : a) v.push_back({x, x, 1});
  return LazySeg(v, SN{LLONG_MAX, 0, 0}, 0LL,
    [](SN a, SN b) {
      return SN{min(a.mn, b.mn), a.sm + b.sm,
                a.len + b.len}; },
    [](ll f, SN s) {
      return SN{s.mn + f, s.sm + f * s.len, s.len}; },
    [](ll f, ll g) { return f + g; }); }
// first i >= l with a[i] < val:
//   st.findFirst(l, [&](SN s) { return s.mn >= val; });
// Range ASSIGN: F = {bool has; ll v},
// comp(f, g) = f.has ? f : g; assign + add: F = {has, v, add}.
