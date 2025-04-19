#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h> 
#include <Windows.h>

#define all(a) a.begin(), a.end()

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


#endif // !UTILS_H
