#include "t_util.h"
#include "../src/2-ds/mo.cpp"
int main() {
  for (int it = 0; it < 3000; it++) {
    int n = it < 200 ? 1 : rnd(1, it % 10 == 0 ? 400 : 30), V = rnd(1, 8);
    vi a(n); for (int& x : a) x = rnd(0, V - 1);
    int q = it % 50 == 0 ? 0 : rnd(1, it % 7 == 0 ? 1000 : 40);
    vector<pii> qs;
    for (int i = 0; i < q; i++) { int l = rnd(0, n), r = rnd(l, n); if (i % 4 == 0) r = l; qs.push_back({l, r}); }
    vi cnt(V); ll d = 0;
    auto res = mo(n, qs, [&](int i) { if (cnt[a[i]]++ == 0) d++; }, [&](int i) { if (--cnt[a[i]] == 0) d--; }, [&] { return d; });
    CHECK(sz(res) == q);
    for (int i = 0; i < q; i++) { set<int> s(a.begin() + qs[i].first, a.begin() + qs[i].second); CHECK(res[i] == sz(s)); }
  }
  { // big timing
    int n = 200000, q = 200000; vi a(n); for (int& x : a) x = rnd(0, 1000); vector<pii> qs; for (int i = 0; i < q; i++) { int l = rnd(0, n), r = rnd(0, n); if (l > r) swap(l, r); qs.push_back({l, r}); }
    vi cnt(1001); ll d = 0; auto res = mo(n, qs, [&](int i) { if (cnt[a[i]]++ == 0) d++; }, [&](int i) { if (--cnt[a[i]] == 0) d--; }, [&] { return d; });
    for (int i = 0; i < 20; i++) { set<int> s(a.begin() + qs[i].first, a.begin() + qs[i].second); CHECK(res[i] == sz(s)); }
  }
  puts("ok");
}
