#include <bits/stdc++.h>
using namespace  std;

struct Nodo
{
	int sum;
	int ps; //max prefix sum
	int ss; //max suffix sum
	int ms; //max sum
};

Nodo *tree;
int n;
vector<int> v;

Nodo unite(Nodo left, Nodo right)
{
	Nodo nodo;
	nodo.sum = left.sum + right.sum;
	nodo.ps = max(left.ps, left.sum + right.ps);
	nodo.ss = max(right.ss, right.sum + left.ss);
	nodo.ms = max(max(left.ms,right.ms),left.ss+right.ps);
	return nodo;	
}

void mergefigli(int i)
{
	assert(i<n);
	tree[i].sum = tree[i*2].sum + tree[i*2+1].sum;
	tree[i].ps = max(tree[i*2].sum, tree[i*2].sum + tree[i*2+1].ps);
	tree[i].ss = max(tree[i*2+1].ss, tree[i*2+1].sum + tree[i*2].ss);
	tree[i].ms = max(max(tree[i*2].ms, tree[i*2+1].ms), tree[i*2].ss + tree[i*2+1].ps);
}

void build(int i, int l, int r) // [l, r]
{
	if(l==r) //foglia
	{
		tree[i].sum = tree[i].ps = tree[i].ss= tree[i].ms= v[i-n];
		return;
	}
	int mid = (l+r)/2;
	build(i*2,l, mid);
	build(i*2+1, mid+1, r);
	mergefigli(i);
}

void update(int i)
{
	//cout<<i<<"ok"<<endl;
	
	
	if(i == 0)//abbiamo superato la radice
		return;
	mergefigli(i);
	update(i/2);
}

Nodo query(int sq, int eq, int inx, int l, int r)
{
	if(l>eq || r<sq)//out of range
	{
		return {0, -9999999, -9999999, -9999999};
	}

	if(l>=sq && r<=eq)
		return tree[inx];
		
	int mid = (l+r)/2;
	Nodo left= query(sq, eq, inx*2, l, mid);
	Nodo right = query(sq, eq, inx*2+1, mid+1, r);
	return unite(left, right);
}
void print()
{
	for(int i=1; i<2*n; i++)
	cout<<i<<" "<<tree[i].sum<<" "<<tree[i].ps<<" "<<tree[i].ss<<" "<<tree[i].ms<<endl;
}

int main()
{
	cin>>n;
	
	int tmp = n;
	n = 1;
	while(n<tmp) n<<=1;
	v.resize(n, 0);
	tree = (Nodo *)malloc(2*n*sizeof(Nodo));
	
	for(int i=0; i<tmp; i++) cin>>v[i];
	build(1,0, n-1);
	
	int q;
	cin>>q;
	for(int i=0; i<q; i++)
	{
		int tipo;
		cin>>tipo;
		if(tipo==0)
		{
			int pos, value;
			cin>>pos>>value;
			pos--;
			tree[n+pos].sum = tree[n+pos].ps = tree[n+pos].ss= tree[n+ pos].ms= value;
			update(((n+pos)/2));
		}
		else
		{
			int sq, eq;
			cin>>sq>>eq;
			sq--;
			eq--;
			Nodo ris = query(sq, eq, 1, 0, n-1);
			cout<<ris.ms<<endl;
		}
	}
}
