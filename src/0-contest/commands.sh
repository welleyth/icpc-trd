# compile (debug):  sanitizers find out-of-bounds / overflow
g++ -std=gnu++20 -O2 -Wall -Wextra -Wshadow -DLOCAL \
  -fsanitize=address,undefined -D_GLIBCXX_DEBUG a.cpp -o a
# compile (fast):
g++ -std=gnu++20 -O2 a.cpp -o a && ./a < in
# stress test: gen.cpp reads seed from argv[1]
for i in $(seq 1 1000); do
  ./gen $i > in; ./a < in > o1; ./brute < in > o2
  cmp -s o1 o2 || { echo "DIFF seed $i"; cat in; break; }
done
