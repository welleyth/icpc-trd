#include "common.h"
#include "../src/5-geom/point.cpp"
#include "../src/5-geom/segments.cpp"
#include "chk.h"
typedef __int128 LL;
int ori(P a, P b, P c) { LL v = (LL)(b.x-a.x)*(c.y-a.y) - (LL)(b.y-a.y)*(c.x-a.x); return (v>0)-(v<0); }
bool onS(P p, P a, P b) { return ori(a,b,p)==0 && min(a.x,b.x)<=p.x && p.x<=max(a.x,b.x) && min(a.y,b.y)<=p.y && p.y<=max(a.y,b.y); }
bool inter(P a, P b, P c, P d) {
  int o1=ori(a,b,c),o2=ori(a,b,d),o3=ori(c,d,a),o4=ori(c,d,b);
  if (o1!=o2 && o3!=o4) {
    // general position or touching
    if (o1==0&&o2==0) return false;  // not reachable here (o1!=o2)
    return true; }
  if (o1==0&&onS(c,a,b)) return true;
  if (o2==0&&onS(d,a,b)) return true;
  if (o3==0&&onS(a,c,d)) return true;
  if (o4==0&&onS(b,c,d)) return true;
  return false; }
// brute with tiny coords: sample on a fine grid of rationals: scale by 12*? exact via lattice of 1/L
bool interBrute(P a, P b, P c, P d) {
  // all intersection points of two segments with integer endpoints are rational; test
  // by scanning parameter t=i/N for N=lcm-ish: use N = 2*|..|... just check exact through
  // cross-multiplication
  ll dx1=b.x-a.x, dy1=b.y-a.y, dx2=d.x-c.x, dy2=d.y-c.y;
  ll den = dx1*dy2 - dy1*dx2;
  if (den != 0) {
    ll tn = (c.x-a.x)*dy2 - (c.y-a.y)*dx2, un = (c.x-a.x)*dy1 - (c.y-a.y)*dx1;
    if (den < 0) den = -den, tn = -tn, un = -un;
    return 0 <= tn && tn <= den && 0 <= un && un <= den; }
  // parallel: share a point? test endpoints (handles degenerate point segments too)
  return onS(a,c,d)||onS(b,c,d)||onS(c,a,b)||onS(d,a,b);
}
int main() {
  for (int iter = 0; iter < 400000; iter++) {
    int R = iter % 3 == 0 ? 2 : iter % 3 == 1 ? 4 : 1;
    auto r = [&]() { return P{rnd(-R, R), rnd(-R, R)}; };
    P a = r(), b = r(), c = r(), d = r(), p = r();
    CHECK(onSeg(p, a, b) == onS(p, a, b));
    bool x = segInter(a, b, c, d);
    CHECK(x == interBrute(a, b, c, d));
    CHECK(x == segInter(c, d, a, b));
    CHECK(x == segInter(b, a, d, c));
  }
  // big coordinates
  for (int iter = 0; iter < 300000; iter++) {
    ll B = 1000000000LL;
    auto r = [&]() { ll m = iter % 4 == 0 ? 3 : B;
      return P{(ll)(rng_() % (2*m+1)) - m, (ll)(rng_() % (2*m+1)) - m}; };
    P a = r(), b = r(), c = r(), d = r();
    if (iter % 5 == 0) c = a + (b - a);        // may overflow? keep within range
    if (iter % 7 == 0) { c = a; }
    bool bad = false; for (P q : {c}) if (llabs(q.x) > B || llabs(q.y) > B) bad = true;
    if (bad) continue;
    CHECK(segInter(a, b, c, d) == inter(a, b, c, d));
    CHECK(onSeg(c, a, b) == onS(c, a, b));
  }
  // extremes
  P A{-1000000000,-1000000000}, Bp{1000000000,1000000000}, C{-1000000000,1000000000}, D{1000000000,-1000000000};
  CHECK(segInter(A,Bp,C,D)); CHECK(!segInter(A,C,D,Bp)==false ? false : true);
  CHECK(onSeg(P{0,0}, A, Bp)); CHECK(!onSeg(P{0,1}, A, Bp));
  CHECK(onSeg(P{1000000000,1000000000}, A, Bp));
  // vertical / overlapping / touching
  CHECK(segInter(P{0,0},P{0,5},P{0,5},P{0,9}));
  CHECK(segInter(P{0,0},P{0,5},P{0,3},P{0,9}));
  CHECK(!segInter(P{0,0},P{0,5},P{0,6},P{0,9}));
  CHECK(segInter(P{0,0},P{0,0},P{0,0},P{0,0}));
  CHECK(!segInter(P{0,0},P{0,0},P{1,0},P{1,0}));
  CHECK(segInter(P{0,0},P{4,0},P{2,0},P{2,0}));
  CHECK(segInter(P{0,0},P{4,4},P{4,4},P{5,0}));
  // lineInter
  for (int iter = 0; iter < 100000; iter++) {
    auto r = [&]() { return PD{(long double)rnd(-20,20), (long double)rnd(-20,20)}; };
    PD a = r(), b = r(), c = r(), d = r();
    if ((b-a).cross(d-c) == 0) continue;
    PD x = lineInter(a, b, c, d);
    CHECK(fabsl((b-a).cross(x-a)) < 1e-8); CHECK(fabsl((d-c).cross(x-c)) < 1e-8);
  }
  // segDist vs ternary search
  for (int iter = 0; iter < 100000; iter++) {
    auto r = [&]() { return PD{(long double)rnd(-9,9), (long double)rnd(-9,9)}; };
    PD p = r(), a = r(), b = r();
    long double lo = 0, hi = 1;
    auto f = [&](long double t) { return (p - (a + (b-a)*t)).len(); };
    for (int i = 0; i < 100; i++) { long double m1 = lo+(hi-lo)/3, m2 = hi-(hi-lo)/3;
      if (f(m1) < f(m2)) hi = m2; else lo = m1; }
    CHECK(fabsl(segDist(p, a, b) - f(lo)) < 1e-9);
    CHECK(fabsl(segDist(p, a, a) - (p-a).len()) < 1e-12);
  }
  DONE();
}
