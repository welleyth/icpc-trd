#include "t_util.h"
#include "../src/6-misc/simpson.cpp"
int main() {
  double pi = acos(-1.0);
  double r1 = integrate([](double x) { return sin(x); }, 0, pi); fprintf(stderr, "sin err %.3e\n", fabs(r1 - 2) / 2); CHECK(fabs(r1 - 2) < 1e-12);
  double r2 = integrate([](double x) { return x * x * x - 2 * x * x + x - 5; }, -1, 3); double ex = (81.0 - 1) / 4 - 2 * (27.0 + 1) / 3 + (9.0 - 1) / 2 - 5 * 4; fprintf(stderr, "cubic err %.3e\n", fabs(r2 - ex) / fabs(ex)); CHECK(fabs(r2 - ex) < 1e-9 * fabs(ex));
  double r3 = integrate([](double x) { return exp(x); }, 0, 5); double e3 = exp(5.0) - 1; fprintf(stderr, "exp err %.3e\n", fabs(r3 - e3) / e3); CHECK(fabs(r3 - e3) / e3 < 1e-12);
  double r4 = integrate([](double x) { return 1 / (1 + x * x); }, 0, 1, 1000000); CHECK(fabs(r4 - pi / 4) < 1e-12);
  double r5 = integrate([](double x) { return x; }, 2, 2, 2); CHECK(r5 == 0);
  double r6 = integrate([](double x) { return x; }, 0, 1, 2); CHECK(fabs(r6 - 0.5) < 1e-15);
  puts("ok");
}
