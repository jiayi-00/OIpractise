#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int MX=5e5+5;
int n;
int a[2*MX];
char ans[2*MX];
void solve(){
    memset(a,0,sizeof(a));
    cin >> n;
    int m=2*n;
    for(int i=1; i<=m; i++) {
        cin >> a[i];
    }
    bool f=0;
    for(int i=n+1; i>=1; i--) {
        int xr=i-1, xl=i+n;
        int hl=i, hr=i+n-1;
        bool ok=1;
        for(int j=1; j<=n; j++) {
            int x=n+1-j;
            int y=2*n+1-x;
            bool ok2=0;
            if(a[xl]==a[hl]) {//right
                ans[x]='R';
                ans[y]='L';
                xl++; hl++;
                ok2=1;
            }
            else if(a[xl]==a[hr]) {//right
                ans[x]='R';
                ans[y]='R';
                xl++; hr--;
                ok2=1;
            }
            else if(a[xr]==a[hl]) {//left
                ans[x]='L';
                ans[y]='L';
                xr--; hl++;
                ok2=1;
            }
            else if(a[xr]==a[hr]) {//left
                ans[x]='L';
                ans[y]='R';
                xr--; hr--;
                ok2=1;
            }
            if(!ok2) {
                ok=0;
                break;
            }
        }
        if(ok) {
            f=1;
            for(int i=1; i<=2*n; i++) {
                cout << ans[i];
            }
            cout << endl;
            break;
        }
    }
    if(!f) {
        cout << -1 << endl;
    }
}
signed main() {
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}