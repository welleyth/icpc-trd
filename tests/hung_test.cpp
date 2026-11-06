#include "common.h"
#include "../src/3-graph/hungarian.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 30000; iter++) {
    int n = rnd(1, 6), m = rnd(n, 7);
    int R = rnd(0, 2) == 0 ? 2 : rnd(0, 1) ? 1000 : 1000000000;
    vector<vector<ll>> a(n, vector<ll>(m));
    bool neg = rnd(0, 1);
    for (auto& r : a) for (ll& x : r) x = rnd(neg ? -R : 0, R);
    if (iter % 7 == 0) for (auto& r : a) for (ll& x : r) x = 5;
    vi cols(m); iota(all(cols), 0); ll best = LLONG_MAX;
    do { ll s = 0; for (int i = 0; i < n; i++) s += a[i][cols[i]];
      best = min(best, s);
    } while (next_permutation(all(cols)));
    auto [c, col] = hungarian(a);
    CHECK(c == best); CHECK(sz(col) == n);
    set<int> st; ll s = 0;
    for (int i = 0; i < n; i++) { st.insert(col[i]);
      CHECK(col[i] >= 0 && col[i] < m); s += a[i][col[i]]; }
    CHECK(sz(st) == n); CHECK(s == c);
  }
  DONE();
}
