#include<bits/stdc++.h>
#define int long long
using namespace std;
int T, n;
int isprime[200005];
void solve() {
    cin >> n;
    int x=n+1;
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    for(int i=2; i*i<=x; i++) {
        if(isprime[i]) {
            
            for(int j=i*2; j<=x; j+=i) {
                isprime[j] = 0;
            }
        }
    }
    if(isprime[x]) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}
signed main() {
    cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}