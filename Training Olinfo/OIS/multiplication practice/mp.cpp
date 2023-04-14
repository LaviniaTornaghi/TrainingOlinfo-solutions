#include <bits/stdc++.h>
using namespace std;

int N;

int main()
{
    scanf("%d", &N);
    while(N--)
    {
		int K;
		int marca[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		int conta = 0;
        scanf("%d", &K);
        long long tmp = K, tmp2 = K;
        for(int i=1; ; i++)
        {
			tmp = tmp2;
			while(tmp)
			{
				marca[tmp%10]++;
				if(marca[tmp%10]==1) conta++;
				tmp/=10;
			}
			tmp2+=K;
			if(conta==10) 
			{
				printf("%d\n",i);
				break;
			}
		}
	}

}
