#!/bin/bash
# compile and run batch D tests
cd "$(dirname "$0")"
FL="-std=gnu++20 -O2 -Wall -fsanitize=address,undefined -fno-sanitize-recover=undefined -D_GLIBCXX_DEBUG"
mkdir -p /tmp/trd_bin
for t in ${@:-functional lifting blockcut linkcut aho aho_dict xortrie prefcount hashpow fastio anglecount lineint}; do
  f=${t}_test.cpp
  ( ulimit -s unlimited
  if g++ $FL $f -o /tmp/trd_bin/$t 2>/tmp/trd_bin/$t.log &&
     timeout 600 /tmp/trd_bin/$t >/tmp/trd_bin/$t.out 2>&1 </dev/null; then
    echo "PASS $f"
  else
    echo "FAIL $f"; head -20 /tmp/trd_bin/$t.log /tmp/trd_bin/$t.out
  fi )
done
