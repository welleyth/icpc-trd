// Li Chao tree: add line y = k x + b, query min at integer x
// in [lo, hi). O(log C) each. For max: negate k, b, answer.
struct LiChao {
  struct Line { ll k, b; ll operator()(ll x) const {
    return k * x + b; } };
  ll lo, hi; vector<Line> t; vi L, R;
  LiChao(ll lo, ll hi) : lo(lo), hi(hi) { node(); }
  int node() { t.push_back({0, LLONG_MAX}); L.push_back(-1);
    R.push_back(-1); return sz(t) - 1; }
  void add(Line nw) { add(nw, 0, lo, hi); }
  void add(Line nw, int x, ll l, ll r) {
    ll m = l + (r - l) / 2;
    bool lef = nw(l) < t[x](l), mid = nw(m) < t[x](m);
    if (mid) swap(t[x], nw);
    if (r - l == 1 || nw.b == LLONG_MAX) return;
    if (lef != mid) {
      if (L[x] < 0) { int c = node(); L[x] = c; }
      add(nw, L[x], l, m);
    } else {
      if (R[x] < 0) { int c = node(); R[x] = c; }
      add(nw, R[x], m, r);
    } }
  ll query(ll q) {
    ll res = LLONG_MAX; int x = 0; ll l = lo, r = hi;
    while (x >= 0) {
      res = min(res, t[x](q));
      ll m = l + (r - l) / 2;
      if (q < m) x = L[x], r = m; else x = R[x], l = m;
    }
    return res; }
};
