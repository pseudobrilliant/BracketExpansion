#include <string>
#include <vector>

using namespace std;

#ifndef BRACKET_EXPRESSION_H
#define BRACKET_EXPRESSION_H

typedef vector<string> ExpressionComponents;

class BracketExpression
{
    public:

    BracketExpression()
    {
        root = true;
        unmatchedChars = new vector<char>();
    }
    
    explicit BracketExpression(vector<char>*& unmatched): unmatchedChars(unmatched)
    {
    }
    
    ~BracketExpression()
    {
        if(root)
        {
            delete unmatchedChars;
        }
    }
    
    string Expand(const string& inputString);
    
    private:
    
    ExpressionComponents expandedExp;
    ExpressionComponents currentExp;
    vector<char>* unmatchedChars;
    bool root = false;
    const char EXPOPEN = '{';
    const char EXPCLOSE = '}';
    const char EXPSEPARATOR = ',';
    const char STRSEPARATOR = ' ';
    const char EXPTERM = '\0';

    void init()
    {
        expandedExp.clear();
        currentExp.clear();
        unmatchedChars->clear();
    }

    ExpressionComponents RecursiveExpand(char *& currentChar);
    void Merge(ExpressionComponents const& mergeExp);

    //Processing functions used for each main component type of the expression syntax 
    void Open(char*& currentChar);
    void Alpha(char*& currentChar);
    ExpressionComponents Close();   
    void Separate();
    void SaveExpanded();
    string ExpressionComponentsToString(ExpressionComponents components) const;
    
}; //END BracketExpression

#endif