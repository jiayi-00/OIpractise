#include<bits/stdc++.h>
#define int long long
using namespace std;
int cnt, head[5005];
int n, m, k;
int fa[100005], c[15], a[15][10005];
bool f[15][10005];
struct node{
    int fro, to, w, id1, id2;
};
vector<node> edges;
vector<node> mst;
bool cmp(node x,node y){
    return x.w<y.w;
}
int find(int x){
    if(fa[x]==x)  return x;
    else{
        fa[x]=find(fa[x]);
        return fa[x];
    }
}
int popcnt(int x){
    int ret=0;
    while(x){
        x&=(x-1);
        ret++;
    }
    return ret;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> k;//n座城市 m条道路 k个乡镇
    for(int i=1; i<=m; i++){
        int a,b,c;
        cin >> a >> b >> c;
        edges.push_back(node{a,b,c,0,0});
    }

    sort(edges.begin(), edges.end(), cmp);
    for(int i=1; i<=n+k; i++){
        fa[i]=i;
    }
    for(int i=0; i<edges.size(); i++){
        int fu=find(edges[i].fro);
        int fv=find(edges[i].to);
        if(fu!=fv){
            fa[fu]=fv;
            mst.push_back(edges[i]);
            if((int)mst.size()==n-1) break;
        }
    }
    vector<vector<node> > town(k);
    for (int i=1; i<=k; i++){
        cin >> c[i];
        town[i-1].reserve(n);
        for (int j=1; j<=n; j++){
            cin >> a[i][j];//将第 i 个乡镇进行城市化改造的费用与在该乡镇与原有的城市间建造道路的费用
            town[i-1].push_back(node{n+i,j,a[i][j],0,0});
        }
        sort(town[i-1].begin(), town[i-1].end(), cmp);
    }

    int total=1<<k;
    vector<int> ptr(k);
    int ans=LLONG_MAX; 

    for (int mask=0; mask<total; mask++){
        int s=popcnt(mask);
        int nl=n+s-1;
        int p=0;
        for(int i=0; i<k; i++){
            if(mask&(1<<i)){
                p+=c[i+1];
            }
        }
        fill(ptr.begin(), ptr.end(), 0);
        int p0=0;
        for(int i=1; i<=n+k; i++)  fa[i]=i;
        int edge_cnt=0,cur=p;
        while(edge_cnt<nl){
            int best_w=LLONG_MAX;
            int which=-1;
            if(p0<(int)mst.size()){
                best_w=mst[p0].w;
                which=0;
            }
            for(int i=0; i<k; i++){
                if(!(mask&(1<<(i))))  continue;
                int pj=ptr[i];
                if(pj<(int)town[i].size() && town[i][pj].w<best_w){
                    best_w=town[i][pj].w;
					which=i+1;
                }
            }
            if(which==-1)  break;
            node e;
            if(which==0){
                e=mst[p0++];
			}
			else{
				e=town[which-1][ptr[which-1]++];
            }
            int fu=find(e.fro);
			int fv=find(e.to);
			if(fu!=fv){
				fa[fu]=fv;
				cur+=e.w;
				edge_cnt++;
			}
        }
        if(edge_cnt==nl)  ans=min(ans,cur);
    }

    if(ans!=LLONG_MAX) cout << ans << endl;
    else cout << "orz" << endl;
    return 0;
}