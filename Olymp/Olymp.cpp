#include <algorithm>
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

std::vector<i64> pows = {
	1,
2,
	4,
	8,
	16,
	32,
	64,
	128,
	256,
	512,
	1024,
	2048,
	4096,
	8192,
	16384,
	32768,
	65536,
	131072,
	262144,
	524288,
	1048576,
	2097152,
	4194304,
	8388608,
	16777216,
	33554432,
	67108864,
	134217728,
	268435456,
	536870912,
	1073741824,
	2147483648,
	4294967296,
	8589934592,
	17179869184,
	34359738368,
	68719476736,
	137438953472,
	274877906944,
	549755813888,
	1099511627776,
	2199023255552,
	4398046511104,
	8796093022208,
	17592186044416,
	35184372088832,
	70368744177664,
	140737488355328,
	281474976710656,
	562949953421312,
	1125899906842624,
	2251799813685248,
	4503599627370496,
	9007199254740992,
	18014398509481984,
	36028797018963968,
	72057594037927936,
	144115188075855872,
	288230376151711744,
	576460752303423488,
};

struct Tuple
{
	i64 value;
	i64 cost;
	i64 count;
};

bool operator<(const Tuple& lhs, const Tuple& rhs)
{
	return (lhs.cost) < (rhs.cost);
}

void _main();

int main(int argc, char **argv)
{
	std::ios_base::sync_with_stdio(false);

#ifdef HOME

	std::setlocale(LC_ALL, "ru-RU");

	Tester tester(_main);

	tester
		.eq(
			"0 500000",
			""
		)
		.eq(
			"1 500000",
			""
		)
		;

#else
	_main();
#endif // HOME

	// _main();

	return 0;
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
	
	std::vector<int> vec(2000000, 1);
	std::list<int> lst(2000000, 1);

	int n, where;

	cin >> n >> where;

	if (n == 0)
	{
		for (size_t i = 0; i < 500; ++i)
		{
			// vec.insert(vec.begin() + where, 2);
			vec.push_back(2);
		}
	}
	else
	{
		for (size_t i = 0; i < 500; ++i)
		{
			auto it = lst.begin();
			std::advance(it, where);
			lst.insert(it, 2);
		}
	}

	/*size_t t;

	cin >> t;

	for (size_t i = 0; i < t; ++i)
	{
		std::multiset<Tuple> vals;

		vals.insert({ 1, 2, 2});

		i64 n;
		cin >> n;
		--n;
		i64 temp = 2;
		size_t iters = 1;

		i64 col = 1;
		i64 cost = 0;		
		auto fst = vals.cbegin();
		auto fstVal = *fst;

		i64 newTemp = 1;

		while (col < 1000000000000000000)
		{
			col = newTemp;

			for (i64 i = 1; i < newTemp; ++i)
			{
				int idx = 0;
				temp = newTemp / i;
				for (int j = 1; j < pows.size(); ++j)
					if (temp < pows[j])
						break;
					else
						idx = j;
				col += i * pows[idx];
			}
			cout << "Temp =" << newTemp << " col = " << col;
		}
	}*/

#ifdef HOME
	// system("pause");
#endif
}