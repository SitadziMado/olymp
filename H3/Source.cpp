#include <algorithm>
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
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <queue>
#include <cmath>

using i64 = long long;
using u64 = unsigned long long;

const std::string DefaultSep = " ";

template<typename T, typename... Ts>
struct Printer;

template<typename T>
struct Printer<T>
{
	void operator()(T&& t)
	{
		print(std::cout, DefaultSep, t);
	}

	void print(std::ostream& stream, const std::string& sep, T&& t)
	{
		stream << t << std::endl;
	}
};

template<typename T, typename... Ts>
struct Printer
{
	void operator()(T&& t, Ts&&... ts)
	{
		print(std::cout, DefaultSep, t, ts...);
	}

	void print(std::ostream& stream, const std::string& sep, T&& t, Ts&&... ts)
	{
		stream << t << sep;

		Printer<Ts...>().print(stream, sep, std::forward<Ts>(ts)...);
	}
};

template<typename... Ts>
void fprint(std::ostream& stream, const std::string& sep, Ts&&... args)
{
	Printer<Ts...>().print(stream, sep, std::forward<Ts>(args)...);
}

template<typename... Ts>
void print(Ts&&... args)
{
	print(DefaultSep, std::forward<Ts>(args)...)
}

template<typename... Ts>
void print(const std::string& sep, Ts&&... args)
{
	fprint(std::cout, sep, std::forward<Ts>(args)...);
}

int main()
{
	using std::cin;
	using std::cout;

#ifdef HOME
	std::ifstream in = std::ifstream("input.txt");
#define cin in
#endif

	std::ios_base::sync_with_stdio(false);

	size_t n;

	cin >> n;

	print("Hello, world!");

#ifdef HOME
	system("pause");
#endif

	return 0;
}