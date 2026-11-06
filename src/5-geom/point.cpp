// Exact integer geometry: |coord| <= 1e9 -> cross fits in ll.
// For real coordinates use T = long double and compare with
// EPS (e.g. 1e-9): sgn(x) = (x > EPS) - (x < -EPS).
template <class T> struct Pt {
  T x, y;
  Pt operator+(Pt o) const { return {x + o.x, y + o.y}; }
  Pt operator-(Pt o) const { return {x - o.x, y - o.y}; }
  Pt operator*(T k) const { return {x * k, y * k}; }
  Pt operator/(T k) const { return {x / k, y / k}; }
  T dot(Pt o) const { return x * o.x + y * o.y; }
  T cross(Pt o) const { return x * o.y - y * o.x; }
  T cross(Pt a, Pt b) const {
    return (a - *this).cross(b - *this); }
  T norm2() const { return x * x + y * y; }
  long double len() const { return sqrtl(norm2()); }
  bool operator<(Pt o) const {
    return tie(x, y) < tie(o.x, o.y); }
  bool operator==(Pt o) const { return x == o.x && y == o.y; }
};
using P = Pt<ll>;
using PD = Pt<long double>;
template <class T> int sgn(T v) { return (v > 0) - (v < 0); }
// a.cross(b, c) > 0 <=> a -> b -> c turns left (CCW).
// Rotate 90 CCW: (-y, x). Angle: atan2l(y, x).
// Normalize direction (dx, dy): divide by gcd(|dx|,|dy|),
// then make the first nonzero coordinate positive.
