#include<bits/stdc++.h>
using namespace std;
int n,ans;
struct candy{
  int x,y,now_p;
}a[100001];
long long m;
bool cmp(candy an,candy bn){
    int ap=an.now_p,bp=bn.now_p;
    if(ap==an.x)  int ap2=an.y;
    else  int ap2=an.x;
    if(bp==bn.x)  int bp2=bn.y;
    else  int bp2=bn.x;
    return ap!=bp?ap<bp:ap2<bp2;
}
int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        cin>>a[i].x>>a[i].y;
        a[i].now_p=a[i].x;
    }  
    while(m>0){
        sort(a+1,a+n+1,cmp);
        m-=a[1].now_p;
        a[1].now_p=a[1].y;
        ans++;
    }
    cout<<ans;
    return 0;
}
