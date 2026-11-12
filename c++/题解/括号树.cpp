#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=5e5+5;
int n,cnt,ans;
int head[maxn],k[maxn];
string s;
struct node{
	int to,next;
}edges[maxn];
void add(int a,int b){
	edges[++cnt].to=b;
	edges[cnt].next=head[a];
	head[a]=cnt;
}
bool check(string s2){
	stack<char> st;
	while(!st.empty())  st.pop();
	for(int i=0; i<s2.size(); i++){
		if(s2[i]=='(')  st.push(s[i]);
		else{
			if(st.empty()||st.top()!='(')  return 0;
			st.pop();
		}
	}
	return st.empty();
}
string se(int l,int r,string s2){
	string str;
	for(int i=l; i<=r; i++)  str+=s2[i];
	return str;
}
void dfs(int i,int fa,string s2){
	k[i]=k[fa];
	for(int l=0; l<s2.size()-1; l++){
		string new_s=se(l,s2.size()-1,s2);
		if(check(new_s)) k[i]++;
	}
	for(int e=head[i]; e; e=edges[e].next){
		int v=edges[e].to;
		if(v==fa)  continue;
		dfs(v,i,s2+s[v-1]);
	}
}


signed main(){
	cin>>n>>s;
	for(int i=1; i<n; i++){
		int a;
		cin>>a;
		add(a,i+1);
		add(i+1,a);
	}
	dfs(1,0,string(" ")+s[0]);
	for(int i=1; i<=n; i++){
		ans^=(i*k[i]);
	}
	cout<<ans;
	return 0;
} 
