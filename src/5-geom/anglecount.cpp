// Angular sweep (needs angleLess): for every vertex v sort the
// other points by angle, then two pointers over the doubled
// order. Example: # acute triangles, no 3 collinear,
// O(n^2 log n). A non-acute triangle has exactly ONE angle
// >= 90: count pairs (u, w) with angle(u, v, w) in [90, 180).
ll countAcute(const vector<P>& a) {
  int n = sz(a); ll bad = 0;
  for (int v = 0; v < n; v++) {
    vector<P> d;
    for (int i = 0; i < n; i++)
      if (i != v) d.push_back(a[i] - a[v]);
    sort(all(d), angleLess);
    int m = sz(d), r1 = 0, r2 = 0;  // (i, r1): ccw angle < 180
    for (int i = 0; i < m; i++) {   // [r2, r1): angle >= 90
      r1 = max(r1, i + 1); r2 = max(r2, i + 1);
      while (r1 < i + m && d[i].cross(d[r1 % m]) > 0) r1++;
      while (r2 < r1 && d[i].dot(d[r2 % m]) > 0) r2++;
      bad += r1 - r2;
    }
  }
  return (ll)n * (n - 1) * (n - 2) / 6 - bad; }
