//largest rectangle on histogram
//O(n)

ll largest_rectangle(vector<int> &hist){
	int n = hist.size();
	ll area = 0;
	stack<int> s;
	for(int i = 0; i < n; i++){
		while(!s.empty() && hist[s.top()] >= hist[i]){
			int tmp = s.top(); s.pop();
			area = max(area, hist[tmp] * (ll)(s.empty()? i: i - s.top() - 1));
		}
		s.push(i);
	}
	while(!s.empty()){
		int tmp = s.top(); s.pop();
		area = max(area, hist[tmp] * (ll)(s.empty()? n: n - s.top() - 1));
	}
	return area;
}