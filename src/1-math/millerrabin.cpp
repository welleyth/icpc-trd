// Deterministic primality test for all n < 2^64.
using ull = unsigned long long;
ull mulmod(ull a, ull b, ull m) {
  return (__uint128_t)a * b % m; }
ull powmod(ull b, ull e, ull m) {
  ull r = 1;
  for (; e; e >>= 1, b = mulmod(b, b, m))
    if (e & 1) r = mulmod(r, b, m);
  return r; }
bool isPrime(ull n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  ull d = n - 1; int s = __builtin_ctzll(d); d >>= s;
  for (ull a : {2, 325, 9375, 28178, 450775, 9780504,
                1795265022}) {
    ull x = powmod(a % n, d, n); int i = s;
    while (x != 1 && x != n - 1 && a % n && i--)
      x = mulmod(x, x, n);
    if (x != n - 1 && i != s) return false;
  }
  return true; }
