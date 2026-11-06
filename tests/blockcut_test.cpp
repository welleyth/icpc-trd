#include "common.h"
#include "../src/3-graph/blockcut.cpp"
#include "chk.h"
// reference: edge-stack BCC
struct Ref { vector<vi> g; vi tin, low; int T = 0; vector<pii> st; set<vi> blocks;
  Ref(vector<vi> g_) : g(g_), tin(sz(g), -1), low(sz(g)) { for (int v = 0; v < sz(g); v++) if (tin[v] < 0) dfs(v, -1); }
  void dfs(int u, int p) { tin[u] = low[u] = T++;
    for (int v : g[u]) { if (v == p) continue;
      if (tin[v] < 0) { st.push_back({u, v}); dfs(v, u); low[u] = min(low[u], low[v]);
        if (low[v] >= tin[u]) { set<int> s; while (true) { auto e = st.back(); st.pop_back(); s.insert(e.first); s.insert(e.second); if (e == pii(u, v)) break; } blocks.insert(vi(all(s))); } }
      else if (tin[v] < tin[u]) { st.push_back({u, v}); low[u] = min(low[u], tin[v]); } } } };
void addE(vector<vi>& g, set<pii>& es, int a, int b) { if (a == b || es.count({min(a,b),max(a,b)})) return; es.insert({min(a,b),max(a,b)}); g[a].push_back(b); g[b].push_back(a); }
int main() {
  for (int it = 0; it < 30000; it++) {
    int n = rnd(1, it % 100 == 0 ? 60 : 10); vector<vi> g(n); set<pii> es;
    int m = rnd(0, 2 * n); for (int i = 0; i < m; i++) addE(g, es, rnd(0, n-1), rnd(0, n-1));
    for (auto& a : g) shuffle(all(a), rng_);
    BlockCut B(g); Ref R(g);
    set<vi> got; vi cnt(n);
    for (int b = n; b < sz(B.tree); b++) { vi s(B.tree[b]); for (int v : s) { cnt[v]++; CHECK(count(all(B.tree[v]), b) == 1); } sort(all(s)); CHECK(adjacent_find(all(s)) == s.end()); got.insert(s); }
    CHECK(got == R.blocks); CHECK(sz(got) == sz(B.tree) - n);
    // cut vertices: vs removal brute
    auto comps = [&](int rem) { vi c(n, -1); int k = 0; for (int s = 0; s < n; s++) if (s != rem && c[s] < 0) { c[s] = k; vi q{s}; while (!q.empty()) { int x = q.back(); q.pop_back(); for (int y : g[x]) if (y != rem && c[y] < 0) c[y] = k, q.push_back(y); } k++; } return k; };
    int base = comps(-1);
    for (int v = 0; v < n; v++) { bool cut = comps(v) > base - (g[v].empty() ? 1 : 0); CHECK((cnt[v] >= 2) == cut); CHECK(cnt[v] == 0 ? g[v].empty() : true); }
    for (int v = 0; v < n; v++) CHECK(B.tree[v].size() == (size_t)cnt[v]);
  }
  // cactus
  for (int it = 0; it < 20000; it++) {
    int n = 1; vector<vi> g(1); set<pii> es; int target = rnd(1, 30);
    int ncyc = 0;
    while (n < target) { int a = rnd(0, n-1); int len = rnd(1, 5);
      vi cyc{a}; for (int i = 0; i < len; i++) { g.emplace_back(); cyc.push_back(n++); }
      if (len == 1) addE(g, es, a, n-1);  // bridge
      else { ncyc++; for (int i = 0; i < sz(cyc); i++) addE(g, es, cyc[i], cyc[(i+1) % sz(cyc)]); } }
    // random relabel + extra isolated
    int iso = rnd(0, 2); for (int i = 0; i < iso; i++) { g.emplace_back(); n++; }
    vi perm(n); iota(all(perm), 0); shuffle(all(perm), rng_);
    vector<vi> h(n); for (int v = 0; v < n; v++) for (int w : g[v]) h[perm[v]].push_back(perm[w]);
    for (auto& a : h) shuffle(all(a), rng_);
    BlockCut B(h); Ref R(h);
    // top vertex = vertex with smaller tin in dfs: nearest to root; verify with B.tin
    set<vi> got;
    for (int b = n; b < sz(B.tree); b++) { auto& t = B.tree[b]; vi s(t); sort(all(s)); got.insert(s);
      int k = sz(t); for (int v : t) CHECK(B.tin[t[0]] <= B.tin[v]);
      if (k == 2) { CHECK(count(all(h[t[0]]), t[1]) == 1); }
      else for (int i = 0; i < k; i++) CHECK(count(all(h[t[i]]), t[(i+1) % k]) == 1); }
    CHECK(got == R.blocks);
  }
  DONE();
}
