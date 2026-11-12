#include<bits/stdc++.h>
#define int long long
using namespace std;
deque<int> q_h;
deque<int> q_e;
int n,k;
struct node{
	int x,a;
}cow[50005];
bool cmp
signed main(){
	cin>>n>>k;
	for(int i=1; i<=n; i++){
		cin>>cow[i].x>>cow[i].a;
	}
	sort(cow+1,cow+n+1,cmp);
	for(int i=1; i<=n; i++){
		while(!q_h.empty()&&x[i]-x[q_h.front()]<k)  q_h.pop_front();
		while(!q_e.empty()&&x[q_e.front()]-x[i]<k)  q_e.pop_front();
		
		
	}
	return 0;
}
