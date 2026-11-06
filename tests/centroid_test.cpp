#include "common.h"
#include "../src/3-graph/centroid.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 20000; iter++) {
    int n = rnd(1, 60);
    g.assign(n, {}); sub.assign(n, 0); cpar.assign(n, -2);
    removed.assign(n, false);
    int shape = rnd(0, 3);
    vi lab(n); iota(all(lab), 0); shuffle(all(lab), rng_);
    vector<pii> ed;
    for (int i = 1; i < n; i++) {
      int pp = shape == 0 ? rnd(0, i-1) : shape == 1 ? i-1 : shape == 2 ? 0 : max(0, i-1-rnd(0,2));
      g[lab[i]].push_back(lab[pp]); g[lab[pp]].push_back(lab[i]);
      ed.push_back({lab[i], lab[pp]}); }
    build(0);
    int roots = 0;
    for (int v = 0; v < n; v++) {
      CHECK(removed[v]); CHECK(cpar[v] != -2);
      if (cpar[v] == -1) roots++; }
    CHECK(roots == 1);
    // centroid-subtree sizes
    vi csz(n, 0), depc(n, -1);
    for (int v = 0; v < n; v++) {
      int d = 0, x = v;
      while (x >= 0 && d <= n) { csz[x]++; x = cpar[x]; d++; }
      CHECK(d <= n);
      depc[v] = d; }
    for (int v = 0; v < n; v++) {
      if (cpar[v] >= 0) CHECK(2 * csz[v] <= csz[cpar[v]]);
      // component of v = its centroid-subtree must be connected
    }
    int lim = 1; while ((1 << lim) <= n) lim++;
    for (int v = 0; v < n; v++) CHECK(depc[v] <= lim);
    // connectivity: centroid-subtree of c is connected in tree
    for (int c = 0; c < n; c++) {
      vector<bool> in(n);
      for (int v = 0; v < n; v++) { for (int x = v; x >= 0; x = cpar[x]) if (x == c) in[v] = true; }
      // BFS from c within in[]
      vector<bool> vis(n); vi q{c}; vis[c] = true;
      for (int i = 0; i < sz(q); i++) for (int w : g[q[i]])
        if (in[w] && !vis[w]) vis[w] = true, q.push_back(w);
      CHECK(sz(q) == csz[c]);
    }
  }
  DONE();
}
