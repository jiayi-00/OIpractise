#include<iostream>
#include<string>
using namespace std;
int cost[10]={6,2,5,5,4,5,6,3,7,6};
string getMinNumber(int n){
if(n<2)return "-1";
string minNum[8]={"-1","-1","1","7","4","2","0","8"};
if(n<=7)return minNum[n];
string result="";
int remaining=n;
while(remaining>0){
for(int digit=0;digit<=9;digit++){
if(remaining-cost[digit]<0)continue;
int rem=remaining-cost[digit];
if(rem==0||rem>=2){
if(result.empty()&&digit==0&&rem!=0)continue;
result+=char('0'+digit);
remaining=rem;
break;
}
}
}
return result;
}
int main(){
int t;
cin>>t;
while(t--){
int n;
cin>>n;
string result=getMinNumber(n);
if(result!="-1")cout<<result<<endl;
}
return 0;
}
