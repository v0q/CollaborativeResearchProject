#include <iomanip>
#include "ExpressionEvaluator.hpp"

/*
 * Please do not look at these!
 */
namespace hsitho {
  namespace Expressions {
		std::shared_ptr<Unknowns> Unknowns::m_instance = 0;

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
			std::string no = newOutput.str();

			parsed = false;
			size_t cos = 0;
			size_t sin = 0;
			do {
				cos = no.find("cos(", cos);
				sin = no.find("sin(", sin);
				if(cos == std::string::npos && sin == std::string::npos) {
					parsed = true;
				}	else if(cos < sin) {
					size_t start = no.find("(", cos) + 1;
					size_t end = no.find(")", cos);
					size_t l = end - start;
					no.replace(start, l, evaluate(no.substr(start, l), "" ,-1, 1));
					end = no.find(")", cos);
					sin -= l - (end - start);
					size_t pos = no.find(" ", cos);
					if(pos < end) {
						do {
							no.replace(pos, 1, "");
							pos = no.find(" ", cos);
							--end;
							--sin;
						} while(pos != std::string::npos && pos < end);
					}
					cos = end;
				} else {
					size_t start = no.find("(", sin) + 1;
					size_t end = no.find(")", sin);
					size_t l = end - start;
					no.replace(start, l, evaluate(no.substr(start, l), "", -1, 1));
					end = no.find(")", sin);
					cos -= l - (end - start);
					size_t pos = no.find(" ", sin);
					if(pos < end) {
						do {
							no.replace(pos, 1, "");
							pos = no.find(" ", sin);
							--end;
							--cos;
						} while(pos != std::string::npos && pos < end);
					}
					sin = end;
				}
			} while(!parsed);

			size_t pos = no.find("e - ", 0);
			while(pos != std::string::npos) {
				std::string d = no;
				no.replace(pos, 4, "e-");
				pos = no.find("e - ", pos);
			}
			pos = no.find("e + ", 0);
			while(pos != std::string::npos) {
				no.replace(pos, 4, "e+");
				pos = no.find("e + ", pos);
			}
			if((pos = no.find("e - ")) != std::string::npos) {
				no.replace(pos, 4, "e-");
			}
			if(no.find(" ") == 0) {
				no.erase(0, 1);
			}
			return no;
		}

		std::string evaluate(const std::string &_expression, const std::string &_prev, const int &_copyNum, const unsigned int &_gen)
    {
      // Generate postfix notation for the expression
			std::string exp = _expression;
			if(exp.find("- ") == 0) {
				exp.erase(1, 1);
			}
			if(_copyNum != -1) {
				size_t pos;
				while((pos = exp.find("copyNum")) != std::string::npos) {
					try {
						exp.replace(pos, 7, boost::lexical_cast<std::string>(_copyNum));
					} catch(const boost::bad_lexical_cast e) {}
				}
			}
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
					float val = boost::lexical_cast<float>(i);
					std::ostringstream ss;
					ss << std::fixed << std::setprecision(4) << val;
					outputQueue.push_back(ss.str());
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

			std::string derp = s;

      s = addSpaces(s);
      std::string finalOutput;
      if(s != _prev) {
				finalOutput = evaluate(s, s, _copyNum, 1);
			} else {
        finalOutput = s;
			}
			if(!_gen) {
				if(finalOutput.find("e", 0) != std::string::npos) {
					std::string test = s;
				}
				setUnknowns(addSpaces(finalOutput));
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
					if((pos = o.find("-sin(")) != std::string::npos) {
						unsigned int startPos = pos+5;
						float sineval = std::sin(boost::lexical_cast<float>(o.substr(startPos, o.find(")", pos) - startPos)));
						std::ostringstream ss;
						ss << std::fixed << std::setprecision(4) << "-" << sineval;
						stack.push_back(ss.str());
						continue;
					} else if((pos = o.find("sin(")) != std::string::npos) {
						unsigned int startPos = pos+4;
						float sineval = std::sin(boost::lexical_cast<float>(o.substr(startPos, o.find(")", pos) - startPos)));
						std::ostringstream ss;
						ss << std::fixed << std::setprecision(4) << sineval;
						stack.push_back(ss.str());
						continue;
					} else if((pos = o.find("-cos(")) != std::string::npos) {
						unsigned int startPos = pos+5;
						float cosineval = std::cos(boost::lexical_cast<float>(o.substr(startPos, o.find(")", pos) - startPos)));
						std::ostringstream ss;
						ss << std::fixed << std::setprecision(4) << "-" << cosineval;
						stack.push_back(ss.str());
						continue;
					} else if((pos = o.find("cos(")) != std::string::npos) {
						unsigned int startPos = pos+4;
						float cosineval = std::cos(boost::lexical_cast<float>(o.substr(startPos, o.find(")", pos) - startPos)));
						std::ostringstream ss;
						ss << std::fixed << std::setprecision(4) << cosineval;
						stack.push_back(ss.str());
						continue;
					} else {
						float val = boost::lexical_cast<float>(o);
						std::ostringstream ss;
						ss << std::fixed << std::setprecision(4) << val;
						stack.push_back(ss.str());
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
						std::ostringstream ss;
						ss << std::fixed << std::setprecision(4) << result;
						stack.push_back(ss.str());
					} catch(const boost::bad_lexical_cast &) {
            if(o == "*") {
							bool parsed = false;
							if(vals[0] != "0.0000" && vals[1] != "0.0000") {
								if(vals[0] == "1.0000") {
									stack.push_back(vals[1]);
								} else if(vals[1] == "1.0000") {
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
							} else {
								stack.push_back("0.0000");
							}
            } else if(o == "/") {
							if(vals[1] != "" && vals[0] != "0.0000" && vals[1] != "0.0000") {
                stack.push_back(std::string(vals[1] + "/" + vals[0]));
              }
						} else if(o == "+") {
							if(vals[1] != "0.0000" && vals[1] != "") {
								if(vals[0] != "0.0000" && vals[0] != "")
                  stack.push_back(std::string(vals[1] + "+" + vals[0]));
                else
                  stack.push_back(std::string(vals[1]));
              } else if(vals[0] != "")
                stack.push_back(std::string(vals[0]));
						} else if(o == "-") {
							if(vals[1] != "" && vals[1] != "0.0000") {
								if(vals[0] != "" && vals[0] != "0.0000")
									stack.push_back(std::string(vals[1] + "-" + vals[0]));
								else
									stack.push_back(vals[1]);
							}
							else if(vals[0] != "0.0000" && vals[0] != "")
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

		std::string getUnknowns()
		{
			std::shared_ptr<Unknowns> u = Unknowns::instance();
			std::ostringstream ss;
			for(auto &s : u->getUnknowns())
				ss << "float " << s.second << " = " << s.first << "; ";
			return ss.str();
		}

		void setUnknowns(const std::string &_expression)
		{
			std::shared_ptr<Unknowns> u = Unknowns::instance();
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
					continue;
				} catch(const boost::bad_lexical_cast &) {}
				if(i == "*" || i == "/") {
					if(stack.size()) {
						std::string op = stack.back();
						if(op == "*" || op == "/") {
							stack.pop_back();
						}
					}
					stack.push_back(i);
				} else if(i == "+" || i == "-") {
					if(stack.size()) {
						std::string op = stack.back();
						if(op == "+" || op == "-" || op == "*" || op == "/") {
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
						stack.pop_back();
					}
					if(stack.size()) stack.pop_back();
				} else {
					try {
						boost::lexical_cast<float>(i);
					} catch(boost::bad_lexical_cast &) {
						u->setUnknown(i);
					}
				}
			}
		}

		std::string replaceUnknowns(const std::string &_expression)
		{
			std::shared_ptr<Unknowns> u = Unknowns::instance();
			std::string thisOutput = _expression;
			for(auto &s : u->getUnknowns()) {
				size_t start_pos = 0;
				while((start_pos = thisOutput.find(s.first, start_pos)) != std::string::npos) {
					thisOutput.replace(start_pos, s.first.length(), s.second);
					start_pos += s.second.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
				}
			}
			return thisOutput;
		}

		void flushUnknowns() {
			std::shared_ptr<Unknowns> u = Unknowns::instance();
			u->clear();
		}
  }
}
/*
 * Please do not look at these!
 */
