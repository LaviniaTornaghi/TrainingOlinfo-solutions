#include <bits/stdc++.h>
using namespace std;

int N, M, res;
bool m[50][50];
int tofill[50][50];
//bellissima matrice 2 based

bool check(int r, int c){
    if(m[r-1][c]==1 && m[r-2][c]==1) return true;
    if(m[r+1][c]==1 && m[r+2][c]==1) return true;
    if(m[r][c+1]==1 && m[r][c+2]==1) return true;
    if(m[r][c-1]==1 && m[r][c-2]==1) return true;
    if(m[r-1][c]==1 && m[r+1][c]==1) return true;
    if(m[r][c-1]==1 && m[r][c+1]==1) return true;
    if(m[r-1][c-1]==1 && m[r-2][c-2]==1) return true;
    if(m[r+1][c+1]==1 && m[r+2][c+2]==1) return true;
    if(m[r-1][c+1]==1 && m[r-2][c+2]==1) return true;
    if(m[r+1][c-1]==1 && m[r+2][c-2]==1) return true;
    if(m[r-1][c-1]==1 && m[r+1][c+1]==1) return true;
    if(m[r-1][c+1]==1 && m[r+1][c-1]==1) return true;
    return false;
}

void computa(int r, int c, int tmp, int rim){
    
    int newr=r, newc=c+1;
    if(c == M+1){
        newr++;
        newc=2;
    }
    
    if(tmp + rim <= res) return;
    
    res = max(res, tmp);
    if(r == N+2) return;
    if(!m[r][c]) rim--;
    
    if(!check(r, c) and !m[r][c]){
        m[r][c] = 1;
        computa(newr, newc, tmp+1, rim);
        m[r][c] = 0;
    }
    
    computa(newr, newc, tmp, rim);
}

int main(){
    cin>>N>>M;
    int rim = N*M;
    for(int i=2; i<N+2; i++)
        for(int j=2; j<M+2; j++){
            cin>>m[i][j];
            if(m[i][j]) rim--;
        }
      
    computa(2, 2, 0, rim);
    
    cout<<res;
}