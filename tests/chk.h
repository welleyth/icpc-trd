// test helpers (not part of the notebook)
[[maybe_unused]] static mt19937 rng_(12345);
[[maybe_unused]] static int rnd(int l, int r) { return l + rng_() % (r - l + 1); }
static int fails_ = 0;
#define CHECK(c) do { if (!(c)) { if (fails_++ < 5) \
  fprintf(stderr, "FAIL %s:%d %s\n", __FILE__, __LINE__, #c); } \
  } while (0)
#define DONE() do { if (fails_) { fprintf(stderr, \
  "%d failures\n", fails_); return 1; } puts("ok"); \
  return 0; } while (0)
