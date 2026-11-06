__builtin_popcountll(x); __builtin_ctzll(x);  // x != 0
__builtin_clzll(x); __lg(x) /* = floor(log2 x) */;
x & -x;          // lowest set bit
mt19937_64 rng(chrono::steady_clock::now()
                 .time_since_epoch().count());
shuffle(all(v), rng);
// __int128 output:
string str128(__int128 x) {
  if (x == 0) return "0";
  string s; bool neg = x < 0;
  unsigned __int128 u = neg ? -(unsigned __int128)x : x;
  while (u) s += char('0' + u % 10), u /= 10;
  if (neg) s += '-';
  return string(s.rbegin(), s.rend()); }
// ceil / floor of a / b for b > 0, any sign of a
// (plain a / b rounds toward zero: -7 / 2 == -3):
ll ceilDiv(ll a, ll b) { return a / b + ((a % b) > 0); }
ll floorDiv(ll a, ll b) { return a / b - ((a % b) < 0); }
// Coordinate compression:
//   vi c = a; sort(all(c)); c.erase(unique(all(c)), c.end());
//   x -> lower_bound(all(c), x) - c.begin()
// Print doubles: cout << fixed << setprecision(10) << x;
// Interactive: cout << "? " << x << endl;  (endl flushes);
//   read answer; on -1 exit immediately. Count queries!
// Big recursion depth (1e6): use iterative or BFS order.
