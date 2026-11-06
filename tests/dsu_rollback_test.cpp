#include "t_util.h"
#include "../src/2-ds/dsu_rollback.cpp"
int main() {
  for (int it = 0; it < 3000; it++) {
    int n = rnd(1, 12); RDSU d(n);
    vector<pii> ops; vi marks; // marks[i] = number of ops at time; ops are successful unions only
    vector<pii> all_unions; vi times; // stack of times
    vector<pii> done; // successful+failed unions applied (logical)
    vi stT; // st size checkpoints
    vector<vector<pii>> hist; // snapshot of applied union lists per checkpoint
    vector<pii> applied;
    for (int step = 0; step < 60; step++) {
      int t = rnd(0, 2);
      if (t < 2) { int a = rnd(0, n - 1), b = rnd(0, n - 1); if (rnd(0, 3) == 0) { stT.push_back(d.time()); hist.push_back(applied); } bool r = d.unite(a, b); applied.push_back({a, b}); (void)r; }
      else if (!stT.empty()) { int k = rnd(0, sz(stT) - 1); d.rollback(stT[k]); applied = hist[k]; stT.resize(k); hist.resize(k); }
      // recompute
      vi p(n); iota(all(p), 0); function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
      int comps = n; for (auto [a, b] : applied) { a = f(a); b = f(b); if (a != b) p[a] = b, comps--; }
      CHECK(d.comps == comps);
      for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) CHECK((d.find(i) == d.find(j)) == (f(i) == f(j)));
      vi cs(n); for (int i = 0; i < n; i++) cs[f(i)]++;
      for (int i = 0; i < n; i++) CHECK(-d.p[d.find(i)] == cs[f(i)]);
      // unite return value
    }
    d.rollback(0); CHECK(d.comps == n); for (int i = 0; i < n; i++) CHECK(d.p[i] == -1);
  }
  { RDSU d(1); CHECK(!d.unite(0, 0)); CHECK(d.comps == 1); d.rollback(0); CHECK(d.comps == 1); }
  { RDSU d(3); int t = d.time(); CHECK(d.unite(0, 1)); CHECK(!d.unite(1, 0)); CHECK(d.time() == t + 1); CHECK(d.unite(1, 2)); d.rollback(t + 1); CHECK(d.comps == 2); CHECK(d.find(0) == d.find(1) && d.find(2) != d.find(0)); }
  puts("ok");
}
