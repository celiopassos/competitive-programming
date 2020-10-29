//MO
//O(n * sqrt(q) * T + q * (logq + logn)), where T is update cost
const int N = (1 << 20);//2^N >= q

ll hilbert(int x, int y) {
	ll rx, ry, s, d = 0;
	for (s = N/2; s>0; s /= 2) {
		rx = (x & s) > 0;
		ry = (y & s) > 0;
		d += s * s * ((3 * rx) ^ ry);
		if (ry == 0) {
			if (rx == 1) {
				x = N-1 - x;
				y = N-1 - y;
			}
			swap(x, y);
		}
	}
	return d;
}

struct Query{
	int l, r, idx;
	ll h;
	Query(int l, int r, int idx): l(l), r(r), idx(idx), h(hilbert(l, r)){}
	bool operator<(const Query &q)const{
		return h < q.h;
	}
 };
 
 void add(int pos){
	 
 }
 
 void remove(int pos){
	 
 }
 
 int getAns(){
	 
 }
 
 vector<int> MO(vector<Query> queries){
	int l = 0, r = -1;
	vector<int> ans(queries.size());
	sort(queries.begin(), queries.end());
	for(auto q: queries){
		while(q.l < l)add(--l);
		while(r < q.r)add(++r);
		while(l < q.l)remove(l++);
		while(q.r < r)remove(r--);
		ans[q.idx] = getAns();
	}
	return ans;
 }