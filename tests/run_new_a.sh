#!/bin/bash
# Compile and run new-snippet tests (math/ds/misc). Usage: tests/run_new_a.sh
cd "$(dirname "$0")"
mkdir -p /tmp/trd_bin
fail=0
for f in ${@:-pollard bm lagrange det dlog dsu_rollback mo persistent reroot aliens knuth simpson}; do
  flags="-std=gnu++20 -O2 -Wall -fsanitize=address,undefined -D_GLIBCXX_DEBUG"
  if g++ $flags ${f}_test.cpp -o /tmp/trd_bin/$f 2>/tmp/trd_bin/$f.log && timeout 600 /tmp/trd_bin/$f >/tmp/trd_bin/$f.out 2>>/tmp/trd_bin/$f.log; then
    echo "PASS ${f}_test.cpp"
  else
    echo "FAIL ${f}_test.cpp (see /tmp/trd_bin/$f.log)"; fail=1
  fi
done
exit $fail
