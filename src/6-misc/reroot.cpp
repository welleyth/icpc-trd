// RE-ROOTING: answer for EVERY root in O(n) total.
// Pass 1 (down): dp over subtrees for root 0.
// Pass 2 (up):   for each child c of v, compute "the tree
// without c's subtree, seen from v" and push it down to c.
//
// (1) Invertible merge (sum, xor, count): remove the child's
// contribution by subtraction. Sum of distances to all nodes:
//   sub[v] = subtree size, ans[0] = sum of depths;
//   ans[c] = ans[v] - sub[c] + (n - sub[c]).
// (2) max/min merge: keep the best AND second best child
// value of v; for child c use the second if c gave the best.
//   e.g. farthest vertex from every v:
//   up[c] = 1 + max(up[v], best child of v other than c).
//
// (3) Generic (any associative merge): prefix/suffix over
// children. T = value of a rooted subtree seen from its
// parent; merge = combine siblings (identity ID);
// lift(x, v) = value of v's subtree when x = merged children.
// Returns res[v] = merge of ALL neighbours of v (seen from v).
// Example below: T = {size, sum of distances to parent}.
using T = pair<ll, ll>;
const T ID = {0, 0};
T merge(T a, T b) { return {a.first + b.first,
                            a.second + b.second}; }
T lift(T x, int v) { return {x.first + 1,
                             x.second + x.first + 1}; }
vector<T> reroot(const vector<vi>& g, int root = 0) {
  int n = sz(g); vi order{root}, par(n, -1);
  for (int i = 0; i < sz(order); i++)       // BFS order
    for (int v : g[order[i]]) if (v != par[order[i]])
      par[v] = order[i], order.push_back(v);
  vector<T> down(n, ID), up(n, ID), res(n);
  for (int i = n - 1; i > 0; i--) {
    int v = order[i];
    down[par[v]] = merge(down[par[v]], lift(down[v], v));
  }
  for (int u : order) {
    vi ch;
    for (int v : g[u]) if (v != par[u]) ch.push_back(v);
    int k = sz(ch); vector<T> pre(k + 1, ID), suf(k + 1, ID);
    for (int i = 0; i < k; i++)
      pre[i + 1] = merge(pre[i], lift(down[ch[i]], ch[i]));
    for (int i = k - 1; i >= 0; i--)
      suf[i] = merge(lift(down[ch[i]], ch[i]), suf[i + 1]);
    res[u] = merge(up[u], pre[k]);
    for (int i = 0; i < k; i++) {      // parent side for ch[i]
      T rest = merge(up[u], merge(pre[i], suf[i + 1]));
      up[ch[i]] = lift(rest, u);
    }
  }
  return res; }   // here: res[v].second = sum of dist from v
