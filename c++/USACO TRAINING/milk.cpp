/*
ID:j8629j81
PROG:milk
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;
struct node{
    int p,a;
    bool operator <(const node &x) const{
        return p<x.p;
    }
}farm[5005];
signed main(){
    freopen("milk.in","r",stdin);
    freopen("milk.out","w",stdout);
    cin >> n >> m;
    for(int i=1; i<=m; i++) cin >> farm[i].p >> farm[i].a;
    sort(farm+1,farm+m+1);
    int ans=0;
    for(int i=1; i<=m; i++){
        if(n>=farm[i].a){
            ans+=farm[i].p*farm[i].a;
            n-=farm[i].a;
        }
        else{
            ans+=farm[i].p*n;
            break;
        }
    }
    cout << ans << '\n';
    return 0;
}