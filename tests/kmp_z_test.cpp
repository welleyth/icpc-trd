#include "common.h"
#include "../src/4-string/kmp_z.cpp"
#include "chk.h"
string rs(int n, int a) { string s; while (n--) s += 'a' + rnd(0, a-1); return s; }
int main() {
  CHECK(pref("").empty()); CHECK(zfunc("").empty());
  CHECK(pref("a") == vi{0}); CHECK(zfunc("a") == vi{1});
  for (int iter = 0; iter < 50000; iter++) {
    int a = rnd(1, 3); string s = rs(rnd(0, 14), a); int n = sz(s);
    auto p = pref(s), z = zfunc(s);
    CHECK(sz(p) == n && sz(z) == n);
    for (int i = 0; i < n; i++) {
      int b = 0;
      for (int k = 1; k <= i; k++) if (s.substr(0, k) == s.substr(i+1-k, k)) b = k;
      CHECK(p[i] == b);
      int l = 0; while (i + l < n && s[l] == s[i+l]) l++;
      CHECK(z[i] == l); }
    if (n) CHECK(z[0] == n);
    // period
    if (n) { int per = n - p[n-1]; bool ok = true;
      for (int i = per; i < n; i++) ok &= s[i] == s[i-per];
      CHECK(ok);
      for (int q = 1; q < per; q++) {
        bool o2 = true;
        for (int i = q; i < n; i++) o2 &= s[i] == s[i-q]; CHECK(!o2); } }
    // search
    string t = rs(rnd(1, 4), a); auto pp = pref(t + '#' + s);
    vi found, br;
    for (int i = 0; i < sz(pp); i++) if (pp[i] == sz(t)) found.push_back(i - 2 * sz(t));
    for (int i = 0; i + sz(t) <= n; i++) if (s.compare(i, sz(t), t) == 0) br.push_back(i);
    CHECK(found == br);
  }
  DONE();
}
