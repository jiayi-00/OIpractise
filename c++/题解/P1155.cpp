// P1155 [NOIP2008 提高组] 双栈排序 —— 二分图染色 + 模拟贪心
// 结论: i<j 这两个元素不能进同一个栈  <==>  存在 k>j 使 a[k]<a[i]<a[j]
//   必要性: 同栈时 a[j] 压在 a[i] 上面, 而 a[k] 比 a[i] 小却还没压进来 ---> 死锁
//   充分性: 冲突点不同色的任意一组染色, 按下面的贪心都能跑完
// 建冲突图 ---> 判二分图, 不是二分图就输出 0
// 每个连通分量内部只有 2 种染色, 分量之间互不影响:
//   把分量里下标最小的点染 1 (它进 S1 输出 'a', 比进 S2 的 'c' 小), 字典序最小
// 模拟: 每一步在所有合法操作里取字典序最小的 (a<b<c<d)
//   合法: 'a' 需要 col[i]==1 且 a[i] 小于栈顶(保持栈内从上到下递增); 'c' 同理
//         'b' 需要栈 1 顶==now; 'd' 需要栈 2 顶==now
//   注意不能"能弹就弹": 栈 2 顶正好是 now 时, 下一个元素若该进 S1, 先压 'a' 再弹 'd' 更小
//   反例 2 3 1 4: 正解 a c a b b a d b, 能弹就弹会得到 a c a b b d a b, 第 6 位 'a'<'d'
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=1005, MXE=1000005;
int n, cnt;
//  suf[i]  ---> a[i..n] 的最小值, 用来 O(1) 判冲突
int a[MX], col[MX], suf[MX];
int head[MX];
struct node{
	int to, nex;
}edges[MXE];
void add(int u, int v) {
	edges[++cnt].to=v;
	edges[cnt].nex=head[u];
	head[u]=cnt;
}
signed main(){
	cin >> n;
	for(int i=1; i<=n; i++)  cin >> a[i];
	suf[n+1]=n+1;
	for(int i=n; i>=1; i--)  suf[i]=min(suf[i+1],a[i]);
	for(int i=1; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			if(a[i]<a[j] && suf[j+1]<a[i]){
				add(i,j);
				add(j,i);
			}
		}
	}
	queue<int> q;
	for(int i=1; i<=n; i++){
		if(col[i])  continue;
		col[i]=1;
		q.push(i);
		while(!q.empty()){
			int u=q.front();
			q.pop();
			for(int e=head[u]; e; e=edges[e].nex){
				int v=edges[e].to;
				if(col[v]==0){
					col[v]=3-col[u];
					q.push(v);
				}
				else if(col[v]==col[u]){
					cout << 0;
					return 0;
				}
			}
		}
	}
	stack<int> s1, s2;
	string ans;
	int now=1, i=1;
	while(i<=n || !s1.empty() || !s2.empty()){
		if(i<=n && col[i]==1 && (s1.empty() || a[i]<s1.top())){
			ans+='a';
			s1.push(a[i]);
			i++;
		}
		else if(!s1.empty() && s1.top()==now){
			ans+='b';
			s1.pop();
			now++;
		}
		else if(i<=n && col[i]==2 && (s2.empty() || a[i]<s2.top())){
			ans+='c';
			s2.push(a[i]);
			i++;
		}
		else{
			ans+='d';
			s2.pop();
			now++;
		}
	}
	for(int i=0; i<2*n; i++){
		if(i)  cout << ' ';
		cout << ans[i];
	}
	return 0;
}