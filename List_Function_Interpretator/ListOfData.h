#pragma once
#include <list>
#include "Token.h"
class ListOfData
{
public:
	ListOfData(Token& newData);
	ListOfData(std::list<Token> newlist);
	ListOfData();

	ListOfData& operator=(const Token& token);
	int size() const;
	void addData(Token& tok);

	Token elem(int pos) const;
	const std::list<Token> withoutFirst();
   std::list<Token>& getData();
private:
	std::list<Token> data;
};

