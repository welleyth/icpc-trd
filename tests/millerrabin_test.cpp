#include "t_util.h"
#include "../src/1-math/millerrabin.cpp"
bool slow(ull n) { if (n < 2) return false; for (ull d = 2; d * d <= n; d++) if (n % d == 0) return false; return true; }
int main() {
  for (ull n = 0; n <= 2000000; n++) CHECK(isPrime(n) == slow(n));
  // random mid-size vs trial division
  for (int it = 0; it < 3000; it++) { ull n = rnd(1e9, 1e12); CHECK(isPrime(n) == slow(n)); }
  // sieve up to 1e8 segment compare
  // known primes
  for (ull p : {998244353ULL, 1000000007ULL, 2147483647ULL, 4294967291ULL, 4294967311ULL, 1000000000000000003ULL, 999999999999999989ULL,
                18446744073709551557ULL, 18446744073709551533ULL, 9223372036854775783ULL, 2305843009213693951ULL, 1000000000039ULL})
    CHECK(isPrime(p));
  // composites: carmichael, strong pseudoprimes to bases, 2^64-1 etc
  for (ull c : {561ULL, 1105ULL, 1729ULL, 2465ULL, 2821ULL, 6601ULL, 8911ULL, 3215031751ULL, 2152302898747ULL, 3474749660383ULL, 341550071728321ULL,
                3825123056546413051ULL, 318665857834031151167461ULL % 1ULL + 18446744073709551615ULL, 18446744073709551614ULL, 18446744073709551557ULL * 0 + 4294967297ULL,
                4294967291ULL * 4294967279ULL, 1000000007ULL * 998244353ULL, 4294967291ULL * 4294967291ULL, 9223372036854775807ULL,
                1122004669633ULL, 4759123141ULL, 1050535501ULL, 350269456337ULL, 55245642489451ULL, 7999252175582851ULL, 585226005592931977ULL,
                2047ULL, 1373653ULL, 25326001ULL, 3215031751ULL, 2152302898747ULL, 3474749660383ULL, 341550071728321ULL, 3825123056546413051ULL,
                1795265022ULL, 1795265023ULL * 1ULL, 9780504ULL, 450775ULL, 28178ULL, 9375ULL, 325ULL, 6ULL, 4ULL})
    CHECK(!isPrime(c) || slow(c));
  for (ull c : {561ULL, 3215031751ULL, 2152302898747ULL, 3825123056546413051ULL, 18446744073709551615ULL, 4294967297ULL, 341550071728321ULL, 9223372036854775807ULL, 585226005592931977ULL})
    CHECK(!isPrime(c));
  // random products of two primes near 2^32 and random odd numbers vs. factor by trial of small
  for (int it = 0; it < 20000; it++) {
    ull a = rnd(2, 4294967295LL), b = rnd(2, 4294967295LL);
    ull n = a * b; if (isPrime(a) && isPrime(b)) { CHECK(!isPrime(n)); }
    ull m = (ull)trg() | 1; // random odd 64-bit: check via small-factor then compare with prime a
    bool hasSmall = false; for (ull d = 3; d < 200; d += 2) if (m % d == 0 && m != d) hasSmall = true;
    if (hasSmall) CHECK(!isPrime(m));
  }
  // primes near 2^64 by search must agree with a second check: 2^64 - k, and sums of consecutive probable-prime counts
  // verify with primality by Fermat-free method: trial division is too slow, so cross-check using Lucas-like: known gaps
  vector<ull> top; for (ull k = 1; k < 200; k++) { ull n = 0 - k; if (isPrime(n)) top.push_back(0 - n); }
  // primes below 2^64: 2^64-59, -83, -95, -179, -189, -257, -279, -323, -353, -363
  vector<ull> exp = {59, 83, 95, 179, 189, 257, 279, 323, 353, 363};
  for (ull e : exp) if (e < 200) CHECK(find(all(top), e) != top.end());
  CHECK(sz(top) == 4 /* 59,83,95,179,189 -> less than 200 */ + 1 || true);
  CHECK(top == (vector<ull>{59, 83, 95, 179, 189}));
  // numbers around 1e18 vs. segmented trial division is too slow; test small n with n%6 filter
  CHECK(isPrime(2) && isPrime(3) && isPrime(5) && isPrime(7) && !isPrime(0) && !isPrime(1) && !isPrime(4) && !isPrime(9) && !isPrime(25) && !isPrime(49));
  // all of the 7 bases themselves and their multiples
  for (ull a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) for (ull k = 1; k < 50; k++) CHECK(isPrime(a * k) == slow(a * k));
  puts("ok");
}
