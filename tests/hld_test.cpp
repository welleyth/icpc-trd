#include "common.h"
#include "../src/3-graph/hld.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 20000; iter++) {
    int n = rnd(1, 30);
    vector<vi> g(n); vi par(n, -1);
    int shape = rnd(0, 2);
    vi lab(n); iota(all(lab), 0); shuffle(all(lab), rng_);
    for (int i = 1; i < n; i++) {
      int pp = shape == 0 ? rnd(0, i-1) : shape == 1 ? i-1 : max(0, i-1-rnd(0,2));
      g[lab[i]].push_back(lab[pp]); g[lab[pp]].push_back(lab[i]); }
    int root = rnd(0, n-1);
    HLD h(g, root);
    vi dep(n, -1), pr(n, -1); dep[root] = 0; vi q{root};
    for (int i = 0; i < sz(q); i++) for (int v : g[q[i]])
      if (dep[v] < 0) { dep[v]=dep[q[i]]+1; pr[v]=q[i]; q.push_back(v); }
    // pos is a permutation
    vi seen(n); for (int v = 0; v < n; v++) seen[h.pos[v]]++;
    for (int i = 0; i < n; i++) CHECK(seen[i] == 1);
    // subtree range
    for (int v = 0; v < n; v++) {
      int cnt = 0;
      for (int u = 0; u < n; u++) {
        bool in = false; for (int x = u; x >= 0; x = pr[x]) if (x == v) in = true;
        bool inr = h.pos[u] >= h.pos[v] && h.pos[u] < h.pos[v] + h.size[v];
        CHECK(in == inr); cnt += in; }
      CHECK(cnt == h.size[v]);
    }
    for (int t = 0; t < 20; t++) {
      int a = rnd(0, n-1), b = rnd(0, n-1);
      set<int> pa; for (int x = a; x >= 0; x = pr[x]) pa.insert(x);
      int l = b; while (!pa.count(l)) l = pr[l];
      set<int> expv;
      for (int x = a; x != l; x = pr[x]) expv.insert(x);
      for (int x = b; x != l; x = pr[x]) expv.insert(x);
      set<int> expe = expv; expv.insert(l);
      vi cover(n);
      h.path(a, b, [&](int lo, int hi) {
        CHECK(lo < hi); for (int i = lo; i < hi; i++) cover[i]++; });
      for (int v = 0; v < n; v++)
        CHECK(cover[h.pos[v]] == (int)expv.count(v));
      // edge version: skip LCA via pos[a]+1 in last step
      vi cov2(n); int last = 0;
      vector<pii> rs;
      h.path(a, b, [&](int lo, int hi) { rs.push_back({lo, hi}); });
      // last call has the LCA at its lo
      rs.back().first++;
      for (auto [lo, hi] : rs) for (int i = lo; i < hi; i++) cov2[i]++;
      for (int v = 0; v < n; v++)
        CHECK(cov2[h.pos[v]] == (int)expe.count(v));
      (void)last;
    }
  }
  DONE();
}
