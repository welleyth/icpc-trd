// p on segment [a, b] (inclusive)?
bool onSeg(P p, P a, P b) {
  return p.cross(a, b) == 0 && (a - p).dot(b - p) <= 0; }
// do closed segments [a,b] and [c,d] intersect?
bool segInter(P a, P b, P c, P d) {
  int d1 = sgn(a.cross(b, c)), d2 = sgn(a.cross(b, d));
  int d3 = sgn(c.cross(d, a)), d4 = sgn(c.cross(d, b));
  if (d1 * d2 < 0 && d3 * d4 < 0) return true;
  return onSeg(c, a, b) || onSeg(d, a, b) ||
         onSeg(a, c, d) || onSeg(b, c, d); }
// intersection point of LINES ab and cd (not parallel)
PD lineInter(PD a, PD b, PD c, PD d) {
  return a + (b - a) * ((c - a).cross(d - c) /
                        (b - a).cross(d - c)); }
// distance from p to segment [a, b]
long double segDist(PD p, PD a, PD b) {
  PD ab = b - a;
  long double t = ab.norm2() == 0 ? 0 :
      max<long double>(0, min<long double>(1,
          (p - a).dot(ab) / ab.norm2()));
  return (p - (a + ab * t)).len(); }
// distance from p to LINE ab = |cross| / |ab|
