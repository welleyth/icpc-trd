// Polynomial hash mod 2^61-1 with random base: get(l, r)
// is the hash of s[l, r). Equal hashes => equal (w.h.p.).
using ull = unsigned long long;
const ull HM = (1ULL << 61) - 1;
ull hmul(ull a, ull b) {
  __uint128_t c = (__uint128_t)a * b;
  ull r = (ull)(c & HM) + (ull)(c >> 61);
  return r >= HM ? r - HM : r; }
mt19937_64 hrng(chrono::steady_clock::now()
                  .time_since_epoch().count());
const ull HB = hrng() % (HM - 1000) + 500;
struct Hash {
  vector<ull> h, p;
  Hash(const string& s) : h(sz(s) + 1), p(sz(s) + 1, 1) {
    for (int i = 0; i < sz(s); i++) {
      h[i + 1] = (hmul(h[i], HB) + (unsigned char)s[i]) % HM;
      p[i + 1] = hmul(p[i], HB);
    } }
  ull get(int l, int r) {
    return (h[r] + HM - hmul(h[l], p[r - l])) % HM; }
};
// LCP of two suffixes: binary search on length with get().
