#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <cstdio>

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
void printSep(const std::string& sep, Ts&&... args)
{
	fprint(std::cout, sep, std::forward<Ts>(args)...);
}

template<typename... Ts>
void print(Ts&&... args)
{
	printSep(DefaultSep, std::forward<Ts>(args)...);
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const std::vector<T>& cont)
{
	auto it = cont.cbegin();

	if (cont.size())
	{
		stream << *it++;

		for (it; it != cont.cend(); ++it)
			stream << DefaultSep << *it;
	}

	return stream;
}
