#include<bits/stdc++.h>
#define int long long
using namespace std; 

int T, n, q;
int cnt = 1;            // 下一个可分配的节点编号（0 号为根节点，已占用）

// Trie 的节点
struct node{
	int size;           // 有多少个插入的字符串经过（到达）该节点
	int a[62];          // 62 个儿子的下标：0~25 小写字母，26~51 大写字母，52~61 数字
}tree[3000005];         // 静态数组建树，避免动态分配

// 把字符映射到 0~61 的编号
int gettp(char s){
	if(s>='a' && s<='z') {          // 小写字母 -> 0~25
		return s-'a';
	}
	if(s>='A' && s<='Z') {          // 大写字母 -> 26~51
		return s-'A'+26;
	}
	else  return s-'0'+52;          // 数字 -> 52~61
}

// 插入字符串 s
void insert(string s){
	int len = s.size();
	int now = 0;                    // 从根节点出发
	for (int i=0; i<len; i++){
		int tp = gettp(s[i]);
		if(!tree[now].a[tp]) {      // 该字符对应的儿子不存在，就新建节点
			tree[now].a[tp] = cnt++;
		}
		now = tree[now].a[tp];      // 走到儿子节点
		tree[now].size++;           // 经过该节点的字符串数量 +1
	}
}

// 查询有多少个已插入的字符串以 s 为前缀
int count(string s){
	int len = s.size();
	int now = 0, ans = 0;
	for(int i=0; i<len; i++){
		int tp = gettp(s[i]);
		if(!tree[now].a[tp]){       // 中途断链，说明没有字符串以 s 为前缀
			return 0;
		}
		now = tree[now].a[tp];
		ans = tree[now].size;       // 走到当前字符后的 size 就是答案
	}
	return ans;
}

signed main(){
	cin >> T;                       // 多组测试数据
	while(T--){
		string s;
		cin >> n >> q;              // n 个待插入串，q 次询问
		for(int i=1; i<=n; i++){
			cin >> s;
			insert(s);
		}
		for(int i=1; i<=q; i++){
			cin >> s;
			cout << count(s) << '\n';
		}
		// 清空 Trie，准备下一组数据
		for(int i=0; i<cnt; i++){
			tree[i].size = 0;
			for(int j=0; j<62; j++){
				tree[i].a[j] = 0;
			}
		}
		cnt = 1;                    // 根节点重新从 1 号开始分配
	}
	return 0;
}
