#include "common.h"
#include "../src/5-geom/point.cpp"
#include "../src/5-geom/angle.cpp"
#include "../src/5-geom/anglecount.cpp"
#include "chk.h"
typedef __int128 LL;
LL cr(P a, P b, P c) { return (LL)(b.x-a.x)*(c.y-a.y) - (LL)(b.y-a.y)*(c.x-a.x); }
LL dt(P a, P b, P c) { return (LL)(b.x-a.x)*(c.x-a.x) + (LL)(b.y-a.y)*(c.y-a.y); }
int main() {
  for (int it = 0; it < 20000; it++) {
    int R = (int[]){3, 10, 1000, 1000000000, 1000000000}[it % 5]; int n = rnd(0, it % 50 == 0 ? 60 : 9);
    vector<P> a;
    for (int tries = 0; sz(a) < n && tries < 2000; tries++) {
      P p; if (R >= 1000000000 && rnd(0,2)==0) p = {rnd(0,1) ? -R : R, rnd(0,1) ? -R : R}; else p = {(ll)rnd(-R, R), (ll)rnd(-R, R)};
      if (R == 1000000000 && rnd(0,1)) { p.x = rnd(0,1) ? R - rnd(0,3) : -R + rnd(0,3); }
      bool ok = true; for (int i = 0; i < sz(a) && ok; i++) { if (a[i] == p) ok = false; for (int j = 0; j < i && ok; j++) if (cr(a[i], a[j], p) == 0) ok = false; }
      if (ok) a.push_back(p); }
    n = sz(a); ll br = 0;
    for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++) for (int k = j+1; k < n; k++)
      br += dt(a[i], a[j], a[k]) > 0 && dt(a[j], a[i], a[k]) > 0 && dt(a[k], a[i], a[j]) > 0;
    shuffle(all(a), rng_);
    CHECK(countAcute(a) == br);
  }
  DONE();
}
