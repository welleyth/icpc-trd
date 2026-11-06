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
// Sliding window max: res[i - k + 1] = max of a[i-k+1 .. i].
// Deque of indices with decreasing values. O(n). Min: flip <=.
vector<ll> windowMax(const vector<ll>& a, int k) {
  deque<int> q; vector<ll> res;
  for (int i = 0; i < sz(a); i++) {
    while (!q.empty() && a[q.back()] <= a[i]) q.pop_back();
    q.push_back(i);
    if (q.front() <= i - k) q.pop_front();
    if (i >= k - 1) res.push_back(a[q.front()]);
  }
  return res; }
