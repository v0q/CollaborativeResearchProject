#include "ExpressionEvaluator.hpp"

/*
 * Please do not look at these!
 */
namespace hsitho {
	namespace Expressions {
		std::string evaluate(const std::string &_expression)
		{
			// Generate postfix notation for the expression
			std::string exp = _expression;
			std::vector<std::string> expElements;
			size_t poss = 0;
			while((poss = exp.find(" ")) != std::string::npos) {
					expElements.push_back(exp.substr(0, poss));
					exp.erase(0, poss + 1);
			}
			expElements.push_back(exp.substr(0, poss));
			exp.erase(0, poss + 1);

			std::vector<std::string> outputQueue, stack;
			for(auto &i : expElements)
			{
				try {
					boost::lexical_cast<float>(i);
					outputQueue.push_back(i);
					continue;
				} catch(const boost::bad_lexical_cast &) {}
				if(i == "*" || i == "/") {
					if(stack.size()) {
						std::string op = stack.back();
						if(op == "*" || op == "/") {
							outputQueue.push_back(op);
							stack.pop_back();
						}
					}
					stack.push_back(i);
				} else if( i == "+" || i == "-") {
					if(stack.size()) {
						std::string op = stack.back();
						outputQueue.push_back(op);
						stack.pop_back();
					}
					stack.push_back(i);
				} else {
					outputQueue.push_back(i);
				}
			}
			while(!stack.empty()) {
				outputQueue.push_back(stack.back());
				stack.pop_back();
			}

			// Evaluate the postfix expression
			stack = evaluatePostFix(outputQueue);

			std::ostringstream output;
			for(auto &s : stack)
			{
				output << s;
			}
			return reorganiseExpression(output.str());
		}

		std::string reorganiseExpression(const std::string &_expression)
		{
			std::string exp = _expression;
			std::vector<std::string> expElements;
			size_t poss = 0;
			while((poss = exp.find(" ")) != std::string::npos) {
					expElements.push_back(exp.substr(0, poss));
					exp.erase(0, poss + 1);
			}
			expElements.push_back(exp.substr(0, poss));
			exp.erase(0, poss + 1);

			std::vector<std::string> outputQueue, unknowns, uoperands, stack;
			for(auto &i : expElements)
			{
				try {
					boost::lexical_cast<float>(i);
					outputQueue.push_back(i);
					continue;
				} catch(const boost::bad_lexical_cast &) {}
				if(i == "*" || i == "/") {
					if(stack.size()) {
						std::string op = stack.back();
						if(op == "*" || op == "/") {
							outputQueue.push_back(op);
							stack.pop_back();
						}
					}
					stack.push_back(i);
				} else if( i == "+" || i == "-") {
					if(stack.size()) {
						std::string op = stack.back();
						outputQueue.push_back(op);
						stack.pop_back();
					}
					stack.push_back(i);
				} else {
					if(stack.size()) {
						uoperands.push_back(stack.back());
						stack.pop_back();
					}
					unknowns.push_back(i);
				}
			}

			while(!stack.empty()) {
				outputQueue.push_back(stack.back());
				stack.pop_back();
			}

			stack = evaluatePostFix(outputQueue);

			std::ostringstream output;
			for(auto &s : stack) {
				output << s;
			}
			for(unsigned int i = 0; i < unknowns.size(); ++i)
			{
				if(uoperands.size() != unknowns.size() && !i)
					output << unknowns[i];
				else
					output << uoperands[i] << unknowns[i];
			}
			return output.str();
		}

		std::vector<std::string> evaluatePostFix(std::vector<std::string> outputQueue)
		{
			std::vector<std::string> stack;
			for(auto &o : outputQueue)
			{
				try {
					boost::lexical_cast<float>(o);
					stack.push_back(o);
					continue;
				} catch(const boost::bad_lexical_cast &) {}

				if(o == "*" || o == "/" || o == "+" || o == "-") {
					std::string val1 = stack.back();
					stack.pop_back();
					std::string val2;
					if(stack.size()) {
						val2 = stack.back();
						stack.pop_back();
					}
					try
					{
						float result;
						float v1 = boost::lexical_cast<float>(val1);
						float v2 = boost::lexical_cast<float>(val2);
						if(o == "*") {
							result = v2 * v1;
						} else if(o == "/") {
							result = v2 / v1;
						} else if(o == "+") {
							result = v2 + v1;
						} else if(o == "-") {
							result = v2 - v1;
						}
						stack.push_back(boost::lexical_cast<std::string>(result));
					} catch(const boost::bad_lexical_cast &) {
						if(o == "*") {
							if(val2 != "" && val1 != "0.0" && val2 != "0.0" && val1 != "0" && val2 != "0") {
								stack.push_back(std::string(val2 + "*" + val1));
							}
						} else if(o == "/") {
							if(val2 != "" && val1 != "0.0" && val2 != "0.0" && val1 != "0" && val2 != "0") {
								stack.push_back(std::string(val2 + "/" + val1));
							}
						} else if(o == "+") {
							if(val2 != "") {
								stack.push_back(std::string(val2 + "+" + val1));
							}
							else if(val1 != "0.0")
								stack.push_back(std::string(val1));
						} else if(o == "-") {
							if(val2 != "")
								stack.push_back(std::string(val2 + " - " + val1));
							else if(val1 != "0.0")
								stack.push_back(std::string("-" + val1));
						}
					}
				} else {
					stack.push_back(o);
				}
			}

			return stack;
		}
	}
}
/*
 * Please do not look at these!
 */
