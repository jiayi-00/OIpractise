#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, n, a;
int b[105];
signed main(){
    cin >> t;
    while(t--){
        cin >> n;
        for(int i=1; i<=n; i++){
            cin >> a;
            b[i] = (1LL << a);
        }
        sort(b+1, b+n+1, greater<int>()); 
        int s1 = 0, s2 = 0;
        for(int i=1; i<=n; i++){
            if(s1 <= s2) s1 += b[i];
            else s2 += b[i];
        }
        cout << s1 * s2 << '\n';
    }
    return 0;
}