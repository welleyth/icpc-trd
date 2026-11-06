// Is simple polygon a inside simple polygon b (boundaries may
// touch)? O(n m log). Idea: boundary of a inside b => a inside
// b (b has no holes). Split every edge of a at the vertices of
// b lying on it; a proper crossing => false; each piece lies
// fully inside or outside, so test its midpoint.
// Points are doubled so midpoints stay integer: needs
// |coord| <= 4e8 (else use Pt<__int128>). Convex b: simply
// check all vertices of a with inConvex (O(n log m)).
bool polyInside(vector<P> a, vector<P> b) {
  for (P& v : a) v = v * 2;
  for (P& v : b) v = v * 2;
  int n = sz(a), m = sz(b);
  for (int i = 0; i < n; i++) {
    P s = a[i], t = a[(i + 1) % n];
    vector<P> cut{s, t};
    for (int j = 0; j < m; j++) {
      P c = b[j], d = b[(j + 1) % m];
      if (sgn(s.cross(t, c)) * sgn(s.cross(t, d)) < 0 &&
          sgn(c.cross(d, s)) * sgn(c.cross(d, t)) < 0)
        return false;                       // proper crossing
      if (onSeg(c, s, t)) cut.push_back(c);
    }
    sort(all(cut), [&](P x, P y) {
      return (x - s).dot(t - s) < (y - s).dot(t - s); });
    for (int k = 0; k + 1 < sz(cut); k++)
      if (!inPoly(b, (cut[k] + cut[k + 1]) / 2)) return false;
  }
  return true; }
