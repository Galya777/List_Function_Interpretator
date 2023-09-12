#include "FuctionsSupported.h"
#include <iostream>

double FuctionsSupported::add(double first, double second)
{
	return first+second;
}

double FuctionsSupported::sub(double first, double second)
{
	return first-second;
}

double FuctionsSupported::mul(double first, double second)
{
	return first*second;
}

double FuctionsSupported::div(double first, double second)
{
	if (second == 0) throw "Impossible to devide by 0!";
	return first/second;
}

double FuctionsSupported::sQrT(double first)
{
	return sqrt(first);
}

int FuctionsSupported::mod(int first, int second)
{
	return first%second;
}

bool FuctionsSupported::en(const Token& first, const Token& second)
{
	if (first.data == UNKNOWN || second.data == UNKNOWN) throw "Parameters are unknown!";
	return first.value==second.value;
}

bool FuctionsSupported::le(const Token& first, const Token& second)
{
	if (first.data == UNKNOWN || second.data == UNKNOWN) throw "Parameters are unknown!";
	return first.value<second.value;
}

bool FuctionsSupported::nand(const Token& first, const Token& second)
{
	if (first.data == UNKNOWN || second.data == UNKNOWN) throw "Parameters are unknown!";
	/// <summary>
	/// values are casted to chars to be possible usage of operator ! without redefinig it
	/// </summary>
	/// <param name="first"></param>
	/// <param name="second"></param>
	/// <returns></returns>
	return !first.value.c_str() || !second.value.c_str();
}

int FuctionsSupported::length(const Token& first)
{
	if (first.data == REAL_NUM) return -1;
	ListOfData d;
	d = first;
	return d.size();
}

Token FuctionsSupported::head(const ListOfData& first)
{
	return first.elem(0);
}

std::list<Token> FuctionsSupported::tail(ListOfData& first)
{
	return first.withoutFirst();
}

ListOfData FuctionsSupported::list(int beggining, int step)
{
	std::list<Token> newlist;
	Token t;
	t.data = REAL_NUM;
	t.value = beggining;
	newlist.push_back(t);
	for (int i = 1; i < 10; i++) {
		Token t1;
		t1.data = REAL_NUM;
		beggining += step;
		t1.value = beggining;
		newlist.push_back(t1);
	}
	return ListOfData(newlist);
}

ListOfData FuctionsSupported::list(int beggining, int step, int count)
{
	std::list<Token> newlist;
	Token t;
	t.data = REAL_NUM;
	t.value = beggining;
	newlist.push_back(t);
	for (int i = 1; i < count; i++) {
		Token t1;
		t1.data = REAL_NUM;
		beggining += step;
		t1.value = beggining;
		newlist.push_back(t1);
	}
	return ListOfData(newlist);
}

std::list<Token> FuctionsSupported::concat(std::list<Token>& first, std::list<Token>& second)
{
	std::list<Token>& concat = first;
    concat.splice(first.end(), second);
	return concat;
}

Token FuctionsSupported::if_operator(bool value, const Token& first, const Token& second)
{
	return value?first:second;
}

int FuctionsSupported::read()
{
	double x;
	std::cout << "read(): ";
	std::cin >> x;
	std::string empty;
	std::getline(std::cin, empty);
	return x;
}

int FuctionsSupported::write(const Token& first)
{
	std::cout << first.value;
	return 0;
}

int FuctionsSupported::int_param(const Token& first)
{
	if (first.data != REAL_NUM) throw "Cannot do this. Must be a number!";
	return (int)first.value.c_str();
}
