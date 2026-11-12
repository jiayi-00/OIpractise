#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, ans=-1e9;
int a[200005], dp[200005];
signed main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> a[i];
		dp[i]=max(a[i],dp[i-1]+a[i]);
		ans=max(ans,dp[i]);
	}	
	cout << ans;
	return 0;
} 
