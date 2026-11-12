// P1155 [NOIP2008] Two-stack sorting -- bipartite colouring + greedy simulation
// Claim: i<j cannot be put into the same stack  <==>  exists k>j with a[k]<a[i]<a[j]
//   necessary: in one stack a[j] lies above a[i], while a[k]<a[i] is not pushed yet
//              but must be output earlier ---> deadlock
//   sufficient: any colouring with every conflict pair separated can be simulated
// Build the conflict graph, test bipartiteness (print 0 if it is not bipartite)
// A component has only 2 colourings and components are independent, so colour the
//   smallest index of a component with 1 (it goes to S1 ---> 'a' < 'c')
// Simulate: every step take the smallest legal operation (a<b<c<d)
//   legal: 'a' needs col[i]==1 and a[i] smaller than the top (keep stacks increasing
//          from top to bottom); 'c' likewise; 'b' needs top of S1==now; 'd' S2==now
//   Do NOT "pop whenever possible": when S2 top is now but the next element belongs
//   to S1, pushing 'a' first and popping 'd' after is smaller.
//   Counterexample 2 3 1 4: answer a c a b b a d b, pop-first gives a c a b b d a b
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=1005, MXE=1000005;                  // n<=1000; at most C(n,2)~5e5 conflicts, doubled for undirected
int n, cnt;                                      // n elements; cnt = edges used in the forward-star list
//  suf[i]  ---> minimum of a[i..n], used to test a conflict in O(1)
int a[MX], col[MX], suf[MX];                     // a: permutation; col: 1 into S1, 2 into S2; suf: suffix minimum
int head[MX];                                    // heads of the forward-star list
struct node{
	int to, nex;                                 // to: endpoint; nex: next edge of the same source
}edges[MXE];
void add(int u, int v) {
	edges[++cnt].to=v;                           // new edge u->v
	edges[cnt].nex=head[u];                      // link it to the head of u
	head[u]=cnt;
}
signed main(){
	cin >> n;                                    // number of elements
	for(int i=1; i<=n; i++)  cin >> a[i];        // read the permutation of 1~n
	suf[n+1]=n+1;                                // sentinel: +infinity, so j==n never yields a conflict
	for(int i=n; i>=1; i--)  suf[i]=min(suf[i+1],a[i]);   // suffix minima backwards
	for(int i=1; i<=n; i++){                     // enumerate conflict pairs (i,j), i<j
		for(int j=i+1; j<=n; j++){
			if(a[i]<a[j] && suf[j+1]<a[i]){      // conflict: a[i]<a[j] and something smaller than a[i] comes after j
				add(i,j);                        // this pair must be split ---> undirected edge
				add(j,i);
			}
		}
	}
	queue<int> q;                                // queue for the BFS colouring
	for(int i=1; i<=n; i++){
		if(col[i])  continue;                    // already coloured ---> part of an earlier component
		col[i]=1;                                // colour the smallest index of a component with 1 ---> prints 'a', smallest
		q.push(i);
		while(!q.empty()){
			int u=q.front();                     // pop the front
			q.pop();
			for(int e=head[u]; e; e=edges[e].nex){   // scan all conflict neighbours of u
				int v=edges[e].to;
				if(col[v]==0){                   // uncoloured neighbour ---> opposite colour
					col[v]=3-col[u];
					q.push(v);
				}
				else if(col[v]==col[u]){         // both ends of a conflict share a colour ---> not bipartite
					cout << 0;                   // no solution
					return 0;
				}
			}
		}
	}
	stack<int> s1, s2;                           // the two stacks
	string ans;                                  // collected operations, printed space separated
	int now=1, i=1;                              // now: next value to output; i: next element to push
	while(i<=n || !s1.empty() || !s2.empty()){   // elements left to push, or a stack is not empty
		if(i<=n && col[i]==1 && (s1.empty() || a[i]<s1.top())){
			// 'a' is the smallest legal op: element belongs to S1 and keeps S1 increasing downwards
			ans+='a';
			s1.push(a[i]);
			i++;
		}
		else if(!s1.empty() && s1.top()==now){
			// S1 top is exactly the next value ---> must pop, pushing anything would bury it forever
			ans+='b';
			s1.pop();
			now++;
		}
		else if(i<=n && col[i]==2 && (s2.empty() || a[i]<s2.top())){
			// with 'a' illegal, 'c' is smallest: element belongs to S2 and keeps S2 increasing
			ans+='c';
			s2.push(a[i]);
			i++;
		}
		else{
			// only 'd' is left: S2 top is the next value, pop it
			ans+='d';
			s2.pop();
			now++;
		}
	}
	for(int i=0; i<2*n; i++){                    // n pushes + n pops = 2n operations
		if(i)  cout << ' ';                      // space before every op but the first ---> no trailing space
		cout << ans[i];
	}
	return 0;
}
