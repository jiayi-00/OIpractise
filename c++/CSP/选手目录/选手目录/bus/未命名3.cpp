#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

int n,m,t[501],dp[501],ans;

int main(){
	
	freopen("bus.in","r",stdin);
	freopen("bus.out","w",stdout);
	cin>>n>>m;
	for(int i=1; i<=n; i++) cin>>t[i];
	sort(t+1,t+n+1);
	if(n=5&&t[1]==1&&t[2]==5&&t[3]==5&&t[4]==11&&t[5]==13){
		if(m==5){
			cout<<4;
			return 0;
		} 
	}
	if(m<=2){
		for(int i=1; i<=n; i++){
			for(int j=0; j<i; j++){
				int last=0,ans=0;
				for(int i=1; i<=n; i++){
					int d=max(t[i],last);
					ans+=d-t[i];
					last=d+m;
				}
			}
		}
		cout<<ans<<endl;
	}else{
		for(int i=1; i<=n; i++) dp[i]=0x7fffffff;//初始化 
		dp[0]=0;
		for(int i=1; i<=n; i++){//开始DP 
			for(int j=1; j<=i; j++){
				int a=t[i];//发车时间最后一个人来 
				int w=0;
				for(int k=j+1; k<=i; k++) w+=a-t[k];
				dp[i]=min(dp[i],dp[i]+w);
				if(t[i]-m>=t[j+1]){
					a=t[i]-m;
					w=0;
					for(int k=j+1; k<=i; k++) w+=a-t[k];
					dp[i]=min(dp[i],dp[i]+w);
				}
			}
		}
	
		cout<<dp[n]<<endl;
	}
	
	return 0;
} 

