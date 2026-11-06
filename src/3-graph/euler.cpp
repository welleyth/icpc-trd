// Euler path/cycle (Hierholzer). g[u] = {(v, edge id)};
// undirected: add the edge to both ends with the same id.
// Start: undirected -> a vertex of odd degree (if any);
// directed -> vertex with out - in = 1 (if any).
// Returns vertices of the path. First check the degrees (0/2
// odd; directed: out-in all 0 or one +1 and one -1); then
// size != m + 1 -> graph not connected -> no path.
vi euler(const vector<vector<pii>>& g, int m, int s) {
  vi it(sz(g)), path, st{s}; vector<bool> used(m);
  while (!st.empty()) {
    int u = st.back(); int& i = it[u];
    while (i < sz(g[u]) && used[g[u][i].second]) i++;
    if (i == sz(g[u])) { path.push_back(u); st.pop_back(); }
    else { used[g[u][i].second] = true;
           st.push_back(g[u][i].first); }
  }
  reverse(all(path));
  return path; }
