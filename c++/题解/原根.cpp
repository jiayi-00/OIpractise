#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1e6+5;
int T;
int phi[MAXN],prime[MAXN],cnt,min_factor[MAXN];
bool is_prime[MAXN];
vector<int> factors;
ll qpow(ll a, ll b,ll mod){
    ll res=1;
    while(b){
        if(b%2)  res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}
void init(){
    for(int i=1; i<MAXN; i++){
        is_prime[i]=true;
        phi[i]=i;
    }
    is_prime[1]=0;
    phi[1]=1;
    for(int i=2; i<MAXN; i++){
        if(is_prime[i]){
            prime[++cnt]=i;
            phi[i]=i-1;
            min_factor[i]=i;
        }
        for(int j=1; j<=cnt&&i*prime[j]<MAXN; j++){
            int num=i*prime[j];
            is_prime[num]=0;
            min_factor[num]=prime[j];
            if(i%prime[j]==0){
                phi[num]=phi[i]*prime[j];
                break;
            }
            else  phi[num]=phi[i]*(prime[j]-1);
        }
    }
}
bool haved(int n){
    if(n==2||n==4)  return 1;
    if(n%2==0) {
        n/=2;
        if(n%2==0)  return 0;
        int temp=n;
        for(int p=3; p*p<=temp; p++){
            if(temp%p==0){
                while(temp%p==0)  temp/=p;
                return temp==1;
            }
        }
        return is_prime[n];
    }
    else {
        int temp=n;
        for(int p=3; p*p<=temp; p++){
            if(temp%p==0){
                while(temp%p==0)  temp/=p;
                return temp==1;
            }
        }
        return is_prime[n];
    }
}
void fac_phi(int x,vector<int>& fac){
    fac.clear();
    while(x>1){
        int p=min_factor[x];
        fac.push_back(p);
        while(x%p==0)  x/=p;
    }
}
bool was(int g,int n,const vector<int>& fac_phi){
    if(__gcd(g,n)!=1)  return 0;
    for(int p : fac_phi){
        if(qpow(g,phi[n]/p,n)==1)  return 0;
    }
    return 1;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    cin>>T;
    while(T--){
        int n,d;
        cin>>n>>d;
        if(!haved(n)){
            cout<<"0\n\n";
            continue;
        }
        int phi_n=phi[n];
        fac_phi(phi_n,factors);
        int g=1;
        for(; g<n; g++){
            if(was(g,n,factors))  break;
        }
        vector<int> ans;
        ll cur=1;
        for(int k=1; k<=phi_n; k++){
            cur=(cur*g)%n;
            if(__gcd(k,phi_n)==1){
                ans.push_back((int)cur);
            }
        }
        sort(ans.begin(),ans.end());
        int total=(int)ans.size();
        int output=total/d;
        cout<<total<<'\n';
        if(output==0){
            cout<<'\n';
            continue;
        }
        for(int i=d-1; i<total; i+=d){
            cout<<ans[i]<<(i+d<total?' ':'\n');
        }
    }
    return 0;
}