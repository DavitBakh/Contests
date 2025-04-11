#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

//finds the cycle in the graph
bool dfs(int v, int prev, vector<list<int>>& g, vector<int>& used, vector<int>& path)
{
	used[v] = 1;
	path.push_back(v);

	for (auto& to : g[v])
	{
		if (!used[to])
			if (dfs(to, v, g, used, path))
				return true;

		if (used[to] == 1 && to != prev)
		{
			auto it = find(all(path), to);
			std::cout << distance(it, path.end()) + 1 << std::endl;
			while (it != path.end())
			{
				std::cout << *it + 1 << ' ';
				it++;
			}
			std::cout << to + 1 << std::endl;

			return true;
		}

	}

	used[v] = 2;
	path.pop_back();

	return false;
}

void dfs(int v, vector<list<int>>& g, vector<int>& used)
{
	used[v] = 1;
	for (auto& to : g[v])
	{
		if (!used[to])
			dfs(to, g, used);
	}
}

void bfs(int source, vector<list<int>>& graph, vector<char>& used)
{
	int n = graph.size();

	queue<int> q;
	q.push(source);
	used[source] = 1;

	while (!q.empty())
	{
		int curr = q.front();
		q.pop();

		for (auto& e : graph[curr])
		{
			if (used[e] == 0)
			{
				q.push(e);
				used[e] = 1;
			}
		}
	}
}

int gcd(int a, int b, int& x, int& y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}

	int tx, ty;
	int c = gcd(b, a % b, tx, ty);
	x = ty;
	y = tx - (a / b) * ty;

	return c;
}
