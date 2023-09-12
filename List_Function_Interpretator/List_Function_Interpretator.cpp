#include <iostream>
#include <fstream>
#include "Parser.h"
/// <summary>
/// This is the main class of our interactive program which interpretates the fictional programming 
/// language ListFunc. 
/// 
/// Sourses of information:
///  https://www.youtube.com/watch?v=LCslqgM48D4 - with this video I made the basics of this interpretator and
/// made a design of the structure of this program
/// 
/// </summary>
/// <returns></returns>
int main(int argc, const char* argv[])
{
    std::cout << "Enter a line:\n";
    std::string line;
    for (int i = 1; i < argc; i++) {
        std::fstream fin(argv[0]);     
        while (!fin.eof()) {
            std::getline(fin, line);
            Lexer::enterText(line);
        }
    }
    while (line !="exit") {
        std::getline(std::cin, line);
        std::cout << "Curr line is: " << line << "\n";
        Lexer::enterText(line);
    }

}
