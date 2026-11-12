#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
void solve(){
    cin>>t;
    while(t--){
        int n;
        string s;
        cin>>n>>s;
        int mxtime=0;
        int i=0;
        while(i<n){
            if(s[i]=='#'){
                int j=i;
                while(j<n && s[j]=='#'){
                    j++;
                }
                int len=j-i;
                int time=(len+1)/2;
                mxtime=max(mxtime,time);
                i=j;
            }
            else{
                i++;
            }
        }
        cout<<mxtime<<endl;
    }
}
signed main(){ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}