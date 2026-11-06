// Dynamic segment tree over [0, N), N up to 2^62: nodes made
// on demand (about 62 per update). Point add, range sum,
// lowerBound = smallest i with a[0] + .. + a[i] >= t (a >= 0).
// Node 0 = null (sum 0), node 1 = root.
struct DynSeg {
  ll N; vector<array<int, 2>> ch; vector<ll> s;
  DynSeg(ll N) : N(N), ch(2), s(2) {}
  int child(int x, int d) {
    if (!ch[x][d]) {
      ch[x][d] = sz(s); ch.push_back({0, 0}); s.push_back(0); }
    return ch[x][d]; }
  void add(ll i, ll v) {
    int x = 1; ll l = 0, r = N; s[x] += v;
    while (r - l > 1) {
      ll m = l + (r - l) / 2; int d = i >= m;
      if (d) l = m; else r = m;
      x = child(x, d); s[x] += v;
    } }
  ll sum(ll ql, ll qr, int x, ll l, ll r) {
    if (!x || qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return s[x];
    ll m = l + (r - l) / 2;
    return sum(ql, qr, ch[x][0], l, m) +
           sum(ql, qr, ch[x][1], m, r); }
  ll sum(ll l, ll r) { return sum(l, r, 1, 0, N); }
  ll lowerBound(ll t) {                    // N if none
    if (s[1] < t) return N;
    int x = 1; ll l = 0, r = N;
    while (r - l > 1) {
      ll m = l + (r - l) / 2; int L = ch[x][0];
      if (s[L] >= t) x = L, r = m;
      else t -= s[L], x = ch[x][1], l = m;
    }
    return l; }
};
