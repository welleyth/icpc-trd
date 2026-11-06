#include "common.h"
#include "../src/4-string/hash.cpp"
#include "chk.h"
int main() {
  for (int it = 0; it < 200000; it++) {
    ull a = (rng_() * 1ULL << 32 ^ rng_()) % (HM - 1) + 1; if (it < 5) a = it + 1; if (it == 5) a = HM - 1;
    CHECK(hmul(hpow(a, HM - 2), a) == 1);
    CHECK(hpow(a, HM - 1) == 1);
  }
  CHECK(hpow(5, 0) == 1); CHECK(hpow(2, 61) == 1); CHECK(hpow(0, 3) == 0);
  CHECK(hpow(3, 5) == 243);
  // hash get consistent
  string s = "abcabcabc"; Hash H(s); CHECK(H.get(0,3) == H.get(3,6)); CHECK(H.get(0,3) != H.get(1,4));
  DONE();
}
