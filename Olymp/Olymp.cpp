#include <algorithm>
#include <array>
#include <chrono>
#include <deque>
#include <fstream>
#include <functional>
#include <iterator>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <limits>
#include <list>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <queue>

#include <thread>

#include <clocale>
#include <cmath>

#ifdef HOME
#include "Tester.h"
#endif // HOME

using i64 = long long;
using u64 = unsigned long long;

void _main();

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(false);

#ifdef HOME

	std::setlocale(LC_ALL, "ru-RU");

	Tester tester(_main);

	tester
		.eq(
			R"(8
+ 0
+ 2
+ 8
+ 32
-
-
-
-)",
R"(No
No
No
Yes
Yes
No
No
No)"
)
.eq(
	R"(5
+ 2
+ 8
+ 32
+ 11
-)",
R"(No
No
Yes
Yes
No)"
)
;

#else
	_main();
#endif // HOME123123

	//_main();

	return 0;
}

using Matrix = std::array<std::array<bool, 43>, 43>;

void remove(Matrix& m, std::array<i64, 43>& xors, i64 t)
{
	for (size_t j = 0; j < xors.size(); ++j)
	{
		if (m[t][j])
		{
			xors[j] -= 1;						
			
			auto xorp = t ^ j;

			if (xorp <= 42)
			{

				m[xorp][j] = false;
				if (xors[j] == 0)
				{
					remove(m, xors, j);
				}
			}

			
		}
	}
}

void _main()
{
	using std::cin;
	using std::cout;

#ifdef HOME
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
#define cin in
#define cout out
#endif

	size_t n;

	cin >> n;

	std::array<i64, 43> nums1 = { 0 };
	std::queue<i64> set;
	for (size_t i = 0; i < n; i++)
	{
		nums1[0] = 1;
		char c;
		cin >> c;
		if (c == '+') {
			size_t t;
			cin >> t;
			set.push(t);
			++nums1[t];
		}
		else {
			size_t t = set.front();
			set.pop();
			--nums1[t];
		}
		std::array<bool, 43> ar = { false };
		std::array<i64, 43> nums = { 0 };
		for (size_t j = 0; j < 43; j++)
		{
			nums[j] = (nums1[j] > 0)?1:0;
		}
		bool changed = true;
		while (changed) {
			changed = false;
			for (size_t k = 0; k < 43; k++)
			{
				if (nums[k] > 0 && !ar[k]) {
					ar[k] = true;
					changed = true;
					for (size_t j = 0; j < 43; j++)
					{
						size_t xorp = k^j;
						if (xorp < 43&&nums[j]>0 && nums[xorp]==0) {
							nums[xorp] += 1;
						}
					}
				}
			}
		}
		if (nums[42] > 0) cout << "Yes" << std::endl; else cout << "No" << std::endl;
	}

#ifdef HOME
	// system("pause");
#endif
}