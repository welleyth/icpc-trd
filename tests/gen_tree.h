// random tree helper for new tests
static vector<vi> randTree(int n, vi& pr, vi& dep, int& root) {
  vector<vi> g(n); vi lab(n); iota(all(lab), 0);
  shuffle(all(lab), rng_);
  int shape = rnd(0, 3);
  for (int i = 1; i < n; i++) {
    int pp = shape == 0 ? rnd(0, i-1) : shape == 1 ? i-1
      : shape == 2 ? max(0, i-1-rnd(0,2)) : 0;
    g[lab[i]].push_back(lab[pp]); g[lab[pp]].push_back(lab[i]); }
  root = rnd(0, n-1);
  pr.assign(n, -1); dep.assign(n, -1); dep[root] = 0; vi q{root};
  for (int i = 0; i < sz(q); i++) for (int v : g[q[i]])
    if (dep[v] < 0) { dep[v]=dep[q[i]]+1; pr[v]=q[i]; q.push_back(v); }
  return g; }
static int bfLca(int a, int b, const vi& pr, const vi& dep) {
  while (a != b) { if (dep[a] < dep[b]) swap(a, b); a = pr[a]; }
  return a; }
