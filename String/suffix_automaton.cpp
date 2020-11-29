struct state {
	int len, link;
	map<char,int> next;
};

state st[2 * MAX];
int sz, last;

void init(){
	sz = 1;
	last = 0;
	st[0].len = 0;
	st[0].link = -1;
	st[0].next.clear();
}

void extend (char c) {
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	st[cur].next.clear();
	int p;
	for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link)
		st[p].next[c] = cur;
	if (p == -1)
		st[cur].link = 0;
	else {
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len)
			st[cur].link = q;
		else {
			int clone = sz++;
			st[clone].len = st[p].len + 1;
			st[clone].next = st[q].next;
			st[clone].link = st[q].link;
			for (; p != -1 && st[p].next[c] == q; p = st[p].link)
				st[p].next[c] = clone;
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}