// Suffix array O(n log n) + LCP (Kasai). sa = sorted suffix
// starts; lcp[i] = LCP(suffix sa[i], suffix sa[i + 1]).
// # distinct substrings = n(n+1)/2 - sum(lcp).
vi suffixArray(string s) {
  s += char(0);                   // s must not contain '\0'
  int n = sz(s); vi p(n), c(n), pn(n), cn(n);
  iota(all(p), 0);
  sort(all(p), [&](int a, int b) { return s[a] < s[b]; });
  for (int i = 1; i < n; i++)
    c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
  for (int h = 1; h < n; h <<= 1) {
    for (int i = 0; i < n; i++) pn[i] = (p[i] - h + n) % n;
    vi cnt(n);                    // counting sort by class
    for (int i = 0; i < n; i++) cnt[c[i]]++;
    for (int i = 1; i < n; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--)
      p[--cnt[c[pn[i]]]] = pn[i];
    cn[p[0]] = 0;
    for (int i = 1; i < n; i++) {
      pii a{c[p[i]], c[(p[i] + h) % n]};
      pii b{c[p[i - 1]], c[(p[i - 1] + h) % n]};
      cn[p[i]] = cn[p[i - 1]] + (a != b);
    }
    c.swap(cn);
    if (c[p[n - 1]] == n - 1) break;
  }
  p.erase(p.begin());
  return p; }
vi lcpArray(const string& s, const vi& sa) {
  int n = sz(s); vi rk(n), lcp(max(0, n - 1));
  for (int i = 0; i < n; i++) rk[sa[i]] = i;
  for (int i = 0, k = 0; i < n; i++) {
    if (rk[i] == n - 1) { k = 0; continue; }
    int j = sa[rk[i] + 1];
    while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
    lcp[rk[i]] = k;
    if (k) k--;
  }
  return lcp; }
