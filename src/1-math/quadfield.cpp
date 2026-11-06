// F_p[sqrt(W)] for a quadratic NON-residue W (5 is one mod
// 998244353, so sqrt 5 "exists" here). Binet with
// phi = (1 + sqrt5) / 2: F_n = 2 * (phi^n).b. Turns
// Fibonacci sums/convolutions into geometric series.
const mint W = 5;
struct Q {
  mint a, b;                                   // a + b sqrt(W)
  Q operator+(Q o) const { return {a + o.a, b + o.b}; }
  Q operator-(Q o) const { return {a - o.a, b - o.b}; }
  Q operator*(Q o) const {
    return {a * o.a + b * o.b * W, a * o.b + b * o.a}; }
  Q pow(ll e) const {
    Q r{1, 0}, x = *this;
    for (; e; e >>= 1, x = x * x) if (e & 1) r = r * x;
    return r; }
  Q inv() const {
    mint d = (a * a - b * b * W).inv();
    return {a * d, (mint(0) - b) * d}; }
};
