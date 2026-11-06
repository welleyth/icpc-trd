// Modular arithmetic. MOD must be prime for division.
const int MOD = 998244353;
struct mint {
  int v;
  mint(ll x = 0) { v = x % MOD; if (v < 0) v += MOD; }
  mint pow(ll e) const {
    mint r = 1, b = *this;
    for (; e; e >>= 1, b *= b) if (e & 1) r *= b;
    return r; }
  mint inv() const { return pow(MOD - 2); }
  mint& operator+=(mint o) {
    v += o.v; if (v >= MOD) v -= MOD;
    return *this; }
  mint& operator-=(mint o) {
    v -= o.v; if (v < 0) v += MOD;
    return *this; }
  mint& operator*=(mint o) {
    v = (ll)v * o.v % MOD; return *this; }
  mint& operator/=(mint o) { return *this *= o.inv(); }
  friend mint operator+(mint a, mint b) { return a += b; }
  friend mint operator-(mint a, mint b) { return a -= b; }
  friend mint operator*(mint a, mint b) { return a *= b; }
  friend mint operator/(mint a, mint b) { return a /= b; }
  friend bool operator==(mint a, mint b) { return a.v == b.v; }
  friend ostream& operator<<(ostream& o, mint a) {
    return o << a.v; }
};
