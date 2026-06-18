#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;++i){
        int value;
        cin>>value;
        if(value%3) cout<<"First";
        else cout<<"Second";
        cout<<endl;
    }
    return 0;
}