#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m;
string w[3005], unw[3005];
signed main() {
    cin >> n >> m;
    for(int i=1; i<=n; i++) {
        cin >> w[i];
        unw[i]=w[i];
        sort(w[i].begin(), w[i].end());
        sort(unw[i].begin(), unw[i].end(), greater<char>());
    }
    for(int i=1; i<=n; i++) {
        int f=1;
        for(int j=1; j<=n; j++) {
            if(w[i]>unw[j]) {
                f=0;
                break;
            }
        }
        if(!f) {
            cout << 0;
            continue;
        }
        cout << 1;
    }
    return 0;
}