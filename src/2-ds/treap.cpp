// Implicit treap (array with split/merge): insert, erase,
// reverse, range sum at any position. O(log n) expected.
const int MX = 1e6 + 5;            // node 0 = empty
int L[MX], R[MX], S[MX], cnt; unsigned Pri[MX];
ll V[MX], Sum[MX]; bool Rev[MX];
mt19937 trng(123);
int node(ll v) {
  ++cnt; Pri[cnt] = trng(); S[cnt] = 1; V[cnt] = Sum[cnt] = v;
  return cnt; }
void push(int x) {
  if (x && Rev[x]) {
    swap(L[x], R[x]); Rev[L[x]] ^= 1; Rev[R[x]] ^= 1;
    Rev[x] = 0; } }
void pull(int x) {
  S[x] = 1 + S[L[x]] + S[R[x]];
  Sum[x] = V[x] + Sum[L[x]] + Sum[R[x]]; }
// a = first k elements of t, b = the rest
void split(int t, int k, int& a, int& b) {
  if (!t) { a = b = 0; return; }
  push(t);
  if (S[L[t]] < k)
    split(R[t], k - S[L[t]] - 1, R[t], b), a = t;
  else split(L[t], k, a, L[t]), b = t;
  pull(t); }
int merge(int a, int b) {
  if (!a || !b) return a | b;
  if (Pri[a] > Pri[b]) { push(a); R[a] = merge(R[a], b);
                     pull(a); return a; }
  push(b); L[b] = merge(a, L[b]); pull(b); return b; }
// reverse [l, r): split(root, r, a, c); split(a, l, a, b);
// Rev[b] ^= 1; root = merge(merge(a, b), c);
// insert v at pos i: split(root, i, a, b);
// root = merge(merge(a, node(v)), b);
