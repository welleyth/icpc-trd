// Simpson's rule on [a, b] with n (even) intervals; error
// O(h^4). Smooth f: n = 1e6 gives ~1e-12 relative error.
template <class F>
double integrate(F f, double a, double b, int n = 1 << 20) {
  double h = (b - a) / n, s = f(a) + f(b);
  for (int i = 1; i < n; i++)
    s += f(a + i * h) * (i & 1 ? 4 : 2);
  return s * h / 3; }
