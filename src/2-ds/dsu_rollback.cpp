// DSU with rollback (union by size, NO path compression):
// O(log n) per find. t = time(); ...; rollback(t) undoes
// all unions made after t.
struct RDSU {
  vi p; vector<pii> st; int comps;      // p[root] = -size
  RDSU(int n) : p(n, -1), comps(n) {}
  int find(int x) { while (p[x] >= 0) x = p[x]; return x; }
  bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (p[a] > p[b]) swap(a, b);
    st.push_back({b, p[b]}); p[a] += p[b]; p[b] = a; comps--;
    return true; }
  int time() { return sz(st); }
  void rollback(int t) {
    while (sz(st) > t) {
      auto [b, pb] = st.back(); st.pop_back();
      p[p[b]] -= pb; p[b] = pb; comps++;
    } }
};
