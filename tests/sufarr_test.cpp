#include "common.h"
#include "../src/4-string/sufarr.cpp"
#include "chk.h"
string rs(int n, int a) { string s; while (n--) s += 'a' + rnd(0, a-1); return s; }
int main() {
  CHECK(suffixArray("").empty()); CHECK(lcpArray("", {}).empty());
  CHECK(suffixArray("a") == vi{0}); CHECK(lcpArray("a", {0}).empty());
  for (int iter = 0; iter < 50000; iter++) {
    string s = rs(rnd(0, 16), rnd(1, 3)); int n = sz(s);
    if (iter % 100 == 0) { s = string(rnd(1, 30), 'a'); n = sz(s); }
    auto sa = suffixArray(s);
    vi bf(n); iota(all(bf), 0);
    sort(all(bf), [&](int a, int b) { return s.substr(a) < s.substr(b); });
    CHECK(sa == bf);
    auto lcp = lcpArray(s, sa);
    CHECK(sz(lcp) == max(0, n-1));
    ll sum = 0;
    for (int i = 0; i + 1 < n; i++) {
      int k = 0; string x = s.substr(sa[i]), y = s.substr(sa[i+1]);
      while (k < sz(x) && k < sz(y) && x[k] == y[k]) k++;
      CHECK(lcp[i] == k); sum += lcp[i]; }
    set<string> ss; for (int i = 0; i < n; i++) for (int l = 1; i+l <= n; l++) ss.insert(s.substr(i, l));
    CHECK((ll)n*(n+1)/2 - sum == sz(ss));
  }
  // large
  string s = rs(200000, 2); auto sa = suffixArray(s); CHECK(sz(sa) == 200000);
  DONE();
}
