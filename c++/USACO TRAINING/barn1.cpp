/*
ID:j8629j81
PROG:barn1
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int m,s,c;
int a[205],b[205];
signed main(){
    freopen("barn1.in","r",stdin);
    freopen("barn1.out","w",stdout);
    cin >> m >> s >> c;
    for(int i=1; i<=c; i++) cin >> a[i];
    sort(a+1,a+c+1);
    if(m>=c){
        cout << c << '\n';
        return 0;
    }
    for(int i=1; i<c; i++) b[i]=a[i+1]-a[i]-1;
    sort(b+1,b+c);
    int ans=a[c]-a[1]+1;
    for(int i=c-1; i>=c-(m-1); i--) ans-=b[i];
    cout << ans << '\n';
    return 0;
}