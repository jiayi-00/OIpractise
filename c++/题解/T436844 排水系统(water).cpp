#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,head[maxn],cnt;
int du[maxn],d[maxn];//入度和出度
queue<int >q;

struct node{
    int to,next,w;
}edges[5*maxn];

struct {
    int p=1,q=1;
}water[maxn];//每个节点的水量

int gcd(int a,int b){
    while(b){
        int t=b;
        b=a%b;
        a=t;
    }
    return a;
}

void add(int a,int b){
    edges[++cnt].to=b;
    edges[cnt].next=head[a];
    edges[cnt].w=0;
    head[a]=cnt;
    du[b]++;
}

int main(){
    cin>>n>>m;
    for(int i=1; i<=n; i++){
        cin>>d[i];
        for(int j=1; j<=d[i]; j++){
            int b;
            cin>>b;
            add(i,b);
        }
    }

    for(int i=1; i<=n; i++){
        if(du[i]==0) {
            q.push(i);
        } 
    }

    while(!q.empty()){
        int u=q.front();
        q.pop();
        int p2=water[u].p;
        int q2=water[u].q*d[u];
        for(int e=head[u]; e; e=edges[e].next){
            int v=edges[e].to;
            int p1=water[v].p;
            int q1=water[v].q;
            int new_p=p1*q2+p2*q1;
            int new_q=q1*q2;
            int gcd_=gcd(new_p,new_q);
            water[v].p=new_p/gcd_;
            water[v].q=new_q/gcd_;
            du[v]--;
            if(du[v]==0){
                q.push(v);
            }
            cout<<u<<'-'<<v<<' '<<p2<<' '<<q2<<'\'<<water[v].p<<'<<water[v].q;
        }
    }

    for(int i=1; i<=n; i++){
        if(d[i]==0){
            cout<<water[i].p<<' '<<water[i].q<<'\n';
        }
    }
    return 0;
}