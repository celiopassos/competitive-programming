int k = 1;
map<vector<int>, int> mp;

int centroid(int n, int u, int prev, auto &g, auto &res){
	bool isCentroid = true;
	int w = 1;
	for(auto v: g[u]){
		if(v != prev){
			int aux = centroid(n, v, u, g, res);
			if(2 * aux > n) isCentroid = false;
			w += aux;
		}
	}
	if(2 * (n - w) > n) isCentroid = false;
	if(isCentroid) res.push_back(u);
	return w;
}

int dfs(int u, int prev, auto &g){
	vector<int> vet;
	for(auto v: g[u])
		if(v != prev)
			vet.push_back(dfs(v, u, g));
	sort(vet.begin(), vet.end());
	if(!mp[vet]) mp[vet] = k++;
	return mp[vet];
}

bool isIsomorphic(auto &tree1, auto &tree2){
	int m1 = tree1.size(), m2 = tree2.size();
	if(m1 != m2) return 0;
	vector<int> c1, c2;
	centroid(m1, 0, -1, tree1, c1);
	centroid(m2, 0, -1, tree2, c2);
	k = 1;
	mp.clear();
	int r1 = dfs(c1[0], -1, tree1);
	int r2 = dfs(c2[0], -1, tree2);	
	if(r1 != r2 && (c1.size() != 2 || r2 != dfs(c1[1], -1, tree1))) return false;	
	return true;
}