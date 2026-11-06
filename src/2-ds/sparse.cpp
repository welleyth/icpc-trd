// Range min on [l, r) in O(1) after O(n log n) build.
struct Sparse {
  vector<vi> t;
  Sparse(const vi& a) : t{a} {
    for (int k = 1; (1 << k) <= sz(a); k++) {
      t.emplace_back(sz(a) - (1 << k) + 1);
      for (int i = 0; i < sz(t[k]); i++)
        t[k][i] = min(t[k - 1][i],
                      t[k - 1][i + (1 << (k - 1))]);
    }
  }
  int query(int l, int r) {          // requires l < r
    int k = __lg(r - l);
    return min(t[k][l], t[k][r - (1 << k)]); }
};
