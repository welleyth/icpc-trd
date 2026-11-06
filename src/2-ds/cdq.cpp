// CDQ divide & conquer: offline 3D dominance. For each point i
// count j != i with a_j <= a_i, b_j <= b_i, c_j <= c_i.
// Sort by (a, b, c), merge equal points (weight w).
// solve(l, r):
// recurse on halves; count (left j, right i) pairs by a sweep
// over b with a Fenwick tree on c; merge halves by b.
// O(n log^2 n). Needs fenwick.cpp; c compressed to [0, C).
// Same scheme: offline queries over time (left = updates,
// right = queries), 4D = CDQ inside CDQ.
vi dominance(const vector<array<int, 3>>& pts, int C) {
  int n = sz(pts); vi idx(n), grp(n);
  iota(all(idx), 0);
  sort(all(idx),
       [&](int x, int y) { return pts[x] < pts[y]; });
  vector<array<int, 3>> u; vi w;
  for (int i : idx) {
    if (u.empty() || u.back() != pts[i]) {
      u.push_back(pts[i]); w.push_back(0); }
    w.back()++; grp[i] = sz(u) - 1;
  }
  int m = sz(u); vi cnt(m), ord(m); iota(all(ord), 0);
  BIT bit(C);
  auto byB = [&](int x, int y) { return u[x][1] < u[y][1]; };
  auto solve = [&](auto&& self, int l, int r) -> void {
    if (r - l <= 1) return;
    int mid = (l + r) / 2;
    self(self, l, mid); self(self, mid, r);
    int j = l;
    for (int i = mid; i < r; i++) {
      for (; j < mid && u[ord[j]][1] <= u[ord[i]][1]; j++)
        bit.add(u[ord[j]][2], w[ord[j]]);
      cnt[ord[i]] += bit.sum(u[ord[i]][2] + 1);
    }
    for (int k = l; k < j; k++)          // undo the adds
      bit.add(u[ord[k]][2], -w[ord[k]]);
    inplace_merge(ord.begin() + l, ord.begin() + mid,
                  ord.begin() + r, byB);
  };
  solve(solve, 0, m);
  vi res(n);
  for (int i = 0; i < n; i++)
    res[i] = cnt[grp[i]] + w[grp[i]] - 1;
  return res; }
