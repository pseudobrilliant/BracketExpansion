#include "BracketExpression.h"
#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[])
{
    std::string input;
    std::getline(cin,input);

    BracketExpression bracketExpression;
    string result = bracketExpression.Expand(input);

    if(!result.empty())
    {
        cout<<result<<"\n";
    }
}