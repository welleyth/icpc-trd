// Mo with rollback: when remove is impossible (max, max xor
// with a trie, DSU) but add + undo is easy. Queries [l, r).
// snap() returns a checkpoint (e.g. history size), roll(t)
// undoes back to it; get() reads the answer (keep it in the
// undoable state). O((n + q) sqrt n) adds.
template <class Add, class Get, class Snap, class Roll>
vector<ll> moRollback(int n, const vector<pii>& qs, Add add,
                      Get get, Snap snap, Roll roll) {
  int q = sz(qs), B = max(1, (int)sqrt(n));
  vi ord(q); iota(all(ord), 0);
  sort(all(ord), [&](int a, int b) {
    if (qs[a].first / B != qs[b].first / B)
      return qs[a].first / B < qs[b].first / B;
    return qs[a].second < qs[b].second; });
  vector<ll> res(q); auto base = snap();
  int cur = -1, r = 0;
  for (int i : ord) {
    auto [ql, qr] = qs[i];
    int b = ql / B, bend = min(n, (b + 1) * B);
    if (qr <= bend) {                  // short: brute force
      roll(base); cur = -1;
      for (int j = ql; j < qr; j++) add(j);
      res[i] = get(); roll(base); continue;
    }
    if (b != cur) { roll(base); cur = b; r = bend; }
    while (r < qr) add(r++);
    auto t = snap();
    for (int j = bend - 1; j >= ql; j--) add(j);
    res[i] = get(); roll(t);
  }
  return res; }
