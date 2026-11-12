/*
ID:j8629j81
PROG:gift1
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
map<string,int > money;
string mp[15];
signed main(){
    freopen("gift1.in","r",stdin);
    freopen("gift1.out","w",stdout);
    cin>>n;
    for(int i=1; i<=n; i++){
        string s;
        cin>>s;
        mp[i]=s;
    }
    for(int i=1; i<=n; i++){
        string s;
        int a,m;
        cin>>s>>a>>m;
        if(m==0)  continue;
        int give=a/m;
        for(int j=1; j<=m; j++){
            string s2;
            cin>>s2;
            money[s2]+=give;
        }
        money[s]-=give*m;
    }
    for(int i=1; i<=n; i++)  cout<<mp[i]<<' '<<money[mp[i]]<<'\n';
    return 0;
}