#include "ExpressionEvaluator.hpp"

/*
 * Please do not look at these!
 */
namespace hsitho {
	namespace Expressions {
		std::string evaluate(const std::string &_expression, const std::string &_prev)
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
			stack = evaluatePostFix(outputQueue);

			std::ostringstream output;
			for(auto &s : stack)
			{
				output << s;
			}

			return reorganiseExpression(output.str(), _prev);
		}

		std::string reorganiseExpression(const std::string &_expression, const std::string &_prev)
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
						if(op == "+" || op == "-" || op == "*" || op == "/") {
							outputQueue.push_back(op);
							stack.pop_back();
						}
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
			std::string o = output.str();
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
					newOutput << o.substr(0, minus) << " - ";
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
			std::string finalOutput;
			if(newOutput.str() != _prev) {
				finalOutput = evaluate(newOutput.str(), newOutput.str());
			} else {
				finalOutput = newOutput.str();
			}
			return finalOutput;
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

				if((o == "*" || o == "/" || o == "+" || o == "-") && stack.size()) {
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
							if(val2 != "" && val1 != "" && val1 != "0.0" && val2 != "0.0" && val1 != "0" && val2 != "0") {
								if(val1.find("+") != std::string::npos || val1.find("-") != std::string::npos) {
									bool parsed = false;
									size_t plus;
									size_t minus;
									do {
										bool definingSymbol = false;
										plus = val1.find("+");
										minus = val1.find("-");
										if(plus == std::string::npos && minus == std::string::npos) {
											parsed = true;
										} else {
											if(val2.find("+") != std::string::npos || val2.find("-") != std::string::npos) {
												bool p = false;
												std::string val2cpy = val2;
												size_t plus2;
												size_t minus2;
												do {
													plus2 = val2cpy.find("+");
													minus2 = val2cpy.find("-");
													if(plus2 == std::string::npos && minus2 == std::string::npos) {
														p = true;
													} else {
														stack.push_back(std::string(val2cpy.substr(0, std::min(plus2, minus2)) + "*" + val1.substr(0, std::min(plus, minus)) + (plus2 < minus2 ? "+" : "-")));
														val2cpy.erase(0, std::min(plus2, minus2) + 1);
													}
												} while(!p);
												stack.push_back(std::string(val2cpy + "*" + val1.substr(0, std::min(plus, minus)) + (plus < minus ? "+" : "-")));
												val2cpy.erase(0, std::min(plus2, minus2) + 1);
											} else {
												if(std::min(plus, minus) == 0) {
													std::string symbol = val1.substr(0, std::min(plus, minus) + 1);
													val1.erase(0, std::min(plus, minus) + 1);
													plus = val1.find("+");
													minus = val1.find("-");
													stack.push_back(std::string(val2 + "*" + symbol + val1.substr(0, std::min(plus, minus)) + (plus != std::string::npos && minus != std::string::npos ? (plus < minus ? "+" : "-") : "")));
													definingSymbol = true;
												} else {
													stack.push_back(std::string(val2 + "*" + val1.substr(0, std::min(plus, minus)) + val1.substr(1) + (plus < minus ? "+" : "-")));
												}
											}
											val1.erase(0, std::min(plus, minus) + 1);
										}
									} while(!parsed);
									if(val2.find("+") != std::string::npos || val2.find("-") != std::string::npos) {
										bool p = false;
										std::string val2cpy = val2;
										size_t plus2;
										size_t minus2;
										do {
											plus2 = val2cpy.find("+");
											minus2 = val2cpy.find("-");
											if(plus2 == std::string::npos && minus2 == std::string::npos) {
												p = true;
											} else {
												stack.push_back(std::string(val2cpy.substr(0, std::min(plus2, minus2)) + "*" + val1 + (plus2 < minus2 ? "+" : "-")));
												val2cpy.erase(0, std::min(plus2, minus2) + 1);
											}
										} while(!p);
										stack.push_back(std::string(val2cpy.substr(0, std::min(plus2, minus2)) + "*" + val1));
										val2cpy.erase(0, std::min(plus2, minus2) + 1);
									}/* else {
										std::cout << "d: " << std::string(val2 + "*" + val1.substr(0, std::min(plus, minus))) << "\n";
										stack.push_back(std::string(val2 + "*" + val1.substr(0, std::min(plus, minus))));
									}*/
									val1.erase(0, std::min(plus, minus) + 1);
								} else if(val2.find("+") != std::string::npos || val2.find("-") != std::string::npos) {
									bool parsed = false;
									size_t plus;
									size_t minus;
									do {
										bool definingSymbol = false;
										plus = val2.find("+");
										minus = val2.find("-");
										if(plus == std::string::npos && minus == std::string::npos) {
											parsed = true;
										} else {
											if(val1.find("+") != std::string::npos || val1.find("-") != std::string::npos) {
												bool p = false;
												std::string val1cpy = val1;
												size_t plus2;
												size_t minus2;
												do {
													plus2 = val1cpy.find("+");
													minus2 = val1cpy.find("-");
													if(plus2 == std::string::npos && minus2 == std::string::npos) {
														p = true;
													} else {
														stack.push_back(std::string(val2.substr(0, std::min(plus, minus)) + "*" + val1cpy.substr(0, std::min(plus2, minus2)) + (plus2 < minus2 ? "+" : "-")));
														val1cpy.erase(0, std::min(plus2, minus2) + 1);
													}
												} while(!p);
												stack.push_back(std::string(val2.substr(0, std::min(plus, minus)) + "*" + val1cpy + (plus2 < minus2 ? "+" : "-")));
												val1cpy.erase(0, std::min(plus2, minus2));
											} else {
												if(std::min(plus, minus) == 0) {
													std::string symbol = val2.substr(0, std::min(plus, minus) + 1);
													val2.erase(0, std::min(plus, minus) + 1);
													plus = val1.find("+");
													minus = val1.find("-");
													stack.push_back(std::string(symbol + val2.substr(0, std::min(plus, minus)) + "*" + val1 + (plus != std::string::npos && minus != std::string::npos ? (plus < minus ? "+" : "-") : "")));
													definingSymbol = true;
												} else {
													stack.push_back(std::string(val2.substr(0, std::min(plus, minus)) + "*" + val1 + (plus < minus ? "+" : "-")));
												}
											}
											val2.erase(0, std::min(plus, minus) + 1);
										}
									} while(!parsed);
									if(val1.find("+") != std::string::npos || val1.find("-") != std::string::npos) {
										bool p = false;
										std::string val1cpy = val1;
										size_t plus2;
										size_t minus2;
										do {
											plus2 = val1cpy.find("+");
											minus2 = val1cpy.find("-");
											if(plus2 == std::string::npos && minus2 == std::string::npos) {
												p = true;
											} else {
												stack.push_back(std::string(val2 + "*" + val1cpy.substr(0, std::min(plus2, minus2)) + (plus2 < minus2 ? "+" : "-")));
												val1cpy.erase(0, std::min(plus2, minus2) + 1);
											}
										} while(!p);
										stack.push_back(std::string(val2 + "*" + val1cpy.substr(0, std::min(plus2, minus2))));
										val1cpy.erase(0, std::min(plus2, minus2) + 1);
									}/* else {
										stack.push_back(std::string(val2.substr(0, std::min(plus, minus)) + "*" + val1));
									}*/
									val2.erase(0, std::min(plus, minus) + 1);
								} else {
									stack.push_back(std::string(val2 + "*" + val1));
								}
							}
						} else if(o == "/") {
							if(val2 != "" && val1 != "0.0" && val2 != "0.0" && val1 != "0" && val2 != "0") {
								stack.push_back(std::string(val2 + "/" + val1));
							}
						} else if(o == "+") {
							if(val2 != "0" && val2 != "0.0" && val2 != "") {
								if(val1 != "0" && val1 != "0.0" && val1 != "")
									stack.push_back(std::string(val2 + "+" + val1));
								else
									stack.push_back(std::string(val2));
							} else if(val1 != "")
								stack.push_back(std::string(val1));
						} else if(o == "-") {
							if(val2 != "" && val2 != "0" && val2 != "0.0")
								stack.push_back(std::string(val2 + "-" + val1));
							else if(val1 != "0.0" && val1 != "")
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
			std::cout << "\n";
 */
