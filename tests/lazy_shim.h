// old Lazy API on top of the generic LazySeg (tests only)
struct Lazy {
  decltype(makeAddMinSum({})) st;
  Lazy(int n) : st(makeAddMinSum(vector<ll>(n))) {}
  void add(int l, int r, ll v) { st.update(l, r, v); }
  ll qmin(int l, int r) { return st.query(l, r).mn; }
  ll qsum(int l, int r) { return st.query(l, r).sm; }
  int firstLess(int l, ll val) { return st.findFirst(l, [&](SN s) { return s.mn >= val; }); }
};
