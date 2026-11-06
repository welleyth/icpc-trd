#include "t_util.h"
#include "../src/2-ds/treap.cpp"
void walk(int t, vector<ll>& out) { if (!t) return; push(t); walk(L[t], out); out.push_back(V[t]); walk(R[t], out); }
void resetT() { for (int i = 0; i <= cnt; i++) L[i] = R[i] = S[i] = 0, Sum[i] = V[i] = 0, Rev[i] = 0; cnt = 0; }
int main() {
  for (int it = 0; it < 5000; it++) {
    resetT(); int root = 0; vector<ll> v;
    for (int q = 0; q < 60; q++) {
      int op = rnd(0, 4), n = sz(v);
      int a, b, c, m;
      if (op == 0 || n == 0) { int i = rnd(0, n); ll x = rnd(-1000000000, 1000000000); split(root, i, a, b); root = merge(merge(a, node(x)), b); v.insert(v.begin() + i, x); }
      else if (op == 1) { int i = rnd(0, n - 1); split(root, i, a, b); split(b, 1, m, c); root = merge(a, c); v.erase(v.begin() + i); }
      else if (op == 2) { int l = rnd(0, n), r = rnd(l, n); split(root, r, a, c); split(a, l, a, b); Rev[b] ^= 1; root = merge(merge(a, b), c); reverse(v.begin() + l, v.begin() + r); }
      else if (op == 3) { int l = rnd(0, n), r = rnd(l, n); split(root, r, a, c); split(a, l, a, b); ll e = 0; for (int k = l; k < r; k++) e += v[k]; CHECK(Sum[b] == e); CHECK(S[b] == r - l); root = merge(merge(a, b), c); }
      else { vector<ll> w; walk(root, w); CHECK(w == v); }
      CHECK(S[root] == sz(v));
    }
    vector<ll> w; walk(root, w); CHECK(w == v);
  }
  // big: sequential appends and reversals
  resetT(); int root = 0; int N = 300000;
  for (int i = 0; i < N; i++) { int a, b; split(root, i, a, b); root = merge(merge(a, node(i)), b); }
  { int a, b, c; split(root, N, a, c); split(a, 0, a, b); Rev[b] ^= 1; root = merge(merge(a, b), c); }
  vector<ll> w; walk(root, w); CHECK(sz(w) == N); for (int i = 0; i < N; i++) CHECK(w[i] == N - 1 - i);
  puts("ok");
}
