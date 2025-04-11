#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>

using namespace std;

#define all(a) a.begin(), a.end()

void Foo()
{
	ios_base::sync_with_stdio(0);
	cout.tie(0);
	cin.tie(0);

	int n;
	std::cin >> n;

	vector<int> vec(n);

	for (int i = 0; i < n; i++)
	{
		std::cin >> vec[i];
	}


	std::cout << *min_element(all(vec)) << std::endl;


}
