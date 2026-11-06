// Point in convex polygon h (CCW, no collinear vertices, as
// from hull()) in O(log n): 0 outside, 1 inside, 2 boundary.
int inConvex(const vector<P>& h, P p) {
  int n = sz(h);
  if (n == 1) return p == h[0] ? 2 : 0;
  if (n == 2) return onSeg(p, h[0], h[1]) ? 2 : 0;
  if (h[0].cross(h[1], p) < 0 || h[0].cross(h[n - 1], p) > 0)
    return 0;
  int lo = 1, hi = n - 1;      // wedge h[0], h[lo], h[lo+1]
  while (hi - lo > 1) {
    int m = (lo + hi) / 2;
    (h[0].cross(h[m], p) >= 0 ? lo : hi) = m;
  }
  int c = sgn(h[lo].cross(h[lo + 1], p));
  if (c < 0) return 0;
  if (c == 0 || onSeg(p, h[0], h[1]) ||
      onSeg(p, h[0], h[n - 1])) return 2;
  return 1; }
// Closest pair: min squared distance, n >= 2, |coord| <= 1e9.
// Sweep by x, keep points with x within sqrt(best). O(n log n)
ll closestPair(vector<P> p) {
  sort(all(p), [](P a, P b) { return a.x < b.x; });
  set<pair<ll, ll>> s;                 // (y, x) in the strip
  ll best = LLONG_MAX;
  for (int i = 0, j = 0; i < sz(p); i++) {
    ll d = (ll)sqrtl(best) + 1;
    while (p[i].x - p[j].x > d) s.erase({p[j].y, p[j].x}), j++;
    for (auto it = s.lower_bound({p[i].y - d, LLONG_MIN});
         it != s.end() && it->first <= p[i].y + d; ++it) {
      ll dx = p[i].x - it->second, dy = p[i].y - it->first;
      best = min(best, dx * dx + dy * dy);
    }
    s.insert({p[i].y, p[i].x});
  }
  return best; }
