// Exact floor(x^(1/k)) for 0 <= x < 2^63, k >= 1 (powl alone
// is off by one near perfect powers). O(k) per check.
ll iroot(ll x, int k) {
  if (k == 1 || x < 2) return x;
  auto ok = [&](ll r) {                 // r^k <= x ?
    __int128 p = 1;
    for (int i = 0; i < k; i++) if ((p *= r) > x) return false;
    return true; };
  ll r = powl(x, 1.0L / k);
  while (r > 0 && !ok(r)) r--;
  while (ok(r + 1)) r++;
  return r; }
// floor(log_b x) for x >= 1, b >= 2, exact
int ilog(ll x, ll b) {
  int k = 0;
  for (__int128 p = b; p <= x; p *= b) k++;
  return k; }
