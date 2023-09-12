#include "Lexer.h"
#include <iostream>
#include "Parser.h"

void Lexer::enterText(const std::string& text) {
    std::size_t SIZE = text.size();
    std::string name;
    size_t i = 0;
    while (i + 1 < SIZE && !(text[i] == '-' && text[i + 1] == '>')) {
        name += text[i++];
    }
    if (i + 1 >= SIZE) {
        if (text[i] == '>' && text[i - 1] == '-') {
            std::cout << "> Empty declaration of function \n";
        }
        else {
            try {
                std::cout << "> ";
                std::cout<<Parser::getInstance().execute(text, ListOfData()).value;
                std::cout << "\n";
            }
            catch (std::exception& e) {
                std::cout << e.what() << "\n";
            }
        }
    }
    else {
        i += 2;
        int paramsCount = 0;
        int smallBracketsCount = 0, bigBracketsCount = 0;
        std::string exprToExecute;
        while (i < SIZE) {
            if (text[i] == '(') smallBracketsCount++;
            if (text[i] == ')') smallBracketsCount--;
            if (text[i] == '[') bigBracketsCount++;
            if (text[i] == ']') bigBracketsCount--;
            if (text[i - 1] == '#') {
                int x = 0;
                while ('0' <= text[i] && text[i] <= '9') {
                    x = x * 10 + (text[i] - '0');
                    i++;
                }
                if (text[i - 1] == '#') {
                    std::cout << "Invalid declaration of function \n";
                    break;
                }
                if (x + 1 - paramsCount > 2) {
                    std::cout << "Invalid declaration of parameters \n";
                    break;
                }
                paramsCount = std::max(paramsCount, x + 1);
                i--;
            }
            exprToExecute += text[i];
            i++;
        }
        if (!smallBracketsCount && !bigBracketsCount) {
            Parser::getInstance().addCustomFunction(new UserFunctions(name, paramsCount, exprToExecute));
        }
    }
}
