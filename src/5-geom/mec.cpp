// Minimum enclosing circle (Welzl), expected O(n) thanks to
// the shuffle. Returns {center, radius}.
// center of the circle through a, b, c (not collinear)
PD circumcenter(PD a, PD b, PD c) {
  PD u = b - a, w = c - a, v = u * w.norm2() - w * u.norm2();
  return a + PD{-v.y, v.x} / (2 * u.cross(w)); }
pair<PD, long double> mec(vector<PD> p) {
  shuffle(all(p), mt19937(1));
  PD c = p[0]; long double r = 0, E = 1 + 1e-12;
  auto out = [&](PD q) { return (q - c).len() > r * E; };
  for (int i = 0; i < sz(p); i++) if (out(p[i])) {
    c = p[i]; r = 0;
    for (int j = 0; j < i; j++) if (out(p[j])) {
      c = (p[i] + p[j]) / 2; r = (p[i] - c).len();
      for (int k = 0; k < j; k++) if (out(p[k])) {
        c = circumcenter(p[i], p[j], p[k]);
        r = (p[i] - c).len();
      }
    }
  }
  return {c, r}; }
