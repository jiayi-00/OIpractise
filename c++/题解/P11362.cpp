#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int mod=1e9+7;
int n, m, v;
map<int,int> mp;
int qpow(int a, int b){
    int res=1;
    while(b) {
        if(b&1)  res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
void solve(){
    int ans=1;
    mp.clear();
    cin >> n >> m >> v;
    bool f=1;
    for(int i=1; i<=m; i++) {
        int c, d;
        cin >> c >> d;
        if(mp[c]!=0 && mp[c]!=d) {
            f=0;
            break;
        } 
        mp[c]=d;
    }
    if(!f){
        cout << 0 << '\n';
        return ;
    }
    int last=-1;
    for(auto it=mp.begin(); it!=mp.end(); it++) {
        int i=it->first;
        if(last==-1){
            ans*=qpow(v,2*(i-1));
            ans%=mod;
            last=i;
            continue;
        }
        int s=i-last;
        ans*=qpow(v,2*s)+mod-qpow(v,s-1)*(v-1)%mod;
        ans%=mod;
        last=i;
    }
    ans*=qpow(v,2*(n-last));
    ans%=mod;
    cout << ans << '\n';
}
signed main() {
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}