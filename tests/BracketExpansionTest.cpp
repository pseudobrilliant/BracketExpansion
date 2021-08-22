#include "gtest/gtest.h"
#include "BracketExpression.h"

TEST(BracketExpressionTest, ValidExpandTests)
{
    BracketExpression bracketExp;
    EXPECT_EQ(bracketExp.Expand("{A,B,C}"),"A B C");
    EXPECT_EQ(bracketExp.Expand("AB{C,D}"), "ABC ABD");
    EXPECT_EQ(bracketExp.Expand("{C,D}AB"), "CAB DAB");
    EXPECT_EQ(bracketExp.Expand("{A,B}{C,D}"), "AC AD BC BD");
    EXPECT_EQ(bracketExp.Expand("{{A,B},{C,D}}"), "A B C D");
    EXPECT_EQ(bracketExp.Expand("{A,B{C,D}}"), "A BC BD");
    EXPECT_EQ(bracketExp.Expand("{ABC}"),"ABC");
    EXPECT_EQ(bracketExp.Expand("AB{C,D}"), "ABC ABD");
    EXPECT_EQ(bracketExp.Expand("{A}{B}{C,D}"), "ABC ABD");
    EXPECT_EQ(bracketExp.Expand("{ABC}"),"ABC");
}

TEST(BracketExpressionTest, ValidNestedExpandTests)
{
    BracketExpression bracketExp;
    EXPECT_EQ(bracketExp.Expand("{{A},{B}}"),"A B");
    EXPECT_EQ(bracketExp.Expand("{A,B,C}{A,B{{A}}}"),"AA ABA BA BBA CA CBA");
    EXPECT_EQ(bracketExp.Expand("D{A,B}{A,B{{C}}}"),"DAA DABC DBA DBBC");
    EXPECT_EQ(bracketExp.Expand("{A,B}{{C,D}EF}"),"ACEF ADEF BCEF BDEF");
    EXPECT_EQ(bracketExp.Expand("{A,B}{{C,D}EF,G}"),"ACEF ADEF AG BCEF BDEF BG");
}

TEST(BracketExpressionTest, InvalidExpandTests)
{
    BracketExpression bracketExp;
    EXPECT_EQ(bracketExp.Expand("}ABC"),"");
    EXPECT_EQ(bracketExp.Expand("}{"),"");
    EXPECT_EQ(bracketExp.Expand("{}"),"");
    EXPECT_EQ(bracketExp.Expand("A,B,C"),"");
    EXPECT_EQ(bracketExp.Expand("{A{B,C}"),"");
    EXPECT_EQ(bracketExp.Expand("{A,B},{C,D}"), "");
    EXPECT_EQ(bracketExp.Expand("{A,"),"");
    EXPECT_EQ(bracketExp.Expand("A{?}"),"");
    EXPECT_EQ(bracketExp.Expand(""),"");

}