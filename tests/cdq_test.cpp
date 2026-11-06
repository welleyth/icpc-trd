#include "t_util.h"
#include "../src/2-ds/fenwick.cpp"
#include "../src/2-ds/cdq.cpp"
int main() {
  CHECK(dominance({}, 1).empty() && dominance({}, 0).empty());
  { auto r = dominance({{5, 5, 0}}, 1); CHECK(sz(r) == 1 && r[0] == 0); }
  for (int it = 0; it < 30000; it++) {
    int n = rnd(1, it % 10 == 0 ? 120 : 15), K = it % 3 == 0 ? 2 : it % 3 == 1 ? 4 : 9, C = K;
    vector<array<int, 3>> p(n);
    for (auto& x : p) x = {(int)rnd(0, K - 1), (int)rnd(0, K - 1), (int)rnd(0, C - 1)};
    auto r = dominance(p, C);
    CHECK(sz(r) == n);
    for (int i = 0; i < n; i++) { int c = 0; for (int j = 0; j < n; j++) if (j != i && p[j][0] <= p[i][0] && p[j][1] <= p[i][1] && p[j][2] <= p[i][2]) c++; CHECK(r[i] == c); }
  }
  { vector<array<int,3>> p(50, {1,1,1}); auto r = dominance(p, 2); for (int x : r) CHECK(x == 49); }
  puts("ok");
}
