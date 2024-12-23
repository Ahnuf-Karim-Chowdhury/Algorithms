#include<bits/stdc++.h>
using namespace std;
//implemented assuming we will place queen no n in row n
int n ;
vector<int> x(100);//store the column number for each queen. The index represents the queen/row number
int cnt=0;

bool Place(int k,int i)//checks if a queen can be placed in a given row k and column i without conflicting with other queens.
{
    for(int j=1; j<=k-1; j++){//k no row te/queen bosabo tai k-1 porjonto queen/row number check korte hbe
        if((x[j]==i) || (abs(x[j]-i)==abs(j-k)))
            return false;
    }
    return true;
}

void N_Queens(int k,int n)//k diye row borarbor jaite thakbo then prottek row er prottek column e kaj korbo
{
    for(int i=1; i<=n; i++){//iterates over all column i in the current row k
        if(Place(k,i)==true){
            x[k]=i;//saving column no i in the kth row/ placing kth queen in colum i
            if(k==n){//then write
                cnt++;
                cout<<"Way no  "<<cnt<<"  is :"<<endl;
                for(int q=1; q<=n; q++)
                    cout<<"Queen ["<<q<<"]  sits in Row "<<q<< " , column "<<x[q]<<"  "<<endl;
                cout<<endl;
            }
            else
                N_Queens(k+1,n);//else go to next row/queen
        }
    }
}

int main()
{
    cout<<"Enter the Number of Queens : "<<endl;
    cin>>n;
    N_Queens(1,n);
    return 0;
}
