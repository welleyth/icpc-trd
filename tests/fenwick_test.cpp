#include "t_util.h"
#include "../src/2-ds/fenwick.cpp"
int main() {
  for (int it = 0; it < 20000; it++) {
    int n = rnd(1, 40); BIT b(n); vector<ll> a(n);
    int mode = it % 3; // 0: sparse zeros, 1: dense, 2: all zero
    for (int q = 0; q < 30; q++) {
      int i = rnd(0, n - 1); ll v = mode == 2 ? 0 : (mode == 0 ? (rnd(0, 3) ? 0 : rnd(0, 5)) : rnd(0, 9));
      if (mode == 1 && it % 2) v = rnd(-5, 5), v = abs(v);
      a[i] += v; b.add(i, v);
      for (int l = 0; l <= n; l++) { ll s = 0; for (int r = l; r <= n; r++) { CHECK(b.sum(l, r) == s); if (r < n) s += a[r]; } }
      for (int i2 = 0; i2 < n; i2++) { } 
      // lowerBound for all s from -1..total+2
      ll tot = accumulate(all(a), 0LL);
      for (ll s = -2; s <= tot + 2; s++) {
        int exp = n; ll p = 0; for (int k = 0; k < n; k++) { p += a[k]; if (p >= s) { exp = k; break; } }
        CHECK(b.lowerBound(s) == exp);
      }
    }
  }
  { BIT b(1); b.add(0, 5); CHECK(b.lowerBound(5) == 0 && b.lowerBound(6) == 1 && b.lowerBound(0) == 0 && b.sum(0, 1) == 5); }
  { BIT b(8); b.add(7, 1); CHECK(b.lowerBound(1) == 7 && b.lowerBound(2) == 8); }
  { BIT b(5); CHECK(b.lowerBound(1) == 5); b.add(4, 3); CHECK(b.lowerBound(3) == 4 && b.lowerBound(1) == 4); }
  // large n
  { int n = 100000; BIT b(n); for (int i = 0; i < n; i++) b.add(i, i % 3 == 0); vector<ll> pre(n + 1);
    for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + (i % 3 == 0);
    for (ll s = 1; s <= pre[n] + 1; s += 7) { int e = lower_bound(pre.begin() + 1, pre.end(), s) - pre.begin() - 1; CHECK(b.lowerBound(s) == e); } }
  // range add point query usage and inversions
  { int n = 20; BIT b(n); vector<ll> a(n);
    for (int q = 0; q < 1000; q++) { int l = rnd(0, n - 1), r = rnd(l + 1, n); ll v = rnd(-9, 9); b.add(l, v); if (r < n) b.add(r, -v); for (int i = l; i < r; i++) a[i] += v;
      for (int i = 0; i < n; i++) CHECK(b.sum(i + 1) == a[i]); } }
  for (int it = 0; it < 2000; it++) { int n = rnd(1, 20); vi a(n); iota(all(a), 0); shuffle(all(a), trg); BIT b(n); ll inv = 0;
    for (int i = 0; i < n; i++) { inv += i - b.sum(a[i] + 1); b.add(a[i], 1); }
    ll e = 0; for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) e += a[i] > a[j]; CHECK(inv == e); }
  puts("ok");
}
