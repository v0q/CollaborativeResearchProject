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
    template<typename T>
    T clamp(const T _val, const T _v1, const T _v2)
    {
      if(_val < _v1)
        return _v1;
      else if(_val > _v2)
        return _v2;
      return _val;
    }
  }
}
