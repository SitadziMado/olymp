#pragma once

#include <chrono>
#include <fstream>
#include <functional>
#include <iterator>
#include <string>

#include "IoHelper.h"

class Tester
{
public:
	Tester();
	Tester(const std::function<void()>& mainFunc);

	template<typename TCallable, typename... Ts>
	static long long ms(const TCallable& callable, Ts&&... args);

	Tester& eq(const std::string& test, const std::string& expected);
	Tester& func(const std::function<void()>& newFunc);

private:
	std::function<void()> mainFunc_;

	static size_t testCnt;
};

template<typename TCallable, typename ...Ts>
inline long long Tester::ms(const TCallable& callable, Ts&& ...args)
{
	using std::chrono::duration_cast;
	using std::chrono::milliseconds;

	static auto hrc = std::chrono::high_resolution_clock();

	auto before = hrc.now();

	callable(std::forward<Ts>(args)...);

	auto after = hrc.now();

	return duration_cast<milliseconds>(after - before).count();
}