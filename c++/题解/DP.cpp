#include<bits/stdc++.h>
using namespace std;
int a,b,c,x,dp[500001];
int main(){
	cin>>a>>b>>c>>x;
	dp[0]=1;
	for(int i=1; i<=x; i++){
		if(i-a>=0)  dp[i]=(dp[i]+dp[i-a])%10007;
		if(i-b>=0)  dp[i]=(dp[i]+dp[i-b])%10007;
		if(i-c>=0)  dp[i]=(dp[i]+dp[i-c])%10007;
	}
	cout<<dp[x];
	return 0;
}
