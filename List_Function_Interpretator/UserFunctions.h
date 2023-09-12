#pragma once
#include <string>
#include "Token.h"
#include "FuctionsSupported.h"
//#include "Parser.h"
#include <stdexcept>
class UserFunctions
{
public:
	UserFunctions(std::string name, int paramsCount, std::string exprToExecute);
	UserFunctions(const UserFunctions& other)=default;
	std::string getName() const;
	int getParameterCount() const { return paramsCount; }
	std::string getExpressionToExecute() const { return exprToExecute; }

	Token calc();
	ListOfData params;
private:
	
	std::string name;
	int paramsCount;
	std::string exprToExecute;
};

