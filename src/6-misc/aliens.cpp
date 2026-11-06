// ALIENS TRICK (Lagrangian relaxation / "WQS binary search").
// Want f(K) = min cost using EXACTLY K items (segments,
// groups, chosen elements ...). Conditions:
//  1. f is convex in k: f(k+1) - f(k) is non-decreasing.
//     (Check by brute force on small random tests! Usual
//     sources: Monge / quadrangle-inequality partition DP,
//     problems that are min-cost flows, "pick k" greedy.)
//  2. Without the count limit, for a penalty lam per item you
//     can compute g(lam) = min_k f(k) + lam*k fast, AND the
//     SMALLEST k achieving that minimum (break ties by count).
// Then cnt(lam) is non-increasing; take the smallest lam with
// cnt(lam) <= K; answer = g(lam) - lam*K (use K, not cnt!).
// Integer costs => integer slopes => integer lam suffices;
// lam range: [-(max |f(k+1)-f(k)|) - 1, max ... + 1].
// For max-profit: negate, or flip the tie-break and search.
pair<ll, int> solveLam(ll lam);  // {g(lam), smallest count}
ll aliens(int K, ll lo, ll hi) {
  while (lo < hi) {
    ll mid = lo + (hi - lo) / 2;
    if (solveLam(mid).second <= K) hi = mid; else lo = mid + 1;
  }
  return solveLam(lo).first - lo * K; }
// Example solveLam (split a into groups, cost(j, i) per group
// + lam, compare pairs {value, count} lexicographically):
//   dp[0] = {0, 0}; dp[i] = min over j < i of
//   {dp[j].first + cost(j, i) + lam, dp[j].second + 1}.
