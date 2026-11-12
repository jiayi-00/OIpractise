#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=1e5+5;
int n;
string s1, s2, t1 ,t2;
int b1[MX], b2[MX];
int cnt1[MX][2], cnt2[MX][2];
void init() {
    memset(cnt1, 0, sizeof(cnt1));
    memset(cnt2, 0, sizeof(cnt2));
    int cur=0;
    for(int i=0; i<n; i++) {
        if(i==0 || t1[i]=='0' || t1[i-1]=='0')  cur++;
        b1[i]=cur;
        cnt1[cur][s1[i]-'0']++;
    }
    cur=0;
    for(int i=0; i<n; i++) {
        if(i==0 || t2[i]=='0' || t2[i-1]=='0')  cur++;
        b2[i]=cur;
        cnt2[cur][s2[i]-'0']++;
    }
}

void solve() {
    int ans=0;
    cin >> n;
    cin >> s1 >> s2 >> t1 >> t2;
    init();
    for(int i=0; i<n; i++) {
        int k1=b1[i], k2=b2[i];
        if(cnt1[k1][0]>0 && cnt2[k2][0]>0) {
            ans++;
            cnt1[k1][0]--;
            cnt2[k2][0]--;
        }
        else if(cnt1[k1][1]>0 && cnt2[k2][1]>0) {
            ans++;
            cnt1[k1][1]--;
            cnt2[k2][1]--;
        }
        else {
            if(cnt1[k1][0]>0)  cnt1[k1][0]--;
            else  cnt1[k1][1]--;
            if(cnt2[k2][0]>0)  cnt2[k2][0]--;
            else  cnt2[k2][1]--;
        }
    }
    cout << ans << '\n';
}
    
   
signed main() {
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}