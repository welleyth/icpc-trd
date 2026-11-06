// Binary trie with a min per node: min of val over stored y
// with (x ^ y) <= k. Count version: store counts, add them up.
// Walk: where k has bit 1, the whole subtree with xor bit 0 is
// valid (take its aggregate), then continue on xor bit 1.
struct XorTrie {
  static const int B = 30;
  vector<array<int, 2>> nx{{0, 0}}; vector<ll> mn{LLONG_MAX};
  void add(int y, ll v) {
    int u = 0; mn[0] = min(mn[0], v);
    for (int i = B - 1; i >= 0; i--) {
      int b = y >> i & 1;
      if (!nx[u][b]) {
        nx[u][b] = sz(nx); nx.push_back({0, 0});
        mn.push_back(LLONG_MAX);
      }
      u = nx[u][b]; mn[u] = min(mn[u], v);
    } }
  ll query(int x, int k) {       // LLONG_MAX if no such y
    ll r = LLONG_MAX; int u = 0;
    for (int i = B - 1; i >= 0; i--) {
      int xb = x >> i & 1;
      if (k >> i & 1) {
        if (nx[u][xb]) r = min(r, mn[nx[u][xb]]);
        u = nx[u][!xb];
      } else u = nx[u][xb];
      if (!u) return r;
    }
    return min(r, mn[u]); }
};
