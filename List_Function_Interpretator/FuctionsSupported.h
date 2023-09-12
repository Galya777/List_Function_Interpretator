#pragma once
#include "ListOfData.h"
/*
* This class represents functions supported by our functional language
*/
#include <list>
class FuctionsSupported
{
public:
	/// <summary>
	/// Main functions
	/// </summary>
	/// <param name="first"></param>
	/// <param name="second"></param>
	/// <returns></returns>
	static bool en(const Token& first, const Token& second);
	static bool le(const Token& first, const Token& second);
	static bool nand(const Token& first, const Token& second);
	static int length(const Token& first);
	static Token head(const ListOfData& first);
	static std::list<Token> tail(ListOfData& first);
/// <summary>
/// Next to functions are using recursion to return infinite list 
/// </summary>
	static ListOfData list(int beggining, int step = 1);
	static ListOfData list(int beggining, int step, int count);
	static std::list<Token> concat(std::list<Token> &first, std::list<Token> &second);
	static Token if_operator(bool value, const Token& first, const Token& second);

	static int read();
	static int write(const Token& first);

	static int int_param(const Token& first);


	///Math functions only for numbers
	///If the value is other than number, there is an exception
	
	static double add(double first, double second);
	static double sub(double first, double second);
	static double mul(double first, double second);
	static double div(double first, double second);
	static int mod(int first, int second);
	static double sQrT(double first);



};

