// LIS, strictly increasing, O(n log n). Non-decreasing:
// upper_bound. Length = sz(d).
int lis(const vi& a) {
  vi d;
  for (int x : a) {
    auto it = lower_bound(all(d), x);
    if (it == d.end()) d.push_back(x); else *it = x;
  }
  return sz(d); }
// 0/1 knapsack reachability with bitset (W up to 1e6):
//   bitset<W + 1> b; b[0] = 1; for (w : items) b |= b << w;
// Subset sums with many equal items: split count c into
// 1, 2, 4, ..., rest (binary splitting) -> O(W sqrt(S)/64).

// Subset DP (Hamiltonian path), O(2^n n^2):
//   dp[mask][v] = path through mask ending at v.
//   dp[1<<v][v] = 1; for mask, v in mask, u not in mask:
//     dp[mask | 1<<u][u] |= dp[mask][v] && adj[v][u].
// Submasks of m (all masks: O(3^n) total):
//   for (int s = m; s; s = (s - 1) & m) { ... }  // + s = 0
// SOS: f[m] = sum over submasks s of m of a[s]. O(2^n n)
//   for i in 0..n-1: for m: if (m >> i & 1) f[m] += f[m^1<<i];

// Digit DP: count x in [0, N] with property. Digits of N
// most significant first; memo[pos][state] for !tight only.
//   ll go(int pos, int st, bool tight, bool started) {
//     if (pos == len) return good(st, started);
//     ll &m = memo[pos][st]; if (!tight && started && m >= 0)
//       return m;
//     ll r = 0; int lim = tight ? dig[pos] : 9;
//     for (int d = 0; d <= lim; d++)
//       r += go(pos+1, next(st, d), tight && d == lim,
//               started || d);
//     if (!tight && started) m = r; return r; }
//   Answer on [L, R] = f(R) - f(L - 1).

// Divide & conquer optimisation: dp_new[i] =
// min_{j < i} dp_old[j] + cost(j, i) when opt(i) is monotone.
// O(k n log n). Call solve(1, n, 0, n - 1).
vector<ll> dpOld, dpNew; ll cost(int j, int i);
void solve(int l, int r, int optl, int optr) {
  if (l > r) return;
  int m = (l + r) / 2, best = -1; ll bv = LLONG_MAX;
  for (int j = optl; j <= min(m - 1, optr); j++) {
    ll v = dpOld[j] + cost(j, m);
    if (v < bv) bv = v, best = j;
  }
  dpNew[m] = bv;
  solve(l, m - 1, optl, best); solve(m + 1, r, best, optr); }
