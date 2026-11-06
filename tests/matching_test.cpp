#include "common.h"
#include "../src/3-graph/matching.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 30000; iter++) {
    int n = rnd(1, 6), m = rnd(1, 6), e = rnd(0, 14);
    Kuhn k(n, m); vector<vi> adj(n);
    for (int i = 0; i < e; i++) {
      int u = rnd(0, n-1), v = rnd(0, m-1);
      k.g[u].push_back(v); adj[u].push_back(v); }
    int r = k.run();
    // brute: dp over mask of right vertices
    vi best(1 << m, -1000); 
    vector<int> dp(1 << m, 0);
    for (int u = 0; u < n; u++) {
      vector<int> nd = dp;
      for (int mask = 0; mask < 1 << m; mask++) for (int v : adj[u])
        if (!(mask >> v & 1)) nd[mask | 1 << v] = max(nd[mask | 1 << v], dp[mask] + 1);
      dp = nd; }
    int br = *max_element(all(dp));
    CHECK(r == br);
    int cnt = 0; vi usedL(n);
    for (int v = 0; v < m; v++) if (k.mt[v] >= 0) {
      cnt++; int u = k.mt[v]; CHECK(!usedL[u]); usedL[u] = 1;
      CHECK(find(all(adj[u]), v) != adj[u].end()); }
    CHECK(cnt == r);
  }
  DONE();
}
