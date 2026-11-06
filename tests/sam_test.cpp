#include "common.h"
#include "../src/4-string/sam.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 20000; iter++) {
    int A = rnd(1, 3), n = rnd(0, iter % 100 == 0 ? 60 : 14);
    string s; for (int i = 0; i < n; i++) s += 'a' + rnd(0, A-1);
    SAM sa; for (char c : s) sa.extend(c - 'a');
    CHECK(sz(sa.len) <= max(1, 2 * n));
    map<string,int> occ;
    for (int i = 0; i < n; i++) for (int l = 1; i + l <= n; l++)
      occ[s.substr(i, l)]++;
    ll d = 0; for (int v = 1; v < sz(sa.len); v++)
      d += sa.len[v] - sa.len[sa.link[v]];
    CHECK(d == sz(occ));
    // occurrences: cnt = 1 for non-clones. clone <=> created in extend
    // as second state; detect: clone iff not equal to `last` at time.
    // Rebuild to know: replay
    SAM sb; vi cnt(1, 0);
    for (char c : s) {
      int before = sz(sb.len); sb.extend(c - 'a');
      cnt.resize(sz(sb.len), 0); cnt[before] = 1; }
    vi ord(sz(sb.len)); iota(all(ord), 0);
    sort(all(ord), [&](int a, int b) { return sb.len[a] > sb.len[b]; });
    for (int v : ord) if (v) cnt[sb.link[v]] += cnt[v];
    // naive for all substrings and non-substrings
    for (auto& [t, c] : occ) {
      int v = 0; for (char ch : t) v = sb.nx[v][ch - 'a'];
      CHECK(v >= 0 && cnt[v] == c); }
    for (int q = 0; q < 20; q++) {
      string t; int L = rnd(0, 6);
      for (int i = 0; i < L; i++) t += 'a' + rnd(0, A);  // may be beyond A... within 26
      int v = 0; for (char ch : t) if (v >= 0) v = sa.nx[v][ch - 'a'];
      bool has = s.find(t) != string::npos;
      CHECK((v >= 0) == has);
    }
  }
  DONE();
}
