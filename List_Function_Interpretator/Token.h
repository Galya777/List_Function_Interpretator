#pragma once
#include <string>
#include <list>

enum DataType {
	UNKNOWN=-1,
    END=0,
	REAL_NUM,
	LIST_LITERAL,
	LIST_UNLITERAL,
	
};

 struct Token
{
	DataType data;
	double num=0;
	std::string value;
};

