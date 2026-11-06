// Factorials, C(n,k), permutations of a multiset. O(N) init.
const int N = 2e6 + 5;
mint fact[N], ifact[N];
void initFact() {
  fact[0] = 1;
  for (int i = 1; i < N; i++) fact[i] = fact[i - 1] * i;
  ifact[N - 1] = fact[N - 1].inv();
  for (int i = N - 1; i > 0; i--) ifact[i - 1] = ifact[i] * i;
}
mint C(int n, int k) {
  if (k < 0 || k > n) return 0;
  return fact[n] * ifact[k] * ifact[n - k]; }
// n! / (c1! c2! ...), n = sum of c
mint multinom(const vi& c) {
  int n = 0; mint r = 1;
  for (int x : c) n += x, r *= ifact[x];
  return r * fact[n]; }
// Lucas (small prime p, ll n): C(n,k) = prod C(n_i, k_i)
// over base-p digits.
