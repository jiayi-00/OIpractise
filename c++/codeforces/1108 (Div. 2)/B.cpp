#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
void solve(){
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        if(n==1){
            cout<<1<<'\n';
        }
        else if(n==2){
            cout<<-1<<'\n';
        }
        else{
            cout<<1<<' '<<2<<' ';
            for(int i=3;i<=n;i++){
                cout<<3*(1LL<<(i-3))<<' ';
            }
            cout<<'\n';
        }
    }
    
}
signed main(){ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}