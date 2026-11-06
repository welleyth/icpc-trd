// Dijkstra, w >= 0. g[u] = {(v, w)}. O(m log m)
using Adj = vector<vector<pair<int, ll>>>;
const ll INF = 4e18;
vector<ll> dijkstra(const Adj& g, int s) {
  vector<ll> d(sz(g), INF);
  priority_queue<pair<ll, int>, vector<pair<ll, int>>,
                 greater<>> pq;
  pq.push({d[s] = 0, s});
  while (!pq.empty()) {
    auto [du, u] = pq.top(); pq.pop();
    if (du != d[u]) continue;
    for (auto [v, w] : g[u])
      if (du + w < d[v]) pq.push({d[v] = du + w, v});
  }
  return d; }
// 0-1 BFS: weights 0/1, deque; w=0 -> push_front, else back.
vector<ll> bfs01(const Adj& g, int s) {
  vector<ll> d(sz(g), INF); deque<int> q{s}; d[s] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop_front();
    for (auto [v, w] : g[u]) if (d[u] + w < d[v]) {
      d[v] = d[u] + w;
      w ? q.push_back(v) : q.push_front(v); }
  }
  return d; }
// Bellman-Ford, any weights; edges (u, v, w). O(nm).
// Returns false if a negative cycle is reachable from s.
bool bellman(int n, vector<array<ll, 3>>& e, int s,
             vector<ll>& d) {
  d.assign(n, INF); d[s] = 0;
  for (int it = 0; it < n; it++) {
    bool ch = false;
    for (auto [u, v, w] : e)
      if (d[u] < INF && d[u] + w < d[v])
        d[v] = d[u] + w, ch = true;
    if (!ch) return true;
  }
  return false; }
// Floyd: for k: for i: for j:  (k is the OUTER loop!)
//   d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
// Negative cycle <=> some d[i][i] < 0.
