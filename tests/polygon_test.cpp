#include "common.h"
#include "../src/5-geom/point.cpp"
#include "../src/5-geom/segments.cpp"
#include "../src/5-geom/polygon.cpp"
#include "chk.h"
typedef __int128 LL;
LL area2b(const vector<P>& p) { LL s = 0; int n = sz(p);
  for (int i = 0; i < n; i++) s += (LL)p[i].x * p[(i+1)%n].y - (LL)p[i].y * p[(i+1)%n].x;
  return s; }
int ori(P a, P b, P c) { LL v = (LL)(b.x-a.x)*(c.y-a.y) - (LL)(b.y-a.y)*(c.x-a.x); return (v>0)-(v<0); }
bool onS(P p, P a, P b) { return ori(a,b,p)==0 && min(a.x,b.x)<=p.x && p.x<=max(a.x,b.x) && min(a.y,b.y)<=p.y && p.y<=max(a.y,b.y); }
bool inTri(P p, P a, P b, P c) {
  int o1 = ori(a,b,p), o2 = ori(b,c,p), o3 = ori(c,a,p);
  bool neg = o1<0||o2<0||o3<0, pos = o1>0||o2>0||o3>0; return !(neg&&pos); }
bool simple(const vector<P>& v) {
  int n = sz(v);
  for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++) if (v[i]==v[j]) return false;
  for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++) {
    P a=v[i],b=v[(i+1)%n],c=v[j],d=v[(j+1)%n];
    if (j == i+1 || (i==0 && j==n-1)) {
      // adjacent: must not overlap beyond the shared point
      if (j == i+1) { if (onS(d,a,b)&&!(d==a)) return false; if (onS(a,c,d)&&!(a==c)) return false; if (onS(a,c,d)) {} }
      // simple overlap test: collinear and folding back
      P sh = (j==i+1)? c : a, o1 = (j==i+1)? a : b, o2 = (j==i+1)? d : d;
      if (j==i+1) { sh=c; o1=a; o2=d; } else { sh=a; o1=b; o2=c; }
      if (ori(sh,o1,o2)==0 && (o1-sh).dot(o2-sh) > 0) return false;
      continue; }
    if (segInter(a,b,c,d)) return false; }
  return true; }
// independent point-in-simple-polygon: ray in irrational-ish direction
int inBrute(const vector<P>& v, P p) {
  int n = sz(v);
  for (int i = 0; i < n; i++) if (onS(p, v[i], v[(i+1)%n])) return 2;
  long double dx = 1, dy = 0.00012345678L; int cnt = 0;
  for (int i = 0; i < n; i++) {
    PD a{(long double)v[i].x - p.x, (long double)v[i].y - p.y};
    PD b{(long double)v[(i+1)%n].x - p.x, (long double)v[(i+1)%n].y - p.y};
    // intersect ray t*(dx,dy), t>0, with segment a + u(b-a)
    long double ex = b.x-a.x, ey = b.y-a.y;
    long double den = dx*ey - dy*ex; if (den == 0) continue;
    long double t = (a.x*ey - a.y*ex) / den, u = (a.x*dy - a.y*dx) / den;
    if (t > 0 && u >= 0 && u < 1) cnt++; }
  return cnt & 1; }
int main() {
  // area2 / inPoly on random simple polygons
  int simples = 0;
  for (int iter = 0; iter < 200000; iter++) {
    int k = rnd(3, 7), R = 4; vector<P> v;
    for (int i = 0; i < k; i++) v.push_back({rnd(-R,R), rnd(-R,R)});
    if (!simple(v)) continue;
    simples++;
    CHECK((LL)area2(v) == area2b(v));
    for (int t = 0; t < 10; t++) {
      P p{rnd(-R-1,R+1), rnd(-R-1,R+1)};
      CHECK(inPoly(v, p) == inBrute(v, p)); }
    for (P q : v) CHECK(inPoly(v, q) == 2);
    auto w = v; reverse(all(w)); CHECK(area2(w) == -area2(v));
  }
  printf("simple polygons tested: %d\n", simples);
  // hull
  for (int iter = 0; iter < 100000; iter++) {
    int n = rnd(0, 9), R = iter % 3 == 0 ? 1 : iter % 3 == 1 ? 3 : 8;
    vector<P> pts; for (int i = 0; i < n; i++) pts.push_back({rnd(-R,R), rnd(-R,R)});
    auto h = hull(pts);
    set<pair<ll,ll>> uniq; for (P p : pts) uniq.insert({p.x,p.y});
    vector<P> u; for (auto [x,y] : uniq) u.push_back({x,y});
    // extreme points brute
    vector<P> ext;
    for (int i = 0; i < sz(u); i++) {
      bool inside = false;
      for (int a = 0; a < sz(u) && !inside; a++) if (a != i)
        for (int b = a; b < sz(u) && !inside; b++) if (b != i) {
          if (a == b) continue;
          if (onS(u[i], u[a], u[b])) inside = true;
          for (int c = b+1; c < sz(u) && !inside; c++) if (c != i && ori(u[a],u[b],u[c]) != 0 && inTri(u[i], u[a], u[b], u[c])) inside = true; }
      if (!inside) ext.push_back(u[i]); }
    set<pair<ll,ll>> hs, es;
    for (P p : h) hs.insert({p.x,p.y});
    for (P p : ext) es.insert({p.x,p.y});
    if (hs != es && fails_ < 3) { for (P p : u) fprintf(stderr, "(%lld,%lld) ", p.x, p.y); fputs("-> hull ", stderr); for (P p : h) fprintf(stderr, "(%lld,%lld) ", p.x, p.y); fputs("\n", stderr); }
    CHECK(hs == es); CHECK(sz(h) == sz(hs));
    int m = sz(h);
    if (m >= 3) {
      CHECK(area2(h) > 0);
      for (int i = 0; i < m; i++) {
        CHECK(ori(h[i], h[(i+1)%m], h[(i+2)%m]) > 0);
        for (P p : u) CHECK(ori(h[i], h[(i+1)%m], p) >= 0); }
    }
    if (sz(u) == 1) CHECK(m == 1);
    if (sz(u) == 2) CHECK(m == 2);
    // diameter
    ll best = 0; for (P a : u) for (P b : u) best = max(best, (a-b).norm2());
    if (n > 0) CHECK(diameter2(h) == best);
  }
  // all identical
  { vector<P> pts(5, P{3, 3}); auto h = hull(pts); CHECK(sz(h) == 1); CHECK(diameter2(h) == 0); }
  { vector<P> pts; CHECK(hull(pts).empty()); }
  { vector<P> pts{{0,0},{1,1},{2,2},{3,3},{1,1}}; auto h = hull(pts); CHECK(sz(h) == 2); CHECK(diameter2(h) == 18); }
  // big coordinates
  for (int iter = 0; iter < 20000; iter++) {
    ll B = 1000000000LL; int n = rnd(1, 30); vector<P> pts;
    for (int i = 0; i < n; i++) {
      auto r = [&]() { int c = rnd(0, 3); if (c == 0) return B; if (c == 1) return -B;
        return (ll)(rng_() % (2*B+1)) - B; };
      pts.push_back({r(), r()}); }
    auto h = hull(pts);
    ll best = 0; for (P a : pts) for (P b : pts) best = max(best, (a-b).norm2());
    CHECK(diameter2(h) == best);
    CHECK((LL)area2(h) == area2b(h)); CHECK(sz(h) < 3 || area2(h) > 0);
    int m = sz(h);
    for (int i = 0; m >= 3 && i < m; i++)
      for (P p : pts) CHECK(ori(h[i], h[(i+1)%m], p) >= 0);
    if (m >= 3) {
      for (P p : pts) CHECK(inPoly(h, p) >= 1); }
  }
  // inPoly with extreme coordinates on big square / diamond
  { vector<P> sq{{-1000000000,-1000000000},{1000000000,-1000000000},{1000000000,1000000000},{-1000000000,1000000000}};
    CHECK(inPoly(sq, P{0,0}) == 1); CHECK(inPoly(sq, P{1000000000,0}) == 2);
    CHECK(inPoly(sq, P{1000000000,1000000000}) == 2); CHECK(inPoly(sq, P{-1000000000,5}) == 2);
    CHECK(area2(sq) == 8000000000000000000LL);
    vector<P> di{{-1000000000,0},{0,-1000000000},{1000000000,0},{0,1000000000}};
    CHECK(inPoly(di, P{999999999,1}) == 2); CHECK(inPoly(di, P{999999999,2}) == 0); CHECK(inPoly(di, P{999999999,0}) == 1);
    CHECK(inPoly(di, P{500000000,500000000}) == 2); CHECK(inPoly(di, P{1000000000,1000000000}) == 0); }
  DONE();
}
