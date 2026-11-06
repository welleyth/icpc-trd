// Binary lifting over any successor function nxt with costs
// c[v] (cost of one step from v): up[k][v] = 2^k-th successor,
// cs[k][v] = cost of those 2^k steps, capped at CAP.
// maxJumps(v, B) = {steps, end vertex}: most steps of total
// cost <= B (need B < CAP).
// Terminal vertex: nxt[t] = t with cost CAP (blocks jumps).
// Memory L * n: choose L = log2(max steps) + 1.
const ll CAP = 2e18;
struct Lift {
  int L; vector<vi> up; vector<vector<ll>> cs;
  Lift(const vi& nxt, const vector<ll>& c, int L)
    : L(L), up(L, nxt), cs(L, c) {
    for (int k = 1; k < L; k++)
      for (int v = 0; v < sz(nxt); v++) {
        int m = up[k - 1][v];
        up[k][v] = up[k - 1][m];
        cs[k][v] = min(CAP, cs[k - 1][v] + cs[k - 1][m]);
      } }
  pair<ll, int> maxJumps(int v, ll B) {
    ll t = 0;
    for (int k = L - 1; k >= 0; k--)
      if (cs[k][v] <= B)
        B -= cs[k][v], t += 1LL << k, v = up[k][v];
    return {t, v}; }
};
// Tree version: nxt = parent; "climb while the weight sum
// fits", or "first ancestor with value > x" (store max).
