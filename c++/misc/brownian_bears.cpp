#include<bits/stdc++.h>
#define int long long
using namespace std;

// n places in a row, on the morning of day 1 bear A is at x and bear B is at y,
// we watch them for d days.  x != y is guaranteed.
int n,x,y,d;

/*
 One single bear moves like this, and EVERY legal move has probability 1/2:
   place 1  -> stay at 1, or walk east to 2      (1/2 each)
   place n  -> walk west to n-1, or stay at n    (1/2 each)
   else     -> walk to p-1, or to p+1            (1/2 each)
 So a PAIR of bears always has exactly 4 equally likely successors, each with
 probability 1/4.  That is why the whole solution can stay in integers: every
 day the common denominator is multiplied by exactly 4, so we simply store
 "probability * 4^day".

 f[i][j] = ( probability that, on the morning of the current day, A is at i,
             B is at j, and they have NEVER foraged together before ) * 4^day.
           f[i][i] stays 0 forever: being on the same place means they met, and
           that mass is dropped instead of being written down.
*/
int f[105][105],g[105][105];

/*
 Sample 1: n=4 x=1 y=2 d=2 -> 3/8
   day 1 from (1,2): (1,1) meet 1/4 | (1,3) | (2,1) | (2,3)   -- note (2,1) is
     NOT a meeting: A is at 2 and B is at 1, they only passed each other.
   day 2: (1,3)->(2,2) meet 1/16 ; (2,1)->(1,1) meet 1/16 ; (2,3) never meets.
   meeting mass = 1/4 + 1/16 + 1/16 = 6/16 = 3/8
 Sample 2: n=6 x=2 y=5 d=2 -> 0/1
   the distance i-j is 3 (odd), and the parity of i-j can only change when a
   bear STAYS on an end place.  With d=2 nobody has time to do that, so they
   can never stand on the same place -> 0/1.
 Sample 3: n=2 x=1 y=2 d=1 -> 1/2 (meet with 1/4 by staying, 1/4 by swapping)
*/

// Where does a bear standing at p go when it makes its k-th choice (k = 0 or 1)?
// At an end place 1 or n the bear is also allowed to stay where it is.
int suc(int p,int k){
	if(p==1)  return k==0?1:2;      // stay at 1, or walk east to 2
	if(p==n)  return k==0?n-1:n;    // walk west to n-1, or stay at n
	return k==0?p-1:p+1;            // ordinary place: west or east
}

// plain gcd (same while-loop style as my "water / drainage system" solution)
int gcd(int a,int b){
	while(b){
		int t=b;
		b=a%b;
		a=t;
	}
	return a;
}

signed main(){
	cin>>n>>x>>y>>d;

	// morning of day 1: probability 1 = 1 / 4^0, so the scaled value is 1
	f[x][y]=1;

	// simulate the days one by one; when the loop ends f is scaled by 4^d
	for(int day=1; day<=d; day++){
		memset(g,0,sizeof(g));          // g = the scaled distribution of the next morning
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				if(f[i][j]==0)  continue;   // unreachable, or already met earlier
				for(int a=0; a<2; a++){
					for(int b=0; b<2; b++){
						// the 4 equally likely successors of the pair (each 1/4)
						int ni=suc(i,a),nj=suc(j,b);
						// same place -> they forage together TODAY, so this mass is
						// not written into g: it is the "met at least once" ending
						// we are looking for.  (Different places, even if the two
						// bears pass each other, is NOT a meeting.)
						if(ni!=nj)  g[ni][nj]+=f[i][j];
					}
				}
			}
		}
		// roll the day forward: tomorrow's morning becomes today's morning
		for(int i=1; i<=n; i++){
			for(int j=1; j<=n; j++){
				f[i][j]=g[i][j];
			}
		}
	}

	// denominator of the whole experiment is 4^d, at most 4^31 = 4.6e18 (fits)
	int all=1;
	for(int i=1; i<=d; i++)  all*=4;

	// sum over i != j = probability(they NEVER met during all d days) * 4^d
	int no=0;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(i!=j)  no+=f[i][j];
		}
	}

	// answer = 1 - never_met = (all - no) / all, then reduce the fraction.
	// If p == 0 then gcd(0, all) == all, so the output becomes exactly "0/1".
	int p=all-no,q=all;
	int gg=gcd(p,q);
	cout<<p/gg<<'/'<<q/gg<<endl;
	return 0;
}
