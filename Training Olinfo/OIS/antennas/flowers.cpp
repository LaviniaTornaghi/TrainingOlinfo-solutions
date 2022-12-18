#include <stdio.h>
#include <assert.h>
#include <bits/stdc++.h>

using namespace std;
// constraints
#define MAXN 100000
#define sx 2*index
#define dx 2*index+1

// input data
int N, D, i;
int L[MAXN], P[MAXN], S[MAXN], T[MAXN];

struct Info
{
	int p;
	int n;
};
bool cmp(Info a, Info b)
{
	return a.p < b.p;
}

struct segTree
{
	int *tree;
	
	
	void init(int N)
	{
		tree = (int*)malloc(sizeof(int)*4*N);
		
		buildTree(1, 0, N-1);
	}
	
	void buildTree(int index, int l, int r)
	{
		tree[index] = INT_MAX;
		if(l>=r)
		{
			return;
		}
		int m = (l+r)/2;
		
		buildTree(sx, l, m);
		buildTree(dx, m+1, r);
	}
	
	int pos;
	int x;
	
	void update(int index, int l, int r)
	{
		if(l>=r)
		{
			tree[index] = x;
			return;
		}
		int m = (l+r)/2;
		
		if(m >= pos)
			update(sx, l, m);
		else
			update(dx, m+1, r);
			
		tree[index] = min(tree[sx], tree[dx]);
	}
	
	int ql, qr = N-1;
	
	int query(int index, int l, int r)
	{
		if(l >= ql and r <= qr)
		{
			return tree[index];
		}
		if(r < ql or l > qr)
		{
			return INT_MAX;
		}
		int m = (l+r)/2;
		
		return min(query(sx, l, m), query(dx, m+1, r));
	}
	
	
};

int main() {
//  uncomment the following lines if you want to read/write from files
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);

    assert(2 == scanf("%d %d", &N, &D));
    for(i=0; i<N; i++)
        assert(4 == scanf("%d %d %d %d", &L[i], &P[i], &S[i], &T[i]));
        
    Info v[N];
    
  	for(int i=0; i<N; i++)
  	{
	  	L[i] += D*i;
	  	P[i] += D*i;
	  	
	  	v[i] = {P[i], i};
	}
	
	sort(v, v+N, cmp);
	
	int pos[N];
	
	for(int i=0; i<N; i++)
		pos[v[i].n] = i;
	
	segTree st;
	st.init(N);
	
	st.pos = pos[0];
	st.x = S[0];
	st.update(1, 0, N-1);
	
	int ris;
	
	for(int i=1; i<N; i++)
	{
		int l = 0;
		int r = N-1;
		
		while(l<r)
		{
	//		cout << "aaaaaa";
			int m = (l+r)/2;
			if(L[i] <= v[m].p)
				r = m;
			else
				l = m+1;
		}
		
		st.ql = l;
		int tmin = st.query(1, 0, N-1);
		
		if(tmin != INT_MAX)
		{
			int t;
		
			if(tmin < S[i])
				st.x = S[i];
			else
			{
				tmin -= S[i];
				t = tmin/T[i] + 1;
				st.x = S[i] + t*T[i];
			}
			st.pos = pos[i];
			st.update(1, 0, N-1);
			
			if(i == N-1)
				ris = st.x;
		}
		else if(i == N-1)
			ris = -1;
		
		

	}
	
	
    
    printf("%d\n", ris); // print the result
    return 0;
}
