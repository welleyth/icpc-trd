#include "t_util.h"
#include "../src/2-ds/persistent.cpp"
int main() {
  for (int it = 0; it < 500; it++) {
    pn = 1; int n = rnd(1, 40), V0 = rnd(1, 10);
    vector<ll> a(n); for (auto& x : a) x = rnd(0, 1000) * 3 % (V0 * 100 + 1);
    vector<ll> u = a; sort(all(u)); u.erase(unique(all(u)), u.end()); int V = sz(u);
    vi c(n); for (int i = 0; i < n; i++) c[i] = lower_bound(all(u), a[i]) - u.begin();
    vi root(n + 1, 0); for (int i = 0; i < n; i++) root[i + 1] = padd(root[i], 0, V, c[i]);
    for (int l = 0; l < n; l++) for (int r = l + 1; r <= n; r++) {
      vector<ll> s(a.begin() + l, a.begin() + r); sort(all(s));
      for (int k = 0; k < sz(s); k++) CHECK(u[kth(root[l], root[r], 0, V, k)] == s[k]);
    }
  }
  { // V = 1
    pn = 1; vi root(4, 0); for (int i = 0; i < 3; i++) root[i + 1] = padd(root[i], 0, 1, 0); CHECK(kth(root[0], root[3], 0, 1, 2) == 0); }
  { // max size
    pn = 1; int n = 200000, V = 200000; vi a(n); for (int& x : a) x = rnd(0, V - 1); vi root(n + 1, 0);
    for (int i = 0; i < n; i++) root[i + 1] = padd(root[i], 0, V, a[i]);
    fprintf(stderr, "nodes used %d of %d\n", pn, PM); CHECK(pn <= PM);
    for (int t = 0; t < 200; t++) { int l = rnd(0, n - 1), r = rnd(l + 1, n); if (t % 20 == 0) { l = 0; r = n; } vi s(a.begin() + l, a.begin() + r); sort(all(s)); int k = rnd(0, sz(s) - 1); CHECK(kth(root[l], root[r], 0, V, k) == s[k]); }
  }
  puts("ok");
}
