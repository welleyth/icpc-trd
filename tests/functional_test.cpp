#include "common.h"
#include "../src/3-graph/functional.cpp"
#include "chk.h"
int main() {
  for (int it = 0; it < 30000; it++) {
    int n = rnd(1, it % 100 == 0 ? 200 : 12); vi f(n);
    int mode = rnd(0, 3);
    for (int i = 0; i < n; i++) f[i] = mode == 0 ? rnd(0, n-1) : mode == 1 ? (rnd(0,3)==0 ? i : rnd(0,n-1)) : mode==2 ? (i+1)%n : max(0, i - rnd(0,2));
    if (mode == 3) f[0] = 0;
    Functional F(f);
    // brute on cycle
    vi bc(n);
    for (int v = 0; v < n; v++) { int u = v; for (int k = 0; k < n; k++) u = f[u];
      // u is on cycle; v on cycle iff reachable from u
      int w = u; bool on = false; for (int k = 0; k <= n; k++) { if (w == v) on = true; w = f[w]; } bc[v] = on; }
    for (int v = 0; v < n; v++) CHECK(F.onCyc[v] == bc[v]);
    int cnt = 0; vi seen(n);
    for (int c = 0; c < sz(F.cycles); c++) { auto& cy = F.cycles[c];
      for (int i = 0; i < sz(cy); i++) { CHECK(F.onCyc[cy[i]]); CHECK(F.f[cy[i]] == cy[(i+1)%sz(cy)]); CHECK(F.cycId[cy[i]] == c); seen[cy[i]]++; cnt++; } }
    int onc = 0; for (int v = 0; v < n; v++) { onc += bc[v]; CHECK(bc[v] ? seen[v] == 1 : (seen[v] == 0 && F.cycId[v] < 0)); }
    CHECK(onc == cnt);
    CHECK(sz(F.order) == n - onc);
    // order validity
    vi pos(n, -1); for (int i = 0; i < sz(F.order); i++) pos[F.order[i]] = i;
    for (int v : F.order) { CHECK(!F.onCyc[v]); if (!F.onCyc[f[v]]) CHECK(pos[f[v]] > pos[v]); }
    // height DP: longest path into v
    vi h(n, 0);
    for (int v : F.order) h[f[v]] = max(h[f[v]], h[v] + 1);
    for (int v = 0; v < n; v++) { int b = 0;
      for (int s = 0; s < n; s++) if (!bc[s]) { int u = s, d = 0;
        while (u != v && !bc[u]) u = f[u], d++;
        if (u == v) b = max(b, d); }
      if (h[v] != b) { for (int x : f) fprintf(stderr, "%d ", x); fprintf(stderr, " v=%d h=%d b=%d\n", v, h[v], b); }
      CHECK(h[v] == b); }
    // dist to cycle
    vi dist(n, 0); for (int i = sz(F.order)-1; i >= 0; i--) dist[F.order[i]] = dist[f[F.order[i]]] + 1;
    for (int v = 0; v < n; v++) { int u = v, d = 0; while (!bc[u]) u = f[u], d++; CHECK(dist[v] == d); }
  }
  DONE();
}
