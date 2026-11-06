// Binary trie for max XOR with a stored number (B bits).
struct Trie {
  static const int B = 30;
  vector<array<int, 2>> nx{{0, 0}}; vi cnt{0};
  void add(int x, int d = 1) {      // d = -1 removes
    int u = 0;
    for (int i = B - 1; i >= 0; i--) {
      int b = x >> i & 1;
      if (!nx[u][b]) {
        nx[u][b] = sz(nx);
        nx.push_back({0, 0}); cnt.push_back(0);
      }
      u = nx[u][b]; cnt[u] += d;
    } }
  int maxXor(int x) {               // trie must be non-empty
    int u = 0, r = 0;
    for (int i = B - 1; i >= 0; i--) {
      int b = x >> i & 1, w = nx[u][!b];
      if (w && cnt[w] > 0) r |= 1 << i, u = w;
      else u = nx[u][b];
    }
    return r; }
};
