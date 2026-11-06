// Pollard rho: prime factors of n < 2^64 (with repetition,
// unsorted), about O(n^(1/4)). Needs millerrabin.cpp.
ull pollard(ull n) {
  ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
  auto f = [&](ull v) { return mulmod(v, v, n) + i; };
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = mulmod(prd, max(x, y) - min(x, y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n); }
vector<ull> factorize(ull n) {
  if (n == 1) return {};
  if (isPrime(n)) return {n};
  ull x = pollard(n);
  auto l = factorize(x), r = factorize(n / x);
  l.insert(l.end(), all(r));
  return l; }
