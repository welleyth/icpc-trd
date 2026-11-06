#include "t_util.h"
#include "../src/1-math/mint.cpp"
int main() {
  ll M = MOD;
  vector<ll> sp = {0, 1, -1, M, -M, M - 1, M + 1, LLONG_MAX, LLONG_MIN, LLONG_MIN + 1, 1LL << 40, -(1LL << 40)};
  auto ref = [&](ll x) { __int128 r = (__int128)x % M; if (r < 0) r += M; return (ll)r; };
  for (int it = 0; it < 200000; it++) {
    ll x = it < 20000 ? sp[rnd(0, sz(sp) - 1)] : rnd(-4e18, 4e18);
    ll y = it % 3 == 0 ? sp[rnd(0, sz(sp) - 1)] : rnd(-4e18, 4e18);
    mint a(x), b(y);
    CHECK(a.v == ref(x) && a.v >= 0 && a.v < MOD);
    CHECK((a + b).v == (ref(x) + ref(y)) % M);
    CHECK((a - b).v == ((ref(x) - ref(y)) % M + M) % M);
    CHECK((a * b).v == ref(x) % M * ref(y) % M);
    if (b.v) { CHECK(((a / b) * b) == a); CHECK((b * b.inv()) == mint(1)); }
    ll e = rnd(0, 100);
    mint r = 1; for (int i = 0; i < e; i++) r *= a;
    CHECK(a.pow(e) == r);
  }
  CHECK(mint(0).pow(0) == mint(1));
  CHECK(mint(5).pow(M - 1) == mint(1));
  CHECK(mint(2).pow(1LL << 40) == mint(2).pow((1LL << 40) % (M - 1)));
  mint z; CHECK(z.v == 0);
  stringstream ss; ss << mint(-1); CHECK(ss.str() == to_string(M - 1));
  puts("ok");
}
