#include "common.h"
#include "../src/4-string/trie.cpp"
#include "chk.h"
int main() {
  for (int iter = 0; iter < 3000; iter++) {
    Trie T; multiset<int> ms;
    int range = iter % 3 == 0 ? 8 : iter % 3 == 1 ? 1000 : (1 << 30) - 1;
    for (int op = 0; op < 60; op++) {
      int t = rnd(0, 2);
      if (t == 0 || ms.empty()) { int x = rnd(0, range); if (rnd(0,3)==0) x = range; T.add(x); ms.insert(x); }
      else if (t == 1) { auto it = ms.begin(); advance(it, rnd(0, sz(ms)-1)); T.add(*it, -1); ms.erase(it); }
      if (ms.empty()) continue;
      int x = rnd(0, range), best = 0;
      for (int y : ms) best = max(best, x ^ y);
      CHECK(T.maxXor(x) == best);
    }
  }
  Trie T; T.add(0); CHECK(T.maxXor(0) == 0); T.add(5); T.add(5, -1); CHECK(T.maxXor(5) == 5);
  Trie U; U.add((1<<30)-1); CHECK(U.maxXor(0) == (1<<30)-1);
  DONE();
}
