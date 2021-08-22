#include "BracketExpression.h"

#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <stdexcept>

using namespace std;

/*Merge a list of string expressions with the current expression list contained within the host BracketExpression object.
Merging is done by attempting an iterative combination of every element in the current expression with the passed in
merge expression. The merge list may contain multiple items from a recursively expanded expression, or it just may be a
 string of one new letter to merge.*/
void BracketExpression::Merge(ExpressionComponents const& mergeExp)
{
    ExpressionComponents results;
    if(!mergeExp.empty())
    {
        //If the current expression is empty but we are merging with a non-empty expression merge by copying the merge list.
        if(currentExp.empty())
        {
            currentExp = mergeExp;
            return;
        }

        //Iterate through the current list of expression components
        for(const auto& currentComponent : currentExp)
        {
            //Iterate through the new list of expression components to merge
            for(const auto& mergeComponent : mergeExp)
            {
                //Create a combination per component in the current expression list for every component in the merge list.
                results.push_back(currentComponent + mergeComponent);
            }
        }
    }
    else
    {
        return;
    }
    
    currentExp = results;
}

//Saving the current list of components into the expanded list as the current expansion has been completed for these components.
void BracketExpression::SaveExpanded()
{
    if(!currentExp.empty())
    {
        std::copy(currentExp.begin(),currentExp.end(), std::back_inserter(expandedExp));
        //Clear the current expression list so we can continue expanding new components.
        currentExp.clear();
    }
}

//Process a closing expression marker within the Bracket syntax
ExpressionComponents BracketExpression::Close()
{
    if(unmatchedChars->empty() || unmatchedChars->back() != EXPCLOSE)
    {
        throw invalid_argument("Invalid input - Close character not expected");
    }
    else
    {
        //Pop the unmatched closing character as it has now been matched and no longer needs to be tracked.
        unmatchedChars->pop_back();
    }

    //Save the current list into the already expanded list as we have completed the current expression expansion.
    SaveExpanded();

    //Return the expanded expression saved up to this point.
    return expandedExp;
}

//Process an open character marker in the bracket expression syntax
void BracketExpression::Open(char*& currentChar)
{
    if(!unmatchedChars->empty() && unmatchedChars->back() == EXPSEPARATOR)
    {
        //Pop any seperator syntax search as we have entered a new expression.
        unmatchedChars->pop_back();
    }

    //We've reached an open marker so we need to search for a matching closing marker as we expand the new expression
    unmatchedChars->push_back(EXPCLOSE);

    //Move the pointer forward one character in the string so the next expansion can start at the beginning of expression.
    currentChar++;

    //Create a new BracketExpression obj with the current pointer to being expanding new expression.
    BracketExpression newExpr(unmatchedChars);

    //Expand and return the new expression.
    ExpressionComponents const& returned = newExpr.RecursiveExpand(currentChar);

    //Merge the returned expression with the current expression to combine components.
    Merge(returned);
}

//Process Alpha characters
void BracketExpression::Alpha(char*& currentChar)
{
    //If the current search was for a separator resolution we can pop that value as an alpha character resolves it.
    if(!unmatchedChars->empty() && unmatchedChars->back() == EXPSEPARATOR)
    {
        unmatchedChars->pop_back();
    }

    //Merge any new letter found with the current expression to combine iteratively
    Merge(vector<string> {std::string(1,*currentChar)});
}

//Process the separating character in the expression syntax
void BracketExpression::Separate()
{
    if(unmatchedChars->empty() || unmatchedChars->back() != '}')
    {
        throw invalid_argument("Invalid input - Separator character not expected");
    }

    //We have reached a separator the next character must be the start of an expression or an alpha character.
    unmatchedChars->push_back(',');

    //Save the current expanded expression as we have reached a separator.
    SaveExpanded();
}


//Recursively expand expressions by processing each character until the end of an expression or the input is reached.
//The current place within the expression is tracked through a currentCHar pointer.
ExpressionComponents BracketExpression::RecursiveExpand(char*& currentChar)
{   
    while(*currentChar != EXPTERM)
    {
        if(*currentChar == EXPOPEN)
        {   
            Open(currentChar);
        }
        else if(*currentChar == EXPCLOSE)
        {
            return Close();
        }
        else if(*currentChar == EXPSEPARATOR)
        {
            Separate();
        }
        else if(isalpha(*currentChar))
        {
            Alpha(currentChar);
        }
        else
        {
            throw invalid_argument("Invalid input - The character does not fit the syntax of a Bracket Expression");
        }
        
        ++currentChar;
    }

    //We've process within the loop and reached the end of input. Time to save the current expression as expanded.
    if(!currentExp.empty())
    {
        SaveExpanded();
    }

    //No component values were ever retrieved ... this likely means none were ever given.
    if(expandedExp.empty())
    {
        throw invalid_argument("Invalid input - Expressions cannot be empty");
    }

    //We reached the end of the input without popping all our search characters, meaning not all characters were resolved.
    if(!unmatchedChars->empty())
    {
        throw invalid_argument("Invalid input - Incomplete expression detected");
    }

    //Return the expanded list of expression components.
    return expandedExp;
}

//Expand a input string using the bracket expression syntax.
string BracketExpression::Expand(const string& inputString)
{
    //Clear any previously run expansions from member variables.
    init();

    string result;

    //Simple check to avoid any complex processing when the string is empty.
    if(inputString.length() == 0)
    {
      return result;
    }

    //Copy the input string so we can traverse without impact on the original string.
    char* tempChar = new char[inputString.length() + 1];
    strcpy(tempChar, inputString.c_str());

    //copy a string ptr as the actual iterator to pass through.
    char* currentChar = tempChar;

    try
    {
        //Attempt to recursively expand the input expression.
        ExpressionComponents strings = RecursiveExpand(currentChar);

        //Create a string representation of the expanded expressions.
        result = ExpressionComponentsToString(strings);
    }
    catch(const std::exception& e)
    {
        result = "";
        //Instructions direct program to not report / print out error messages regarding invalid expressions
    }

    delete[] tempChar;
    return result;
}

//Create a string representation of the expanded expressions.
string BracketExpression::ExpressionComponentsToString(ExpressionComponents components) const
{
    stringstream imploded;
    size_t size = components.size();
    for(int i = 0; i < size; i++)
    {
        imploded << components.at(i);
        if(i != size - 1)
        {
            imploded<<STRSEPARATOR;
        }
    }

    return imploded.str();
}