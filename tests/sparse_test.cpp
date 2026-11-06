#include "t_util.h"
#include "../src/2-ds/sparse.cpp"
auto MNF = [](int a, int b) { return min(a, b); };
int main() {
  for (int it = 0; it < 20000; it++) {
    int n = rnd(1, 40); vi a(n); for (int& x : a) x = it % 3 == 0 ? 7 : rnd(-1000000000, 1000000000);
    if (it % 3 == 1) for (int& x : a) x = rnd(-3, 3);
    Sparse s(a, MNF);
    for (int l = 0; l < n; l++) for (int r = l + 1; r <= n; r++) CHECK(s.query(l, r) == *min_element(a.begin() + l, a.begin() + r));
  }
  { Sparse s(vi{}, MNF); }
  { vi a(1 << 16); for (int& x : a) x = rnd(-100, 100); Sparse s(a, MNF); for (int q = 0; q < 100000; q++) { int l = rnd(0, sz(a) - 1), r = rnd(l + 1, min<ll>(sz(a), l + 300)); CHECK(s.query(l, r) == *min_element(a.begin() + l, a.begin() + r)); } CHECK(s.query(0, sz(a)) == *min_element(all(a))); }
  puts("ok");
}
