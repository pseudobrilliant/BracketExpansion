set(SOURCE_FILES BracketExpressionMain.cpp BracketExpression.cpp BracketExpression.h)
add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCE_FILES})
add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SOURCE_FILES})
