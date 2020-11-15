//Persistent Implicit treap
//Expected complexity
//Query, Update, reverse, merge, split: O(log n)
const int SEED = chrono::steady_clock::now().time_since_epoch().count();
mt19937_64 rng(SEED);

typedef struct node{
	int val,sum,lazy,rev;
	ll size;
	struct node *l,*r;
}node;
typedef node* pnode;

pnode init(int val){
	pnode ret = new node;
	ret->size=1;
	ret->val=ret->sum=val;
	ret->lazy=ret->rev=0;
	ret->l=ret->r=NULL;
	return ret;
}

pnode copy(pnode t){
	if(!t)return t;
	pnode r = init(t->val);
	r->l=t->l;
	r->r=t->r;
	return r;
}

ll sz(pnode t){
	return t?t->size:0;
}

void lazy(pnode t){
	if(!t)return;
	if(t->lazy){
		t->val+=t->lazy;
		t->sum+=t->lazy*sz(t);
		if(t->l)t->l->lazy+=t->lazy;
		if(t->r)t->r->lazy+=t->lazy;
		t->lazy=0;
	}
	if(t->rev){
		swap(t->l, t->r);
		if(t->l)t->l->rev^=1;
		if(t->r)t->r->rev^=1;
		t->rev=0;
	}
}

void reset(pnode t){
	if(t)t->sum = t->val;
}

void combine(pnode& t,pnode l,pnode r){
	if(!l || !r)return void(t = l?l:r);
	t->sum = (l->sum + r->sum)%MOD;
}

void operation(pnode t){
	if(!t)return;
	t->size=sz(t->l)+1+sz(t->r);
	reset(t);
	lazy(t->l);lazy(t->r);
	combine(t,t->l,t);
	combine(t,t,t->r);
}

void split(pnode t,pnode &l,pnode &r,ll pos,ll add=0){
	if(!t)return void(l=r=NULL);
	lazy(t);
	ll curr_pos = add + sz(t->l);
	if(curr_pos<=pos)
		l = copy(t), split(l->r,l->r,r,pos,curr_pos+1);
	else
		r = copy(t), split(r->l,l,r->l,pos,add);
	operation(l);
	operation(r);
}

void merge(pnode &t,pnode l,pnode r){
	lazy(l);lazy(r);
	if(!l || !r) t = copy(l?l:r);
	else if(rng() % (sz(l) + sz(r)) < sz(l))
		t = copy(l), merge(t->r,t->r,r);
	else
		t = copy(r), merge(t->l,l,t->l);
	operation(t);
}

int query(pnode t,int l,int r){
	pnode L,mid,R;
	split(t,L,mid,l-1);
	split(mid,t,R,r-l);
	int ans = t->sum;
	merge(mid,L,t);
	merge(t,mid,R);
	return ans;
}

void update(pnode &t, pnode s,int l,int r,int val){
	pnode L,mid,R;
	split(s,L,mid,l-1);
	split(mid,s,R,r-l);
	s->lazy+=val;
	merge(mid,L,s);
	merge(t,mid,R);
}

void reverse(pnode &t, pnode s, int l, int r){
	pnode L,mid,R;
	split(s,L,mid,l-1);
	split(mid,s,R,r-l);
	s->rev^=1;
	merge(mid,L,s);
	merge(t,mid,R);
}