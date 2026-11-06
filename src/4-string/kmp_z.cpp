// p[i] = longest proper border of s[0..i]. O(n)
// Find t in s: p = pref(t + '#' + s); match ends where
// p[i] == |t| (start = i - 2|t|). Period of s: n - p[n-1].
vi pref(const string& s) {
  int n = sz(s); vi p(n);
  for (int i = 1; i < n; i++) {
    int k = p[i - 1];
    while (k && s[i] != s[k]) k = p[k - 1];
    p[i] = k + (s[i] == s[k]);
  }
  return p; }
// z[i] = longest common prefix of s and s[i..]; z[0] = n.
vi zfunc(const string& s) {
  int n = sz(s); vi z(n);
  if (n) z[0] = n;
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z; }
