#include "t_util.h"
#include "../src/2-ds/pbds.cpp"
int main() {
  for (int it = 0; it < 3000; it++) {
    oset<int> s; set<int> b;
    for (int q = 0; q < 60; q++) {
      int x = rnd(-20, 20);
      if (rnd(0, 2)) { s.insert(x); b.insert(x); } else { s.erase(x); b.erase(x); }
      CHECK(sz(s) == sz(b));
      int y = rnd(-22, 22); CHECK((int)s.order_of_key(y) == (int)distance(b.begin(), b.lower_bound(y)));
      if (sz(b)) { int k = rnd(0, sz(b) - 1); CHECK(*s.find_by_order(k) == *next(b.begin(), k)); }
      CHECK(s.find_by_order(sz(b)) == s.end());
    }
  }
  // multiset via pairs
  { oset<pair<int, int>> m; int id = 0; for (int x : {5, 5, 3, 5, 1}) m.insert({x, id++}); CHECK((int)m.order_of_key({5, -1}) == 2); CHECK((int)m.order_of_key({6, -1}) == 5); CHECK(m.find_by_order(2)->first == 5); }
  { oset<ll> s; s.insert(LLONG_MIN); s.insert(LLONG_MAX); CHECK((int)s.order_of_key(0) == 1); }
  // SafeHash
  unordered_map<ll, int, SafeHash> m; m.reserve(1 << 10); map<ll, int> b;
  for (int i = 0; i < 200000; i++) { ll k = rnd(-1000, 1000) * (i % 2 ? 1 : 1LL << 40); m[k] += i; b[k] += i; }
  CHECK(sz(m) == sz(b)); for (auto [k, v] : b) CHECK(m[k] == v);
  CHECK(SafeHash()(5) == SafeHash()(5));
  { gp_hash_table<ll, int, SafeHash> h; for (int i = 0; i < 1000; i++) h[i * 1000003LL] = i; for (int i = 0; i < 1000; i++) CHECK(h[i * 1000003LL] == i); CHECK(h.find(-1) == h.end()); }
  puts("ok");
}
