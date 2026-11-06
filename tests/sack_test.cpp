#include "common.h"
#include "../src/3-graph/sack.cpp"
#include "chk.h"
#include "gen_tree.h"
int main() {
  for (int iter = 0; iter < 2000; iter++) {
    int n = rnd(1, iter % 100 == 0 ? 2000 : 30), root; vi pr, dep;
    g = randTree(n, pr, dep, root);
    int C = rnd(1, n);
    col.assign(n, 0); for (int& c : col) c = rnd(1, C);
    ans.assign(n, -1);
    dfs(root, -1);
    vector<set<int>> ex(n);
    for (int v = 0; v < n; v++)
      for (int x = v; x >= 0; x = pr[x]) ex[x].insert(col[v]);
    for (int v = 0; v < n; v++) CHECK(ans[v] == sz(ex[v]));
  }
  // path of 1e5 (recursion depth) and star
  int n = 100000;
  g.assign(n, {}); for (int i = 1; i < n; i++) {
    g[i-1].push_back(i); g[i].push_back(i-1); }
  col.assign(n, 0); for (int& c : col) c = rnd(1, n);
  ans.assign(n, 0); auto t0 = clock(); dfs(0, -1);
  fprintf(stderr, "path %.2fs\n", (double)(clock()-t0)/CLOCKS_PER_SEC);
  set<int> s; for (int v = n-1; v >= 0; v--) { s.insert(col[v]); CHECK(ans[v] == sz(s)); }
  g.assign(n, {}); for (int i = 1; i < n; i++) {
    g[0].push_back(i); g[i].push_back(0); }
  ans.assign(n, 0); t0 = clock(); dfs(0, -1);
  fprintf(stderr, "star %.2fs\n", (double)(clock()-t0)/CLOCKS_PER_SEC);
  DONE();
}
