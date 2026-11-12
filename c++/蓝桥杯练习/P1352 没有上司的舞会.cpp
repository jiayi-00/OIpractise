#include<bits/stdc++.h> 
using namespace std;
int n,a[6001],f[6001],dp[6001][2],root;
void dfs(int i){
	dp[i][1]=a[i];
	for(int j=1; j<=n; j++){
		if(f[j]==i){
			dfs(j);
			dp[i][0]+=max(dp[j][1],dp[j][0]);
			dp[i][1]+=dp[j][0];
		}
	}
}
int main(){
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	int l,k;
	for(int i=1; i<=n-1; i++){
		cin>>l>>k;
		f[l]=k;
	}
	for(int i=1; i<=n; i++){
		if(f[i]==0){
			root=i;
			break;
		}
	}
	dfs(root);
	cout<<max(dp[root][1],dp[root][0]);
	return 0;
}
