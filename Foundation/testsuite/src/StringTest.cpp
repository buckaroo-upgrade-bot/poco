//
// StringTest.cpp
//
// $Id: //poco/1.4/Foundation/testsuite/src/StringTest.cpp#1 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "StringTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/String.h"
#include "Poco/Format.h"
#include "Poco/MemoryStream.h"
#include "Poco/Stopwatch.h"
#include <iostream>
#include <iomanip>
#include <cstdio>


using Poco::trimLeft;
using Poco::trimLeftInPlace;
using Poco::trimRight;
using Poco::trimRightInPlace;
using Poco::trim;
using Poco::trimInPlace;
using Poco::toUpper;
using Poco::toUpperInPlace;
using Poco::toLower;
using Poco::toLowerInPlace;
using Poco::icompare;
using Poco::translate;
using Poco::translateInPlace;
using Poco::replace;
using Poco::replaceInPlace;
using Poco::cat;
using Poco::strToInt;
using Poco::strToFloat;
using Poco::thousandSeparator;
using Poco::decimalSeparator;
using Poco::format;
using Poco::MemoryInputStream;
using Poco::Stopwatch;


StringTest::StringTest(const std::string& name): CppUnit::TestCase(name)
{
}


StringTest::~StringTest()
{
}


void StringTest::testTrimLeft()
{
	{
		std::string s = "abc";
		assert (trimLeft(s) == "abc");
	}
		std::string s = " abc ";
		assert (trimLeft(s) == "abc ");
	{
	std::string s = "  ab c ";
	assert (trimLeft(s) == "ab c ");
	}
}


void StringTest::testTrimLeftInPlace()
{
	{
		std::string s = "abc";
		assert (trimLeftInPlace(s) == "abc");
	}
	{
		std::string s = " abc ";
		assert (trimLeftInPlace(s) == "abc ");
	}
	{
		std::string s = "  ab c ";
		assert (trimLeftInPlace(s) == "ab c ");
	}
}


void StringTest::testTrimRight()
{
	{
		std::string s = "abc";
		assert (trimRight(s) == "abc");
	}
	{
		std::string s = " abc ";
		assert (trimRight(s) == " abc");
	}
	{
		std::string s = "  ab c  ";
		assert (trimRight(s) == "  ab c");
	}
}


void StringTest::testTrimRightInPlace()
{
	{
		std::string s = "abc";
		assert (trimRightInPlace(s) == "abc");
	}
	{
		std::string s = " abc ";
		assert (trimRightInPlace(s) == " abc");
	}
	{
		std::string s = "  ab c  ";
		assert (trimRightInPlace(s) == "  ab c");
	}
}


void StringTest::testTrim()
{
	{
		std::string s = "abc";
		assert (trim(s) == "abc");
	}
	{
		std::string s = "abc ";
		assert (trim(s) == "abc");
	}
	{
		std::string s = "  ab c  ";
		assert (trim(s) == "ab c");
	}
}


void StringTest::testTrimInPlace()
{
	{
		std::string s = "abc";
		assert (trimInPlace(s) == "abc");
	}
	{
		std::string s = " abc ";
		assert (trimInPlace(s) == "abc");
	}
	{
		std::string s = "  ab c  ";
		assert (trimInPlace(s) == "ab c");
	}
}


void StringTest::testToUpper()
{
	{
		std::string s = "abc";
		assert (toUpper(s) == "ABC");
	}
	{
		std::string s = "Abc";
		assert (toUpper(s) == "ABC");
	}
	{
		std::string s = "abc";
		assert (toUpperInPlace(s) == "ABC");
	}
	{
		std::string s = "Abc";
		assert (toUpperInPlace(s) == "ABC");
	}
}


void StringTest::testToLower()
{
	{
		std::string s = "ABC";
		assert (toLower(s) == "abc");
	}
	{
		std::string s = "aBC";
		assert (toLower(s) == "abc");
	}
	{
		std::string s = "ABC";
		assert (toLowerInPlace(s) == "abc");
	}
	{
		std::string s = "aBC";
		assert (toLowerInPlace(s) == "abc");
	}
}


void StringTest::testIcompare()
{
	std::string s1 = "AAA";
	std::string s2 = "aaa";
	std::string s3 = "bbb";
	std::string s4 = "cCcCc";
	std::string s5;
	assert (icompare(s1, s2) == 0);
	assert (icompare(s1, s3) < 0);
	assert (icompare(s1, s4) < 0);
	assert (icompare(s3, s1) > 0);
	assert (icompare(s4, s2) > 0);
	assert (icompare(s2, s4) < 0);
	assert (icompare(s1, s5) > 0);
	assert (icompare(s5, s4) < 0);

	std::string ss1 = "xxAAAzz";
	std::string ss2 = "YaaaX";
	std::string ss3 = "YbbbX";
	assert (icompare(ss1, 2, 3, ss2, 1, 3) == 0);
	assert (icompare(ss1, 2, 3, ss3, 1, 3) < 0);
	assert (icompare(ss1, 2, 3, ss2, 1) == 0);
	assert (icompare(ss1, 2, 3, ss3, 1) < 0);
	assert (icompare(ss1, 2, 2, ss2, 1, 3) < 0);
	assert (icompare(ss1, 2, 2, ss2, 1, 2) == 0);
	assert (icompare(ss3, 1, 3, ss1, 2, 3) > 0);
	
	assert (icompare(s1, s2.c_str()) == 0);
	assert (icompare(s1, s3.c_str()) < 0);
	assert (icompare(s1, s4.c_str()) < 0);
	assert (icompare(s3, s1.c_str()) > 0);
	assert (icompare(s4, s2.c_str()) > 0);
	assert (icompare(s2, s4.c_str()) < 0);
	assert (icompare(s1, s5.c_str()) > 0);
	assert (icompare(s5, s4.c_str()) < 0);
	
	assert (icompare(ss1, 2, 3, "aaa") == 0);
	assert (icompare(ss1, 2, 2, "aaa") < 0);
	assert (icompare(ss1, 2, 3, "AAA") == 0);
	assert (icompare(ss1, 2, 2, "bb") < 0);
	
	assert (icompare(ss1, 2, "aaa") > 0);
}


void StringTest::testTranslate()
{
	std::string s = "aabbccdd";
	assert (translate(s, "abc", "ABC") == "AABBCCdd");
	assert (translate(s, "abc", "AB") == "AABBdd");
	assert (translate(s, "abc", "") == "dd");
	assert (translate(s, "cba", "CB") == "BBCCdd");
	assert (translate(s, "", "CB") == "aabbccdd");
}


void StringTest::testTranslateInPlace()
{
	std::string s = "aabbccdd";
	translateInPlace(s, "abc", "ABC");
	assert (s == "AABBCCdd");
}


void StringTest::testReplace()
{
	std::string s("aabbccdd");
	
	assert (replace(s, std::string("aa"), std::string("xx")) == "xxbbccdd");
	assert (replace(s, std::string("bb"), std::string("xx")) == "aaxxccdd");
	assert (replace(s, std::string("dd"), std::string("xx")) == "aabbccxx");
	assert (replace(s, std::string("bbcc"), std::string("xx")) == "aaxxdd");
	assert (replace(s, std::string("b"), std::string("xx")) == "aaxxxxccdd");
	assert (replace(s, std::string("bb"), std::string("")) == "aaccdd");
	assert (replace(s, std::string("b"), std::string("")) == "aaccdd");
	assert (replace(s, std::string("ee"), std::string("xx")) == "aabbccdd");
	assert (replace(s, std::string("dd"), std::string("")) == "aabbcc");

	assert (replace(s, "aa", "xx") == "xxbbccdd");
	assert (replace(s, "bb", "xx") == "aaxxccdd");
	assert (replace(s, "dd", "xx") == "aabbccxx");
	assert (replace(s, "bbcc", "xx") == "aaxxdd");
	assert (replace(s, "bb", "") == "aaccdd");
	assert (replace(s, "b", "") == "aaccdd");
	assert (replace(s, "ee", "xx") == "aabbccdd");
	assert (replace(s, "dd", "") == "aabbcc");
	
	s = "aabbaabb";
	assert (replace(s, std::string("aa"), std::string("")) == "bbbb");
	assert (replace(s, std::string("a"), std::string("")) == "bbbb");
	assert (replace(s, std::string("a"), std::string("x")) == "xxbbxxbb");
	assert (replace(s, std::string("a"), std::string("xx")) == "xxxxbbxxxxbb");
	assert (replace(s, std::string("aa"), std::string("xxx")) == "xxxbbxxxbb");

	assert (replace(s, std::string("aa"), std::string("xx"), 2) == "aabbxxbb");

	assert (replace(s, "aa", "") == "bbbb");
	assert (replace(s, "a", "") == "bbbb");
	assert (replace(s, "a", "x") == "xxbbxxbb");
	assert (replace(s, "a", "xx") == "xxxxbbxxxxbb");
	assert (replace(s, "aa", "xxx") == "xxxbbxxxbb");
	
	assert (replace(s, "aa", "xx", 2) == "aabbxxbb");
}


void StringTest::testReplaceInPlace()
{
	std::string s("aabbccdd");

	assert (replaceInPlace(s, std::string("aa"), std::string("xx")) == "xxbbccdd");
}


void StringTest::testCat()
{
	std::string s1("one");
	std::string s2("two");
	std::string s3("three");
	std::string s4("four");
	std::string s5("five");
	std::string s6("six");

	assert (cat(s1, s2) == "onetwo");
	assert (cat(s1, s2, s3) == "onetwothree");
	assert (cat(s1, s2, s3, s4) == "onetwothreefour");
	assert (cat(s1, s2, s3, s4, s5) == "onetwothreefourfive");
	assert (cat(s1, s2, s3, s4, s5, s6) == "onetwothreefourfivesix");
	
	std::vector<std::string> vec;
	assert (cat(std::string(), vec.begin(), vec.end()) == "");
	assert (cat(std::string(","), vec.begin(), vec.end()) == "");
	vec.push_back(s1);
	assert (cat(std::string(","), vec.begin(), vec.end()) == "one");
	vec.push_back(s2);
	assert (cat(std::string(","), vec.begin(), vec.end()) == "one,two");
	vec.push_back(s3);
	assert (cat(std::string(","), vec.begin(), vec.end()) == "one,two,three");
}


void StringTest::testStringToInt()
{
	stringToInt<Poco::Int8>();
	stringToInt<Poco::UInt8>();
	stringToInt<Poco::Int16>();
	stringToInt<Poco::UInt16>();
	stringToInt<Poco::Int32>();
	stringToInt<Poco::UInt32>();
#if defined(POCO_HAVE_INT64)
	stringToInt<Poco::Int64>();
	stringToInt<Poco::UInt64>();
#endif
}


void StringTest::testStringToFloat()
{
#ifndef POCO_NO_FPENVIRONMENT
	
	const char ds = decimalSeparator();
	const char ts = thousandSeparator();
	double result;
	assert(strToFloat(format("1", ds), result));
	assertEqualDelta(1.0, result, 0.01);
	assert(strToFloat(format("0", ds), result));
	assertEqualDelta(0.0, result, 0.01);
	assert(strToFloat(format("0%c0", ds), result));
	assertEqualDelta(0.0, result, 0.01);
	assert(strToFloat(format("0%c0", ds), result));
	assertEqualDelta(0., result, 0.01);
	assert(strToFloat(format("0%c0", ds), result));
	assertEqualDelta(.0, result, 0.01);
	assert(strToFloat(format("12%c34", ds), result));
	assertEqualDelta(12.34, result, 0.01);
	assert(strToFloat(format("12%c34f", ds), result));
	assertEqualDelta(12.34, result, 0.01);
	assert(strToFloat(format("12%c34", ds), result));
	assertEqualDelta(12.34, result, 0.01);
	assert(strToFloat(format("-12%c34", ds), result));
	assertEqualDelta(-12.34, result, 0.01);
	assert(strToFloat(format("%c34", ds), result));
	assertEqualDelta(.34, result, 0.01);
	assert(strToFloat(format("-%c34", ds), result));
	assertEqualDelta(-.34, result, 0.01);
	assert(strToFloat(format("12%c", ds), result));
	assertEqualDelta(12., result, 0.01);
	assert(strToFloat(format("-12%c", ds), result));
	assertEqualDelta(-12., result, 0.01);
	assert(strToFloat("12", result));
	assertEqualDelta(12, result, 0.01);
	assert(strToFloat("-12", result));
	assertEqualDelta(-12, result, 0.01);
	assert(strToFloat(format("12%c3456789012345678901234567890", ds), result));
	assertEqualDelta(12.34, result, 0.01);

	assert(strToFloat(format("1%c234%c3456789012345678901234567890", ts, ds), result));
	assertEqualDelta(1234.3456789, result, 0.00000001);
	assert(strToFloat(format("12%c345%c3456789012345678901234567890", ts, ds), result));
	assertEqualDelta(12345.3456789, result, 0.00000001);
	assert(strToFloat(format("123%c456%c3456789012345678901234567890", ts, ds), result));
	assertEqualDelta(123456.3456789, result, 0.00000001);
	assert(strToFloat(format("1%c234%c567%c3456789012345678901234567890", ts, ts, ds), result));
	assertEqualDelta(1234567.3456789, result, 0.00000001);
	assert(strToFloat(format("12%c345%c678%c3456789012345678901234567890", ts, ts, ds), result));
	assertEqualDelta(12345678.3456789, result, 0.00000001);
	assert(strToFloat(format("123%c456%c789%c3456789012345678901234567890", ts, ts, ds), result));
	assertEqualDelta(123456789.3456789, result, 0.00000001);

	if ((std::numeric_limits<double>::max() / 10) < 1.23456e10)
		fail ("test value larger than max value for this platform");
	else
	{
		double d = 12e34;
		assert(strToFloat(format("12e34", ds), result));
		assertEqualDelta(d, result, 0.01e34);
			
		d = 1.234e100;
		assert(strToFloat(format("1%c234e100", ds), result));
		assertEqualDelta(d, result, 0.01);
		assert(strToFloat(format("1%c234E+100", ds), result));
		assertEqualDelta(d, result, 0.01);
		
		d = 1.234e-100;
		assert(strToFloat(format("1%c234E-100", ds), result));
		assertEqualDelta(d, result, 0.01);
		
		d = -1.234e100;
		assert(strToFloat(format("-1%c234e+100", ds), result));
		assertEqualDelta(d, result, 0.01);
		assert(strToFloat(format("-1%c234E100", ds), result));
		assertEqualDelta(d, result, 0.01);
		
		d = 1.234e-100;
		assert(strToFloat(format(" 1%c234e-100 ", ds), result));
		assertEqualDelta(d, result, 0.01);
		assert(strToFloat(format(" 1%c234e-100 ", ds), result));
		assertEqualDelta(d, result, 0.01);
		assert(strToFloat(format("  1%c234e-100 ", ds), result));
		assertEqualDelta(d, result, 0.01);

		d = 1234.234e-100;
		assert(strToFloat(format(" 1%c234%c234e-100 ", ts, ds), result));
		assertEqualDelta(d, result, 0.01);
		d = 12345.234e-100;
		assert(strToFloat(format(" 12%c345%c234e-100 ", ts, ds), result));
		assertEqualDelta(d, result, 0.01);
		d = 123456.234e-100;
		assert(strToFloat(format("  123%c456%c234e-100 ", ts, ds), result));
		assertEqualDelta(d, result, 0.01);

		d = -1234.234e-100;
		assert(strToFloat(format(" -1%c234%c234e-100 ", ts, ds), result));
		assertEqualDelta(d, result, 0.01);
		d = -12345.234e-100;
		assert(strToFloat(format(" -12%c345%c234e-100 ", ts, ds), result));
		assertEqualDelta(d, result, 0.01);
		d = -123456.234e-100;
		char ou = 0;
		assert(strToFloat(format("  -123%c456%c234e-100 ", ts, ds), result));
		assertEqualDelta(d, result, 0.01);
		assert (ou == 0);
	}

	double d = 12.34e-10;
	assert(strToFloat(format("12%c34e-10", ds), result));
	assertEqualDelta(d, result, 0.01);
	assert(strToFloat(format("-12%c34", ds), result));
	assertEqualDelta(-12.34, result, 0.01);
	
	assert(strToFloat(format("   12%c34", ds), result));
	assertEqualDelta(12.34, result, 0.01);
	assert(strToFloat(format("12%c34   ", ds), result));
	assertEqualDelta(12.34, result, 0.01);
	assert(strToFloat(format(" 12%c34  ", ds), result));
	assertEqualDelta(12.34, result, 0.01);

#endif // POCO_NO_FPENVIRONMENT
}


void StringTest::testStringToFloatError()
{
#ifndef POCO_NO_FPENVIRONMENT
	const char ds = decimalSeparator();
	const char ts = thousandSeparator();

	double result = 0.0;
	char ou;
	assert (!strToFloat(format("a12%c3", ds), result, ou));
	assert (!strToFloat(format("1b2%c3", ds), result, ou));
	assert (!strToFloat(format("12c%c3", ds), result, ou));
	assert (!strToFloat(format("12%cx3", ds), result, ou));

	double d = -123456.234e-100;
	assert(strToFloat(format("123%c456%c234e-1000000", ts, ds), result, ou));
	assert (ou < 0); // loss of precision
	assertEqualDelta(d, result, 0.01); // value still good
	assert(!strToFloat(format("123%c456%c234e1000000", ts, ds), result, ou));
	assert(!strToFloat(format("123%c456%c234e+1000000", ts, ds), result, ou));
	assert(!strToFloat(0, result, ou)); // strToFloat is resilient to null pointers
	assert(!strToFloat("", result, ou));
#endif
}


void StringTest::testNumericLocale()
{
#if !defined(POCO_NO_LOCALE) && POCO_OS == POCO_OS_WINDOWS_NT
	try
	{
		char dp = decimalSeparator();
		char ts = thousandSeparator();
		std::locale loc;
		std::cout << "Original locale: '" << loc.name() << '\'' << std::endl;
		std::cout << "Decimal point: '" << decimalSeparator() << '\'' << std::endl;
		std::cout << "Thousand separator: '" << ts << '\'' << std::endl;

		std::locale::global(std::locale("German"));
		std::locale locGerman;
		assert (',' == decimalSeparator());
		assert ('.' == thousandSeparator());
		std::cout << "New locale: '" << locGerman.name() << '\'' << std::endl;
		std::cout << "Decimal point: '" << decimalSeparator() << '\'' << std::endl;
		std::cout << "Thousand separator: '" << thousandSeparator() << '\'' << std::endl;

		std::locale::global(std::locale("US"));
		std::locale locUS;
		assert ('.' == decimalSeparator());
		assert (',' == thousandSeparator());
		std::cout << "New locale: '" << locUS.name() << '\'' << std::endl;
		std::cout << "Decimal point: '" << decimalSeparator() << '\'' << std::endl;
		std::cout << "Thousand separator: '" << thousandSeparator() << '\'' << std::endl;

		std::locale::global(loc);
		dp = decimalSeparator();
		ts = thousandSeparator();
		std::cout << "Final locale: '" << loc.name() << '\'' << std::endl;
		std::cout << "Decimal point: '" << decimalSeparator() << '\'' << std::endl;
		std::cout << "Thousand separator: '" << thousandSeparator() << '\'' << std::endl;
		assert (dp == decimalSeparator());
		assert (ts == thousandSeparator());
	} catch (std::runtime_error& ex)
	{
		std::cout << ex.what() << std::endl;
		warnmsg ("Locale not found, skipping test");
	}
#endif
}


void StringTest::benchmarkStrToInt()
{
	Poco::Stopwatch sw;
	int number = 123456789;
	std::string num = "123456789";
	int res;
	sw.start();
	for (int i = 0; i < 1000000; ++i) parseStream(num, res);
	sw.stop();
	std::cout << "parseStream Number: " << res << std::endl;
	double timeStream = sw.elapsed() / 1000.0;

	char* pC = 0;
	sw.restart();
	for (int i = 0; i < 1000000; ++i) res = std::strtol(num.c_str(), &pC, 10);
	sw.stop();
	std::cout << "std::strtol Number: " << res << std::endl;
	double timeStrtol = sw.elapsed() / 1000.0;
	
	sw.restart();
	for (int i = 0; i < 1000000; ++i) strToInt(num.c_str(), res, 10);
	sw.stop();
	std::cout << "strToInt Number: " << res << std::endl;
	double timeStrToInt = sw.elapsed() / 1000.0;
	
	sw.restart();
	for (int i = 0; i < 1000000; ++i) std::sscanf(num.c_str(), "%d%c", &res);
	sw.stop();
	std::cout << "sscanf Number: " << res << std::endl;
	double timeScanf = sw.elapsed() / 1000.0;

	int graph;
	std::cout << std::endl << "Timing and speedup relative to I/O stream:" << std::endl << std::endl;
	std::cout << std::setw(14) << "Stream:\t" << std::setw(10) << std::setfill(' ') << timeStream << "[ms]" << std::endl;

	std::cout << std::setw(14) << "std::strtol:\t" << std::setw(10) << std::setfill(' ') << timeStrtol << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeStrtol) << '\t' ;
	graph = (int) (timeStream / timeStrtol); for (int i = 0; i < graph; ++i) std::cout << '|';

	std::cout << std::endl << std::setw(14) << "strToInt:\t" << std::setw(10) << std::setfill(' ') << timeStrToInt << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeStrToInt) << '\t' ;
	graph = (int) (timeStream / timeStrToInt); for (int i = 0; i < graph; ++i) std::cout << '|';

	std::cout << std::endl << std::setw(14) << "std::sscanf:\t" << std::setw(10) << std::setfill(' ')  << timeScanf << "[ms]" <<
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeScanf) << '\t' ;
	graph = (int) (timeStream / timeScanf); for (int i = 0; i < graph; ++i) std::cout << '|';
	std::cout << std::endl;
}


void StringTest::benchmarkStrToFloat()
{
	Poco::Stopwatch sw;
	double number = 1.23456e-123;
	std::string num = "1.23456e-123";
	double res;
	sw.start();
	for (int i = 0; i < 1000000; ++i) parseStream(num, res);
	sw.stop();
	std::cout << "parseStream Number: " << res << std::endl;
	double timeStream = sw.elapsed() / 1000.0;

	char* pC = 0;
	sw.restart();
	for (int i = 0; i < 1000000; ++i) res = std::strtod(num.c_str(), &pC);
	sw.stop();
	std::cout << "std::strtod Number: " << res << std::endl;
	double timeStrtod = sw.elapsed() / 1000.0;

	sw.restart();
	char ou = 0;
	for (int i = 0; i < 1000000; ++i) strToFloat(num.c_str(), res, ou);
	sw.stop();
	std::cout << "strToFloat Number: " << res << std::endl;
	double timeStrToFloat = sw.elapsed() / 1000.0;
	
	sw.restart();
	for (int i = 0; i < 1000000; ++i) std::sscanf(num.c_str(), "%f%c", &res);
	sw.stop();
	std::cout << "sscanf Number: " << res << std::endl;
	double timeScanf = sw.elapsed() / 1000.0;

	int graph;
	std::cout << std::endl << "Timing and speedup relative to I/O stream:" << std::endl << std::endl;
	std::cout << std::setw(14) << "Stream:\t" << std::setw(10) << std::setfill(' ') << timeStream << "[ms]" << std::endl;

	std::cout << std::setw(14) << "std::strtod:\t" << std::setw(10) << std::setfill(' ') << timeStrtod << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeStrtod) << '\t' ;
	graph = (int) (timeStream / timeStrtod); for (int i = 0; i < graph; ++i) std::cout << '#';
	std::cout << std::endl << std::setw(14) << "strToFloat:\t" << std::setw(10) << std::setfill(' ') << timeStrToFloat << "[ms]" << 
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeStrToFloat) << '\t' ;
	graph = (int) (timeStream / timeStrToFloat); for (int i = 0; i < graph; ++i) std::cout << '#';
	std::cout << std::endl << std::setw(14) << "std::sscanf:\t" << std::setw(10) << std::setfill(' ')  << timeScanf << "[ms]" <<
	std::setw(10) << std::setfill(' ')  << "Speedup: " << (timeStream / timeScanf) << '\t' ;
	graph = (int) (timeStream / timeScanf); for (int i = 0; i < graph; ++i) std::cout << '#';
	std::cout << std::endl;
}


void StringTest::setUp()
{
}


void StringTest::tearDown()
{
}


CppUnit::Test* StringTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("StringTest");

	CppUnit_addTest(pSuite, StringTest, testTrimLeft);
	CppUnit_addTest(pSuite, StringTest, testTrimLeftInPlace);
	CppUnit_addTest(pSuite, StringTest, testTrimRight);
	CppUnit_addTest(pSuite, StringTest, testTrimInPlace);
	CppUnit_addTest(pSuite, StringTest, testTrim);
	CppUnit_addTest(pSuite, StringTest, testTrimRightInPlace);
	CppUnit_addTest(pSuite, StringTest, testToUpper);
	CppUnit_addTest(pSuite, StringTest, testToLower);
	CppUnit_addTest(pSuite, StringTest, testIcompare);
	CppUnit_addTest(pSuite, StringTest, testTranslate);
	CppUnit_addTest(pSuite, StringTest, testTranslateInPlace);
	CppUnit_addTest(pSuite, StringTest, testReplace);
	CppUnit_addTest(pSuite, StringTest, testReplaceInPlace);
	CppUnit_addTest(pSuite, StringTest, testCat);
	CppUnit_addTest(pSuite, StringTest, testStringToInt);
	CppUnit_addTest(pSuite, StringTest, testStringToFloat);
	CppUnit_addTest(pSuite, StringTest, testStringToFloatError);
	CppUnit_addTest(pSuite, StringTest, testNumericLocale);
	//CppUnit_addTest(pSuite, StringTest, benchmarkStrToFloat);
	//CppUnit_addTest(pSuite, StringTest, benchmarkStrToInt);

	return pSuite;
}
