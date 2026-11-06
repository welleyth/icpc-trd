#include "t_util.h"
#include "../src/1-math/millerrabin.cpp"
#include "../src/1-math/pollard.cpp"
vector<ull> trial(ull n) { vector<ull> r; for (ull d = 2; d * d <= n; d++) while (n % d == 0) r.push_back(d), n /= d; if (n > 1) r.push_back(n); return r; }
ull rndPrime(int bits) { while (true) { ull p = (trg() >> (64 - bits)) | (1ULL << (bits - 1)); if (isPrime(p)) return p; } }
void chk(ull n) {
  auto f = factorize(n); sort(all(f));
  __uint128_t pr = 1; for (ull p : f) { CHECK(isPrime(p)); pr *= p; }
  CHECK(pr == n);
}
int main() {
  for (ull n = 1; n <= 1000000; n++) { auto f = factorize(n); sort(all(f)); CHECK(f == trial(n)); }
  for (ull n = 1000000; n < 1000000 + 20000; n++) { auto f = factorize(n); sort(all(f)); CHECK(f == trial(n)); }
  for (int it = 0; it < 2000; it++) { ull a = rndPrime(rnd(2, 32)), b = rndPrime(rnd(2, 32)); chk(a * b); }
  for (int it = 0; it < 300; it++) { ull a = rndPrime(32), b = rndPrime(32); auto f = factorize(a * b); sort(all(f)); CHECK(sz(f) == 2 && f[0] * f[1] == a * b && f[0] == min(a, b)); }
  for (int it = 0; it < 300; it++) { ull p = rndPrime(rnd(2, 32)); chk(p * p); if (p < 2600000) { chk(p * p * p); } }
  for (int it = 0; it < 200; it++) { ull p = rndPrime(rnd(2, 20)); __uint128_t v = 1; vector<ull> exp; while (v * p < ((__uint128_t)1 << 64)) { v *= p; exp.push_back((ull)v); } for (ull x : exp) { auto f = factorize(x); CHECK(f.size() >= 1); chk(x); } }
  for (ull n : {4ULL, 8ULL, 16ULL, 9ULL, 25ULL, 1ULL << 63, 1ULL << 62, ~0ULL, ~0ULL - 1, 6ULL, 1ULL}) chk(n);
  CHECK(sz(factorize(1ULL << 63)) == 63); CHECK(sz(factorize(4)) == 2);
  // 2^64-1 = 3*5*17*257*641*65537*6700417
  { auto f = factorize(~0ULL); sort(all(f)); CHECK((f == vector<ull>{3, 5, 17, 257, 641, 65537, 6700417})); }
  // squares of large primes
  for (int it = 0; it < 200; it++) { ull p = rndPrime(32); auto f = factorize(p * p); CHECK(sz(f) == 2 && f[0] == p && f[1] == p); }
  // largest primes < 2^32 squared etc
  { ull p = 4294967291ULL; auto f = factorize(p * p); CHECK(sz(f) == 2 && f[0] == p); ull q = 4294967279ULL; chk(p * q); chk(p * p); }
  // primorial-ish smooth numbers and products of many small
  for (int it = 0; it < 2000; it++) { __uint128_t v = 1; while (true) { ull p = rnd(2, 1000); if (v * p >= ((__uint128_t)1 << 64)) break; v *= p; } chk((ull)v); }
  // 3 primes
  for (int it = 0; it < 1000; it++) { chk(rndPrime(21) * rndPrime(21) * rndPrime(21)); chk(rndPrime(10) * rndPrime(25) * rndPrime(28)); }
  // random any
  for (int it = 0; it < 3000; it++) chk(trg());
  // timing
  auto t0 = chrono::steady_clock::now();
  for (int it = 0; it < 100; it++) chk((ull)rnd(900000000000000000LL, 1000000000000000000LL));
  for (int it = 0; it < 100; it++) chk(rndPrime(30) * rndPrime(30));
  double s = chrono::duration<double>(chrono::steady_clock::now() - t0).count();
  fprintf(stderr, "time 100 random 1e18 + 100 semiprimes (asan): %.3fs\n", s);
  puts("ok");
}
