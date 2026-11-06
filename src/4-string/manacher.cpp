// Palindromes. t = "#s0#s1#...#"; d[i] = radius in t.
// For center i in t: longest palindrome in s has length
// d[i] - 1 and starts at (i - d[i] + 1) / 2.
// Number of palindromic substrings = sum of d[i] / 2.
vi manacher(const string& s) {
  string t = "#";
  for (char c : s) t += c, t += '#';
  int n = sz(t); vi d(n);
  for (int i = 0, l = 0, r = -1; i < n; i++) {
    int k = i > r ? 1 : min(d[l + r - i], r - i + 1);
    while (i - k >= 0 && i + k < n && t[i - k] == t[i + k])
      k++;
    d[i] = k--;
    if (i + k > r) l = i - k, r = i + k;
  }
  return d; }
