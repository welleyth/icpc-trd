// Virtual (auxiliary) tree of key vertices ks: the keys plus
// their pairwise LCAs, O(k log n). tin = DFS preorder (e.g.
// HLD::pos), lca = HLD::lca. Returns its vertices in preorder
// (first = root); vpar[v] = virtual parent (-1 for the root).
// Edge (vpar[v], v) stands for a path of dep[v]-dep[vpar[v]].
template <class F>
vi virtualTree(vi ks, const vi& tin, F lca, vi& vpar) {
  auto cmp = [&](int a, int b) { return tin[a] < tin[b]; };
  sort(all(ks), cmp);
  for (int i = 0, k = sz(ks); i + 1 < k; i++)
    ks.push_back(lca(ks[i], ks[i + 1]));
  sort(all(ks), cmp); ks.erase(unique(all(ks)), ks.end());
  for (int i = 0; i < sz(ks); i++)
    vpar[ks[i]] = i ? lca(ks[i - 1], ks[i]) : -1;
  return ks; }
// Typical use: sum of k over all queries <= 2e5; run a DP on
// the virtual tree (children = reverse of vpar) per query.
