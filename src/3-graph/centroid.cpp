// Centroid decomposition: every path passes through the
// centroid that is highest in the centroid tree. O(n log n)
// times the work per level.
vector<vi> g; vi sub, cpar; vector<bool> removed;
int calcSize(int u, int p) {
  sub[u] = 1;
  for (int v : g[u]) if (v != p && !removed[v])
    sub[u] += calcSize(v, u);
  return sub[u]; }
int findCentroid(int u, int p, int n) {
  for (int v : g[u])
    if (v != p && !removed[v] && 2 * sub[v] > n)
      return findCentroid(v, u, n);
  return u; }
void build(int u, int p = -1) {   // sub, cpar, removed sized n
  int c = findCentroid(u, -1, calcSize(u, -1));
  cpar[c] = p; removed[c] = true;
  // ... count paths through c: DFS into each child subtree
  // of c (only !removed vertices), combine with earlier ones
  for (int v : g[c]) if (!removed[v]) build(v, c);
}
