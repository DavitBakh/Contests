#ifndef UTILS_H
#define UTILS_H

#pragma optimize("gt", on)  // Enable global optimization + fast code generation

#include <bits/stdc++.h> 
#include <Windows.h>

#define all(a) a.begin(), a.end()
#define ull unsigned long long

constexpr unsigned long long INF = 1e18;
constexpr int MOD = 1e9 + 7;

void CopyToClipboard(const std::string& text)
{
	// Open the clipboard
	if (!OpenClipboard(nullptr))
	{
		std::cerr << "Failed to open clipboard!" << std::endl;
		return;
	}

	// Empty the clipboard
	EmptyClipboard();

	// Allocate a global memory object for the text
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
	if (!hMem)
	{
		std::cerr << "Failed to allocate global memory!" << std::endl;
		CloseClipboard();
		return;
	}

	// Copy the text to the memory object
	memcpy(GlobalLock(hMem), text.c_str(), text.size() + 1);
	GlobalUnlock(hMem);

	// Set the clipboard data
	if (!SetClipboardData(CF_TEXT, hMem))
	{
		std::cerr << "Failed to set clipboard data!" << std::endl;
		GlobalFree(hMem);
		CloseClipboard();
		return;
	}

	// Close the clipboard
	CloseClipboard();
	std::cout << "Text copied to clipboard successfully!" << std::endl;
}
std::string GetFromClipboard()
{
	std::string clipboardText;

	// Open the clipboard
	if (!OpenClipboard(nullptr))
	{
		std::cerr << "Failed to open clipboard!" << std::endl;
		return clipboardText;
	}

	// Get clipboard data in CF_TEXT format
	HANDLE hData = GetClipboardData(CF_TEXT);
	if (!hData)
	{
		std::cerr << "Failed to get clipboard data!" << std::endl;
		CloseClipboard();
		return clipboardText;
	}

	// Lock the handle to get the actual text pointer
	char* pszText = static_cast<char*>(GlobalLock(hData));
	if (pszText)
	{
		clipboardText = pszText;  // Copy the text from the clipboard
		GlobalUnlock(hData);
	}
	else
		std::cerr << "Failed to lock global memory!" << std::endl;

	// Close the clipboard
	CloseClipboard();

	return clipboardText;
}

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

void GetZF(const string& str, vector<int>& z)
{
	int n = str.size();

	int l = 0, r = 0;
	for (int i = 1; i < n; ++i)
	{
		if (r >= i)
			z[i] = min(z[i - l], r - i + 1);

		while (z[i] + i < n && str[z[i]] == str[z[i] + i])
			++z[i];

		if (i + z[i] - 1 > r)
		{
			l = i;
			r = i + z[i] - 1;
		}
	}
}

int binpow(int a, int b, int m = MOD)
{
	int res = 1;
	a %= m;
	while (b > 0) {
		if (b & 1) res = res * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return res;
}

void Eratasfen()
{
	int N = 6e6;
	vector<int> p, ip(N, 1);

	p.push_back(2);
	for (int i = 4; i <= N; i += 2)
		ip[i] = 0;

	for (int i = 3; i <= N; i += 2)
	{
		if (ip[i])
		{
			for (int j = 2 * i; j <= N; j += i)
				ip[j] = 0;

			p.push_back(i);
		}
	}
}
void Djikstra(vector < vector < pair<int, int>>>& gr)
{
	int n = gr.size();
	vector<int> d(n, INF);

	d[0] = 0;
	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0,0 });

	while (!pq.empty())
	{
		int v = pq.top().second, cur_d = pq.top().first;
		pq.pop();

		if (cur_d > d[v])
			continue;

		for (auto& i : gr[v])
		{
			int to = i.first;
			int cost = i.second;

			if (d[v] + cost < d[to])
			{
				d[to] = d[v] + cost;
				pq.push({ d[to], to });
			}
		}
	}
}

void Prim(vector<vector<pair<int, int>>>& gr)
{
	int n = gr.size();

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ 0,0 });

	vector<char> used(n);
	unsigned long long minCost = 0;
	while (!pq.empty())
	{
		pair<int, int> curr = pq.top();
		pq.pop();

		int v = curr.second;
		int cost = curr.first;

		if (used[v])
			continue;

		used[v] = 1;
		minCost += cost;
		for (auto& e : gr[v])
		{
			if (!used[e.first])
				pq.push({ e.second, e.first });
		}
	}

	if (any_of(all(used), [&](char ch) {return ch == 0; }))
		std::cout << "IMPOSSIBLE" << std::endl;
	else
		std::cout << minCost << std::endl;
}

int partition(vector<int>& arr, int pivotIndex)
{
	int low = 0, high = arr.size() - 1;
	int pivot = arr[pivotIndex];

	while (low < high)
	{
		while (low < high && arr[low] <= pivot)
			++low;

		while (low < high && arr[high] >= pivot)
			--high;

		if (low < high)
		{
			swap(arr[low], arr[high]);
		}
	}

	swap(arr[high], arr[pivotIndex]);

	return high;
}

int longestCommonSubsequence(string text1, string text2)
{
	int n = text1.size();
	int m = text2.size();

	vector<vector<int>> dp(n + 1, vector<int>(m + 1));

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (text1[i - 1] == text2[j - 1])
				dp[i][j] = dp[i - 1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}

	return dp.back().back();
}

#endif // !UTILS_H
