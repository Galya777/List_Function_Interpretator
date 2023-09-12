#include "Parser.h"
#include <iostream>
#include <stack>

Parser::Parser() {

    allFunctions.emplace("eq", new UserFunctions("eq", 2, ""));
    allFunctions.emplace("le", new UserFunctions("le", 2, ""));
    allFunctions.emplace("nand", new UserFunctions("nand", 2, ""));
    allFunctions.emplace("length", new UserFunctions("length", 1, ""));
    allFunctions.emplace("head", new UserFunctions("head", 1, ""));
    allFunctions.emplace("tail", new UserFunctions("tail", 1, ""));
    allFunctions.emplace("list", new UserFunctions("list", -1, ""));
    allFunctions.emplace("concat", new UserFunctions("concat", 2, ""));
    allFunctions.emplace("if", new UserFunctions("if", 3, ""));
    allFunctions.emplace("read", new UserFunctions("read", 0, ""));
    allFunctions.emplace("write", new UserFunctions("write", 1, ""));
    allFunctions.emplace("int", new UserFunctions("int", 1, ""));

    allFunctions.emplace("add", new UserFunctions("add", 2, ""));
    allFunctions.emplace("sub", new UserFunctions("sub", 2, ""));
    allFunctions.emplace("mul", new UserFunctions("mul", 2, ""));
    allFunctions.emplace("div", new UserFunctions("div", 2, ""));
    allFunctions.emplace("mod", new UserFunctions("mod", 2, ""));
    allFunctions.emplace("sqrt", new UserFunctions("sqrt", 1, ""));

}

Token Parser::getResultFromIf(const std::string& str, int& ind, const ListOfData& params) {
    std::string fst, snd, thr;
    int smallBracketsCount = 0, bigBracketsCount = 0;
    while (!(str[ind] == ',' && !smallBracketsCount && !bigBracketsCount)) {
        if (str[ind] == '(') smallBracketsCount++;
        if (str[ind] == ')') smallBracketsCount--;
        if (str[ind] == '[') bigBracketsCount++;
        if (str[ind] == ']') bigBracketsCount--;
        fst += str[ind++];
    }
    ind++;
    smallBracketsCount = 0, bigBracketsCount = 0;
    while (!(str[ind] == ',' && !smallBracketsCount && !bigBracketsCount)) {
        if (str[ind] == '(') smallBracketsCount++;
        if (str[ind] == ')') smallBracketsCount--;
        if (str[ind] == '[') bigBracketsCount++;
        if (str[ind] == ']') bigBracketsCount--;
        snd += str[ind++];
    }
    ind++;
    smallBracketsCount = 0, bigBracketsCount = 0;
    while (!(str[ind] == ')' && !smallBracketsCount && !bigBracketsCount)) {
        if (str[ind] == '(') smallBracketsCount++;
        if (str[ind] == ')') smallBracketsCount--;
        if (str[ind] == '[') bigBracketsCount++;
        if (str[ind] == ']') bigBracketsCount--;
        thr += str[ind++];
    }
    ;
    Token t1, t2;
    t1.value = fst;
    t2.value = snd;

    return FuctionsSupported::if_operator(thr == "true" ? true : false, t1, t2);
}

Token Parser::execute(const std::string& expression, const ListOfData& params) {

    std::string str;
    std::stack<UserFunctions*> functionNames;
    int bracketsCount = 0;
    bool unlimited = false;
    Token ans;
    for (int ind = 0; ind < expression.size(); ind++) {
        char i = expression[ind];
        if (str == "if") {
            ind++;
            ans = getResultFromIf(expression, ind, params);
            if (!functionNames.empty()) functionNames.top()->params.addData(ans);
            str = "";

        }
        else if (i == '(' && !bracketsCount) {
            if (allFunctions.find(str) == allFunctions.end()) throw std::invalid_argument("There is no function with name= " + str);
            functionNames.emplace(new UserFunctions(*allFunctions.at(str)));
            str = "";

        }
        else if (i == ',' && !bracketsCount) {
            ans = convertToParam(str, params);
            if (!str.empty()) functionNames.top()->params.addData(ans);
            str = "";
        }
        else if (i == ')' && !bracketsCount) {
            UserFunctions* cF = functionNames.top();
            functionNames.pop();
            ans = convertToParam(str, params);
            if (!str.empty()) cF->params.addData(ans);
            ans = (cF->calc());
            if (ans.data == LIST_UNLITERAL) unlimited = true;
            if (!functionNames.empty()) functionNames.top()->params.addData(ans);
            str = "";
            delete cF;
        }
        else if (i == '[') {
            bracketsCount++;
            str += i;
        }
        else if (i == ']') {
            bracketsCount--;
            str += i;
        }
        else if (bracketsCount > 0 || (bracketsCount == 0 && i != ' ' && i != '\n' && i != '\t')) {
            str += i;
        }
    }

    if (!str.empty()) ans = convertToParam(str, params);
    if (unlimited && ans.data == LIST_LITERAL) ans.data= LIST_UNLITERAL;
    return ans;
}

Token Parser::convertToParam(std::string& str, const ListOfData& params) {
    if (('0' <= str[0] && str[0] <= '9') || str[0] == '-') {
        Token t;
        t.value = std::stod(str);
        return t;
    }
    else if (str[0] == '[') {
        double x = 0;
        std::list<Token> l;
        std::string number;
        for (size_t i = 1; i < str.size(); i++) {
            if (str[i] == '-' || ('0' <= str[i] && str[i] <= '9')) {
                number += str[i];
            }
            else if (str[i] == ' ') {
                x = std::stod(number);
                number = "";
                Token t = {REAL_NUM, x};
                l.emplace_back(t);
            }
            else if (str[i] == '[') {
                int bigBracketsCount = 1;
                std::string expr = "[";
                i++;
                while (bigBracketsCount != 0) {
                    if (str[i] == '[') bigBracketsCount++;
                    if (str[i] == ']') bigBracketsCount--;
                    expr += str[i++];
                }
                l.emplace_back(convertToParam(expr, params));
            }
            else if (str[i] != ']') {
                int smallBracketsCount = 0, bigBracketsCount = 0;
                std::string expr;
                while (!(str[i] == ' ' && !smallBracketsCount && !bigBracketsCount) && i + 1 < str.size()) {
                    if (str[i] == '(') smallBracketsCount++;
                    if (str[i] == ')') smallBracketsCount--;
                    if (str[i] == '[') bigBracketsCount++;
                    if (str[i] == ']') bigBracketsCount--;
                    expr += str[i++];
                }
                l.emplace_back(Parser::getInstance().execute(expr, params));
            }

        }
        if (!number.empty()) {
            x = std::stod(number);
            number = "";
            Token t = {REAL_NUM, x};
            l.emplace_back(t);
         }
        return l.front(); 
        }
    else {
        int index = 0;
        int i = 1;
        while ('0' <= str[i] && str[i] <= '9')
            index = index * 10 + (str[i++] - '0');
        return params.elem(index);
    }
    return Token();
}

Parser& Parser::getInstance() {
    static Parser instance;
    return instance;
}

void Parser::addCustomFunction(UserFunctions* function) {
    if (allFunctions.find(function->getName()) != allFunctions.end()) {
        std::cout << "> 1 \n";
        UserFunctions* curr = allFunctions.at(function->getName());
        allFunctions.erase(function->getName());
        delete curr;
    }
    else {
        std::cout << "> 0 \n";
    }
    allFunctions.emplace(function->getName(), function);
}
