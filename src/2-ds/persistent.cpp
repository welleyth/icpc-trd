// Persistent segment tree (counts over values [0, V)).
// Every padd makes a new version with O(log V) new nodes;
// node 0 = empty tree (version 0). Memory: n * (log2 V + 2).
// k-th smallest of a[l, r) (k 0-based, values compressed):
//   root[0] = 0; root[i + 1] = padd(root[i], 0, V, a[i]);
//   kth(root[l], root[r], 0, V, k)
const int PM = 2e5 * 20;
int Lc[PM], Rc[PM], Cnt[PM], pn = 1;
int padd(int t, int l, int r, int pos) {
  int x = pn++;
  Lc[x] = Lc[t]; Rc[x] = Rc[t]; Cnt[x] = Cnt[t] + 1;
  if (r - l > 1) {
    int m = (l + r) / 2;
    if (pos < m) Lc[x] = padd(Lc[t], l, m, pos);
    else Rc[x] = padd(Rc[t], m, r, pos);
  }
  return x; }
int kth(int a, int b, int l, int r, int k) {   // tree b - a
  if (r - l == 1) return l;
  int m = (l + r) / 2, c = Cnt[Lc[b]] - Cnt[Lc[a]];
  return k < c ? kth(Lc[a], Lc[b], l, m, k)
               : kth(Rc[a], Rc[b], m, r, k - c); }
