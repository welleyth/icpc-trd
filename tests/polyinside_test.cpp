#include "common.h"
#include "../src/5-geom/point.cpp"
#include "../src/5-geom/segments.cpp"
#include "../src/5-geom/polygon.cpp"
#include "../src/5-geom/convex.cpp"
#include "../src/5-geom/polyinside.cpp"
mt19937 rng(5);
bool properX(P a, P b, P c, P d) {
  return sgn(a.cross(b, c)) * sgn(a.cross(b, d)) < 0 && sgn(c.cross(d, a)) * sgn(c.cross(d, b)) < 0; }
bool simple(const vector<P>& v) {        // no two edges share points except adjacent at endpoint
  int n = sz(v);
  if (abs(area2(v)) == 0) return false;
  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (v[i] == v[j]) return false;
  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    P a = v[i], b = v[(i + 1) % n], c = v[j], d = v[(j + 1) % n];
    bool adj = (j == i + 1) || (i == 0 && j == n - 1);
    if (!adj) { if (segInter(a, b, c, d)) return false; }
    else { // adjacent: only the shared vertex may be common -> not collinear overlapping
      P sh = (j == i + 1) ? b : a, o1 = (j == i + 1) ? a : b, o2 = (j == i + 1) ? d : c;
      if (sh.cross(o1, o2) == 0 && (o1 - sh).dot(o2 - sh) > 0) return false;
    }
  }
  return true; }
vector<P> randPoly(int C) {
  while (true) { int n = rng() % 5 + 3; vector<P> v(n); for (auto& p : v) p = {(ll)(rng() % (C + 1)), (ll)(rng() % (C + 1))};
    if (simple(v)) return v; } }
// brute: sample rational points (step 1/S) inside/on a, require inside/on b
bool brute(const vector<P>& a, const vector<P>& b, int C) {
  const int S = 24; vector<P> A = a, B = b; for (auto& p : A) p = p * S; for (auto& p : B) p = p * S;
  for (ll x = 0; x <= C * S; x++) for (ll y = 0; y <= C * S; y++) { P q{x, y}; if (inPoly(A, q) && !inPoly(B, q)) return false; }
  return true; }
int main() {
  int cnt[2] = {0, 0}, bad = 0;
  for (int it = 0; it < 20000; it++) {
    int C = 4; auto a = randPoly(C), b = randPoly(C);
    if (rng() % 3 == 0) { auto h = hull(b); if (sz(h) >= 3) b = h; }
    if (rng() % 4 == 0) a = b;          // identical
    bool r = polyInside(a, b), e = brute(a, b, C);
    cnt[r]++;
    if (r != e) { bad++; if (bad <= 5) { printf("MISMATCH ours=%d brute=%d\nA:", r, e); for (P p : a) printf(" (%lld,%lld)", p.x, p.y); printf("\nB:"); for (P p : b) printf(" (%lld,%lld)", p.x, p.y); puts(""); } }
  }
  printf("inside=%d outside=%d mismatches=%d\n", cnt[1], cnt[0], bad);
  return bad != 0; }
