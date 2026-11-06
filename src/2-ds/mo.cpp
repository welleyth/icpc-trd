// Mo's algorithm: offline queries [l, r) on a static array.
// add(i) / rem(i) change the current window, get() = answer.
// O((n + q) sqrt n) calls of add/rem: keep them O(1).
template <class Add, class Rem, class Get>
vector<ll> mo(int n, const vector<pii>& qs, Add add, Rem rem,
              Get get) {
  int q = sz(qs), B = max(1, int(n / sqrt(max(q, 1))));
  vi ord(q); iota(all(ord), 0);
  sort(all(ord), [&](int a, int b) {
    int x = qs[a].first / B, y = qs[b].first / B;
    if (x != y) return x < y;
    return x & 1 ? qs[a].second > qs[b].second
                 : qs[a].second < qs[b].second; });
  vector<ll> res(q); int l = 0, r = 0;   // window [l, r)
  for (int i : ord) {
    auto [ql, qr] = qs[i];
    while (r < qr) add(r++);
    while (l > ql) add(--l);
    while (r > qr) rem(--r);
    while (l < ql) rem(l++);
    res[i] = get();
  }
  return res; }
