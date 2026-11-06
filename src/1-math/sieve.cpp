// Linear sieve: spf[x] = smallest prime factor. O(n).
// n = 1e7 -> about 0.1 s, 40 MB (vector<int>).
vi spf, primes;
void sieve(int n) {
  spf.assign(n + 1, 0); primes.clear();
  for (int i = 2; i <= n; i++) {
    if (!spf[i]) spf[i] = i, primes.push_back(i);
    for (int p : primes) {
      if (p > spf[i] || (ll)i * p > n) break;
      spf[i * p] = p;
    }
  }
}
// factorize x <= n in O(log x): {prime, exponent}
vector<pii> factor(int x) {
  vector<pii> f;
  while (x > 1) {
    int p = spf[x], e = 0;
    while (x % p == 0) x /= p, e++;
    f.push_back({p, e});
  }
  return f; }
// trial division for x <= 1e12..1e14: O(sqrt x)
vector<pair<ll, int>> factorSlow(ll x) {
  vector<pair<ll, int>> f;
  for (ll p = 2; p * p <= x; p++) if (x % p == 0) {
    int e = 0; while (x % p == 0) x /= p, e++;
    f.push_back({p, e}); }
  if (x > 1) f.push_back({x, 1});
  return f; }
// all divisors from factorization (unsorted)
vector<ll> divisors(const vector<pair<ll, int>>& f) {
  vector<ll> d{1};
  for (auto [p, e] : f) {
    int s = sz(d);
    for (ll i = 0, q = p; i < e; i++, q *= p)
      for (int j = 0; j < s; j++) d.push_back(d[j] * q);
  }
  return d; }
// Euler phi from factorization: n * prod (1 - 1/p)
ll phi(ll n, const vector<pair<ll, int>>& f) {
  for (auto [p, e] : f) n = n / p * (p - 1);
  return n; }
