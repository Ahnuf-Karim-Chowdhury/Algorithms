#include<bits/stdc++.h>
using namespace std;

int main(){
    int m=3,n=3,l=4;

    for (int i=1;i<=l;i++){
        for(int j=1;j<=l;j++){
            if(i==m || j==n || fabs(m-i)==fabs(n-j)){
                cout<<" 0 ";
            }
            else{
                cout<<" ("<<i<<","<<j<<") ";
            }
        }
        cout<<"\n";
    }


}