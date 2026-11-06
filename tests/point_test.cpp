#include "common.h"
#include "../src/5-geom/point.cpp"
#include "chk.h"
typedef __int128 LL;
int main() {
  for (int iter = 0; iter < 200000; iter++) {
    ll B = iter % 2 ? 1000000000LL : 10;
    auto r = [&]() { return (ll)(rng_() % (2 * B + 1)) - B; };
    P a{r(), r()}, b{r(), r()}, c{r(), r()};
    LL cr = (LL)(b.x-a.x)*(c.y-a.y) - (LL)(b.y-a.y)*(c.x-a.x);
    CHECK((LL)a.cross(b, c) == cr);
    CHECK(sgn(a.cross(b, c)) == (cr > 0) - (cr < 0));
    CHECK(a.cross(b) == a.x*b.y - a.y*b.x);
    CHECK(a.dot(b) == a.x*b.x + a.y*b.y);
    CHECK((b - a).norm2() == (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
    CHECK(((a < b) == (make_pair(a.x,a.y) < make_pair(b.x,b.y))));
    CHECK((a == b) == (a.x == b.x && a.y == b.y));
    P s = a + b - b; CHECK(s == a);
    CHECK((a * 3).x == 3 * a.x);
  }
  PD p{3, 4}; CHECK(fabsl(p.len() - 5) < 1e-12); CHECK(fabsl((p/2).x - 1.5) < 1e-12);
  // extremes: coordinates +-1e9 diff 2e9, norm2 of diff fits
  P a{-1000000000, -1000000000}, b{1000000000, 1000000000};
  CHECK((b - a).norm2() == 8000000000000000000LL);
  CHECK(a.cross(b, P{1000000000, -1000000000}) < 0);
  DONE();
}
