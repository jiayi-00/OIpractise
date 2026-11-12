#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MX=500005;
int n;
int a[2*MX],p[2*MX],vis[MX];

/*
 The first move is either L (take a[1]) or R (take a[2n]).
 Say it is L: then b[1]=a[1] and b is a palindrome, so b[2n]=a[1] as well, hence the very last
 element taken must be a[pos], where pos is the other occurrence of a[1].
 After that the whole process is driven only by equality of values:

   [l1,r1] = the outer part not taken yet;  [eL,eR] = the middle part already matched,
   which initially is just the single position pos.
   At each step we take a number from l1 or r1 (it becomes the k-th element of the front half of b),
   and its mirror element (front half of b) must lie next to the middle part, i.e. eL-1 or eR+1,
   with the same value. Since every value occurs exactly twice, "same value" means those two
   positions are the two occurrences of one value.

 So each step has at most two choices: take the left end / take the right end;
 when both are legal take the left one (letter 'L' is smaller).
 There are n-1 steps and the middle part then exactly fills up, so hitting a step where neither
 end can be taken means the answer is -1. The inequalities in the conditions keep the outer and
 middle parts disjoint, so no position is taken twice.
*/

//  f=0: first move L, f=1: first move R; returns "!" if impossible
string go(int f){
	int l1,r1,pos;
	string s(2*n+1,'?');
	if(f==0){ s[1]='L'; pos=p[1]; l1=2; r1=2*n; }
	else { s[1]='R'; pos=p[2*n]; l1=1; r1=2*n-1; }
	s[2*n]='L';                 // only one number left, L and R take the same one; 'L' is smaller
	int eL=pos,eR=pos;          // middle part already matched
	for(int k=2; k<=n; k++){
		int ql=0,qr=0;          // 1: mirror element on the left of the middle part, 2: on the right
		if(p[l1]==eL-1 && p[l1]>l1)  ql=1;
		else if(p[l1]==eR+1 && l1<=eL-1 && p[l1]<=r1)  ql=2;
		if(p[r1]==eL-1 && r1>=eR+1 && p[r1]>=l1)  qr=1;
		else if(p[r1]==eR+1 && p[r1]<r1)  qr=2;
		if(ql){
			s[k]='L';
			if(ql==1)  s[2*n+1-k]='L',eL--;
			else  s[2*n+1-k]='R',eR++;
			l1++;
		}
		else if(qr){
			s[k]='R';
			if(qr==1)  s[2*n+1-k]='L',eL--;
			else  s[2*n+1-k]='R',eR++;
			r1--;
		}
		else  return "!";
	}
	return s.substr(1);
}

void solve(){
	cin >> n;
	for(int i=1; i<=2*n; i++)  cin >> a[i];
	for(int i=1; i<=n; i++)  vis[i]=0;
	for(int i=1; i<=2*n; i++){
		if(vis[a[i]]==0)  vis[a[i]]=i;            // first occurrence
		else  p[i]=vis[a[i]],p[vis[a[i]]]=i;      // the twin position
	}
	string s1=go(0);
	if(s1!="!"){ cout << s1 << '\n'; return; }    // starting with L is always smaller
	string s2=go(1);
	if(s2!="!")  cout << s2 << '\n';
	else  cout << -1 << '\n';
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--)  solve();
	return 0;
}
