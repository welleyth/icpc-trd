// twice the signed area (> 0 if counter-clockwise)
ll area2(const vector<P>& pg) {
  ll s = 0;
  for (int i = 0, n = sz(pg); i < n; i++)
    s += pg[i].cross(pg[(i + 1) % n]);
  return s; }
// 0 = outside, 1 = inside, 2 = on boundary. O(n), any polygon
int inPoly(const vector<P>& pg, P p) {
  int n = sz(pg); bool in = false;
  for (int i = 0; i < n; i++) {
    P a = pg[i], b = pg[(i + 1) % n];
    if (onSeg(p, a, b)) return 2;
    if ((a.y > p.y) != (b.y > p.y) &&
        ((b - a).cross(p - a) > 0) == (b.y > a.y)) in = !in;
  }
  return in; }
// Convex hull (monotone chain), CCW, no collinear points.
vector<P> hull(vector<P> pts) {
  sort(all(pts)); pts.erase(unique(all(pts)), pts.end());
  if (sz(pts) < 3) return pts;
  vector<P> h(2 * sz(pts)); int k = 0;
  for (int it = 0; it < 2; it++, reverse(all(pts))) {
    int start = k;
    for (P p : pts) {
      while (k >= start + 2 &&
             h[k - 2].cross(h[k - 1], p) <= 0) k--;
      h[k++] = p;
    }
    k--;
  }
  h.resize(k);
  return h; }
// max squared distance between two points (rotating calipers
// on the hull h, CCW)
ll diameter2(const vector<P>& h) {
  int n = sz(h); ll best = 0;
  if (n < 2) return 0;
  for (int i = 0, j = 1 % n; i < n; i++) {
    while ((h[(i + 1) % n] - h[i]).cross(
               h[(j + 1) % n] - h[j]) > 0) j = (j + 1) % n;
    best = max({best, (h[i] - h[j]).norm2(),
                (h[(i + 1) % n] - h[j]).norm2()});
  }
  return best; }
// Pick: A = I + B/2 - 1, B = sum gcd(|dx|, |dy|) over edges.
