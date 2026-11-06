#include "common.h"
#include "../src/4-string/xortrie.cpp"
#include "chk.h"
int main() {
  { XorTrie t; CHECK(t.query(5, 0) == LLONG_MAX); CHECK(t.query(0, (1<<30)-1) == LLONG_MAX); }
  for (int it = 0; it < 30000; it++) {
    int M = (int[]){4, 16, 64, 1 << 30}[it % 4];
    XorTrie t; vector<pair<int,ll>> st; int n = rnd(0, 12);
    for (int i = 0; i < n; i++) { int y = rnd(0, M-1); ll v = rnd(0,3)==0 ? (ll)rnd(0,10) - 1000000000000LL : rnd(0, 1000); t.add(y, v); st.push_back({y, v}); }
    for (int q = 0; q < 20; q++) {
      int x = rnd(0, M-1); int k = q == 0 ? 0 : q == 1 ? (1<<30)-1 : rnd(0,1) ? rnd(0, M-1) : rnd(0, (1<<30)-1);
      ll best = LLONG_MAX; for (auto& [y, v] : st) if ((x ^ y) <= k) best = min(best, v);
      CHECK(t.query(x, k) == best);
    }
  }
  DONE();
}
