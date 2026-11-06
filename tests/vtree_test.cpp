#include "common.h"
#include "../src/3-graph/hld.cpp"
#include "../src/3-graph/virtualtree.cpp"
#include "chk.h"
#include "gen_tree.h"
int main() {
  for (int iter = 0; iter < 30000; iter++) {
    int n = rnd(1, iter % 50 == 0 ? 200 : 20), root; vi pr, dep;
    auto g = randTree(n, pr, dep, root);
    HLD h(g, root);
    // pos is a DFS preorder: parent first, subtree contiguous
    for (int v = 0; v < n; v++) {
      if (v != root) CHECK(h.pos[pr[v]] < h.pos[v]);
      for (int u = 0; u < n; u++) {
        bool in = false;
        for (int x = u; x >= 0; x = pr[x]) in |= x == v;
        CHECK(in == (h.pos[u] >= h.pos[v] &&
                     h.pos[u] < h.pos[v] + h.size[v])); }
    }
    for (int t = 0; t < 10; t++) {
      int k = rnd(1, min(2 * n, 8)); vi ks;
      for (int i = 0; i < k; i++)
        ks.push_back(t == 0 && i == 0 ? root : rnd(0, n-1));
      if (t == 1) ks.assign(1, rnd(0, n-1));
      set<int> ex(all(ks));
      for (int a : ks) for (int b : ks)
        ex.insert(bfLca(a, b, pr, dep));
      vi vpar(n, -2);
      vi res = virtualTree(ks, h.pos,
        [&](int a, int b) { return h.lca(a, b); }, vpar);
      CHECK(set<int>(all(res)) == ex);
      CHECK(sz(res) == sz(ex));
      // root of VT = shallowest
      int rt = *min_element(all(ex), [&](int a, int b){return dep[a]<dep[b];});
      CHECK(res[0] == rt);
      for (int i = 0; i + 1 < sz(res); i++)
        CHECK(h.pos[res[i]] < h.pos[res[i+1]]);
      for (int v : res) {
        int e = -1;
        for (int x = pr[v]; x >= 0; x = pr[x])
          if (ex.count(x)) { e = x; break; }
        CHECK(vpar[v] == e);
      }
    }
  }
  DONE();
}
