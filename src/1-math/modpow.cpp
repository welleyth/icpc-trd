// Plain ll version (any modulus m <= 3e9; use __int128
// multiplication for m up to 1e18).
ll power(ll b, ll e, ll m) {
  ll r = 1; b %= m; if (b < 0) b += m;
  for (; e; e >>= 1, b = b * b % m) if (e & 1) r = r * b % m;
  return r; }
// a*x + b*y = g = gcd(a, b)
ll egcd(ll a, ll b, ll& x, ll& y) {
  if (!b) { x = 1, y = 0; return a; }
  ll g = egcd(b, a % b, y, x); y -= a / b * x; return g; }
// inverse of a mod m when gcd(a, m) = 1 (m need not be prime)
ll inverse(ll a, ll m) {
  ll x, y; egcd((a % m + m) % m, m, x, y);
  return (x % m + m) % m; }
// CRT: x = a (mod m), x = b (mod n), 0<=a<m, 0<=b<n.
// Returns {x, lcm(m,n)} or {-1,-1} if no solution.
pair<ll, ll> crt(ll a, ll m, ll b, ll n) {
  ll x, y, g = egcd(m, n, x, y);
  if ((b - a) % g) return {-1, -1};
  ll l = m / g * n;
  ll t = (__int128)(b - a) / g * x % (n / g);
  ll r = (a + (__int128)t * m) % l;
  return {r < 0 ? r + l : r, l}; }
