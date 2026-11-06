#include "common.h"
#include "../src/3-graph/lca.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 20000; iter++) {
    int n = rnd(1, 40);
    vector<vi> g(n); vi par(n, -1);
    // random labels
    vi lab(n); iota(all(lab), 0); shuffle(all(lab), rng_);
    int shape = rnd(0, 2);
    for (int i = 1; i < n; i++) {
      int pp = shape == 0 ? rnd(0, i-1) : shape == 1 ? i-1 : max(0, i-1-rnd(0,2));
      g[lab[i]].push_back(lab[pp]); g[lab[pp]].push_back(lab[i]);
    }
    int root = lab[0];
    if (rnd(0, 1)) root = rnd(0, n-1);
    // brute: parent/depth by BFS from root
    vi dep(n, -1); dep[root] = 0; vi q{root};
    for (int i = 0; i < sz(q); i++) for (int v : g[q[i]])
      if (dep[v] < 0) { dep[v] = dep[q[i]]+1; par[v] = q[i]; q.push_back(v); }
    LCA L(g, root);
    for (int t = 0; t < 30; t++) {
      int a = rnd(0, n-1), b = rnd(0, n-1);
      set<int> anc; for (int x = a; x >= 0; x = par[x]) anc.insert(x);
      int x = b; while (!anc.count(x)) x = par[x];
      CHECK(L.lca(a, b) == x);
      CHECK(L.dist(a, b) == dep[a] + dep[b] - 2 * dep[x]);
      int k = rnd(0, dep[a]); int y = a;
      for (int i = 0; i < k; i++) y = par[y];
      CHECK(L.kth(a, k) == y);
    }
  }
  DONE();
}
