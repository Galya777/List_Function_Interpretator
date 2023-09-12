#include "ListOfData.h"

ListOfData::ListOfData(Token& newData)
{
    data.push_back(newData);
}

ListOfData::ListOfData(std::list<Token> newlist)
{
    data = newlist;
}

ListOfData::ListOfData()
{
    data=std::list<Token>();
}

ListOfData& ListOfData::operator=(const Token& token)
{
    if (token.data == LIST_LITERAL || token.data == LIST_UNLITERAL)
        *this = token;
    else throw "It must be a list!";
    // TODO: insert return statement here
    return *this;
}

int ListOfData::size() const
{
    return data.size();
}

void ListOfData::addData(Token& tok)
{
    data.push_back(tok);
}

Token ListOfData::elem(int pos) const
{
    auto el = data.begin();

    std::advance(el, pos);
    return *el;
}

const std::list<Token> ListOfData::withoutFirst() 
{
    data.pop_front();
    return data;
}

std::list<Token>& ListOfData::getData()
{
    return data;
}
