#include "t_util.h"
#include "../src/1-math/sieve.cpp"
int main() {
  for (int n : {0, 1, 2, 3, 4, 10, 97, 100, 1000, 100000, 2000000}) {
    primes.clear();
    sieve(n);
    CHECK(sz(spf) == n + 1);
    vector<bool> comp(n + 2);
    vi pr;
    for (int i = 2; i <= n; i++) {
      if (!comp[i]) { pr.push_back(i); for (ll j = (ll)i * i; j <= n; j += i) comp[j] = 1; }
    }
    CHECK(pr == primes);
    for (int i = 2; i <= n; i++) {
      if (n > 3000 && i > 3000) { if (i % 997 && i % 101 && i % 100003) continue; }
      int p = i; for (int d = 2; d * d <= i; d++) if (i % d == 0) { p = d; break; }
      CHECK(spf[i] == p);
      auto f = factor(i); ll prod = 1; int last = 0;
      for (auto [q, e] : f) { CHECK(q > last); last = q; CHECK(e >= 1); for (int k = 0; k < e; k++) prod *= q; }
      CHECK(prod == i);
    }
    CHECK(factor(1).empty());
  }
  // calling sieve twice without clearing primes
  primes.clear(); sieve(100); sieve(100);
  CHECK(sz(primes) == 25);
  // factorSlow / divisors / phi
  for (ll x = 1; x <= 3000; x++) {
    auto f = factorSlow(x);
    ll prod = 1; for (auto [p, e] : f) for (int k = 0; k < e; k++) prod *= p;
    CHECK(prod == x);
    auto d = divisors(f); sort(all(d));
    vector<ll> bd; for (ll i = 1; i <= x; i++) if (x % i == 0) bd.push_back(i);
    CHECK(d == bd);
    ll ph = 0; for (ll i = 1; i <= x; i++) if (std::gcd(i, x) == 1) ph++;
    CHECK(phi(x, f) == ph);
  }
  CHECK(factorSlow(1).empty());
  for (ll x : {999999999989LL, 1000000007LL * 998244353LL, 999999937LL * 999999937LL, 1LL << 40, 963761198400LL, 1000000000000LL}) {
    auto f = factorSlow(x); ll prod = 1;
    for (auto [p, e] : f) for (int k = 0; k < e; k++) prod *= p;
    CHECK(prod == x);
    auto d = divisors(f); CHECK(sz(d) > 0);
    for (ll v : d) CHECK(x % v == 0);
    set<ll> s(all(d)); CHECK(sz(s) == sz(d));
  }
  puts("ok");
}
