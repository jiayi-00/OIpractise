#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=2e5+10;
int a[MX];
void solve(){
    int t;
    cin>>t;
    while(t--){
        int n,sum=0;
        cin>>n;
        bool f=1;
        for(int i=1;i<=n;i++){
            cin>>a[i];
            
        }
        for(int i=1;i<=n;i++){
            sum+=a[i];
            int need=(int)i*(i+1)/2;
            if(sum<need){
                f=0;   
                break;
            }
        }
        cout<<(f?"YES":"NO")<<endl;
    }
}
signed main(){ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}