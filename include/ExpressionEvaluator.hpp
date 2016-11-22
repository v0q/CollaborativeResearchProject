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
		std::string evaluate(const std::string &_expression, const std::string &_prev = "");
		std::string reorganiseExpression(const std::string &_expression, const std::string &_prev = "");
		std::vector<std::string> evaluatePostFix(std::vector<std::string> outputQueue);
	}
}
/*
 * Please do not look at these!
 */
