#include<bits/stdc++.h>
#define int long long
using namespace std;
deque<int> q;
int n,m,a[1000005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n>>m;
	for(int i=1; i<=n; i++)  cin>>a[i];
	
	// 第一行:最小值(递增队列)
	for(int i=1; i<=n; i++){
		while(!q.empty()&&i-q.front()>=m)  q.pop_front();
		while(!q.empty()&&a[i]<=a[q.back()])  q.pop_back();
		q.push_back(i);
		if(i>=m)  cout<<a[q.front()]<<' ';
	}
	cout<<'\n';
	
	// 第二行:最大值(递减队列)
	q.clear();
	for(int i=1; i<=n; i++){
		while(!q.empty()&&i-q.front()>=m)  q.pop_front();
		while(!q.empty()&&a[i]>=a[q.back()])  q.pop_back();
		q.push_back(i);
		if(i>=m)  cout<<a[q.front()]<<' ';
	}
	cout<<'\n';
	return 0;
}