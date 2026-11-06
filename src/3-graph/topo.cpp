// Kahn topological order of a DAG; size < n => has a cycle.
// For lexicographically smallest order use a min-heap.
vi topo(const vector<vi>& g) {
  int n = sz(g); vi indeg(n), order;
  for (auto& es : g) for (int v : es) indeg[v]++;
  for (int i = 0; i < n; i++)
    if (!indeg[i]) order.push_back(i);
  for (int i = 0; i < sz(order); i++)
    for (int v : g[order[i]])
      if (!--indeg[v]) order.push_back(v);
  return order; }
// Bipartite check: BFS coloring c[v] = c[u] ^ 1; conflict =>
// odd cycle. Grid BFS: dx[] = {1,-1,0,0}, dy[] = {0,0,1,-1}.
