#pragma once
#include "FuctionsSupported.h"
#include "UserFunctions.h"
#include "Lexer.h"
#include <map>



/*
* This class represents the parser and the idea of it is from the video I mentioned in the main page
*/
class Parser
{

public:

    static Parser& getInstance();
    static Token convertToParam(std::string& str, const ListOfData& data);

    void addCustomFunction(UserFunctions* function);
    Token execute(const std::string& expression, const ListOfData& data);

private:
    std::map<std::string, UserFunctions*> allFunctions;
    Parser();
    Parser(const Parser& other) = default;
    Token getResultFromIf(const std::string& str, int& ind, const ListOfData& data);
};

