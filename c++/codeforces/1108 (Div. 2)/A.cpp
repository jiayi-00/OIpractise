#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
void solve(){
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        for(int i=1;i<=n;i++){
            cout<<(i%2==0?i-1:i+1)<<" ";
        }
        cout<<"\n";
    }
}
signed main(){ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}