#include<iostream>
using namespace std;
void swapRef(int &a , int &b){int t=a; a=b; b=t;}
void swapptr(int *a , int *b){int t=*a; *a=*b; *b=t;}
int main(){
    int x=10,y=20;
    swapRef(x,y);
    cout<<"after swapRef:x="<<x<<"y="<<y<<endl;
    swapptr(&x ,&y);
    cout<<"after swapptr:x="<<x<<"y="<<y<<endl;
    int &alias=x;
    alias =99;
    cout<<"x via alias="<<x<<endl;
    return 0;
}