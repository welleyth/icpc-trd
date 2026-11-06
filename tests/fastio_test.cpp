#include "common.h"
#include "../src/0-contest/fastio.cpp"
#include "chk.h"
int main() {
  const char* path = "/tmp/trd_bin/fastio.txt";
  { FILE* f = fopen(path, "w");
    fputs("-> -- 12 -5 +7 x-3 a5 --4 -  -9 3-4 - 6\n  hello  wor-ld\n\n\t  tok\n", f);
    fputs("123456789012345678 -9223372036854775807 0 -0 -", f); fclose(f); }
  freopen(path, "r", stdin);
  CHECK(readInt() == 12); CHECK(readInt() == -5); CHECK(readInt() == 7);
  CHECK(readInt() == -3); CHECK(readInt() == 5); CHECK(readInt() == -4);
  CHECK(readInt() == -9); CHECK(readInt() == 3); CHECK(readInt() == 4); // terminator "-" is consumed
  CHECK(readInt() == 6);
  CHECK(readStr() == "hello"); CHECK(readStr() == "wor-ld"); CHECK(readStr() == "tok");
  CHECK(readInt() == 123456789012345678LL); CHECK(readInt() == -9223372036854775807LL);
  CHECK(readInt() == 0); CHECK(readInt() == 0);
  CHECK(readStr() == "-"); CHECK(readStr() == ""); 
  // big file crossing buffer boundaries
  { FILE* f = fopen(path, "w"); vector<ll> v; for (int i = 0; i < 300000; i++) { v.push_back((ll)rnd(0, 1<<30) * (rnd(0,1) ? -1 : 1)); fprintf(f, "%lld%s", v.back(), i%7 ? " " : "\n"); } fclose(f);
    freopen(path, "r", stdin); bufLen = bufPos = 0;
    for (ll x : v) CHECK(readInt() == x); }
  DONE();
}
