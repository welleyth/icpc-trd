#include "t_util.h"
#include "../src/2-ds/lichao.cpp"
int main() {
  for (int it = 0; it < 20000; it++) {
    ll lo, hi, K, B;
    switch (it % 4) {
      case 0: lo = 0; hi = rnd(1, 20); K = 10; B = 100; break;
      case 1: lo = -rnd(1, 20); hi = rnd(lo + 1, 20); K = 10; B = 100; break;
      case 2: lo = -1000000000; hi = 1000000000; K = 2000000000LL; B = 1000000000000000000LL; break;
      default: lo = rnd(-30, 0); hi = lo + rnd(1, 40); K = 2000000000LL; B = 1000000000000000000LL; break;
    }
    LiChao t(lo, hi); vector<pair<ll, ll>> ls;
    int q = rnd(0, 12);
    for (int i = 0; i < q + 12; i++) {
      if (i < q) { ll k = rnd(-K, K), b = rnd(-B, B); if (it % 7 == 0) k = 0; if (it % 11 == 0 && !ls.empty()) k = ls[0].first, b = ls[0].second + rnd(-1, 1); t.add({k, b}); ls.push_back({k, b}); }
      // query
      vector<ll> xs; if (hi - lo <= 45) for (ll x = lo; x < hi; x++) xs.push_back(x); else { xs = {lo, hi - 1, 0, lo + 1, hi - 2}; for (int j = 0; j < 20; j++) xs.push_back(rnd(lo, hi - 1)); }
      for (ll x : xs) { ll e = LLONG_MAX; for (auto [k, b] : ls) e = min(e, k * x + b); CHECK(t.query(x) == e); }
    }
  }
  // empty tree query
  { LiChao t(-5, 5); CHECK(t.query(0) == LLONG_MAX); t.add({1, 0}); CHECK(t.query(-5) == -5 && t.query(4) == 4); }
  // single point range
  { LiChao t(3, 4); t.add({2, 1}); t.add({-1, 20}); CHECK(t.query(3) == 7); }
  // max via negation
  { LiChao t(-10, 10); t.add({3, 0}); t.add({-2, 0}); CHECK(-t.query(-10) == 30 && -t.query(10) == 20); }
  puts("ok");
}
