#include "common.h"
#define CHECK(c) do { if (!(c)) { fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); exit(1); } } while (0)
#include "tricks_extract.inc"
int main() {
  mt19937_64 g(5);
  auto fl = [](__int128 a, __int128 b) { __int128 q = a / b; if (a % b < 0) q--; return q; };
  for (ll a = -50; a <= 50; a++) for (ll b = 1; b <= 20; b++) { CHECK(floorDiv(a, b) == (ll)fl(a, b)); CHECK(ceilDiv(a, b) == (ll)-fl(-(__int128)a, b)); }
  for (int it = 0; it < 1000000; it++) {
    ll a = (ll)g(), b = (ll)(g() % (it % 2 ? 1000000000ULL : 9000000000000000000ULL)) + 1;
    CHECK(floorDiv(a, b) == (ll)fl(a, b)); CHECK(ceilDiv(a, b) == (ll)-fl(-(__int128)a, b));
  }
  CHECK(floorDiv(-1LL, 1LL) == -1); CHECK(ceilDiv(LLONG_MIN, 1) == LLONG_MIN && floorDiv(LLONG_MAX, 1) == LLONG_MAX && ceilDiv(LLONG_MAX, LLONG_MAX) == 1 && floorDiv(LLONG_MIN, LLONG_MAX) == -2 && ceilDiv(LLONG_MIN, LLONG_MAX) == -1);
  CHECK(ceilDiv(0, 5) == 0 && floorDiv(0LL, 5) == 0 && ceilDiv(-1, 5) == 0 && floorDiv(-1LL, 5) == -1 && ceilDiv(1, 5) == 1 && floorDiv(1LL, 5) == 0);
  // str128
  CHECK(str128(0) == "0" && str128(5) == "5" && str128(-5) == "-5" && str128(10) == "10" && str128(-1000) == "-1000");
  __int128 mx = (((__int128)1 << 126) - 1) * 2 + 1;
  CHECK(str128(mx) == "170141183460469231731687303715884105727");
  CHECK(str128(-mx) == "-170141183460469231731687303715884105727");
  CHECK(str128((__int128)LLONG_MAX * LLONG_MAX) == "85070591730234615847396907784232501249");
  CHECK(str128((__int128)LLONG_MIN) == "-9223372036854775808");
  for (int it = 0; it < 100000; it++) {
    __int128 x = ((__int128)(ll)g() << 64 | g()) >> (g() % 120); if (x == ((__int128)1 << 127)) continue;
    string s = str128(x); __int128 y = 0; bool neg = s[0] == '-'; for (char c : s) if (c != '-') y = y * 10 + (c - '0'); if (neg) y = -y;
    CHECK(y == x); CHECK(s == "0" || s[neg] != '0');
  }
  // min value (documented only as __int128 output): -x overflows
  string m = str128((__int128)1 << 127);
  CHECK(m == "-170141183460469231731687303715884105728");
  puts("ok");
}
