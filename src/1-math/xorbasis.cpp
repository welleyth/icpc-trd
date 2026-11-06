// Linear basis over GF(2) for numbers < 2^60.
struct XorBasis {
  ll b[60] = {}; int cnt = 0;
  bool add(ll x) {             // false if x already spanned
    for (int i = 59; i >= 0; i--) if (x >> i & 1) {
      if (!b[i]) { b[i] = x; cnt++; return true; }
      x ^= b[i];
    }
    return false; }
  ll maxXor(ll x = 0) {        // max of x ^ (subset xor)
    for (int i = 59; i >= 0; i--) x = max(x, x ^ b[i]);
    return x; }
  bool has(ll x) {             // x is a subset xor?
    for (int i = 59; i >= 0; i--)
      if (x >> i & 1) { if (!b[i]) return false; x ^= b[i]; }
    return true; }
};  // # distinct subset xors = 2^cnt
