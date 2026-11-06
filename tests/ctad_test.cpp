#include "t_util.h"
#include "../src/1-math/mint.cpp"
#include "../src/2-ds/segtree.cpp"
#include "../src/2-ds/fenwick.cpp"
#include "../src/2-ds/sparse.cpp"
int main() {
  int n = 37;
  Seg mx(n, LLONG_MIN, [](ll a, ll b) { return max(a, b); });
  Seg sm(n, 0LL, [](ll a, ll b) { return a + b; });
  static_assert(is_same_v<decltype(mx.ID), ll>); static_assert(is_same_v<decltype(sm.ID), ll>);
  BIT b(n); static_assert(is_same_v<decltype(b.t), vector<ll>>);
  BIT<mint> bm(n); BIT<double> bd(n);
  vector<ll> a(n, LLONG_MIN), s(n);
  for (int it = 0; it < 3000; it++) {
    int i = rnd(0, n - 1); ll v = rnd(-1000000000000LL, 1000000000000LL);
    mx.set(i, v); sm.set(i, v); a[i] = v; ll old = s[i]; s[i] = v;
    b.add(i, 5000000000LL * (v % 7)); bm.add(i, v); bd.add(i, 0.5);
    (void)old;
    int l = rnd(0, n), r = rnd(l, n);
    ll m1 = LLONG_MIN, s1 = 0; mint ms = 0; for (int k = l; k < r; k++) m1 = max(m1, a[k]), s1 += s[k];
    CHECK(mx.query(l, r) == m1); CHECK(sm.query(l, r) == s1); CHECK(mx.get(i) == v);
    ll bs = 0; mint bm1 = 0; for (int k = l; k < r; k++) bs += 0, bm1 += 0;
    (void)bs; (void)bm1; (void)ms;
  }
  { BIT c(n); vector<ll> p(n); for (int k = 0; k < 500; k++) { int i = rnd(0, n-1); ll v = rnd(0, 1LL<<40); c.add(i, v); p[i] += v;
      int l = rnd(0, n), r = rnd(l, n); ll t = 0; for (int j = l; j < r; j++) t += p[j]; CHECK(c.sum(l, r) == t); } }
  { BIT<mint> c(n); vector<mint> p(n); for (int k = 0; k < 500; k++) { int i = rnd(0, n-1); mint v = rnd(0, MOD-1); c.add(i, v); p[i] += v;
      int l = rnd(0, n), r = rnd(l, n); mint t = 0; for (int j = l; j < r; j++) t += p[j]; CHECK(c.sum(l, r) == t); } }
  { BIT<double> c(n); c.add(3, 1.5); c.add(4, 2.25); CHECK(c.sum(0, n) == 3.75); }
  Seg mn(n, (int)INT_MAX, [](int x, int y) { return min(x, y); }); mn.set(2, 5); CHECK(mn.query(0, n) == 5);
  struct P { int x; }; // noncommutative: string concat
  Seg cs(8, string(), [](string x, string y) { return x + y; });
  for (int i = 0; i < 8; i++) cs.set(i, string(1, 'a' + i));
  CHECK(cs.query(1, 7) == "bcdefg"); CHECK(cs.query(0, 8) == "abcdefgh"); CHECK(cs.query(3, 3) == "");
  for (int it = 0; it < 300; it++) {
    int m = rnd(1, 40); vector<int> v(m); for (int& x : v) x = rnd(1, 1000);
    Sparse g(v, [](int x, int y) { return gcd(x, y); });
    Sparse mi(v, [](int x, int y) { return min(x, y); });
    vector<ll> w(v.begin(), v.end());
    Sparse mxs(w, [](ll x, ll y) { return max(x, y); });
    for (int l = 0; l < m; l++) for (int r = l + 1; r <= m; r++) {
      int gg = 0, mm = INT_MAX; ll MM = 0; for (int k = l; k < r; k++) gg = gcd(gg, v[k]), mm = min(mm, v[k]), MM = max<ll>(MM, v[k]);
      CHECK(g.query(l, r) == gg); CHECK(mi.query(l, r) == mm); CHECK(mxs.query(l, r) == MM); } }
  puts("ok");
}
