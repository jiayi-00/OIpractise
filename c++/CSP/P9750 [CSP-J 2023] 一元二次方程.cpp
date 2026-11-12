#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int t,m;
int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}
void sim(int &p,int &q){
	if(q<0){
		p=-p;
		q=-q;
	}
	int g=gcd(abs(p),abs(q));
	p/=g;
	q/=g;
}
void pf(int p,int q){
	if(q==1)cout<<p;
	else cout<<p<<"/"<<q;
}
int main(){
	cin>>t>>m;
	while(t--){
		int a,b,c;
		cin>>a>>b>>c;
		int d=b*b-4*a*c;
		if(d<0){
			cout<<"NO"<<endl;
			continue;
		}
		if(d==0){
			int x=-b;
			int y=2*a;
			if(y<0){
				x=-x;
				y=-y;
			}
			sim(x,y);
			if(y==1)cout<<x<<endl;
			else cout<<x<<"/"<<y<<endl;
		}else{
			int sd=sqrt(d);
			if(sd*sd==d){
				int x1=-b+sd;
				int x2=-b-sd;
				int y=2*a;
				sim(x1,y);
				sim(x2,y);
				if(x1*y>x2*y){
					pf(x1,y);
				}else{
					pf(x2,y);
				}
				cout<<endl;
			}else{
				int in=d;
				int f=1;
				for(int i=2;i*i<=in;i++){
					while(in%(i*i)==0){
						f*=i;
						in/=i*i;
					}
				}
				int p1=-b;
				int p2=f;
				int y=2*a;
				sim(p1,y);
				int tg=gcd(abs(p2),abs(y));
				p2/=tg;
				int yr=y/tg;
				if(p1!=0){
					pf(p1,y);
					cout<<"+";
				}
				if(p2==1&&yr==1){
					cout<<"sqrt("<<in<<")";
				}else if(p2==1){
					cout<<"sqrt("<<in<<")/"<<yr;
				}else if(yr==1){
					cout<<p2<<"*sqrt("<<in<<")";
				}else{
					cout<<p2<<"*sqrt("<<in<<")/"<<yr;
				}
				cout<<endl;
			}
		}
	}
	return 0;
}
