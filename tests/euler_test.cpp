#include "common.h"
#include "../src/3-graph/euler.cpp"
#include "chk.h"
int main() {
  int falsePos = 0;
  for (int iter = 0; iter < 60000; iter++) {
    bool dir = iter & 1;
    int n = rnd(1, 7), m = rnd(0, 9);
    vector<vector<pii>> g(n); vector<pii> es;
    vi in(n), out(n), deg(n);
    vi p(n); iota(all(p), 0);
    function<int(int)> f=[&](int x){return p[x]==x?x:p[x]=f(p[x]);};
    for (int i = 0; i < m; i++) {
      int u = rnd(0, n-1), v = rnd(0, n-1);
      es.push_back({u, v}); g[u].push_back({v, i});
      if (!dir) g[v].push_back({u, i});
      out[u]++; in[v]++; deg[u]++; deg[v]++;
      p[f(u)] = f(v); }
    bool conn = true; int root = -1;
    for (int i = 0; i < n; i++) if (deg[i]) {
      if (root < 0) root = f(i); else if (f(i) != root) conn = false; }
    int s = 0; bool exists = conn, degOk = true;
    if (!dir) {
      int odd = 0; for (int i = 0; i < n; i++) if (deg[i] % 2) {
        odd++; if (odd == 1) s = i; }
      if (odd != 0 && odd != 2) exists = false, degOk = false;
      if (!odd) for (int i = 0; i < n; i++) if (deg[i]) { s = i; break; }
    } else {
      int plus = 0, minus = 0, bad = 0; bool setS = false;
      for (int i = 0; i < n; i++) {
        int d = out[i] - in[i];
        if (d == 1) { plus++; s = i; setS = true; }
        else if (d == -1) minus++;
        else if (d != 0) bad++; }
      if (bad || plus > 1 || minus > 1 || plus != minus) exists = false, degOk = false;
      if (!setS) for (int i = 0; i < n; i++) if (deg[i]) { s = i; break; }
    }
    auto path = euler(g, m, s);
    if (exists) {
      CHECK(sz(path) == m + 1);
      multiset<pii> ms;
      for (auto [u, v] : es) {
        ms.insert({u, v}); if (!dir) ms.insert({v, u}); }
      // each undirected edge consumed once in some direction
      bool ok = sz(path) == m + 1;
      for (int i = 0; ok && i + 1 < sz(path); i++) {
        pii e{path[i], path[i+1]};
        auto it = ms.find(e);
        if (it == ms.end()) { ok = false; break; }
        ms.erase(it);
        if (!dir) { auto jt = ms.find({e.second, e.first});
          if (jt == ms.end()) { ok = false; break; } ms.erase(jt); }
      }
      CHECK(ok);
    } else if (sz(path) == m + 1) falsePos++;
    // with the degree conditions satisfied, size != m+1 <=> disconnected
    if (!exists && degOk && sz(path) == m + 1) CHECK(false);
  }
  printf("false positives (size==m+1 but no path): %d\n", falsePos);
  CHECK(falsePos > 0); // documented: degrees must be checked
  DONE();
}
