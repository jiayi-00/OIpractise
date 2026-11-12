/*
ID:j8629j81
PROG:beads
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
string s;
signed main(){
    freopen("beads.in","r",stdin);
    freopen("beads.out","w",stdout);
    cin>>n>>s;
    s+=s;
    int max_beads = 0;
    for(int i=0; i<n; i++){
        int cnt = 0;
        char color = ' ';
        for(int j=i; j<i+n; j++){
            if(color == ' ' && s[j] != 'w') color = s[j];
            if(s[j] == color || s[j] == 'w') cnt++;
            else break;
        }
        if(cnt==n) {
            max_beads = n;
            break;
        }
        color = ' ';
        for(int j=i+n-1; j>=i+cnt-1; j--){
            if(color == ' ' && s[j] != 'w') color = s[j];
            if(s[j] == color || s[j] == 'w') cnt++;
            else break;
        }
        max_beads = max(max_beads, cnt);
    }
    cout<<max_beads<<'\n';
    return 0;
}