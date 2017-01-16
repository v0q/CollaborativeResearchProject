#pragma once

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>

/*
 * Please do not look at these!
 */
namespace hsitho {
  namespace Expressions
	{	
		class Unknowns {
			public:
				static std::shared_ptr<Unknowns> instance()
				{
					if(m_instance == nullptr)
						m_instance.reset(new Unknowns);

					return m_instance;
				}

				~Unknowns() {}
				void setUnknown(std::string &_val) {
					if(_val.find("copyNum", 0) != std::string::npos || _val == "") {
						return;
					}
					if(m_unknowns.find(_val) == m_unknowns.end()) {
						for(auto &s : m_unknowns) {
							if(s.second == _val)
								return;
						}
						unsigned int a = m_unknowns.size();
						m_unknowns[_val] = 'a' + a;
						std::cout << "Unknown: " << _val << "\n";
					}
				}

				std::unordered_map<std::string, std::string> getUnknowns() { return m_unknowns; }
				void clear() { m_unknowns.clear(); }

				void printUnknowns() {
					for(auto &s : m_unknowns)
						std::cout << s.first << " " << s.second << "\n";
				}

			private:
				Unknowns() {}
				Unknowns(const Unknowns &_rhs) = delete;
				Unknowns& operator= (const Unknowns &_rhs) = delete;

				static std::shared_ptr<Unknowns> m_instance;
				std::unordered_map<std::string, std::string> m_unknowns;
		};

		void parseExpression(std::string &_expression);
    std::string addSpaces(const std::string &_expression);
		std::string evaluate(const std::string &_expression, const std::string &_prev = "", const int &_copyNum = -1, const unsigned int &_gen = 0);
		std::string evaluatePostFix(std::vector<std::string> outputQueue);
		std::string getUnknowns();
		void setUnknowns(const std::string &_expression);
		std::string replaceUnknowns(const std::string &_expression);
		void flushUnknowns();

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
