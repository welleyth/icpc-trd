// For each i: L[i] = nearest j < i with a[j] < a[i] (or -1),
// R[i] = nearest j > i with a[j] <= a[i] (or n). O(n)
// ("<" / "<=" pair avoids double counting equal minima:
// sum of mins of all subarrays = sum a[i]*(i-L[i])*(R[i]-i))
void nearestSmaller(const vector<ll>& a, vi& L, vi& R) {
  int n = sz(a); L.assign(n, -1); R.assign(n, n);
  vi st;
  for (int i = 0; i < n; i++) {
    while (!st.empty() && a[st.back()] >= a[i]) {
      R[st.back()] = i; st.pop_back(); }
    if (!st.empty()) L[i] = st.back();
    st.push_back(i);
  }
}
// Sliding window max (width k): deque of indices with
// decreasing values; pop front when index <= i - k.
