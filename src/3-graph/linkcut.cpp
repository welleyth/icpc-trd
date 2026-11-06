// Link-cut tree: dynamic forest, O(log n) amortised. Nodes
// 1..n (0 = null). Unrooted: link(u, v) joins two trees,
// cut(u, v) removes the edge u-v, connected(u, v).
// Rooted forest (fixed roots, e.g. pointer graphs): only
// linkRooted / cutParent / findRoot; never call makeRoot.
// Path sums: add val/sum, recompute in a pull() after rotate
// and access (like the treap).
struct LCT {
  vector<array<int, 2>> ch; vi p; vector<bool> rev;
  LCT(int n) : ch(n + 1), p(n + 1), rev(n + 1) {}
  bool isRoot(int x) {        // root of its splay tree
    return ch[p[x]][0] != x && ch[p[x]][1] != x; }
  void push(int x) {
    if (!rev[x]) return;
    swap(ch[x][0], ch[x][1]);
    for (int c : ch[x]) if (c) rev[c] = !rev[c];
    rev[x] = false; }
  void rotate(int x) {
    int y = p[x], z = p[y], d = ch[y][1] == x;
    if (!isRoot(y)) ch[z][ch[z][1] == y] = x;
    p[x] = z; ch[y][d] = ch[x][!d];
    if (ch[x][!d]) p[ch[x][!d]] = y;
    ch[x][!d] = y; p[y] = x; }
  void splay(int x) {
    vi st{x};
    for (int y = x; !isRoot(y); y = p[y]) st.push_back(p[y]);
    for (int i = sz(st) - 1; i >= 0; i--) push(st[i]);
    while (!isRoot(x)) {
      int y = p[x], z = p[y];
      if (!isRoot(y))
        rotate((ch[y][1] == x) == (ch[z][1] == y) ? y : x);
      rotate(x);
    } }
  void access(int x) {
    for (int last = 0; x; last = x, x = p[x]) {
      splay(x); ch[x][1] = last; } }
  void makeRoot(int x) {
    access(x); splay(x); rev[x] = !rev[x]; }
  int findRoot(int x) {
    access(x); splay(x);
    while (push(x), ch[x][0]) x = ch[x][0];
    splay(x); return x; }
  bool connected(int u, int v) {
    return findRoot(u) == findRoot(v); }
  void link(int u, int v) { makeRoot(u); p[u] = v; }
  void cut(int u, int v) {               // edge u-v must exist
    makeRoot(u); access(v); splay(v); ch[v][0] = p[u] = 0; }
  void linkRooted(int u, int v) {          // u is a tree root
    access(u); splay(u); p[u] = v; }
  void cutParent(int u) {                  // u is not a root
    access(u); splay(u); p[ch[u][0]] = 0; ch[u][0] = 0; }
};
