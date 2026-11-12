#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, m;			// n：数列长度   m：操作次数
int t[500005];		// 树状数组（ Fenwick Tree ），t[i] 维护区间 (i-lowbit(i), i] 的元素和

// lowbit(i)：取出 i 的二进制最低位的 1 所对应的值，例如 lowbit(6)=2, lowbit(8)=8
// 补码性质：i & (-i) 恰好等于这个值，它决定了树状数组中每个节点「管多长」
int lowbit(int i){
	return i&(-i);
}

// 单点加：把位置 i 的元素加上 v
// 需要沿着 i → i+lowbit(i) 一路向上更新所有「覆盖到 i」的节点，直到越界
void add(int i,int v){
	while(i<=n){
		t[i]+=v;
		i+=lowbit(i);	// 跳到父节点，父节点负责的区间更长且包含当前位置
	}
}

// 前缀和查询：求 a[1] + a[2] + ... + a[i]
// 从 i 出发沿 i → i-lowbit(i) 不断向左下跳，把经过的区间和累加起来
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
	// 建树：等价于对每个位置做一次单点加（也可 O(n) 线性建树，这里用朴素方式）
	for(int i=1; i<=n; i++){
		int x;
		cin >> x;
		add(i,x);
	}
	for(int i=1; i<=m; i++){
		int op, x, y;
		cin >> op >> x >> y;
		if(op==1){
			add(x,y);	// 操作 1：单点修改，把第 x 个数加上 y
		}
		else{
			// 操作 2：区间求和，用前缀和相减得到 a[x] + ... + a[y]
			cout << query(y)-query(x-1) << '\n';
		}
	}
	return 0;
}
