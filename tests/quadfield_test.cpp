#include "t_util.h"
#include "../src/1-math/mint.cpp"
#include "../src/1-math/quadfield.cpp"
int main() {
  CHECK(mint(5).pow((MOD - 1) / 2) == mint(MOD - 1));
  Q phi{mint(2).inv(), mint(2).inv()};
  mint a = 0, b = 1;
  for (int n = 0; n <= 2000; n++) { CHECK(phi.pow(n).b * 2 == a); tie(a, b) = make_pair(b, a + b); }
  // big n via matrix
  auto fib = [&](ll n) { array<mint,4> r{1,0,0,1}, m{1,1,1,0};
    auto mu = [](array<mint,4> x, array<mint,4> y) { return array<mint,4>{x[0]*y[0]+x[1]*y[2], x[0]*y[1]+x[1]*y[3], x[2]*y[0]+x[3]*y[2], x[2]*y[1]+x[3]*y[3]}; };
    for (; n; n >>= 1, m = mu(m, m)) if (n & 1) r = mu(r, m);
    return r[1]; };
  for (int i = 0; i < 2000; i++) { ll n = rnd(0, 1000000000000000000LL); CHECK(phi.pow(n).b * 2 == fib(n)); }
  for (int i = 0; i < 20000; i++) {
    Q x{mint(rnd(0, MOD - 1)), mint(rnd(0, MOD - 1))}; if (i % 10 == 0) x.a = 0; if (i % 11 == 0) x.b = 0;
    if (x.a == 0 && x.b == 0) continue;
    Q p = x * x.inv(); CHECK(p.a == 1 && p.b == 0);
    Q y{mint(rnd(0, MOD - 1)), mint(rnd(0, MOD - 1))}, z{mint(rnd(0, MOD - 1)), mint(rnd(0, MOD - 1))};
    Q l = (x * y) * z, r = x * (y * z); CHECK(l.a == r.a && l.b == r.b);
    Q d1 = x * (y + z), d2 = x * y + x * z; CHECK(d1.a == d2.a && d1.b == d2.b);
    Q s = x - x; CHECK(s.a == 0 && s.b == 0);
  }
  Q s5{0, 1}; Q sq = s5 * s5; CHECK(sq.a == 5 && sq.b == 0);
  puts("ok");
}
