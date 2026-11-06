#!/bin/bash
# Compile and run all math/ds/misc tests. Usage: tests/run_math_ds.sh
cd "$(dirname "$0")"
mkdir -p /tmp/trd_bin
sed -n "/^\/\/ __int128 output/,/^ll floorDiv/p" ../src/6-misc/tricks.cpp > tricks_extract.inc
fail=0
for f in ${@:-mint binom modpow sieve millerrabin matrix xorbasis gauss ntt fft dsu fenwick segtree lazyseg sparse monostack pbds lichao treap dp search tricks}; do
  
  flags="-std=gnu++20 -O2 -Wall -fsanitize=address,undefined"
  [ $f != pbds ] && flags="$flags -D_GLIBCXX_DEBUG"
  if g++ $flags ${f}_test.cpp -o /tmp/trd_bin/$f 2>/tmp/trd_bin/$f.log && timeout 300 /tmp/trd_bin/$f >/tmp/trd_bin/$f.out 2>>/tmp/trd_bin/$f.log; then
    echo "PASS ${f}_test.cpp"
  else
    echo "FAIL ${f}_test.cpp (see /tmp/trd_bin/$f.log)"; fail=1
  fi
done
exit $fail
