#include "common.h"
#include "../src/5-geom/point.cpp"
#include "../src/5-geom/segments.cpp"
#include "../src/5-geom/polygon.cpp"
#include "../src/5-geom/convex.cpp"
#include "../src/5-geom/mec.cpp"
#include "chk.h"
typedef long double ld;
int main() {
  // MEC
  for (int iter = 0; iter < 20000; iter++) {
    int n = rnd(1, 30); ll R = iter % 3 == 0 ? 5 : iter % 3 == 1 ? 10000 : 1000000000;
    int mode = rnd(0, 4);
    vector<PD> p(n);
    ll x0 = rnd(-R, R), y0 = rnd(-R, R), dx = rnd(-3, 3), dy = rnd(-3, 3);
    for (int i = 0; i < n; i++) {
      if (mode == 0) p[i] = {(ld)x0, (ld)y0};
      else if (mode == 1) { ll t = rnd(-R/4, R/4)/3; p[i] = {(ld)(x0 + dx*t), (ld)(y0 + dy*t)}; }
      else if (mode == 2) p[i] = {(ld)rnd(-R, R), (ld)(i % 2 ? y0 : y0 + 1)};
      else p[i] = {(ld)rnd(-R, R), (ld)rnd(-R, R)};
    }
    if (mode == 4) for (auto& q : p) { q.x = (ld)((ll)q.x % 7 * (R/7)); q.y = (ld)((ll)q.y % 5 * (R/7)); }
    auto [c, r] = mec(p);
    ld best = 1e30L;
    auto test = [&](PD cc, ld rr) {
      for (auto& q : p) if ((q - cc).len() > rr * (1 + 1e-9L) + 1e-9L) return;
      best = min(best, rr); };
    for (int i = 0; i < n; i++) {
      test(p[i], 0);
      for (int j = i+1; j < n; j++) {
        PD cc = (p[i] + p[j]) / 2; test(cc, (p[i]-cc).len());
        for (int k = j+1; k < n; k++) {
          ld cr = (p[j]-p[i]).cross(p[k]-p[i]);
          if (fabsl(cr) < 0.5L) continue;  // integer coords: exact collinear => 0
          PD c3 = circumcenter(p[i], p[j], p[k]); test(c3, (p[i]-c3).len());
        }
      }
    }
    CHECK(fabsl(r - best) <= 1e-8L * max<ld>(1, best));
    for (auto& q : p) CHECK((q - c).len() <= r * (1 + 1e-9L) + 1e-9L);
    CHECK(isfinite((double)r) && isfinite((double)c.x));
  }
  // inConvex
  for (int iter = 0; iter < 100000; iter++) {
    ll R = iter % 3 == 0 ? 3 : iter % 3 == 1 ? 30 : 1000000000;
    int n = rnd(1, iter % 5 == 0 ? 2 : 12);
    vector<P> pts(n);
    for (auto& q : pts) q = {rnd(-R, R), rnd(-R, R)};
    if (R > 100 && rnd(0, 1)) for (auto& q : pts) { q.x = (rnd(0,1)? R : -R); if (rnd(0,1)) q.y = -R; }
    if (iter % 11 == 0) for (auto& q : pts) q.y = 7;
    auto h = hull(pts);
    vector<P> qs;
    for (int t = 0; t < 15; t++) qs.push_back({rnd(-R, R), rnd(-R, R)});
    for (int t = 0; t < 4; t++) qs.push_back({rnd(-R/3-2, R/3+2), rnd(-R/3-2, R/3+2)});
    for (P v : h) qs.push_back(v);
    for (int i = 0; i < sz(h) && sz(h) > 1; i++) {
      P a = h[i], b = h[(i+1)%sz(h)];
      qs.push_back((a + b) / 2);  // may be non-lattice edge midpoint
      qs.push_back(a + (b - a) * 0);
      ll g = __gcd(abs(b.x-a.x), abs(b.y-a.y));
      if (g > 1) qs.push_back(a + (b - a) / g);
      qs.push_back(a + (b - a) / 3);
      qs.push_back(b + (b - a));
      qs.push_back(a - (b - a));
      for (int d = -1; d <= 1; d++) qs.push_back({(a.x+b.x)/2 + d, (a.y+b.y)/2 + d});
    }
    for (P q : qs) {
      if (abs(q.x) > 2000000000LL || abs(q.y) > 2000000000LL) continue;
      if (R == 1000000000 && (abs(q.x) > 1000000000 || abs(q.y) > 1000000000)) continue;
      CHECK(inConvex(h, q) == inPoly(h, q)); }
    // fix: inPoly with n=1,2 hull: onSeg handles; ok
  }
  // closestPair
  for (int iter = 0; iter < 60000; iter++) {
    ll R = iter % 4 == 0 ? 3 : iter % 4 == 1 ? 1000 : 1000000000;
    int n = rnd(2, iter % 50 == 0 ? 300 : 12), mode = rnd(0, 4);
    vector<P> p(n);
    for (auto& q : p) {
      q = {rnd(-R, R), rnd(-R, R)};
      if (mode == 1) q.x = 0; else if (mode == 2) q.y = -R;
      else if (mode == 3) { q.x = rnd(0,1) ? R : -R; if (rnd(0,1)) q.y = -q.y; }
    }
    if (mode == 4 && n > 2) p[1] = p[0];
    ll best = LLONG_MAX;
    for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++) {
      ll dx = p[i].x-p[j].x, dy = p[i].y-p[j].y; best = min(best, dx*dx+dy*dy); }
    CHECK(closestPair(p) == best);
  }
  DONE();
}
