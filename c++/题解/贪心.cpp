#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans=-1e9;
struct node{
	int x,y;
}a[50005];
bool cmp(node a1,node b1){
	return min(a1.x,b1.y)<min(b1.x,a1.y);
}
signed main(){
	cin>>n;
	for(int i=1; i<=n; i++){
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	int sum=0;
	for(int i=1; i<=n; i++){
		ans=max(ans,sum-a[i].y);
		sum+=a[i].x;
	}
	cout<<ans;
	return 0;
} 
