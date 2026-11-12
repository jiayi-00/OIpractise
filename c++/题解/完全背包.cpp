#include<bits/stdc++.h>
using namespace std;
int n,k,a[505],c[505],dp[1000000005];
int main(){
    cin>>n>>k;
    for(int i=1; i<=n; i++){
        cin>>a[i]>>c[i];
    }
    for(int i=1; i<=n; i++){
        for(int j=k; j>=c[i]; j--){
            dp[j]=max(dp[j],dp[j-c[i]]+a[i]);
        }
    }
    cout<<dp[k];
    return 0;
}
