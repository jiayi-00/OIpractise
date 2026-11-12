#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX = 2e5 + 10;
const int mod = 1e9 + 7;

int t;
int a[MX];

void solve() {
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++) cin >> a[i];
        
        map<int,int> cnt;
        for(int i = 1; i <= n; i++) cnt[a[i]]++;
        
        unordered_map<int,int> dp_pos, dp_neg;
        dp_pos[0] = 1;
        
        for(auto it1 = cnt.begin(); it1 != cnt.end(); it1++) {
            int x = it1->first;
            int c = it1->second;
            
            for(int j = 1; j <= c; j++) {
                unordered_map<int,int> new_dp_pos = dp_pos;
                unordered_map<int,int> new_dp_neg = dp_neg;
                
                for(auto it2 = dp_pos.begin(); it2 != dp_pos.end(); it2++) {
                    int sum = it2->first;
                    int cnt2 = it2->second;
                    int new_sum = sum - x;
                    new_dp_neg[new_sum] = (new_dp_neg[new_sum] + cnt2) % mod;
                }
                
                for(auto it2 = dp_neg.begin(); it2 != dp_neg.end(); it2++) {
                    int sum = it2->first;
                    int cnt2 = it2->second;
                    int new_sum = sum + x;
                    new_dp_pos[new_sum] = (new_dp_pos[new_sum] + cnt2) % mod;
                }
                
                dp_pos = new_dp_pos;
                dp_neg = new_dp_neg;
            }
        }
        
        int ans = (dp_pos[0] + dp_neg[0]) % mod;
        cout << ans << "\n";
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}