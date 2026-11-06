#include "common.h"
#include "../src/4-string/aho.cpp"
#include "chk.h"
string rs(int n, int a) { string s; while (n--) s += 'a' + rnd(0, a-1); return s; }
int occ(const string& t, const string& p) {
  int c = 0; for (int i = 0; i + sz(p) <= sz(t); i++) c += t.compare(i, sz(p), p) == 0; return c; }
int main() {
  for (int iter = 0; iter < 30000; iter++) {
    int a = rnd(1, 3), k = rnd(0, 5); Aho A; vector<string> ps;
    for (int i = 0; i < k; i++) { ps.push_back(rs(rnd(0, 4), a)); A.add(ps.back()); }
    A.build();
    string t = rs(rnd(0, 20), a);
    int u = 0; ll tot = 0, br = 0;
    for (char ch : t) { u = A.nx[u][ch-'a']; CHECK(u >= 0 && u < sz(A.nx)); tot += A.out[u]; }
    for (auto& p : ps) br += occ(t, p);   // empty pattern counts at every position
    // empty pattern: out[0] incremented; counted only via root visits
    ll br2 = 0;
    for (auto& p : ps) { if (p.empty()) br2 += sz(t); else br2 += occ(t, p); }
    CHECK(tot == br2); (void)br;
    // every node: out == # patterns that are suffix of node string
    // reconstruct node strings
    vector<string> str(sz(A.nx)); 
    function<void(int)> dfs;
    vi seen(sz(A.nx));
    queue<int> q; q.push(0); seen[0] = 1;
    // use trie edges: those with depth increasing
    vi dep(sz(A.nx), -1); dep[0] = 0;
    while (!q.empty()) { int x = q.front(); q.pop();
      for (int c = 0; c < 26; c++) { int y = A.nx[x][c];
        if (dep[y] < 0) { dep[y] = dep[x]+1; str[y] = str[x] + char('a'+c); q.push(y); } } }
    for (int x = 0; x < sz(A.nx); x++) {
      int e = 0;
      for (auto& p : ps) if (sz(p) <= sz(str[x]) && str[x].compare(sz(str[x])-sz(p), sz(p), p) == 0) e++;
      CHECK(A.out[x] == e); }
  }
  DONE();
}
