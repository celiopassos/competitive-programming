//2-SAT
struct SAT{
	int n;
	vector<vector<int>> g;
	SAT(int n): n(n), g(2*n){}
	int neg(int x){
		return x<n? x+n: x-n;
	}
	
	void addCondition(int a, int b){
		g[neg(a)].push_back(b);
		g[neg(b)].push_back(a);
	}
 
	pair<bool, vector<int>> solve(){
		vector<int> comp = tarjan(g), res(n);
		for(int i = 0; i < n; i++){
			if(comp[i]==comp[i+n])return {false, vector<int>()};
			res[i] = comp[i] < comp[i+n];
		}
		return {true, res};
	}
};