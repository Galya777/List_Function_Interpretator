#include "UserFunctions.h"
#include "Parser.h"

UserFunctions::UserFunctions(std::string name, int paramsCount, std::string exprToExecute)
{
	this->name = name;
	this->paramsCount = paramsCount;
	this->exprToExecute = exprToExecute;
}

std::string UserFunctions::getName() const
{
	return name;
}

Token UserFunctions::calc() {
    Token t= (Token)Parser::getInstance().execute(exprToExecute, params);
    if (params.size() != paramsCount && name != "list") throw std::invalid_argument("Not enough parameters for " + name);
    if (exprToExecute.empty()) {
        if (name == "eq") {
            t.value=(FuctionsSupported::en(params.elem(0), params.elem(1)));
        }
        if (name == "le") {
            t.value = (FuctionsSupported::le(params.elem(0), params.elem(1)));
        }
        if (name == "nand") {
            t.value = (FuctionsSupported::nand(params.elem(0), params.elem(1)));
        }
        if (name == "length") {
            t.value = (FuctionsSupported::length(params.elem(0)));
        }
        if (name == "head") {
            t.value = (FuctionsSupported::head(params)).value;
        }
        if (name == "tail") {
            ListOfData l = FuctionsSupported::tail(params);
            if (params.elem(0).data == LIST_UNLITERAL) t = params.elem(0);
            t = l.elem(0);
        }
        if (name == "list") {
            if (params.size() == 1) {
                if (params.elem(0).data != REAL_NUM) throw std::invalid_argument("Invalid arguments for list(#0) function, #0 must be a REAL_NUMBER");
                t = FuctionsSupported::list((int)params.elem(0).value.c_str()).elem(0);
            }
            if (params.size() == 2) {
                if (params.elem(0).data != REAL_NUM || params.elem(1).data != REAL_NUM) throw std::invalid_argument("Invalid arguments for list(#0,#1) function");
                t = FuctionsSupported::list((int)params.elem(0).value.c_str(), (int)params.elem(1).value.c_str()).elem(0);
            }
            if (params.size() == 3) {
                if (params.elem(0).data != REAL_NUM || params.elem(1).data != REAL_NUM || params.elem(2).data != REAL_NUM) throw std::invalid_argument("Invalid arguments for list(#0,#1,#2) function");
                t = FuctionsSupported::list((int)params.elem(0).value.c_str(), (int)params.elem(1).value.c_str(), (int)params.elem(2).value.c_str()).elem(0);
            }
            throw std::invalid_argument("Not enough parameters for " + name);
        }
        if (name == "concat") {
            if (params.elem(0).data != LIST_LITERAL || params.elem(0).data == REAL_NUM) throw std::invalid_argument("Invalid arguments for concat function");
            std::list<Token> conc = FuctionsSupported::concat(params.getData(), params.getData());
            if (params.elem(1).data == LIST_UNLITERAL) t = params.elem(1);
            t = conc.front();
        }
        if (name == "read") {
            t.value = (FuctionsSupported::read());
        }
        if (name == "write") {
            t.value = (FuctionsSupported::write(params.elem(0)));
        }
        if (name == "read") {
            t.value = (FuctionsSupported::write(params.elem(0)));
        }
        if (name == "int") {
            t.value = (FuctionsSupported::int_param(params.elem(0)));
        }
        if (name == "add") {
            if (params.elem(0).data != REAL_NUM || params.elem(1).data != REAL_NUM) throw std::invalid_argument("Invalid argument: must be real number in add function");
            t.value = (FuctionsSupported::add(stod(params.elem(0).value), stod(params.elem(1).value)));
        }
        if (name == "sub") {
            if (params.elem(0).data != REAL_NUM || params.elem(1).data != REAL_NUM) throw std::invalid_argument("Invalid argument: must be real number in sub function");
            t.value = (FuctionsSupported::sub(stod(params.elem(0).value), stod(params.elem(1).value)));
        }
        if (name == "mul") {
            if (params.elem(0).data != REAL_NUM || params.elem(1).data != REAL_NUM) throw std::invalid_argument("Invalid argument: must be real number in mul function");
            t.value = (FuctionsSupported::mul(stod(params.elem(0).value), stod(params.elem(1).value)));
        }
        if (name == "div") {
            if (params.elem(0).data != REAL_NUM || params.elem(1).data != REAL_NUM) throw std::invalid_argument("Invalid argument: must be real number in div function");
            t.value = (FuctionsSupported::div(stod(params.elem(0).value), stod(params.elem(1).value)));
        }
        if (name == "mod") {
            if (params.elem(0).data != REAL_NUM || params.elem(1).data != REAL_NUM) throw std::invalid_argument("Invalid argument: must be real number in mod function");
            t.value = (FuctionsSupported::mod(stod(params.elem(0).value), stod(params.elem(1).value)));
        }
        if (name == "sqrt") {
            if (params.elem(0).data != REAL_NUM) throw std::invalid_argument("Invalid argument: must be real number in sqrt function");
            t.value = (FuctionsSupported::sQrT( stod(params.elem(0).value)));
        }
    }
    return t;
}
