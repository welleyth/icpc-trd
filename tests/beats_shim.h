// old Beats API on top of LazySeg + makeBeats (tests only)
struct Beats {
  decltype(makeBeats({})) st;
  Beats(const vector<ll>& a) : st(makeBeats(a)) {}
  void chmin(int l, int r, ll v) { st.update(l, r, v); }
  ll qsum(int l, int r) { return st.query(l, r).sum; }
  ll qmax(int l, int r) { return st.query(l, r).mx; }
};
