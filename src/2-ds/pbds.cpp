#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using oset = tree<T, null_type, less<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
// s.find_by_order(k): iterator to k-th smallest (0-based)
// s.order_of_key(x):  number of elements < x
// multiset: store pair<T, int> {value, unique id}

// Anti-hack hash for unordered_map / gp_hash_table
struct SafeHash {
  size_t operator()(uint64_t x) const {
    static const uint64_t R =
      chrono::steady_clock::now().time_since_epoch().count();
    x += R + 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31); }
};
// unordered_map<ll, int, SafeHash> m; m.reserve(1 << 20);
// gp_hash_table<ll, int, SafeHash> h;   (faster)
