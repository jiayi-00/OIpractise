#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
using namespace std;
const int mx=2000005;
const int B=131;
ull hsh[mx],p[mx];
int tot1[mx],tot2[mx];
int b[200];
int f[mx][27];
char s[mx];

ull gethsh(int l,int r){
    return hsh[r]-hsh[l-1]*p[r-l+1];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    p[0]=1;
    for(int i=1;i<mx;i++) p[i]=p[i-1]*B;
    while(T--){
        memset(tot1,0,sizeof(tot1));
        memset(tot2,0,sizeof(tot2));
        memset(b,0,sizeof(b));
        memset(f,0,sizeof(f)); 
        scanf("%s",s+1);
        ll ans=0;
        int n=strlen(s+1);
        for(int i=1;i<=n;i++){
            hsh[i]=hsh[i-1]*B+s[i];
        }
        for(int i=1;i<=n;i++){
            tot1[i]=tot1[i-1];
            b[s[i]]++;
            if(b[s[i]]&1) tot1[i]++;
            else tot1[i]--;
        }
        memset(b,0,sizeof(b));
        for(int i=n;i>=1;i--){
            tot2[i]=tot2[i+1];
            b[s[i]]++;
            if(b[s[i]]&1) tot2[i]++;
            else tot2[i]--;
        }
        for(int i=1;i<=n;i++){
            for(int j=0;j<=26;j++) f[i][j]=f[i-1][j];
            for(int j=tot1[i];j<=26;j++) f[i][j]++;
        }
        for(int i=2;i<=n-1;i++){
            for(int k=1;k*i<n;k++){
                if(k==1||gethsh(1,i)==gethsh((k-1)*i+1,k*i)){
                    ans+=f[i-1][tot2[i*k+1]];
                }else break;
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
