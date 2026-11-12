#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=5e5+5;	// 最大点数（留一点余量）
int n,m,s,cnt;			// n：点数   m：询问次数   s：树根   cnt：边计数器
int head[maxn],fa[maxn][35],dep[maxn];
						// head[i]：以 i 为起点的第一条边的编号（链式前向星的「链表头」）
						// fa[i][j]：节点 i 向上跳 2^j 步所到达的祖先（倍增表）
						//           fa[i][0] 就是 i 的直接父亲；35 ≈ log2(5e5) 向上取整后的余量
						// dep[i]：节点 i 的深度（根节点深度为 1，0 号虚点深度为 0）

struct node{
	int to,nex;			// to：这条边指向的点   nex：同一起点的下一条边的编号（链表指针）
}edges[maxn*2];			// 无向树有 n-1 条边，每条存两次，所以开 2 倍空间

// 加边：在 a 的邻接链表头部插入一条指向 b 的边（头插法）
void add(int a,int b){
	edges[++cnt].to=b;		// 新边编号为 ++cnt，终点是 b
	edges[cnt].nex=head[a];	// 新边的「下一条」指向原来 a 链表的第一条边
	head[a]=cnt;			// head 更新为新边，成为链表新的头
}

// 从 s 出发 DFS 预处理：求每个点的深度 dep[] 和倍增祖先表 fa[][]
void dfs(int i,int f){		// i：当前节点   f：i 的父亲
	dep[i]=dep[f]+1;		// 深度 = 父亲深度 + 1（根的父亲是 0，dep[0]=0，所以根深度为 1）
	fa[i][0]=f;				// 向上 2^0=1 步就是直接父亲
	int mac=log2(dep[i]);	// 只需填到 2^mac ≈ dep[i] 层即可，再往上会跳到根之上，无意义
	for(int j=1; j<=mac; j++){
		// 倍增递推：向上跳 2^j 步 = 先跳 2^(j-1) 步，再从这个落点继续跳 2^(j-1) 步
		fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	for(int e=head[i]; e; e=edges[e].nex){	// 遍历 i 的所有邻边（e 为边编号，为 0 表示链表结束）
		int v=edges[e].to;
		if(v==f)  continue;		// 无向图中会存反向边，跳过父亲避免走回头路（树的性质下这足够了）
		dfs(v,i);				// 递归处理子节点，父亲是自己
	}
}

// 求节点 a 和 b 的最近公共祖先
int lca(int a,int b){
	if(dep[a]<dep[b]){		// 保证 a 是更深的那个（若不是就交换）
		int t=a;
		a=b;
		b=t;
	}
	// 第一步：把更深的 a 向上提到与 b 同深度
	// 从大步长到小步长尝试，只要提完之后深度仍不低于 b，就真的提上去（二进制拆分思想）
	for(int i=log2(dep[a]-dep[b]); i>=0; i--){
		if(dep[fa[a][i]]>=dep[b])  a=fa[a][i];
		// 注意：若 fa[a][i] 为 0（跳过了根），dep[0]=0 < dep[b]，条件不成立，所以不会跳飞
	}
	if(a==b)  return a;		// 提平之后重合，说明 b 本身就是 a 的祖先，它就是 LCA
	// 第二步：a、b 同深度，二者一起向上跳
	// 同样从大步长往下枚举：只要 fa[a][i] 与 fa[b][i] 不同，说明这个高度还在 LCA 下面，可以放心跳
	int mac=log2(dep[a]);
	for(int i=mac; i>=0; i--){
		if(fa[a][i]!=fa[b][i]){
			a=fa[a][i];
			b=fa[b][i];
		}
		// 若二者祖先相同则不跳，因为那可能刚好越过 LCA（或就是 LCA 本身）
	}
	// 循环结束时 a、b 停在 LCA 的正下方一层，它们的父亲就是答案
	return fa[a][0];
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m>>s;
	for(int i=1; i<n; i++){	// 树有 n-1 条边
		int a,b;
		cin>>a>>b;
		add(a,b);			// 无向边，正反都要加
		add(b,a);
	}
	dfs(s,0);				// 以 s 为根预处理，根的父节点设为虚点 0
	for(int i=1; i<=m; i++){
		int a,b;
		cin>>a>>b;
		cout<<lca(a,b)<<'\n';
	}
	return 0;
}
