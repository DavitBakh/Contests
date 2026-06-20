#include<bits/stdc++.h>

using namespace std;

struct SegTree
{
	size_t size;
	vector<long long> tree;

	SegTree(int n)
	{
		size = 1;
		while (size < n)
			size *= 2;

		tree.assign(2 * size - 1, 0);
	}

	SegTree(vector<int>& vec) : SegTree(vec.size())
	{
		build(vec, 0, 0, size);
	}

	void build(vector<int>& vec, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			if (lx < vec.size())
				tree[x] = vec[lx];

			return;
		}

		int mid = midpoint(lx, rx);
		build(vec, 2 * x + 1, lx, mid);
		build(vec, 2 * x + 2, mid, rx);
		tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
	}

	void Set(int i, int v)
	{
		Set(i, v, 0, 0, size);
	}

	void Set(int i, int v, int x, int lx, int rx)
	{
		if (rx - lx == 1)
		{
			tree[x] = v;
			return;
		}

		int mid = midpoint(lx, rx);
		if (i < mid)
			Set(i, v, 2 * x + 1, lx, mid);
		else
			Set(i, v, 2 * x + 2, mid, rx);

		tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
	}


	long long Sum(int l, int r)
	{
		return Sum(l, r, 0, 0, size);
	}

	long long Sum(int l, int r, int x, int lx, int rx)
	{
		if (rx <= l || r <= lx)
			return 0;

		if (l <= lx && rx <= r)
			return tree[x];

		int mid = midpoint(lx, rx);
		return Sum(l, r, 2 * x + 1, lx, mid) + Sum(l, r, 2 * x + 2, mid, rx);
	}
};