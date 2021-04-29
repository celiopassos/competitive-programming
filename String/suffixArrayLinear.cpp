struct suffixArray{
	#define F(x) ((x) / 3 + ((x) % 3 == 1 ? 0 : n1))
	#define G(x) ((x) < n1 ? (x)*3 + 1 : ((x)-n1) * 3 + 2)
	int n;
	vector<int> v1, v2, wv, v, sa, lcp, res;
	string str;
	suffixArray(string str, int n): n(n), v1(3*n), v2(3*n), wv(3*n), v(3*n), sa(3*n), lcp(n), str(str){}
	
	int c0(int *r, int a, int b) {
		return r[a] == r[b] && r[a + 1] == r[b + 1] && r[a + 2] == r[b + 2];
	}

	int c12(int k, int *r, int a, int b) {
		if (k == 2) return r[a] < r[b] || r[a] == r[b] && c12(1, r, a + 1, b + 1);
		return r[a] < r[b] || r[a] == r[b] && wv[a + 1] < wv[b + 1];
	}

	void radix(int *r, vector<int> &a, vector<int> &b, int n, int K){
		vector<int> c(K);
		for (int i = 0; i < n; i++) wv[i] = r[a[i]];
		for (int i = 0; i < n; i++) c[wv[i]]++;
		for (int i = 1; i < K; i++) c[i] += c[i - 1];
		for (int i = n - 1; i >= 0; i--) b[--c[wv[i]]] = a[i];
	}

	void dc3(int *r, int *sa, int n, int K) {
		int i, j, *r12 = r + n, *san = sa + n, n0 = 0, n1 = (n + 1) / 3, n12 = 0, p;
		r[n] = r[n + 1] = 0;
		for(i = 0; i < n; i++) if(i % 3 != 0)v1[n12++] = i;
		radix(r + 2, v1, v2, n12, K);
		radix(r + 1, v2, v1, n12, K);
		radix(r, v1, v2, n12, K);
		for (p = 1, r12[F(v2[0])] = 0, i = 1; i < n12; i++)
			r12[F(v2[i])] = c0(r, v2[i - 1], v2[i]) ? p - 1 : p++;
		if (p < n12) dc3(r12, san, n12, p);
		else for (i = 0; i < n12; i++) san[r12[i]] = i;
		for(i = 0; i < n12; i++)
			if (san[i] < n1) v2[n0++] = san[i] * 3;
		if (n % 3 == 1) v2[n0++] = n - 1;
		radix(r, v2, v1, n0, K);
		for (i = 0; i < n12; i++)
			wv[v2[i] = G(san[i])] = i;
		for (i = 0, j = 0, p = 0; i < n0 && j < n12; p++)
			sa[p] = c12(v2[j] % 3, r, v1[i], v2[j]) ? v1[i++] : v2[j++];
		while(i < n0) sa[p++] = v1[i++];
		while(j < n12)sa[p++] = v2[j++];
	}
	
	vector<int> getSA(){
		for(int i = 0; i < n; i++)v[i] = str[i];
		dc3(&v[0], &sa[0], n+1, 256);
		sa.resize(n+1);
		return sa;
	}
	
	vector<int> getLCP(){
		int k=0;
		vector<int> rank(n+1,0);
		for(int i=0; i<=n; i++) rank[sa[i]]=i;
		for(int i=0; i<n; i++, k-=!!k){
			if(rank[i]==n) {k=0; continue;}
			int j=sa[rank[i]+1];
			while(i+k<n && j+k<n && str[i+k]==str[j+k]) k++;
			lcp[rank[i]]=k;
		}
		return lcp;
	}
	
	void dfs(){
		int ans = 1;
		stack<int> s;
		vector<vector<int>> child(n+1);
		vi L(n+1), R(n+1);
		auto report = [&](int i){};
		s.push(0);
		lcp[0] = -1;
		lcp.push_back(-1);
		for(int i = 1; i <= n; i++){
			L[i] = R[i] = i-1;
			while(!s.empty() && lcp[i] < lcp[s.top()]){
				int id = s.top();
				s.pop();
				R[id] = i-1;
				report(id);
				L[i] = L[id];
				if(!s.empty() && lcp[i] <= lcp[s.top()])
					child[s.top()].push_back(id);
				else 
					child[i].push_back(id);
			}
			if(lcp[i] > lcp[s.top()]) s.push(i);
		}
	}
};