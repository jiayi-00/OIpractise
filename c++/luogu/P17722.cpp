// P17722 [SCP-S 2026] file -- give every batch a weight W, process in ascending W, closed form
// Let S_t be the set of batches archived after operation t.
// Position of core a_j = (#cores <= a_j) + sum_{i in S_t} #{x in b_i : x < a_j}
//   the first term summed over j is 1+2+...+n = n(n+1)/2, order independent, appears m times
//   for the second term put W_i = sum_j #{x in b_i : x < a_j}, the batch's own contribution
// total = m*n(n+1)/2 + sum_{t=1..m} sum_{i in S_t} W_i = m*n(n+1)/2 + sum_i W_i*(m-t_i+1)
//   where t_i is the moment batch i is processed, so W_i is counted m-t_i+1 times
// swapping neighbours with t_i<t_j changes cost by (W_j-W_i)*(t_j-t_i) --> ascending W is optimal
// so sort by W ascending, the largest W gets the smallest coefficient 1; no simulation needed
// prefix sums on the value domain 2e6 give #{x < a_j}; O(value range + L + m log m)
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=2000005, MXM=1000005;
int n, m;
//  pre[x]  ---> number of core files with id <= x
int pre[MX], w[MXM];                             // w[i] = W_i of batch i
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		int x;
		cin >> x;
		pre[x]=1;                                // ids are distinct, mark directly
	}
	for(int i=1; i<MX; i++)  pre[i]+=pre[i-1];   // prefix sum over the value domain
	for(int i=1; i<=m; i++){
		int l, s=0;
		cin >> l;
		for(int j=1; j<=l; j++){
			int x;
			cin >> x;
			s+=n-pre[x];                         // how many cores this id is smaller than
		}
		w[i]=s;
	}
	sort(w+1,w+m+1);                             // ascending W: heavy batches go last, smaller coefficient
	int ans=m*n*(n+1)/2;                         // the fixed part, paid m times
	for(int i=1; i<=m; i++)  ans+=w[i]*(m-i+1);  // the i-th smallest W is counted m-i+1 times
	cout << ans;
	return 0;
}
