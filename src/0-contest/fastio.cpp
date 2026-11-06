// Fast input: 2x faster than unsynced cin (2e6 ints: 60 ms
// vs 120 ms). Use when input is > 5e6 numbers.
// Do not mix with cin/scanf; not for interactive problems.
char buf[1 << 16]; int bufLen = 0, bufPos = 0;
int gc() {
  if (bufPos == bufLen) {
    bufLen = fread(buf, 1, sizeof buf, stdin); bufPos = 0;
    if (bufLen <= 0) return -1;
  }
  return buf[bufPos++]; }
ll readInt() {
  int c = gc(); bool neg = false;    // '-' right before digits
  while (c < '0' || c > '9') {
    if (c == -1) return 0;           // end of input
    neg = c == '-'; c = gc(); }
  ll x = 0;
  for (; c >= '0' && c <= '9'; c = gc())
    x = x * 10 + (c - '0');
  return neg ? -x : x; }
string readStr() {                 // next non-space token
  int c = gc();
  while (c != -1 && isspace(c)) c = gc();
  string s;
  for (; c != -1 && !isspace(c); c = gc()) s += char(c);
  return s; }
