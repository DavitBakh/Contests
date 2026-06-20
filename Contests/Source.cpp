#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX20_CISO646_REMOVED_WARNING
#include<bits/stdc++.h>
#include<unordered_set>
//#include<primesieve.hpp>
using namespace std;


#define all(a) a.begin(), a.end()
#define read(x) for(auto &e : x) cin >> e;
#define forall(x) for(auto &e : x)
#define printLine(x) {for(auto& e : x) std::cout << e << ' '; std::cout << '\n';};

constexpr int MOD = 1e9 + 7;

typedef unsigned long long ull;
typedef long long ll;
typedef unsigned int ui;

ll power(ll base, ll exp)
{
	ll res = 1;
	base %= MOD;

	while (exp > 0)
	{
		if (exp % 2 == 1)
			res = (res * base) % MOD;

		base = (base * base) % MOD;
		exp /= 2;
	}

	return res;
}

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

	return 0;
}