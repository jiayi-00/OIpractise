#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, m;				// n：数列长度   m：操作次数
int t[500005],cha[500005];	// cha[i]：原数列第 i 项的值（cha[0] 默认为 0）
							// t[]：树状数组，但这里维护的是「差分数组」的前缀和结构

// lowbit(i)：取出 i 的二进制最低位的 1 所对应的值，例如 lowbit(6)=2, lowbit(8)=8
// 补码性质：i & (-i) 恰好等于这个值，它决定了树状数组中每个节点「管多长」
int lowbit(int i){
	return i&(-i);
}

// 单点加：把「差分数组」的第 i 项加上 v
// 需要沿着 i → i+lowbit(i) 一路向上更新所有「覆盖到 i」的节点，直到越界
void add(int i,int v){
	while(i<=n){
		t[i]+=v;
		i+=lowbit(i);	// 跳到父节点，父节点负责的区间更长且包含当前位置
	}
}

// 前缀和查询：求差分数组 d[1] + d[2] + ... + d[i]
// 根据差分的定义，d 的前缀和还原出来正好就是原数列第 i 项的值
int query(int i){
	int s=0;
	while(i){
		s+=t[i];
		i-=lowbit(i);	// 去掉最低位的 1，等价于「剥掉」最后一段已统计的区间
	}
	return s;
}

signed main(){
	cin >> n >> m;
	// 建树：树状数组里存的是差分数组 d[i] = cha[i] - cha[i-1]
	// 由于 cha[0] = 0，直接边读边算差分即可，不需要先把 cha 全部读完
	for(int i=1; i<=n; i++){
		int x;
		cin >> cha[i];
		add(i,cha[i]-cha[i-1]);
	}
	for(int i=1; i<=m; i++){
		int op, x;
		cin >> op;
		if(op==1){
			int y, k;
			cin >> x >> y >> k;
			// 区间加：给 a[x..y] 统一加 k
			// 差分数组上只需要改两个点：d[x] += k，d[y+1] -= k
			// 这样求前缀和时，x 及其之后都会 +k，y+1 及其之后又抵消回来
			add(x,k);
			add(y+1,-k);	// 注意 y+1 可能等于 n+1，add 内部有 i<=n 的判断，越界会自动跳过
		}
		else{
			// 单点查询：差分数组的前缀和就是原数列在该位置的值
			cin >> x;
			cout << query(x) << '\n';
		}
	}
	return 0;
}
