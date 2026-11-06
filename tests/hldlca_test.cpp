#include "common.h"
#include "../src/3-graph/hld.cpp"
#include "chk.h"
#include "gen_tree.h"
int main() {
  for (int iter = 0; iter < 20000; iter++) {
    int n = rnd(1, iter % 50 == 0 ? 300 : 25), root; vi pr, dep;
    auto g = randTree(n, pr, dep, root);
    HLD h(g, root);
    for (int t = 0; t < 30; t++) {
      int a = rnd(0, n-1), b = rnd(0, n-1);
      CHECK(h.lca(a, b) == bfLca(a, b, pr, dep));
      CHECK(h.lca(a, a) == a);
    }
    // path graph
  }
  DONE();
}
