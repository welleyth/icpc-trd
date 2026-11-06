// Binary search on the answer: first x in [lo, hi] with
// ok(x) true (ok monotone false..true); hi+1 if none.
ll firstTrue(ll lo, ll hi, function<bool(ll)> ok) {
  hi++;
  while (lo < hi) {
    ll mid = lo + (hi - lo) / 2;
    ok(mid) ? hi = mid : lo = mid + 1;
  }
  return lo; }
// Reals: for (int it = 0; it < 100; it++) { m = (l+r)/2; ... }
// Ternary search (max of unimodal f on integers):
//   while (hi - lo > 2) {
//     m1 = lo + (hi - lo) / 3; m2 = hi - (hi - lo) / 3;
//     f(m1) < f(m2) ? lo = m1 : hi = m2; }
//   then check every x in [lo, hi].
// Two pointers: for r: add(r); while (bad) remove(l++);
// Parallel binary search: all queries' [lo,hi] at once,
// one sweep per round (log rounds), e.g. with DSU.
