#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX20_CISO646_REMOVED_WARNING
#include<bits/stdc++.h>
#include<unordered_set>
//#include<primesieve.hpp>
using namespace std;


#define all(a) a.begin(), a.end()
#define read(x) for(auto &elem : x) cin >> elem;
#define forall(x) for(auto &e : x)

constexpr int MOD = 1e9 + 7;


int main()
{
#pragma region Preparations
#ifdef _LOCAL
	freopen("input.txt", "r", stdin);
#endif // _LOCAL

	std::ios_base::sync_with_stdio(0);
	std::cout.tie(0);
	std::cin.tie(0);
#pragma endregion


	int n, x;
	std::cin >> n >> x;

	vector<int> weight(n+1);
	for (int i = 1; i <= n; i++)
		std::cin >> weight[i];

	vector<int> cost(n+1);
	for (int i = 1; i <= n; i++)
		std::cin >> cost[i];

	vector<vector<int>> dp(n + 1, vector<int>(x + 1));

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= x; j++)
		{
			if (j >= weight[i])
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + cost[i]);
			else
				dp[i][j] = dp[i - 1][j];
		}
	}

	std::cout << dp[n][x] << std::endl;

}