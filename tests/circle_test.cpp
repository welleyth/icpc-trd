#include "common.h"
#include "../src/5-geom/point.cpp"
#include "../src/5-geom/circle.cpp"
#include "chk.h"
typedef __int128 LL;
int main() {
  // circle-line, exact count via integers
  for (int iter = 0; iter < 300000; iter++) {
    int R = iter % 2 ? 6 : 1000;
    ll cx = rnd(-R,R), cy = rnd(-R,R), r = rnd(1, R), ax = rnd(-R,R), ay = rnd(-R,R), bx = rnd(-R,R), by = rnd(-R,R);
    if (ax == bx && ay == by) continue;
    PD c{(long double)cx,(long double)cy}, a{(long double)ax,(long double)ay}, b{(long double)bx,(long double)by};
    auto res = circleLine(c, r, a, b);
    LL cr = (LL)(bx-ax)*(cy-ay) - (LL)(by-ay)*(cx-ax);
    LL l2 = (LL)(bx-ax)*(bx-ax) + (LL)(by-ay)*(by-ay);
    LL lhs = cr * cr, rhs = (LL)r * r * l2;
    int cnt = lhs < rhs ? 2 : lhs == rhs ? 1 : 0;
    CHECK(sz(res) == cnt);
    for (auto p : res) {
      CHECK(fabsl((p - c).len() - r) < 1e-6L * max<ll>(1, r));
      CHECK(fabsl((b - a).cross(p - a)) < 1e-6L * sqrtl(l2) * max<ll>(1, R/10)); }
  }
  // circle-circle
  for (int iter = 0; iter < 300000; iter++) {
    int R = iter % 2 ? 6 : 1000;
    ll x1 = rnd(-R,R), y1 = rnd(-R,R), x2 = rnd(-R,R), y2 = rnd(-R,R), r1 = rnd(1, R), r2 = rnd(1, R);
    if (x1 == x2 && y1 == y2) { CHECK(circleCircle(PD{(long double)x1,(long double)y1}, r1, PD{(long double)x2,(long double)y2}, r2).empty()); continue; }
    auto res = circleCircle(PD{(long double)x1,(long double)y1}, r1, PD{(long double)x2,(long double)y2}, r2);
    LL d2 = (LL)(x1-x2)*(x1-x2) + (LL)(y1-y2)*(y1-y2);
    LL sum = (LL)(r1+r2)*(r1+r2), dif = (LL)(r1-r2)*(r1-r2);
    int cnt = (d2 > sum || d2 < dif) ? 0 : (d2 == sum || d2 == dif) ? 1 : 2;
    CHECK(sz(res) == cnt);
    for (auto p : res) {
      CHECK(fabsl((p - PD{(long double)x1,(long double)y1}).len() - r1) < 1e-6L);
      CHECK(fabsl((p - PD{(long double)x2,(long double)y2}).len() - r2) < 1e-6L); }
  }
  DONE();
}
