#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, M; cin>>N>>M;
    
    if((N*M) %4){
        cout<<-1;
        exit(0);
    }
    cout<<(N*M)/4<<endl;
    
    if(!(N%4)){
        for(int i=0, l=0; i<N; i+=4, l+= M){
            for(int j=0; j<4; j++){
                for(int k=l; k<l+M; k++)
                    cout<<k<<" ";
                cout<<endl;
            }
        }    
    }
    else if(!(M%4)){
        int x = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(j && !(j%4)) x++;
                cout<<x<<" ";
            }
            x++;
            cout<<endl;
        }
    }
    else{
        for(int i = 0, k = 0; i<N; i+=2, k+= (M/2)){
            for(int l=0; l<2; l++){
                for(int j=k; j<k+(M/2); j++) cout<<j<<" "<<j<<" ";
                cout<<endl;
            }
        }

    }
}

