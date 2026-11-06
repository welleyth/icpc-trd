#include "t_util.h"
#include "../src/2-ds/monostack.cpp"
int main() {
  for (int it = 0; it < 30000; it++) {
    int n = rnd(1, 20), k = it % 5 == 0 ? 1 : it % 5 == 1 ? n : rnd(1, n);
    int V = it % 2 ? 3 : 1000000000;
    vector<ll> a(n); for (ll& v : a) v = rnd(-V, V);
    auto r = windowMax(a, k);
    CHECK(sz(r) == n - k + 1);
    for (int i = 0; i + k <= n; i++) CHECK(r[i] == *max_element(a.begin() + i, a.begin() + i + k));
    // min via negation
    vector<ll> b = a; for (ll& v : b) v = -v; auto rm = windowMax(b, k);
    for (int i = 0; i + k <= n; i++) CHECK(-rm[i] == *min_element(a.begin() + i, a.begin() + i + k));
    vi L, R; nearestSmaller(a, L, R); ll s = 0, br = 0;
    for (int i = 0; i < n; i++) s += a[i] * (i - L[i]) * (R[i] - i);
    for (int l = 0; l < n; l++) for (int r2 = l; r2 < n; r2++) br += *min_element(a.begin() + l, a.begin() + r2 + 1);
    CHECK(s == br);
  }
  puts("ok");
}
