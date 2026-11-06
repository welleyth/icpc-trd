#include "common.h"
#include "../src/3-graph/lifting.cpp"
#include "chk.h"
int main() {
  for (int it = 0; it < 20000; it++) {
    int n = rnd(1, 12); vi nx(n); vector<ll> c(n);
    int ter = rnd(0, 2) ? rnd(0, n-1) : -1;
    ll mx = rnd(0,3)==0 ? 1000000000000LL : rnd(0, 5);
    for (int i = 0; i < n; i++) { nx[i] = rnd(0, n-1); c[i] = (ll)(((unsigned long long)rng_() << 20 ^ rng_()) % (mx + 1)); }
    if (ter >= 0) { nx[ter] = ter; c[ter] = CAP; }
    int steps = rnd(1, 60); int L = 1; while ((1LL << L) <= steps) L++;
    // L = log2(max steps)+1 ; only jumps up to 2^L -1 >= steps are exercised
    Lift T(nx, c, L);
    for (int q = 0; q < 20; q++) {
      int v = rnd(0, n-1); ll B = rnd(0,4)==0 ? 0 : (ll)(rng_() % (mx * 40 + 2));
      if (rnd(0, 20) == 0) B = 1000000000000000000LL;
      // brute: up to 2^L-1 steps
      ll t = 0, b = B; int u = v;
      while (t < (1LL << L) - 1 && c[u] <= b) { b -= c[u]; u = nx[u]; t++; }
      auto r = T.maxJumps(v, B);
      CHECK(r.first == t && r.second == u);
    }
  }
  // CAP saturation: big costs chain
  { vi nx{1,2,3,4,4}; vector<ll> c{(ll)1e18,(ll)1e18,(ll)1e18,(ll)1e18,CAP};
    Lift T(nx, c, 4); auto r = T.maxJumps(0, (ll)1e18); CHECK(r.first==1 && r.second==1);
    r = T.maxJumps(0, (ll)1e18 * 2 - 1); CHECK(r.first == 1);
    r = T.maxJumps(0, CAP - 1); CHECK(r.first == 1 && r.second == 1); }
  DONE();
}
