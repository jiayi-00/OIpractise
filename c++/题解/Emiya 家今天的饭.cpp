#include<bits/stdc++.h>
using namespace std;
const int mod=998244353;
int n,m,ans=0;
int a[105][2005],cnt[2005];
void dfs(int now,int k){
    if(now>n){
        if(k==0)return;
        bool f=1;
        for(int j=1;j<=m;j++){
            if(cnt[j]*2>k){
                f=0;
                break;
            }
        }
        if(f) (ans+=1)%mod;
        return;
    }
    dfs(now+1,k);
    for(int j=1;j<=m;j++){
        if(!a[now][j])  continue;
        cnt[j]++;
        dfs(now+1,k+1);
        cnt[j]--;
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
        	cin>>a[i][j];
		}
	}      
    dfs(1,0);
    cout<<ans%mod;
    return 0;
}

