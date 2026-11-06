// Suffix automaton of s: <= 2|s| states, every substring of s
// = a path from state 0. len = longest string in the state,
// link = suffix link (tree rooted at 0). O(26 |s|) memory.
// - # distinct substrings = sum over states v > 0 of
//   len[v] - len[link[v]]
// - occurrences: cnt[v] = 1 for states created as `cur` (not
//   clones); then, in decreasing len order,
//   cnt[link[v]] += cnt[v].
// - s contains t: walk nx from state 0.
struct SAM {
  vector<array<int, 26>> nx; vi len, link; int last = 0;
  SAM() { newState(0, -1); }
  int newState(int l, int lk) {
    nx.emplace_back(); nx.back().fill(-1);
    len.push_back(l); link.push_back(lk);
    return sz(len) - 1; }
  void extend(int c) {                  // c in [0, 26)
    int cur = newState(len[last] + 1, 0), p = last;
    while (p >= 0 && nx[p][c] < 0) nx[p][c] = cur, p = link[p];
    if (p >= 0) {
      int q = nx[p][c];
      if (len[p] + 1 == len[q]) link[cur] = q;
      else {
        int cl = newState(len[p] + 1, link[q]); nx[cl] = nx[q];
        while (p >= 0 && nx[p][c] == q)
          nx[p][c] = cl, p = link[p];
        link[q] = link[cur] = cl;
      }
    }
    last = cur; }
};
