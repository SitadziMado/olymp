#include "Tester.h"

Tester::Tester()
{}

Tester::Tester(const std::function<void()>& mainFunc) :
	mainFunc_(mainFunc)
{}

Tester& Tester::eq(const std::string& test, const std::string& expected)
{
	std::ofstream("input.txt") << test;

	auto duration = Tester::ms(mainFunc_);

	std::string output;

	std::copy(
		std::istreambuf_iterator<char>(std::ifstream("output.txt")),
		std::istreambuf_iterator<char>(),
		std::back_inserter(output)
	);

	// lab_po_3_204A
	if (output == expected)
	{
		printSep(
			"",
			"���� ",
			testCnt,
			": �� (",
			duration,
			" ��)"
		);
	}
	else
	{
		printSep("", "���� ", testCnt, ": ���������");
		print(expected);
		print("\t��������: ");

		if (output == "")
			print("<��� ������>");
		else
			print(output);
	}

	++testCnt;

	return *this;
}

Tester& Tester::func(const std::function<void()>& newFunc)
{
	auto func = newFunc;
	mainFunc_.swap(func);
	testCnt = 0;
	return *this;
}

size_t Tester::testCnt = 0;