#include "common.h"
#include "../src/5-geom/point.cpp"
#include "../src/5-geom/angle.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 100000; iter++) {
    int R = iter % 2 ? 3 : 1000;
    vector<P> v; int n = rnd(1, 9);
    for (int i = 0; i < n; i++) { P p{rnd(-R,R), rnd(-R,R)}; if (p.x==0&&p.y==0) p.x = 1; v.push_back(p); }
    auto ang = [&](P p) { long double a = atan2l(p.y, p.x); if (a < 0) a += 2*acosl(-1); return a; };
    auto eq = [&](P a, P b) { return a.cross(b) == 0 && a.dot(b) > 0; };
    sort(all(v), angleLess);
    for (int i = 0; i + 1 < n; i++) {
      CHECK(!angleLess(v[i+1], v[i]));
      bool e = eq(v[i], v[i+1]);
      CHECK(e == (!angleLess(v[i], v[i+1]) && !angleLess(v[i+1], v[i])));
      if (!e) CHECK(ang(v[i]) < ang(v[i+1]) + 1e-18L);
    }
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
      bool l = angleLess(v[i], v[j]);
      if (eq(v[i], v[j])) CHECK(!l);
      else CHECK(l == (ang(v[i]) < ang(v[j])));
    }
  }
  // axis directions order
  vector<P> v{{0,-1},{-1,0},{0,1},{1,0},{1,1}};
  sort(all(v), angleLess);
  CHECK(v[0] == (P{1,0}) && v[1] == (P{1,1}) && v[2] == (P{0,1}) && v[3] == (P{-1,0}) && v[4] == (P{0,-1}));
  // huge
  P a{1000000000,1}, b{1000000000,2}, c{-1000000000,-1000000000};
  CHECK(angleLess(a, b)); CHECK(!angleLess(b, a)); CHECK(angleLess(b, c));
  P d{-1000000000, 1}, e{-1000000000, 2};
  CHECK(angleLess(e, d)); CHECK(!angleLess(d, e));
  DONE();
}
