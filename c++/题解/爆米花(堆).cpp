#include<bits/stdc++.h>
#define int long long
using namespace std;
priority_queue<int> q;
int n;
signed main(){
	cin >> n;
	for(int i=1; i<=n; i++) {
		int op, x;;
		cin >> op;
		if(op==1) {
			cin >> x;
			q.push(x);
		}
		if(op==0) {
			if(q.empty()) {
				cout << -1 << '\n';
			}
			else {
				cout << q.top() << '\n';
				q.pop();
			}
		}
	}
	return 0;
}
