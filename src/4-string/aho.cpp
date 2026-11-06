// Aho-Corasick over 'a'..'z'. After build(): nx = full
// automaton, link = suffix link, out[u] = # patterns that
// end at u or at its suffix links. O(total * 26)
struct Aho {
  static const int A = 26;
  vector<array<int, A>> nx; vi link, out, term, dict;
  Aho() { newNode(); }
  int newNode() { nx.emplace_back(); nx.back().fill(-1);
    link.push_back(0); out.push_back(0); term.push_back(0);
    return sz(nx) - 1; }
  int add(const string& s) {        // returns end node
    int u = 0;
    for (char ch : s) {
      int c = ch - 'a';
      if (nx[u][c] < 0) { int w = newNode(); nx[u][c] = w; }
      u = nx[u][c];
    }
    out[u]++; term[u]++; return u; }
  void build() {                    // BFS
    queue<int> q; dict.assign(sz(nx), -1);
    for (int c = 0; c < A; c++)
      if (nx[0][c] < 0) nx[0][c] = 0; else q.push(nx[0][c]);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      out[u] += out[link[u]];
      if (u) dict[u] = term[link[u]] ? link[u] : dict[link[u]];
      for (int c = 0; c < A; c++) {
        int v = nx[u][c];
        if (v < 0) nx[u][c] = nx[link[u]][c];
        else { link[v] = nx[link[u]][c]; q.push(v); }
      }
    } }
};
// dict[u] = nearest proper suffix-link ancestor where a
// pattern ends (-1 if none): list all matches at a text
// position: if term[u] u itself, then dict[u], dict[dict[u]],
// ... until -1 (term > 0 for each listed node).
// total matches in text: u = 0; for c: u = nx[u][c],
// ans += out[u]. Per-pattern counts: add 1 to cnt[u] for
// each text position, then push cnt along links in reverse
// BFS order.
