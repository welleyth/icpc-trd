// Circle (c, r) intersect line ab. 0, 1 or 2 points.
const long double EPS = 1e-9;
vector<PD> circleLine(PD c, long double r, PD a, PD b) {
  PD ab = b - a, p = a + ab * ((c - a).dot(ab) / ab.norm2());
  long double h2 = r * r - (c - p).norm2();
  if (h2 < -EPS) return {};
  if (h2 < EPS) return {p};
  PD d = ab * (sqrtl(h2) / ab.len());
  return {p - d, p + d}; }
// Two circles (equal circles -> empty: handle separately).
vector<PD> circleCircle(PD a, long double r1, PD b,
                        long double r2) {
  PD d = b - a; long double d2 = d.norm2();
  if (d2 < EPS) return {};
  long double x = (d2 + r1 * r1 - r2 * r2) / 2;
  long double h2 = r1 * r1 - x * x / d2;
  if (h2 < -EPS) return {};
  PD p = a + d * (x / d2);
  if (h2 < EPS) return {p};
  PD perp = PD{-d.y, d.x} * sqrtl(h2 / d2);
  return {p - perp, p + perp}; }
