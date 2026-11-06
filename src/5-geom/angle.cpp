// Sort vectors by polar angle in [0, 2pi) from the +x axis.
bool upper(P a) { return a.y > 0 || (a.y == 0 && a.x > 0); }
bool angleLess(P a, P b) {
  if (upper(a) != upper(b)) return upper(a);
  return a.cross(b) > 0; }
// sort(all(v), angleLess);  (no zero vectors!)
// Equal angle: !angleLess(a,b) && !angleLess(b,a).
