#!/bin/bash
# compile and run graph/string/geometry tests
cd "$(dirname "$0")"
FL="-std=gnu++20 -O2 -Wall -fsanitize=address,undefined -D_GLIBCXX_DEBUG"
mkdir -p /tmp/trd_bin
for t in shortest topo scc bridges lca hld euler matching dinic \
  mcmf centroid kmp_z hash manacher sufarr aho trie point \
  segments polygon angle circle; do
  f=${t}_test.cpp
  [ -f $f ] || { echo "MISSING $f"; continue; }
  if g++ $FL $f -o /tmp/trd_bin/$t 2>/tmp/trd_bin/$t.log &&
     /tmp/trd_bin/$t >/tmp/trd_bin/$t.out 2>&1; then
    echo "PASS $f"
  else
    echo "FAIL $f"; head -20 /tmp/trd_bin/$t.log /tmp/trd_bin/$t.out
  fi
done
