#include "t_util.h"
#include "../src/2-ds/dsu.cpp"
int main() {
  for (int it = 0; it < 5000; it++) {
    int n = rnd(1, 30); DSU d(n); vi c(n); iota(all(c), 0);
    for (int q = 0; q < 60; q++) {
      int a = rnd(0, n - 1), b = rnd(0, n - 1);
      bool diff = c[a] != c[b];
      CHECK(d.unite(a, b) == diff);
      if (diff) { int o = c[b], nw = c[a]; for (int& x : c) if (x == o) x = nw; }
      int x = rnd(0, n - 1), y = rnd(0, n - 1);
      CHECK((d.find(x) == d.find(y)) == (c[x] == c[y]));
      CHECK(d.size(x) == count(all(c), c[x]));
    }
  }
  DSU d(1); CHECK(d.size(0) == 1 && !d.unite(0, 0));
  DSU e(200000); for (int i = 1; i < 200000; i++) e.unite(i - 1, i); CHECK(e.size(5) == 200000);
  DSU f(200000); for (int i = 199999; i > 0; i--) f.unite(i, i - 1); CHECK(f.size(5) == 200000 && f.find(0) == f.find(199999));
  puts("ok");
}
