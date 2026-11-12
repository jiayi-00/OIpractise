#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int t,n,m,a,lift[101][101],dp[10005],w[101],v[105],s[10005];

int main(){
	
	freopen("souvenir.in","r",stdin);
	freopen("souvenir.out","w",stdout);
	
	cin>>t>>n>>m;
	for(int i=1; i<=t; i++){
		for(int j=1; j<=n; j++){
			cin>>lift[i][j];
		}
	}
	if(t==1){
		cout<<m<<endl;
	}else if(t==2){
		for(int i=1; i<=n; i++){
			w[i]=lift[1][i];
			v[i]=lift[2][i]-lift[1][i];
		}
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				if(j>=w[i]) dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
			}
		}
		cout<<dp[m]+m<<endl;
	}
	
	return 0;
}
