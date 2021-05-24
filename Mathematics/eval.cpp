namespace expr_solver{
	int getPriority(int ch){
		if(ch == '+')return 0;
		if(ch == '*')return 1;
		return -1;
	}
	bool isOperator(int ch){
		return (ch == '+' || ch == '*');
	}
	
	template<typename T>
	void process(stack<T> &st, char op){
		T a = st.top();st.pop();
		T b = st.top();st.pop();
		if(op == '+') st.push(a+b);
		if(op == '*') st.push(a*b);
	}
	
	template<typename T>T eval(const string &expr){
		stack<T> st;
		stack<char> op;
		for(int i = 0; i < expr.size(); i++){
			char c = expr[i];
			if(c == ' ')continue;
			if(c == '(')op.push(c);
			else if(c == ')'){
				while(op.top() != '('){
					process(st, op.top());
					op.pop();
				}
				op.pop();
			}
			else if(isOperator(c)){
				while(!op.empty() && getPriority(op.top()) >= getPriority(c)){
					process(st, op.top());
					op.pop();
				}
				op.push(c);
			}
			else{
				T num(0);
				while(i < (int)expr.size() && isalnum(expr[i])){
					num *= T(10);
					num += T(expr[i]-'0');
					i++;
				}
				st.push(num);
				i--;
			}
		}
		while(!op.empty()){
			process(st, op.top());
			op.pop();
		}
		return st.top();
	}
}