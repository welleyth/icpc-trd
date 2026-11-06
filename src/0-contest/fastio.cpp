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
  int c = gc();
  while (c != '-' && (c < '0' || c > '9')) c = gc();
  bool neg = c == '-'; if (neg) c = gc();
  ll x = 0;
  for (; c >= '0' && c <= '9'; c = gc())
    x = x * 10 + (c - '0');
  return neg ? -x : x; }
