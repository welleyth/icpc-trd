// Discrete log (baby-step giant-step): smallest x >= 0 with
// a^x = b (mod m), gcd(a, m) = 1, m <= 3e9; -1 if none.
// O(sqrt m) time and memory.
ll dlog(ll a, ll b, ll m) {
  a %= m; b %= m;
  ll n = sqrtl(m) + 1;
  unordered_map<ll, ll> big;           // b * a^q -> largest q
  for (ll q = 0, cur = b; q <= n; q++, cur = cur * a % m)
    big[cur] = q;
  ll an = power(a, n, m);
  for (ll p = 1, cur = an; p <= n; p++, cur = cur * an % m)
    if (big.count(cur)) return p * n - big[cur];
  return -1; }
// floor sum: sum_{i=0}^{n-1} floor((a*i + b) / m),
// n, m >= 1, a, b >= 0. O(log). (lattice points under line)
ll floorSum(ll n, ll m, ll a, ll b) {
  ll ans = 0;
  while (true) {
    if (a >= m) ans += n * (n - 1) / 2 * (a / m), a %= m;
    if (b >= m) ans += n * (b / m), b %= m;
    ll yMax = a * n + b;
    if (yMax < m) break;
    n = yMax / m; b = yMax % m; swap(m, a);
  }
  return ans; }
