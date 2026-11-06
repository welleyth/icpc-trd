#include "common.h"
#include "../src/4-string/manacher.cpp"
#include "chk.h"
string rs(int n, int a) { string s; while (n--) s += 'a' + rnd(0, a-1); return s; }
bool pal(const string& s, int l, int len) {
  for (int i = 0; i < len / 2; i++) if (s[l+i] != s[l+len-1-i]) return false;
  return true; }
int main() {
  CHECK(manacher("") == vi{1});
  for (int iter = 0; iter < 50000; iter++) {
    string s = rs(rnd(0, 14), rnd(1, 3)); int n = sz(s);
    auto d = manacher(s); CHECK(sz(d) == 2*n+1);
    ll cnt = 0, brute = 0;
    for (int l = 0; l < n; l++) for (int len = 1; l+len <= n; len++) brute += pal(s, l, len);
    for (int i = 0; i < 2*n+1; i++) {
      cnt += d[i] / 2;
      int len = d[i] - 1, st = (i - d[i] + 1) / 2;
      CHECK(st >= 0 && st + len <= n);
      CHECK(pal(s, st, len));
      // maximal: cannot extend
      if (st > 0 && st + len < n) CHECK(s[st-1] != s[st+len]);
      // longest palindrome centred at i (centre in doubled coords)
      int best = 0;
      for (int l = 0; l < n; l++) for (int ln = 1; l+ln <= n; ln++)
        if (2*l + ln == i && pal(s, l, ln)) best = max(best, ln);
      // centre of palindrome [l, l+ln) in t is 2l+ln
      CHECK(best == len);
    }
    CHECK(cnt == brute);
  }
  DONE();
}
