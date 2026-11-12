/*
ID:j8629j81
PROG:milk2
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,ans1=0,ans2=0;
vector<pair<int,int> > v;
signed main(){
    freopen("milk2.in","r",stdin);
    freopen("milk2.out","w",stdout);
    cin>>n;
    v.resize(n+1);
    for(int i=1; i<=n; i++){
        cin>>v[i].first>>v[i].second;
    }
    sort(v.begin()+1,v.end());
    int oa=v[1].first,ob=v[1].second;
    ans1=ob-oa;
    for(int i=2; i<=n; i++){
        if(v[i].first<=ob){
            ob=max(ob,v[i].second);
            ans1=max(ans1,ob-oa);
        }
        else{
            ans1=max(ans1,ob-oa);
            ans2=max(ans2,v[i].first-ob);
            oa=v[i].first,ob=v[i].second;
        }
    }
    cout<<ans1<<" "<<ans2<<"\n";
    return 0;
}