/*
ID:j8629j81
PROG:transform
LANG:C++
*/
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
char a[15][15],b[15][15];
bool same(char x[15][15], char y[15][15]){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(x[i][j]!=y[i][j]) return false;
        }
    }
    return true;
}
void rotate(char src[15][15], char dst[15][15]){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            dst[j][n+1-i]=src[i][j];
        }
    }
}
void reflect(char src[15][15], char dst[15][15]){
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            dst[i][j]=src[i][n-j+1];
        }
    }
}
signed main(){
    freopen("transform.in","r",stdin);
    freopen("transform.out","w",stdout);
    cin>>n;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin>>a[i][j];
        }
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin>>b[i][j];
        }
    }
    char t[15][15],u[15][15];
    rotate(a,t);
    if(same(t,b)){
        cout<<1<<"\n";
        return 0;
    }
    rotate(t,u);
    if(same(u,b)){
        cout<<2<<"\n";
        return 0;
    }
    rotate(u,t);
    if(same(t,b)){
        cout<<3<<"\n";
        return 0;
    }
    reflect(a,t);
    if(same(t,b)){
        cout<<4<<"\n";
        return 0;
    }
    rotate(t,u);
    if(same(u,b)){
        cout<<5<<"\n";
        return 0;
    }
    rotate(u,t);
    if(same(t,b)){
        cout<<5<<"\n";
        return 0;
    }
    rotate(t,u);
    if(same(u,b)){
        cout<<5<<"\n";
        return 0;
    }
    if(same(a,b)){
        cout<<6<<"\n";
        return 0;
    }
    cout<<7<<"\n";
    return 0;
}