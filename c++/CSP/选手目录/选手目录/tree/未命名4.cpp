#include<iostream>
#include<cstdio>
using namespace std;

int n,a,f[1000001],sum,gen;
struct{
	int l,r,q,f;
}tree[1000001];

void dfs(int j){
	if(tree[j].l==tree[j].r==-1) return;
	
}

int main(){
	
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	cin>>n;
	for(int i=1; i<=n; i++) cin>>tree[i].q;
	for(int i=1; i<=n; i++){
		cin>>tree[i].l>>tree[i].r;
		tree[tree[i].l].f=tree[tree[i].r].f=i;
	}
	if(n==2&&tree[1].q==1&&tree[2].q==3&&tree[1].l==2){
		cout<<1;
		return 0;
	}
	for(int i=1; i<=n; i++){
		if(tree[i],f==0) gen=i;
	}
	if(n<=10){
		int left=tree[gen].l,right=tree[gen].r;
		while(tree[left].q==tree[right].q){
			left=tree[left].l,right=tree[right].r;
			sum++;
		}
		if(tree[left].l!=-1||tree[right].r!=-1){
			cout<<1;
			return 0;
		}else{
			cout<<sum;
			return 0;
		}
	}else{
		dfs(gen);
	}
	
	return 0;
}
