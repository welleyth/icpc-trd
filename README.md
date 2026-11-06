# ICPC Team Reference Document — team UZI (Jagiellonian University)

A compact, tested ICPC notebook: **[UZI-TRD.pdf](UZI-TRD.pdf)** (13 A4 pages).

Every snippet is short enough to type during a contest, uses one of the
fastest standard implementations, and is stress-tested against brute force
(63 test files, run with AddressSanitizer + UBSan + `_GLIBCXX_DEBUG`).

## Format (general ICPC TRD rules)

- at most 25 single-sided A4 pages, no separate title page;
- page number in the upper right, university and team name in the upper left;
- code 8 pt, other text at least 7 pt (readable at 0.5 m).

## Contents

| Section | Snippets |
|---|---|
| Contest | template, compile & stress-test script, fast input, limits table, pre-submit / WA checklist, "when stuck" ideas |
| Mathematics | mint (998244353), binomials, egcd / inverse / CRT, sieve & factorisation, Miller–Rabin, Pollard rho, matrix power, Gauss mod p, determinant, XOR basis, NTT, exact FFT, Berlekamp–Massey + k-th term, Lagrange interpolation, discrete log, floor sum; number theory / combinatorics / games formulas |
| Data structures | DSU, Fenwick, segment tree, lazy segment tree, sparse table, monotonic stack, ordered set + safe hash, Li Chao tree, implicit treap, DSU with rollback, Mo's algorithm, persistent segment tree |
| Graphs | Dijkstra / 0-1 BFS / Bellman–Ford, topological sort, SCC + 2-SAT, bridges & articulation points, LCA, HLD, centroid decomposition, virtual tree, small-to-large, Euler path, Kuhn, Dinic, min-cost flow, Hungarian |
| Strings | prefix / Z function, hashing (mod 2^61-1), Manacher, suffix array + LCP, Aho–Corasick, binary trie, suffix automaton |
| Geometry | integer point / segment / polygon primitives, convex hull, diameter, angle sort, circles, minimum enclosing circle, point in convex polygon, closest pair, polygon inside polygon |
| DP & techniques | LIS, bitmask / digit / SOS patterns, divide & conquer opt., Knuth opt., Aliens trick, re-rooting, binary / ternary search, bit tricks, Simpson integration, STL pitfalls |

Advanced snippets have a short **When / How / Pitfalls** note above the code.

## Layout

```
trd.tex            LaTeX source of the notebook
src/<section>/     the snippets (fragments written against src/0-contest/template.cpp)
tests/             brute-force stress tests + runners
UZI-TRD.pdf        built notebook
```

## Build

```bash
latexmk -pdf trd.tex          # needs TeX Live (extarticle, listings, multicol, lmodern)
```

Code lines must stay at most 63 characters so they do not wrap in print:

```bash
awk 'length > 63 {print FILENAME": "$0}' src/*/*.cpp
```

## Tests

```bash
bash tests/run_math_ds.sh        # math + data structures
bash tests/run_graph_str_geom.sh # graphs, strings, geometry
bash tests/run_new_a.sh          # newer math / DS / DP snippets
bash tests/run_new_b.sh          # newer graph / string / geometry snippets
g++ -std=gnu++20 -fsyntax-only tests/compile_all.cpp   # everything compiles together
```

A full run takes about 10 minutes (sanitizer builds).

## Credits

Several snippets follow well-known public implementations, rewritten in this
notebook's style: [KACTL](https://github.com/kth-competitive-programming/kactl)
(FFT, Miller–Rabin, Pollard rho, Berlekamp–Massey, linear recurrence) and
[cp-algorithms](https://cp-algorithms.com/) (Hungarian algorithm, suffix array,
Manacher), plus the AtCoder Library's floor sum.
