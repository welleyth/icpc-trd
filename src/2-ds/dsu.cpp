// Disjoint set union, O(alpha(n)) amortized.
struct DSU {
  vi p;                        // p[root] = -size
  DSU(int n) : p(n, -1) {}
  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  int size(int x) { return -p[find(x)]; }
  bool unite(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (p[a] > p[b]) swap(a, b);
    p[a] += p[b]; p[b] = a;
    return true; }
};
// Kruskal: sort edges by w; if (d.unite(u, v)) cost += w;
