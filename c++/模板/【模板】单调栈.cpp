#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int a[3000005], f[3000005];
stack<int> st;
signed main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> a[i];
		while(!st.empty() && a[i]>a[st.top()]){
			f[st.top()]=i;
			st.pop();
		}
		st.push(i);
	}
	for(int i=1; i<=n; i++){
		cout << f[i] << ' ';
	}
	return 0;
} 
