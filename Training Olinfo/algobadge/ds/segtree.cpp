#include <vector>
#include <algorithm>
#include <climits>
#include <cstdio>
#include <unistd.h>

using namespace std;

typedef long long lld;
#define MAXN 1000010


struct Nodo
{
	lld sum;
	lld min; 
	lld to_add;
	lld to_set;
	bool is_to_set = false;
	
};

struct SegmentTree
{
	Nodo tree[4*MAXN];
	int n;
	lld * vec;
	int qs, qe;
	
	inline void lazy(int inx, int l, int r)
	{
		if(tree[inx].is_to_set)
		{
			tree[inx].sum = tree[inx].to_set * (r - l + 1);
			tree[inx].min = tree[inx].to_set;
			
			if(l != r)
			{
				tree[2*inx].to_set = tree[2*inx + 1].to_set = tree[inx].to_set;
				tree[2*inx].is_to_set = tree[2*inx + 1].is_to_set = true;
				
				tree[2*inx].to_add = tree[2*inx + 1].to_add = 0;
			}
			tree[inx].is_to_set = false;
		}
		else if(tree[inx].to_add != 0)
		{
			tree[inx].sum += tree[inx].to_add * (r - l + 1);
			tree[inx].min += tree[inx].to_add;
			
			if(l != r)
			{
				if(tree[2*inx].is_to_set)
					tree[2*inx].to_set += tree[inx].to_add;
				else
					tree[2*inx].to_add += tree[inx].to_add;
				
				if(tree[2*inx+1].is_to_set)
					tree[2*inx+1].to_set += tree[inx].to_add;
				else
					tree[2*inx+1].to_add += tree[inx].to_add;
				
			}
			tree[inx].to_add = 0;
		}
		
	}
	
	inline void build(int inx, int l, int r)
	{
		if(l == r)
		{
			tree[inx].sum = tree[inx].min = vec[l];
			return;
		}
		
		int m = (l+r)/2;
		
		build(2*inx, l, m);
		build(2*inx+1, m+1, r);
		tree[inx].sum = tree[2*inx].sum + tree[2*inx + 1].sum;
		tree[inx].min = min(tree[2*inx].min, tree[2*inx + 1].min);

	}
	
	inline lld get_sum(int inx, int l, int r)
	{
		lazy(inx, l, r);
		
		if(l >= qs and r <= qe)
		{
			return tree[inx].sum;	
		}
		if(r < qs or l > qe)
			return 0;
			
		int m = (l + r) /2;
		return get_sum(2 * inx, l, m) + get_sum(2*inx +1, m+1, r);
	}
	
	inline void lazy_add(int inx, int l, int r, lld x)
	{
		lazy(inx, l, r);
				
		if(l >= qs and r <= qe)
		{
			tree[inx].to_add = x;
			lazy(inx, l, r);
			return;
		}
		if(r < qs or l > qe)
			return;
			
		int m = (l + r) /2;
		lazy_add(2*inx, l, m, x);
		lazy_add(2*inx + 1, m+1, r, x);
		
		tree[inx].sum = tree[2*inx].sum + tree[2*inx+1].sum;
		tree[inx].min = min(tree[2*inx].min, tree[2*inx+1].min);
	}
	
	inline void lazy_set(int inx, int l, int r, lld x)
	{
		lazy(inx, l, r);
				
		if(l >= qs and r <= qe)
		{
			tree[inx].to_set = x;
			tree[inx].is_to_set = true;
			lazy(inx, l, r);
			return;
		}
		if(r < qs or l > qe)
			return;
			
		int m = (l + r) /2;
		lazy_set(2 * inx, l, m, x);
		lazy_set(2*inx +1, m+1, r, x);

		tree[inx].sum = tree[2*inx].sum + tree[2*inx+1].sum;
		tree[inx].min = min(tree[2*inx].min, tree[2*inx+1].min);
	}
	
	inline lld get_min(int inx, int l, int r)
	{
		lazy(inx, l, r);
		
		if(l >= qs and r <= qe)
		{
			return tree[inx].min;	
		}
		if(r < qs or l > qe)
		{
			return LLONG_MAX;			
		}
		
		int m = (l + r) /2;
		return min(get_min(2 * inx, l, m), get_min(2*inx +1, m+1, r));
	}
	
	inline int lower_bound(int inx, int l, int r, int x)
	{
		lazy(inx, l, r);
			
		if(tree[inx].min > x or r < qs or l > qe)
			return -1;	
		if(l == r)
			return l;
			
		int m = (l + r) /2;
		
		int lb = lower_bound(2 * inx, l, m, x);
		
		if(lb != -1)
			return lb;
		return lower_bound(2*inx +1, m+1, r, x);
	}
	
	void printSegmentTree()
	{
	    int left = 1, right = 2;
	    int i;
	    while (left < 2 * n)
	    {
	        for (i = left; i < right; i++)
	            printf("%lld ", tree[i].sum);
	        printf("\n");
	        left *= 2;
	        right *= 2;
	    }
	
	}
};

SegmentTree st;

void init(vector<long long> a)
{
	st.n = a.size();
	st.vec = a.data();
	st.build(1, 0, a.size() - 1);
}

long long get_sum(int l, int r)
{
	st.qs = l;
	st.qe = r - 1;
	return st.get_sum(1, 0, st.n - 1);
}

void add(int l, int r, long long x)
{
	st.qs = l;
	st.qe = r - 1;
	
	return st.lazy_add(1, 0, st.n - 1, x);
}
void set_range(int l, int r, long long x)
{
	st.qs = l;
	st.qe = r - 1;
		
	return st.lazy_set(1, 0, st.n - 1, x);
}
long long get_min(int l, int r)
{
	st.qs = l;
	st.qe = r - 1;
	
	return st.get_min(1, 0, st.n - 1);
}
int lower_bound(int l, int r, long long x)
{
	st.qs = l;
	st.qe = r - 1;
	
	return st.lower_bound(1, 0, st.n - 1, x);
}
void printSegmentTree()
{
	st.printSegmentTree();
}
