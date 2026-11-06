// Segment tree beats as an instance of LazySeg (lazyseg.cpp):
// range chmin a_i = min(a_i, x), range sum and max.
// Amortised O((n + q) log n). Chmax: store -a, chmin with -x.
// Node: max, strict second max, count of max, sum, fail.
struct BN { ll mx, smx, cnt, sum; bool fail = false; };
BN mergeBN(BN a, BN b) {
  if (a.mx < b.mx) swap(a, b);
  if (a.mx == b.mx)
    return {a.mx, max(a.smx, b.smx), a.cnt + b.cnt,
            a.sum + b.sum};
  return {a.mx, max(a.smx, b.mx), a.cnt, a.sum + b.sum}; }
auto makeBeats(const vector<ll>& a) {
  vector<BN> v;
  for (ll x : a) v.push_back({x, LLONG_MIN, 1, x});
  return LazySeg(v, BN{LLONG_MIN, LLONG_MIN, 0, 0}, LLONG_MAX,
    mergeBN,
    [](ll f, BN s) {                 // chmin with f
      if (f >= s.mx) return s;
      if (f > s.smx) { s.sum -= (s.mx - f) * s.cnt; s.mx = f; }
      else s.fail = true;        // 2nd max too: descend
      return s; },
    [](ll f, ll g) { return min(f, g); }); }
// st.update(l, r, x) = chmin; st.query(l, r).sum / .mx
