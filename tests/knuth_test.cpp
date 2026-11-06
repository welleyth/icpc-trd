#include "t_util.h"
vector<ll> pre;
ll w(int l, int r);
#include "../src/6-misc/knuth.cpp"
ll w(int l, int r) { return pre[r + 1] - pre[l]; }
int main() {
  for (int it = 0; it < 20000; it++) {
    int n = it < 10 ? 1 + it % 3 : rnd(1, 40); vector<ll> a(n); for (ll& x : a) x = rnd(0, it % 2 ? 5 : 1000000);
    pre.assign(n + 1, 0); for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + a[i];
    vector<vector<ll>> d(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; len++) for (int l = 0; l + len - 1 < n; l++) { int r = l + len - 1; d[l][r] = LLONG_MAX; for (int m = l; m < r; m++) d[l][r] = min(d[l][r], d[l][m] + d[m + 1][r] + w(l, r)); }
    CHECK(knuth(n) == d[0][n - 1]);
  }
  puts("ok");
}
