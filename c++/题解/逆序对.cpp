#include<iostream>
using namespace std;
int n, ans;
int a[500005];
int merge_sort(int l, int r, int a[]){
	if(l>=r)  return 0;
	int mid=(l+r)>>1;
	int cnt=merge_sort(l,mid,a)+merge_sort(mid+1,r,a);
	int b[r-l+2];
	int i=l, j=mid+1, k=1;
	while(i<=mid && j<=r) {
		if(a[i]<=a[j]) b[k++]=a[i++];
		else {
			b[k++]=a[j++];
			cnt+=mid-i+1; 
		}
	}
	while(i<=mid)  b[k++]=a[i++];
	while(j<=r)  b[k++]=a[j++];
	for(int p=l; p<=r; p++) a[p]=b[p-l+1]; 
	return cnt;
}
signed main(){
	cin >> n;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
	}
	cout << merge_sort(1, n, a);
	return 0;
}
