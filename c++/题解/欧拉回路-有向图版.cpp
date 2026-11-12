#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, cnt;
int ans[1000005], rdu[100005], cdu[100005];
vector<int> a[100005];
int pos[100005]; 

void dfs(int i){
    for(int &j = pos[i]; j < a[i].size(); ) {
        int to = a[i][j];
        j++; 
        dfs(to);
    }
    ans[++cnt]=i;
}

signed main() {
    cin >> n >> m;
    for(int i=1; i<=m; i++) {
        int u, v;
        cin >> u >> v;
        cdu[u]++; rdu[v]++;
        a[u].push_back(v);
    }
    for(int i=1; i<=n; i++) {
        sort(a[i].begin(), a[i].end());
    }
    
    int start=0, end=0;
    bool f=0;
    for(int i=1; i<=n; i++) {
        if(abs(rdu[i]-cdu[i])>1){
            f=1;
        }
        if(rdu[i]>cdu[i]) {
            if(end!=0)  f=1;
            end=i;
        } 
        if(cdu[i]>rdu[i]) {
            if(start!=0)  f=1;
            start=i;
        }
    }
    if(f){
        cout << "No";
        return 0;
    }
    
    dfs(start==0 ? 1 : start);
    for(int i=cnt; i>=1; i--) {
        cout << ans[i] << ' ';
    }
    return 0; 
}
