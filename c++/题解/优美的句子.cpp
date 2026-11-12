#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, cnt, q;
int ans[10005], du[1005];
int a[1005][1005];
void dfs(int i){
	for(int j=1; j<=53; j++) {
		if(a[i][j]) {
			a[i][j]--;
			a[j][i]--;
			dfs(j);
		} 
	}
	ans[++cnt]=i;
}
int gettp(char s) {
	if(s>='A' && s<='Z')  return s-'A'+1;
	return s-'a'+27;
}
char f(int x){
	if(x>=1 && x<=26)  return (char)(x+'A'-1);
	return (char)(x+'a'-27);
}
signed main() {
	cin >> n;
	for(int i=1; i<=n; i++) {
		char s1, s2, en;
		cin >> s1 >> s2;
		int u=gettp(s1), v=gettp(s2);
		du[u]++; du[v]++;
		a[u][v]++; a[v][u]++;
	}
	int total=0;
	for(int i=1; i<=53; i++) {
		if(du[i]%2==1)  total++;
	}
	if(total!=0 && total!=2) {
		cout << "No Solution";
		return 0;
	}
	
	for(int i=1; i<=53; i++) {
		if(du[i]%2==1) {
			q=i;
			break;
		}
	}
	if(q==0) {
		for(int i=1; i<=53; i++) {
			if(du[i]!=0) {
				q=i;
				break;
			}
		}
	}
	dfs(q);
	for(int i=cnt; i>=1; i--) {
		cout << f(ans[i]);
	}
	
	return 0; 
}
/*
题目描述



小A认为 n 个单词是优美的，这 n 个单词每个单词都只含有2个字母。每个单词倒过来，小A也觉得是优美的。
例如如果AB是优美的，那么BA也是优美的。

请你说一句优美的话，要求这句话的任何长度为2的子串都是优美的。



输入格式

第一行输入n。

接下来n行每行2个字母，表示一个优美的单词。

输出格式

如果没有任何一句话满足要求，输出No Solution。
如果这句话不唯一，输出字典序最小的句子。


提示

n 个无序字母对各不相同。

n 的规模可以通过计算得到。  

内存:
131072 KB
耗时:
1000 MS
输入输出样例
输入# 1
4
aY
tY
Wt
aW
输出# 1
WaYtW
*/
