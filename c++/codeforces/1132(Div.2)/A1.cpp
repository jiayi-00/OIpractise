#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, a, b;
signed main(){
    cin >> t;
    while(t--){
        cin >> n;
        if(n%2==0)  a=b=n/2;
        else a=n/2, b=n/2+1;
    //    cout << a << ' ' << b << '\n';
        cout << a*b << '\n';
    }
    return 0;
}