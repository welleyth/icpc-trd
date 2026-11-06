#include "t_util.h"
#include "../src/1-math/mint.cpp"
#include "../src/1-math/binom.cpp"
int main() {
  initFact();
  CHECK(fact[0] == mint(1) && ifact[0] == mint(1));
  mint f = 1;
  for (int i = 1; i < N; i++) { f *= i; if (i < 1000 || i % 9973 == 0 || i > N - 5) CHECK(fact[i] == f); CHECK(fact[i] * ifact[i] == mint(1)); }
  static mint P[70][70];
  for (int n = 0; n < 70; n++) { P[n][0] = 1; for (int k = 1; k <= n; k++) P[n][k] = P[n-1][k-1] + (k <= n - 1 ? P[n-1][k] : mint(0)); }
  for (int n = 0; n < 70; n++) for (int k = -2; k <= n + 2; k++) {
    if (k < 0 || k > n) CHECK(C(n, k) == mint(0)); else CHECK(C(n, k) == P[n][k]); }
  for (int it = 0; it < 100000; it++) {
    int n = rnd(1, N - 1), k = rnd(0, n);
    CHECK(C(n, k) == C(n, n - k));
    if (k) CHECK(C(n, k) == C(n - 1, k - 1) + C(n - 1, k));
  }
  CHECK(C(N - 1, 0) == mint(1) && C(N - 1, N - 1) == mint(1));
  for (int it = 0; it < 20000; it++) {
    int m = rnd(0, 5); vi c(m); int n = 0;
    for (int& x : c) x = rnd(0, 8), n += x;
    mint r = 1; int rem = n;
    for (int x : c) { r *= C(rem, x); rem -= x; }
    CHECK(multinom(c) == r);
  }
  CHECK(multinom({}) == mint(1));
  puts("ok");
}
