#pragma once

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>

/*
 * Please do not look at these!
 */
namespace hsitho {
	namespace Expressions
	{
		void parseExpression(std::string &_expression);
		std::string addSpaces(const std::string &_expression);
		std::string evaluate(const std::string &_expression, const std::string &_prev = "");
		std::string evaluatePostFix(std::vector<std::string> outputQueue);
	}
}
/*
 * Please do not look at these!
 */
