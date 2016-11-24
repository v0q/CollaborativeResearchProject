#include "ExpressionEvaluator.hpp"

/*
 * Please do not look at these!
 */
namespace hsitho {
	namespace Expressions {
		void parseExpression(std::string &_expression) {
			size_t pos;
			while((pos = _expression.find("*+")) != std::string::npos) {
				_expression.replace(pos, 2, "*");
			}
			while((pos = _expression.find("*-")) != std::string::npos) {
				_expression.replace(pos, 2, "*");
				_expression.insert(0, "-");
			}
			while((pos = _expression.find("--")) != std::string::npos) {
				_expression.replace(pos, 2, "+");
			}
			while((pos = _expression.find("++")) != std::string::npos) {
				_expression.replace(pos, 2, "+");
			}
			while((pos = _expression.find("+-")) != std::string::npos) {
				_expression.replace(pos, 2, "-");
			}
			while((pos = _expression.find("-+")) != std::string::npos) {
				_expression.replace(pos, 2, "-");
			}
		}

		std::string addSpaces(const std::string &_expression) {
			std::string o = _expression;
			std::ostringstream newOutput;
			bool parsed = false;
			do {
				size_t plus = o.find("+");
				size_t minus = o.find("-");
				size_t multiply = o.find("*");
				size_t divide = o.find("/");
				if(plus == std::string::npos && minus == std::string::npos && multiply == std::string::npos && divide == std::string::npos) {
					parsed = true;
				}	else if(plus < minus && plus < multiply && plus < divide) {
					newOutput << o.substr(0, plus) << " + ";
					o.erase(0, plus + 1);
				} else if(minus < plus && minus < multiply && minus < divide) {
					std::string d = newOutput.str();
					if((newOutput.str().find("* ") == newOutput.str().length() - 2 || newOutput.str().find("/ ") == newOutput.str().length() - 2) && minus == 0) {
						newOutput << o.substr(0, minus) << "-";
					} else {
						newOutput << o.substr(0, minus) << " - ";
					}
					o.erase(0, minus + 1);
				} else if(multiply < plus && multiply < minus && multiply < divide) {
					newOutput << o.substr(0, multiply) <<  " * ";
					o.erase(0, multiply + 1);
				} else if(divide < plus && divide < multiply && divide < minus) {
					newOutput << o.substr(0, divide) << " / ";
					o.erase(0, divide + 1);
				}
			} while(!parsed);
			newOutput << o;

			return newOutput.str();
		}

		std::string evaluate(const std::string &_expression, const std::string &_prev)
		{
			// Generate postfix notation for the expression
			std::string exp = _expression;
			std::vector<std::string> expElements;
			size_t poss = 0;
			while((poss = exp.find(" ")) != std::string::npos) {
				if(exp.substr(0, poss) != "") {
					expElements.push_back(exp.substr(0, poss));
				}
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
				} else if(i == "+" || i == "-") {
					if(stack.size()) {
						std::string op = stack.back();
						if(op == "+" || op == "-" || op == "*" || op == "/") {
							outputQueue.push_back(op);
							stack.pop_back();
						}
					}
					stack.push_back(i);
				} else if(i == "(") {
					stack.push_back(i);
				} else if(i == ")") {
					while(stack.back() != "(" && stack.size()) {
						std::string op = stack.back();while((poss = exp.find(" ")) != std::string::npos) {
							expElements.push_back(exp.substr(0, poss));
							exp.erase(0, poss + 1);
						}
						outputQueue.push_back(op);
						stack.pop_back();
					}
					if(stack.size()) stack.pop_back();
				} else {
					outputQueue.push_back(i);
				}
			}
			while(!stack.empty()) {
				outputQueue.push_back(stack.back());
				stack.pop_back();
			}

			// Evaluate the postfix expression
			std::string s = evaluatePostFix(outputQueue);
			if(s.find("+") == 0)
				s.erase(0, 1);

			s = addSpaces(s);
			std::string finalOutput;
			if(s != _prev) {
				finalOutput = evaluate(s, s);
			} else {
				finalOutput = s;
			}
			std::string::iterator end_pos = std::remove(finalOutput.begin(), finalOutput.end(), ' ');
			finalOutput.erase(end_pos, finalOutput.end());

			return finalOutput;
		}

		std::string evaluatePostFix(std::vector<std::string> outputQueue)
		{
			std::vector<std::string> stack;

			for(auto &o : outputQueue)
			{
				try {
					size_t pos;
					if((pos = o.find("sin(")) != std::string::npos) {
						unsigned int startPos = pos+4;
						std::string sineval = boost::lexical_cast<std::string>(std::sin(boost::lexical_cast<float>(o.substr(startPos, o.find(")", pos) - startPos))));
						stack.push_back(sineval);
						continue;
					} else if((pos = o.find("cos(")) != std::string::npos) {
						unsigned int startPos = pos+4;
						std::string cosineval = boost::lexical_cast<std::string>(std::cos(boost::lexical_cast<float>(o.substr(startPos, o.find(")", pos) - startPos))));
						stack.push_back(cosineval);
						continue;
					} else {
						boost::lexical_cast<float>(o);
						stack.push_back(o);
						continue;
					}
				} catch(const boost::bad_lexical_cast &) {}

				if((o == "*" || o == "/" || o == "+" || o == "-") && stack.size()) {
					std::string vals[2];
					vals[0] = stack.back();
					parseExpression(vals[0]);
					stack.pop_back();
					if(stack.size()) {
						vals[1] = stack.back();
						parseExpression(vals[1]);
						stack.pop_back();
					}
					try
					{
						float result;
						float v1 = boost::lexical_cast<float>(vals[0]);
						float v2 = boost::lexical_cast<float>(vals[1]);
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
							bool parsed = false;
							if(vals[0] != "0.0" && vals[0] != "0" && vals[1] != "0.0" && vals[1] != "0") {
								if(vals[0] == "1.0" || vals[0] == "1") {
									stack.push_back(vals[1]);
								} else if(vals[1] == "1.0" || vals[1] == "1") {
									stack.push_back(vals[0]);
								} else {
									for(unsigned int i = 0; i < 2; ++i) {
										unsigned int otherValInd = (i+1)%2;
										std::string curValCpy(vals[i]);
										size_t plus;
										size_t minus;
										while(!parsed) {
											bool parsed2 = false;
											std::string otherValCpy(vals[otherValInd]);
											plus = curValCpy.find("+", 1);
											minus = curValCpy.find("-", 1);
											if(plus != std::string::npos || minus != std::string::npos) {
												size_t plus2;
												size_t minus2;
												while(!parsed2) {
													plus2 = otherValCpy.find("+", 1);
													minus2 = otherValCpy.find("-", 1);
													if(plus2 != std::string::npos || minus2 != std::string::npos) {
														std::string val = otherValCpy.substr(0, std::min(plus2, minus2)) + "*" + curValCpy.substr(0, std::min(plus, minus));
														parseExpression(val);
														if(val.find("+") != 0 && val.find("-") != 0 && val.find("*") != 0  && val.find("/") != 0)
															stack.push_back("+" + val);
														else
															stack.push_back(val);
														otherValCpy.erase(0, std::min(plus2, minus2));
													} else {
														std::string val = otherValCpy.substr(0, std::min(plus2, minus2)) + "*" + curValCpy.substr(0, std::min(plus, minus));
														parseExpression(val);
														if(val.find("+") != 0 && val.find("-") != 0 && val.find("*") != 0  && val.find("/") != 0)
															stack.push_back("+" + val);
														else
															stack.push_back(val);
														curValCpy.erase(0, std::min(plus, minus));
														parsed2 = true;
													}
												}
											} else {
												parsed2 = false;
												std::string otherValCpy(vals[otherValInd]);
												size_t plus2;
												size_t minus2;
												while(!parsed2) {
													plus2 = otherValCpy.find("+", 1);
													minus2 = otherValCpy.find("-", 1);
													if(plus2 != std::string::npos || minus2 != std::string::npos) {
														std::string val = otherValCpy.substr(0, std::min(plus2, minus2)) + "*" + curValCpy.substr(0, std::min(plus, minus));
														parseExpression(val);
														if(val.find("+") != 0 && val.find("-") != 0 && val.find("*") != 0  && val.find("/") != 0)
															stack.push_back("+" + val);
														else
															stack.push_back(val);
														otherValCpy.erase(0, std::min(plus2, minus2));
													} else {
														std::string val = otherValCpy.substr(0, std::min(plus2, minus2)) + "*" + curValCpy.substr(0, std::min(plus, minus));
														parseExpression(val);
														if(val.find("+") != 0 && val.find("-") != 0 && val.find("*") != 0  && val.find("/") != 0)
															stack.push_back("+" + val);
														else
															stack.push_back(val);
														curValCpy.erase(0, std::min(plus, minus));
														parsed2 = true;
													}
												}
												parsed = true;
											}
										}
									}
								}
							}
						} else if(o == "/") {
							if(vals[1] != "" && vals[0] != "0.0" && vals[1] != "0.0" && vals[0] != "0" && vals[1] != "0") {
								stack.push_back(std::string(vals[1] + "/" + vals[0]));
							}
						} else if(o == "+") {
							if(vals[1] != "0" && vals[1] != "0.0" && vals[1] != "") {
								if(vals[0] != "0" && vals[0] != "0.0" && vals[0] != "")
									stack.push_back(std::string(vals[1] + "+" + vals[0]));
								else
									stack.push_back(std::string(vals[1]));
							} else if(vals[0] != "")
								stack.push_back(std::string(vals[0]));
						} else if(o == "-") {
							if(vals[1] != "" && vals[1] != "0" && vals[1] != "0.0")
								stack.push_back(std::string(vals[1] + "-" + vals[0]));
							else if(vals[0] != "0.0" && vals[0] != "")
								stack.push_back(std::string("-" + vals[0]));
						}
					}
				} else {
					stack.push_back(o);
				}
			}

			std::ostringstream output;
			for(auto &s : stack)
			{
				output << s;
			}
			std::string final = output.str();
			parseExpression(final);
			return final;
		}
	}
}
/*
 * Please do not look at these!
			std::cout << "\n";
 */
