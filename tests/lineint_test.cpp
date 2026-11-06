#include "common.h"
#include "../src/5-geom/point.cpp"
#include "../src/5-geom/segments.cpp"
#include "chk.h"
typedef __int128 LL;
LL crx(P a, P b, P c) { return (LL)(b.x-a.x)*(c.y-a.y) - (LL)(b.y-a.y)*(c.x-a.x); }
int main() {
  int lat = 0, non = 0, par = 0;
  for (int it = 0; it < 2000000; it++) {
    int R = (int[]){3, 10, 1000, 1000000000, 1000000000}[it % 5];
    auto rp = [&]() { P p{(ll)rnd(-R, R), (ll)rnd(-R, R)}; if (R == 1000000000 && rnd(0,2)==0) p = {rnd(0,1)?-R:R, rnd(0,1)?-R:R}; return p; };
    P a = rp(), b = rp(), c = rp(), d = rp();
    if (a == b || c == d) continue;
    if (it % 7 == 0) { // make lattice intersection: pick pt, directions
      P x = rp(); ll s = rnd(1, 3);
      P u{rnd(-3, 3), rnd(-3, 3)}, w{rnd(-3,3), rnd(-3,3)};
      if (R >= 1000) { x.x /= 2; x.y /= 2; }
      a = x - u * s; b = x + u; c = x - w; d = x + w * s;
      if (llabs(a.x) > R || llabs(a.y) > R || llabs(b.x) > R || llabs(b.y) > R || llabs(c.x) > R || llabs(c.y) > R || llabs(d.x) > R || llabs(d.y) > R) continue;
      if (a == b || c == d) continue; }
    if (it % 11 == 0) { c = a + (b - a) * 0; d = b; if (c == d) continue; } // coincident lines
    if (it % 13 == 0) { P v = b - a; c = rp(); d = c + v; if (llabs(d.x) > R || llabs(d.y) > R) continue; } // parallel
    P res{-77, -77};
    bool ok = lineInterInt(a, b, c, d, res);
    // exact rational brute
    LL den = (LL)(b.x-a.x)*(d.y-c.y) - (LL)(b.y-a.y)*(d.x-c.x);
    if (den == 0) { CHECK(!ok); par++; continue; }
    LL num = (LL)(c.x-a.x)*(d.y-c.y) - (LL)(c.y-a.y)*(d.x-c.x);
    // point = a + (b-a) * num/den
    LL X = (LL)a.x * den + (LL)(b.x-a.x) * num, Y = (LL)a.y * den + (LL)(b.y-a.y) * num;
    { LL D = (LL)(a.x-b.x)*(c.y-d.y) - (LL)(a.y-b.y)*(c.x-d.x);
      LL p1 = (LL)a.x*b.y - (LL)a.y*b.x, p2 = (LL)c.x*d.y - (LL)c.y*d.x;
      LL NX = p1*(c.x-d.x) - (LL)(a.x-b.x)*p2, NY = p1*(c.y-d.y) - (LL)(a.y-b.y)*p2;
      
      bool l2 = NX % D == 0 && NY % D == 0; CHECK(l2 == (X % den == 0 && Y % den == 0)); if (ok) CHECK((LL)res.x == NX / D && (LL)res.y == NY / D); }
    bool lt = X % den == 0 && Y % den == 0;
    CHECK(ok == lt);
    if (lt) { lat++; CHECK((LL)res.x == X / den && (LL)res.y == Y / den);
      CHECK(crx(a,b,res)==0 && crx(c,d,res)==0);
      } else non++;
  }
  fprintf(stderr, "lat %d non %d par %d\n", lat, non, par);
  DONE();
}
