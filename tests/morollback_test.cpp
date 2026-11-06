#include "t_util.h"
#include "../src/2-ds/morollback.cpp"
int main() {
  for (int it = 0; it < 6000; it++) {
    int n = it % 10 == 0 ? 1 : rnd(1, it % 4 == 0 ? 200 : 25); ll V = it % 2 ? 7 : 1000000000;
    vector<ll> a(n); for (ll& v : a) v = rnd(0, V);
    int q = rnd(1, 60); vector<pii> qs(q);
    for (auto& [l, r] : qs) { l = rnd(0, n); r = rnd(l, n); if (rnd(0, 4) == 0) r = l; if (rnd(0, 6) == 0) l = r = rnd(0, n); if (rnd(0,4)==0) r = min<ll>(n, l + rnd(0, 3)); }
    // part 1: max element with history (-1 if empty)
    {
      ll cur = -1; vector<ll> hist;
      auto res = moRollback(n, qs, [&](int i) { hist.push_back(cur); cur = max(cur, a[i]); },
                            [&]() { return cur; }, [&]() { return sz(hist); },
                            [&](int t) { while (sz(hist) > t) cur = hist.back(), hist.pop_back(); });
      for (int i = 0; i < q; i++) { ll m = -1; for (int k = qs[i].first; k < qs[i].second; k++) m = max(m, a[k]); CHECK(res[i] == m); }
    }
    // part 2: max xor of pair via trie with history (0 if < 2 elements... empty-state best=0)
    {
      vector<array<int,2>> ch(1); vector<int> hist;   // hist of nodes created count & best
      ll best = 0; vector<tuple<int,ll>> h; int cntEl = 0;
      auto add = [&](int idx) {
        ll v = a[idx]; h.push_back({sz(ch), best});
        if (cntEl > 0) { int x = 0; ll r = 0; for (int b = 30; b >= 0; b--) { int bit = v >> b & 1; if (ch[x][bit ^ 1]) { r |= 1LL << b; x = ch[x][bit ^ 1]; } else x = ch[x][bit]; } best = max(best, r); }
        int x = 0; vector<pii> links;
        for (int b = 30; b >= 0; b--) { int bit = v >> b & 1; if (!ch[x][bit]) { ch.push_back({0, 0}); ch[x][bit] = sz(ch) - 1; links.push_back({x, bit}); } x = ch[x][bit]; }
        cntEl++; };
      // undo needs links; simpler: store them in a stack
      vector<vector<pii>> lk; vector<ll> bh; vector<int> ce; ch.assign(1, {0, 0}); best = 0; cntEl = 0;
      auto add2 = [&](int idx) {
        ll v = a[idx]; bh.push_back(best); ce.push_back(cntEl);
        if (cntEl > 0) { int x = 0; ll r = 0; for (int b = 30; b >= 0; b--) { int bit = v >> b & 1; if (ch[x][bit ^ 1]) { r |= 1LL << b; x = ch[x][bit ^ 1]; } else x = ch[x][bit]; } best = max(best, r); }
        int x = 0; vector<pii> links;
        for (int b = 30; b >= 0; b--) { int bit = v >> b & 1; if (!ch[x][bit]) { ch.push_back({0, 0}); ch[x][bit] = sz(ch) - 1; links.push_back({x, bit}); } x = ch[x][bit]; }
        lk.push_back(links); cntEl++; };
      (void)add;
      auto res = moRollback(n, qs, add2, [&]() { return best; }, [&]() { return sz(bh); },
        [&](int t) { while (sz(bh) > t) { for (auto [x, b] : lk.back()) { ch[x][b] = 0; } ch.resize(ch.size() - lk.back().size()); lk.pop_back(); best = bh.back(); bh.pop_back(); cntEl = ce.back(); ce.pop_back(); } });
      for (int i = 0; i < q; i++) { ll m = 0; for (int x = qs[i].first; x < qs[i].second; x++) for (int y = x + 1; y < qs[i].second; y++) m = max(m, a[x] ^ a[y]); CHECK(res[i] == m); }
    }
    // part 3: distinct count with counts + history
    {
      vector<int> c(V < 100 ? V + 1 : 0); map<ll,int> mc; int dist = 0; vector<ll> hv;
      auto res = moRollback(n, qs, [&](int i) { if (mc[a[i]]++ == 0) dist++; hv.push_back(a[i]); },
        [&]() { return (ll)dist; }, [&]() { return sz(hv); },
        [&](int t) { while (sz(hv) > t) { if (--mc[hv.back()] == 0) dist--; hv.pop_back(); } });
      for (int i = 0; i < q; i++) { set<ll> s(a.begin() + qs[i].first, a.begin() + qs[i].second); CHECK(res[i] == sz(s)); }
    }
  }
  puts("ok");
}
