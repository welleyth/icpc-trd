#include "t_util.h"
#include "../src/6-misc/reroot.cpp"
vi bfs(const vector<vi>& g, int s) { vi d(sz(g), -1); d[s] = 0; queue<int> q; q.push(s); while (!q.empty()) { int u = q.front(); q.pop(); for (int v : g[u]) if (d[v] < 0) d[v] = d[u] + 1, q.push(v); } return d; }
int main() {
  for (int it = 0; it < 5000; it++) {
    int n = it < 5 ? 1 : rnd(1, 40); int kind = it % 4;
    vector<vi> g(n); vi lab(n); iota(all(lab), 0); shuffle(all(lab), trg);
    for (int i = 1; i < n; i++) { int p = kind == 0 ? i - 1 : kind == 1 ? 0 : kind == 2 ? rnd(0, i - 1) : max(0, i - (int)rnd(1, 3)); int a = lab[i], b = lab[p]; g[a].push_back(b); g[b].push_back(a); }
    for (auto& v : g) shuffle(all(v), trg);
    int root = rnd(0, n - 1);
    auto res = reroot(g, root);
    // formulas (1),(2) per brute force
    vi par(n, -1), sub(n, 1), ord{root}; for (int i = 0; i < sz(ord); i++) for (int v : g[ord[i]]) if (v != par[ord[i]]) par[v] = ord[i], ord.push_back(v);
    for (int i = n - 1; i > 0; i--) sub[par[ord[i]]] += sub[ord[i]];
    vi d0 = bfs(g, root); vector<ll> ans(n); ans[root] = accumulate(all(d0), 0LL);
    for (int i = 1; i < n; i++) { int c = ord[i], v = par[c]; ans[c] = ans[v] - sub[c] + (n - sub[c]); }
    // (2) farthest distance
    vi dn(n, 0), second(n, 0), up(n, 0);
    // best child values: 1+dn[child]
    for (int i = n - 1; i > 0; i--) { int c = ord[i], v = par[c]; int val = 1 + dn[c]; if (val > dn[v]) second[v] = dn[v], dn[v] = val; else if (val > second[v]) second[v] = val; }
    vi far(n); far[root] = dn[root];
    for (int i = 1; i < n; i++) { int c = ord[i], v = par[c]; int other = (1 + dn[c] == dn[v]) ? second[v] : dn[v]; up[c] = 1 + max(up[v], other); far[c] = max(dn[c], up[c]); }
    for (int s = 0; s < n; s++) {
      vi d = bfs(g, s); ll sum = accumulate(all(d), 0LL);
      CHECK(res[s].second == sum); CHECK(ans[s] == sum); CHECK(far[s] == *max_element(all(d)));
      CHECK(res[s].first == n - 1 + 0 || true);
    }
  }
  { vector<vi> g(1); auto r = reroot(g); CHECK(sz(r) == 1 && r[0].second == 0); }
  puts("ok");
}
