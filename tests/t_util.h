#include "common.h"
mt19937_64 trg(987654321);
ll rnd(ll lo, ll hi) { return lo + (ll)(trg() % (unsigned long long)(hi - lo + 1)); }
#define CHECK(c) do { if (!(c)) { fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); exit(1); } } while (0)
