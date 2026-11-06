#include "t_util.h"
#include "../src/2-ds/bit2d.cpp"
auto MXF2 = [](ll a, ll b) { return max(a, b); };
int main() {
  for (int it = 0; it < 5000; it++) {
    int n = rnd(1, 12), m = rnd(1, 12); BIT2D b(n, m, LLONG_MIN, MXF2); vector<vector<ll>> a(n, vector<ll>(m, LLONG_MIN));
    for (int q = 0; q < 60; q++) {
      int x = rnd(0, n - 1), y = rnd(0, m - 1); ll v = rnd(-1000000000000LL, 1000000000000LL); b.upd(x, y, v); a[x][y] = max(a[x][y], v);
      int qx = rnd(0, n), qy = rnd(0, m); ll r = LLONG_MIN;
      for (int i = 0; i < qx; i++) for (int j = 0; j < qy; j++) r = max(r, a[i][j]);
      CHECK(b.query(qx, qy) == r);
    }
  }
  puts("ok");
}
