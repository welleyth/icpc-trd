#include "t_util.h"
const int MOD = 998244353;
#include "../src/1-math/matrix.cpp"
int main() {
  for (int it = 0; it < 3000; it++) {
    int k = rnd(1, 5); Mat a(k, vector<ll>(k));
    for (auto& r : a) for (ll& x : r) x = rnd(0, it % 2 ? 3 : MOD - 1);
    ll e = rnd(0, 30);
    Mat r(k, vector<ll>(k)); for (int i = 0; i < k; i++) r[i][i] = 1;
    for (int i = 0; i < e; i++) r = mul(r, a);
    CHECK(mpow(a, e) == r);
  }
  // non-square mul
  Mat a = {{1, 2, 3}, {4, 5, 6}}, b = {{7, 8}, {9, 10}, {11, 12}};
  CHECK(mul(a, b) == (Mat{{58, 64}, {139, 154}}));
  // fibonacci
  Mat f = {{1, 1}, {1, 0}};
  ll x = 0, y = 1; for (int i = 0; i < 1000; i++) { tie(x, y) = make_pair(y, (x + y) % MOD); }
  CHECK(mpow(f, 1000)[0][1] == x);
  CHECK(mpow(f, 0) == (Mat{{1, 0}, {0, 1}}));
  // large exponent: a^(e) with a^(MOD-1)... use diagonal
  Mat d = {{3, 0}, {0, 5}};
  Mat r = mpow(d, 1000000000000000000LL);
  auto pw = [&](ll bb, ll ee) { ll rr = 1; for (; ee; ee >>= 1, bb = bb * bb % MOD) if (ee & 1) rr = rr * bb % MOD; return rr; };
  CHECK(r[0][0] == pw(3, 1000000000000000000LL) && r[1][1] == pw(5, 1000000000000000000LL));
  Mat one = {{7}}; CHECK(mpow(one, 5)[0][0] == 16807);
  puts("ok");
}
