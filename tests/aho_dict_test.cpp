#include "common.h"
#include "../src/4-string/aho.cpp"
#include "chk.h"
string rs(int n, int a) { string s; while (n--) s += 'a' + rnd(0, a-1); return s; }
int main() {
  for (int it = 0; it < 40000; it++) {
    int a = rnd(1, 3), k = rnd(0, 7); Aho A; vector<string> ps; vi ends;
    for (int i = 0; i < k; i++) { ps.push_back(rs(rnd(1, 5), a)); ends.push_back(A.add(ps.back())); }
    if (rnd(0, 3) == 0 && k) { ps.push_back(ps[0]); A.add(ps[0]); }
    if (rnd(0, 3) == 0 && k) { string s = ps[0].substr(rnd(0, sz(ps[0])-1)); ps.push_back(s); A.add(s); }
    A.build();
    string t = rs(rnd(0, 25), a); int u = 0;
    for (int i = 0; i < sz(t); i++) {
      u = A.nx[u][t[i]-'a'];
      multiset<int> want; for (auto& p : ps) if (sz(p) <= i+1 && t.compare(i+1-sz(p), sz(p), p) == 0) want.insert(sz(p));
      multiset<int> got; int x = A.term[u] ? u : A.dict[u]; // patterns ending exactly at node u too
      vector<int> chain; for (int y = u; y != -1; y = A.dict[y]) chain.push_back(y);
      // per comment: u, dict[u], ... ; first element may have term 0
      for (int y : chain) if (A.term[y]) for (int c = 0; c < A.term[y]; c++) { /* length unknown; use depth */ }
      (void)x;
      // depth per node
      static vi dep; if (i == 0 || true) { dep.assign(sz(A.nx), -1); queue<int> q; q.push(0); dep[0]=0; while(!q.empty()){int v=q.front();q.pop(); for(int c=0;c<26;c++){int w=A.nx[v][c]; if(dep[w]<0){dep[w]=dep[v]+1;q.push(w);}}} }
      for (size_t j = 0; j < chain.size(); j++) { int y = chain[j]; if (j > 0) CHECK(A.term[y] > 0); for (int c = 0; c < A.term[y]; c++) got.insert(dep[y]); }
      CHECK(got == want);
      CHECK(A.out[u] == (int)want.size());
    }
  }
  DONE();
}
