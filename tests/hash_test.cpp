#include "common.h"
#include "../src/4-string/hash.cpp"
#include "chk.h"
string rs(int n, int a) { string s; while (n--) s += 'a' + rnd(0, a-1); return s; }
int main() {
  Hash e(""); CHECK(e.get(0, 0) == 0);
  for (int iter = 0; iter < 20000; iter++) {
    int a = rnd(1, 2); string s = rs(rnd(0, 20), a); int n = sz(s);
    Hash h(s);
    for (int q = 0; q < 20; q++) {
      int l1 = rnd(0, n), r1 = rnd(l1, n), l2 = rnd(0, n), r2 = rnd(l2, n);
      bool eq = s.substr(l1, r1-l1) == s.substr(l2, r2-l2);
      bool he = r1-l1 == r2-l2 && h.get(l1, r1) == h.get(l2, r2);
      CHECK(eq == he);
      CHECK(h.get(l1, r1) < HM); }
  }
  // mulmod vs __int128
  for (int i = 0; i < 100000; i++) {
    ull a = rng_() * 1000003ULL % HM, b = (((ull)rng_() << 32) | rng_()) % HM;
    CHECK(hmul(a, b) == (ull)((__uint128_t)a * b % HM)); }
  CHECK(hmul(HM-1, HM-1) == 1);
  // bytes >127 and '\0'
  string s = "\xff\xfe"; s += '\0'; Hash h(s); CHECK(h.get(0,3) != h.get(0,2));
  DONE();
}
