#pragma once
#include <unordered_set>
#include <string>
#include "Token.h"
class Lexer
{
public:
    Lexer() = default;

    ///add new text for executing
   static void enterText(const std::string& text);

  
};

