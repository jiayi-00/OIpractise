#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=1e5+5;
int n, m1, m2, ans;
int cnt1[MX], cnt2[MX];
int sum1[MX], sum2[MX];
struct node{
    int a, b;
}nod1[MX];
node nod2[MX];

priority_queue<int, vector<int>, greater<int> > fr1, fr2;//实现先到先得
priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > q1, q2;
bool cmp(node x, node y){
    return x.a<y.a;
}

signed main() {
    cin >> n >> m1 >> m2;
    for(int i=1; i<=m1; i++) {
        cin >> nod1[i].a >> nod1[i].b;
    }
    for(int i=1; i<=m2; i++) {
        cin >> nod2[i].a >> nod2[i].b;
    }
    sort(nod1+1,nod1+m1+1,cmp);
    sort(nod2+1,nod2+m2+1,cmp);
    //-----------------------------------------
    
    for(int i=1; i<=m1; i++) {
        fr1.push(i);
    }
    for(int i=1; i<=m1; i++) {
        while(!q1.empty() && q1.top().first<nod1[i].a) {
            fr1.push(q1.top().second);
            q1.pop();
        }
        if(!fr1.empty()) {
            int id=fr1.top();
            sum1[id]++;
            q1.push({nod1[i].b,id});
            fr1.pop();
        }
    }
    for(int i=1; i<=n; i++) {
        if(i<=m1) cnt1[i]=cnt1[i-1]+sum1[i];
        else  cnt1[i]=cnt1[i-1];
    }
    //----------------------------------------
    
    for(int i=1; i<=m2; i++) {
        fr2.push(i);
    }
    for(int i=1; i<=m2; i++) {
        while(!q2.empty() && q2.top().first<nod2[i].a) {
            fr2.push(q2.top().second);
            q2.pop();
        }
        if(!fr2.empty()) {
            int id=fr2.top();
            sum2[id]++;
            q2.push({nod2[i].b,id});
            fr2.pop();
        }
    }
    for(int i=1; i<=n; i++) {
        if(i<=m2) cnt2[i]=cnt2[i-1]+sum2[i];
        else  cnt2[i]=cnt2[i-1];
    }
    //-------------------------------------
    for(int i=0; i<=n; i++) {
        ans=max(ans,cnt1[i]+cnt2[n-i]);
    }
    cout << ans << '\n';
    return 0;
}