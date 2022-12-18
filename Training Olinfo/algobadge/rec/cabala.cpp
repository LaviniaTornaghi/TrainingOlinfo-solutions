#include <stdio.h>
#include <assert.h>
#include <string>
#include <vector>
#include <deque>
using namespace std;
//alert:questo codice fa particolarmente schifo, estremamente sconsigliato
//sia da leggere che come idea risolutiva

typedef unsigned long long u64;
typedef unsigned long long u32;
u64 CIFRE_19 = (u64)1000000000 *(u64)1000000002;
 
vector<u64>cabala;
deque<u64>dq;

u64 Ncifre[19] = 
{
    0, 10, 100, 1000, 10000, 100000, 1000*1000, 1000*1000*10, 1000*1000*100, 1000*1000*1000,
    (u64)1000*1000*1000*10, (u64)1000*1000*1000*100, (u64)1000*1000*1000*1000,
    (u64)1000*1000*1000*1000*10, (u64)1000*1000*1000*1000*100, (u64)1000*1000*1000*1000*1000,
    (u64)1000*1000*1000*1000*1000*10, (u64)1000*1000*1000*1000*1000*100, (u64)1000*1000*1000*1000*1000*1000    
};


void fillCabala()
{
    dq.push_back(3);
    dq.push_back(6);
    dq.push_back(9);
    
    while(true)
    {
        u64 val =  dq.front();
        dq.pop_front();
    
        if(val > CIFRE_19)
            break;
        // ========== metto in salvo il valore nel vector
        cabala.push_back(val);
        
        if (val%10 == 3)
        {
            u64 val1 = val*10+6;
            u64 val2 = val*10+9;
            dq.push_back(val1);
            dq.push_back(val2);
        }    
        else if (val%10 == 6)
        {
            u64 val1 = val*10+3;
            u64 val2 = val*10+9;
            dq.push_back(val1);
            dq.push_back(val2);
        }    
        else //9
        {
            u64 val1 = val*10+3;
            u64 val2 = val*10+6;
            dq.push_back(val1);
            dq.push_back(val2);
        }    
    }
}

u32 occulta(int N, int M) 
{
    u32 max = 0;
    int i=0;

    for(i=0; i<cabala.size(); i++)
    {
        if (cabala[i] > Ncifre[N])
            break;
        int val = cabala[i] % M;
        if (val > max)
            max = val;
    }
    return max;
}


int main() 
{
    int T, N, M, i;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    fillCabala();
    scanf("%d", &T);
    for (i=0; i<T; i++) 
    {
        scanf("%d %d", &N, &M);
        printf("%d ", (int)occulta(N, M));
    }

    printf("\n");
    return 0;
}
