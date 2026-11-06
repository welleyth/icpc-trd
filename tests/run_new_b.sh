#!/bin/bash
# compile and run the new graph/string/geom tests (batch B)
cd "$(dirname "$0")"
FL="-std=gnu++20 -O2 -Wall -fsanitize=address,undefined -D_GLIBCXX_DEBUG"
mkdir -p /tmp/trd_bin
(
for t in ${@:-hld hldlca vtree hung sack sam mecconv}; do
  f=${t}_test.cpp
  [ $t = sack ] && ulimit -s unlimited
  if g++ $FL $f -o /tmp/trd_bin/$t 2>/tmp/trd_bin/$t.log &&
     timeout 600 /tmp/trd_bin/$t >/tmp/trd_bin/$t.out 2>&1; then
    echo "PASS $f"
  else
    echo "FAIL $f"; head -20 /tmp/trd_bin/$t.log /tmp/trd_bin/$t.out
  fi
done
)
