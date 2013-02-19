//
// DirectoryIteratorsTest.cpp
//
// $Id: //poco/1.4/Foundation/testsuite/src/DirectoryIteratorsTest.cpp#1 $
//
// Copyright (c) 2012, Applied Informatics Software Engineering GmbH.
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


#include "DirectoryIteratorsTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/SortedDirectoryIterator.h"
#include "Poco/RecursiveDirectoryIterator.h"
#include "Poco/FileStream.h"

#include <iostream>

using namespace Poco;


DirectoryIteratorsTest::DirectoryIteratorsTest(const std::string& name):
	CppUnit::TestCase(name)
{
}


DirectoryIteratorsTest::~DirectoryIteratorsTest()
{
}


void DirectoryIteratorsTest::testDirectoryIterator()
{
	Path p = path();
	DirectoryIterator dirIterator(p);
	DirectoryIterator end;
	std::vector<std::string> result;
	std::string file;

	while (dirIterator != end)
	{
		file = dirIterator->path();
		++dirIterator;
		result.push_back(file);
	}

	assertEquals(7, result.size());
}


void DirectoryIteratorsTest::testSortedDirectoryIterator()
{
	Path p = path();
	SortedDirectoryIterator dirIterator(p);
	SortedDirectoryIterator end;
	std::vector<std::string> result;
	std::string file;

	while (dirIterator != end)
	{
		file = Path(dirIterator->path()).getFileName();
		++dirIterator;
		result.push_back(file);
	}

	assertEquals(7, result.size());
	assertEquals("first", result[0]);
	assertEquals("1", result[1]);
	assertEquals("2", result[2]);
	assertEquals("A", result[3]);
	assertEquals("B", result[4]);
	assertEquals("a", result[5]);
	assertEquals("b", result[6]);
}


void DirectoryIteratorsTest::testSimpleRecursiveDirectoryIterator()
{
	Path p = path();
	SimpleRecursiveDirectoryIterator dirIterator(p);
	SimpleRecursiveDirectoryIterator end;
	std::vector<std::string> result;
	std::string file;

	while (dirIterator != end)
	{
		file = dirIterator->path();
		++dirIterator;
		result.push_back(file);
	}

	assertEquals(20, result.size());
}


void DirectoryIteratorsTest::testSiblingsFirstRecursiveDirectoryIterator()
{
	Path p = path();
	SiblingsFirstRecursiveDirectoryIterator dirIterator(p);
	SiblingsFirstRecursiveDirectoryIterator end;
	std::vector<std::string> result;
	std::string file;

	while (dirIterator != end)
	{
		file = dirIterator->path();
		++dirIterator;
		result.push_back(file);
	}

	assertEquals(20, result.size());
}


void DirectoryIteratorsTest::setUp()
{
	try
	{
		File d(path());
		d.remove(true);
	}
	catch (...)
	{
	}

	/*
	  Build Directory Tree like this:

	  DirectoryIteratorsTest
		|-- 1
		|-- 2
		|-- A
		|-- B
		|-- a
		|-- b
		`-- first
			|-- 1
			|-- 2
			|-- A
			|-- B
			|-- a
			|-- b
			`-- second
				|-- 1
				|-- 2
				|-- A
				|-- B
				|-- a
				`-- b

		2 directories, 18 files
	 */
	Path p = path();
	createSubdir(p);

	p.pushDirectory("first");
	createSubdir(p);

	p.pushDirectory("second");
	createSubdir(p);
}


void DirectoryIteratorsTest::createSubdir(Path& p)
{
	File d(p);
	d.createDirectories();
	FileStream f1(p.toString() + "b");
	FileStream f2(p.toString() + "1");
	FileStream f3(p.toString() + "A");
	FileStream f4(p.toString() + "2");
	FileStream f5(p.toString() + "B");
	FileStream f6(p.toString() + "a");
}


void DirectoryIteratorsTest::tearDown()
{
	try
	{
		File d(path());
		d.remove(true);
	}
	catch (...)
	{
	}
}


Poco::Path DirectoryIteratorsTest::path() const
{
	Path p(Path::current());
	p.pushDirectory("DirectoryIteratorsTest");
	return p;
}


CppUnit::Test* DirectoryIteratorsTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DirectoryIteratorsTest");

	CppUnit_addTest(pSuite, DirectoryIteratorsTest, testDirectoryIterator);
	CppUnit_addTest(pSuite, DirectoryIteratorsTest, testSortedDirectoryIterator);
	CppUnit_addTest(pSuite, DirectoryIteratorsTest, testSimpleRecursiveDirectoryIterator);
	CppUnit_addTest(pSuite, DirectoryIteratorsTest, testSiblingsFirstRecursiveDirectoryIterator);

	return pSuite;
}
