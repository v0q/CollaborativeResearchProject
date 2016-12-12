#pragma once

#include "nodeEditor/NodeData.hpp"
#include "ExpressionEvaluator.hpp"

struct Vec4f
{
	Vec4f() {}
	Vec4f(const std::string &_x, const std::string &_y, const std::string &_z, const std::string &_w) :
		m_x(_x),
		m_y(_y),
		m_z(_z),
		m_w(_w)
	{}


	Vec4f operator +(const Vec4f &_rhs) {
		m_x = _rhs.m_x;
		m_y = _rhs.m_y;
		m_z = _rhs.m_z;
		m_w = _rhs.m_w;

		return *this;
	}

	void operator =(const Vec4f &_rhs) {
		m_x = _rhs.m_x;
		m_y = _rhs.m_y;
		m_z = _rhs.m_z;
		m_w = _rhs.m_w;
	}

	std::string m_x = "0.0";
	std::string m_y = "0.0";
	std::string m_z = "0.0";
  std::string m_w = "1.0";
};

enum DFNodeType
{
	PRIMITIVE,
	TRANSFORM,
	MIX,
	VECTOR,
  SCALAR,
	COLOR,
	OUTPUT
};

class Mat4f
{
public:
	Mat4f() {}
  Mat4f(const std::string &_m00, const std::string &_m10, const std::string &_m20, const std::string &_m30,
        const std::string &_m01, const std::string &_m11, const std::string &_m21, const std::string &_m31,
        const std::string &_m02, const std::string &_m12, const std::string &_m22, const std::string &_m32,
        const std::string &_m03, const std::string &_m13, const std::string &_m23, const std::string &_m33)
	{
    m_m4f[0][0] = _m00;
    m_m4f[0][1] = _m01;
    m_m4f[0][2] = _m02;
    m_m4f[0][3] = _m03;

    m_m4f[1][0] = _m10;
    m_m4f[1][1] = _m11;
    m_m4f[1][2] = _m12;
    m_m4f[1][3] = _m13;

    m_m4f[2][0] = _m20;
    m_m4f[2][1] = _m21;
    m_m4f[2][2] = _m22;
    m_m4f[2][3] = _m23;

    m_m4f[3][0] = _m30;
    m_m4f[3][1] = _m31;
    m_m4f[3][2] = _m32;
    m_m4f[3][3] = _m33;
	}
	~Mat4f() {}

	Mat4f& operator=(const Mat4f& _m) noexcept
	{
		m_m4f[0][0] = _m.m_m4f[0][0];
		m_m4f[0][1] = _m.m_m4f[0][1];
		m_m4f[0][2] = _m.m_m4f[0][2];
		m_m4f[0][3] = _m.m_m4f[0][3];

		m_m4f[1][0] = _m.m_m4f[1][0];
		m_m4f[1][1] = _m.m_m4f[1][1];
		m_m4f[1][2] = _m.m_m4f[1][2];
		m_m4f[1][3] = _m.m_m4f[1][3];

		m_m4f[2][0] = _m.m_m4f[2][0];
		m_m4f[2][1] = _m.m_m4f[2][1];
		m_m4f[2][2] = _m.m_m4f[2][2];
		m_m4f[2][3] = _m.m_m4f[2][3];

		m_m4f[3][0] = _m.m_m4f[3][0];
		m_m4f[3][1] = _m.m_m4f[3][1];
		m_m4f[3][2] = _m.m_m4f[3][2];
		m_m4f[3][3] = _m.m_m4f[3][3];

		return *this;
	}

	Mat4f operator*(const Mat4f& _m) const noexcept
	{
		Mat4f temp;
		std::ostringstream row;

		std::cout << "Matrices to multiply: \n";
		this->print();
		_m.print();
		std::cout << "\n";

		row << "( " << m_m4f[0][0] << " ) * ( " << _m.m_m4f[0][0] << " ) + ( " << m_m4f[1][0] << " ) * ( " << _m.m_m4f[0][1] << " ) + ( " << m_m4f[2][0] << " ) * ( " << _m.m_m4f[0][2] << " ) + ( " << m_m4f[3][0] << " ) * ( " << _m.m_m4f[0][3] << " )";
		temp.m_m4f[0][0] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][1] << " ) * ( " << _m.m_m4f[0][0] << " ) + ( " << m_m4f[1][1] << " ) * ( " << _m.m_m4f[0][1] << " ) + ( " << m_m4f[2][1] << " ) * ( " << _m.m_m4f[0][2] << " ) + ( " << m_m4f[3][1] << " ) * ( " << _m.m_m4f[0][3] << " )";
		temp.m_m4f[0][1] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][2] << " ) * ( " << _m.m_m4f[0][0] << " ) + ( " << m_m4f[1][2] << " ) * ( " << _m.m_m4f[0][1] << " ) + ( " << m_m4f[2][2] << " ) * ( " << _m.m_m4f[0][2] << " ) + ( " << m_m4f[3][2] << " ) * ( " << _m.m_m4f[0][3] << " )";
		temp.m_m4f[0][2] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][3] << " ) * ( " << _m.m_m4f[0][0] << " ) + ( " << m_m4f[1][3] << " ) * ( " << _m.m_m4f[0][1] << " ) + ( " << m_m4f[2][3] << " ) * ( " << _m.m_m4f[0][2] << " ) + ( " << m_m4f[3][3] << " ) * ( " << _m.m_m4f[0][3] << " )";
		temp.m_m4f[0][3] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][0] << " ) * ( " << _m.m_m4f[1][0] << " ) + ( " << m_m4f[1][0] << " ) * ( " << _m.m_m4f[1][1] << " ) + ( " << m_m4f[2][0] << " ) * ( " << _m.m_m4f[1][2] << " ) + ( " << m_m4f[3][0] << " ) * ( " << _m.m_m4f[1][3] << " )";
		temp.m_m4f[1][0] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][1] << " ) * ( " << _m.m_m4f[1][0] << " ) + ( " << m_m4f[1][1] << " ) * ( " << _m.m_m4f[1][1] << " ) + ( " << m_m4f[2][1] << " ) * ( " << _m.m_m4f[1][2] << " ) + ( " << m_m4f[3][1] << " ) * ( " << _m.m_m4f[1][3] << " )";
		temp.m_m4f[1][1] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][2] << " ) * ( " << _m.m_m4f[1][0] << " ) + ( " << m_m4f[1][2] << " ) * ( " << _m.m_m4f[1][1] << " ) + ( " << m_m4f[2][2] << " ) * ( " << _m.m_m4f[1][2] << " ) + ( " << m_m4f[3][2] << " ) * ( " << _m.m_m4f[1][3] << " )";
		temp.m_m4f[1][2] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][3] << " ) * ( " << _m.m_m4f[1][0] << " ) + ( " << m_m4f[1][3] << " ) * ( " << _m.m_m4f[1][1] << " ) + ( " << m_m4f[2][3] << " ) * ( " << _m.m_m4f[1][2] << " ) + ( " << m_m4f[3][3] << " ) * ( " << _m.m_m4f[1][3] << " )";
		temp.m_m4f[1][3] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][0] << " ) * ( " << _m.m_m4f[2][0] << " ) + ( " << m_m4f[1][0] << " ) * ( " << _m.m_m4f[2][1] << " ) + ( " << m_m4f[2][0] << " ) * ( " << _m.m_m4f[2][2] << " ) + ( " << m_m4f[3][0] << " ) * ( " << _m.m_m4f[2][3] << " )";
		temp.m_m4f[2][0] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][1] << " ) * ( " << _m.m_m4f[2][0] << " ) + ( " << m_m4f[1][1] << " ) * ( " << _m.m_m4f[2][1] << " ) + ( " << m_m4f[2][1] << " ) * ( " << _m.m_m4f[2][2] << " ) + ( " << m_m4f[3][1] << " ) * ( " << _m.m_m4f[2][3] << " )";
		temp.m_m4f[2][1] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][2] << " ) * ( " << _m.m_m4f[2][0] << " ) + ( " << m_m4f[1][2] << " ) * ( " << _m.m_m4f[2][1] << " ) + ( " << m_m4f[2][2] << " ) * ( " << _m.m_m4f[2][2] << " ) + ( " << m_m4f[3][2] << " ) * ( " << _m.m_m4f[2][3] << " )";
		temp.m_m4f[2][2] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][3] << " ) * ( " << _m.m_m4f[2][0] << " ) + ( " << m_m4f[1][3] << " ) * ( " << _m.m_m4f[2][1] << " ) + ( " << m_m4f[2][3] << " ) * ( " << _m.m_m4f[2][2] << " ) + ( " << m_m4f[3][3] << " ) * ( " << _m.m_m4f[2][3] << " )";
		temp.m_m4f[2][3] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][0] << " ) * ( " << _m.m_m4f[3][0] << " ) + ( " << m_m4f[1][0] << " ) * ( " << _m.m_m4f[3][1] << " ) + ( " << m_m4f[2][0] << " ) * ( " << _m.m_m4f[3][2] << " ) + ( " << m_m4f[3][0] << " ) * ( " << _m.m_m4f[3][3] << " )";
		temp.m_m4f[3][0] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][1] << " ) * ( " << _m.m_m4f[3][0] << " ) + ( " << m_m4f[1][1] << " ) * ( " << _m.m_m4f[3][1] << " ) + ( " << m_m4f[2][1] << " ) * ( " << _m.m_m4f[3][2] << " ) + ( " << m_m4f[3][1] << " ) * ( " << _m.m_m4f[3][3] << " )";
		temp.m_m4f[3][1] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][2] << " ) * ( " << _m.m_m4f[3][0] << " ) + ( " << m_m4f[1][2] << " ) * ( " << _m.m_m4f[3][1] << " ) + ( " << m_m4f[2][2] << " ) * ( " << _m.m_m4f[3][2] << " ) + ( " << m_m4f[3][2] << " ) * ( " << _m.m_m4f[3][3] << " )";
		temp.m_m4f[3][2] = hsitho::Expressions::evaluate(row.str());
		row.clear();
		row.str("");
		row << "( " << m_m4f[0][3] << " ) * ( " << _m.m_m4f[3][0] << " ) + ( " << m_m4f[1][3] << " ) * ( " << _m.m_m4f[3][1] << " ) + ( " << m_m4f[2][3] << " ) * ( " << _m.m_m4f[3][2] << " ) + ( " << m_m4f[3][3] << " ) * ( " << _m.m_m4f[3][3] << " )";
		temp.m_m4f[3][3] = hsitho::Expressions::evaluate(row.str());

		return temp;
	}

	std::string matrix(int _x, int _y) const { return m_m4f[_x][_y]; }

	void print() const {
		for(int y = 0; y < 4; ++y)
		{
			for(int x = 0; x < 4; ++x)
			{
				std::cout << m_m4f[x][y] << ", ";
			}
			std::cout << "\n";
		}
	}

	void print(const Mat4f &_m) const {
		for(int y = 0; y < 4; ++y)
		{
			for(int x = 0; x < 4; ++x)
			{
				std::cout << _m.m_m4f[x][y] << " ";
			}
			std::cout << "\n";
		}
	}

private:
//	union
//	{
		std::string m_m4f[4][4] = {
			{"1.0", "0.0", "0.0", "0.0"},
			{"0.0", "1.0", "0.0", "0.0"},
			{"0.0", "0.0", "1.0", "0.0"},
			{"0.0", "0.0", "0.0", "1.0"}
		};
//		std::string m_matrix[16] = {
//			"1.0", "0.0", "0.0", "0.0",
//			"0.0", "1.0", "0.0", "0.0",
//			"0.0", "0.0", "1.0", "0.0",
//			"0.0", "0.0", "0.0", "1.0"
//		};
//		struct
//		{
//			struct
//			{
//				std::string m_00;
//				std::string m_01;
//				std::string m_02;
//				std::string m_03;
//				std::string m_10;
//				std::string m_11;
//				std::string m_12;
//				std::string m_13;
//				std::string m_20;
//				std::string m_21;
//				std::string m_22;
//				std::string m_23;
//				std::string m_30;
//				std::string m_31;
//				std::string m_32;
//				std::string m_33;
//			};
//		};
//	};
};


class DistanceFieldInput : public NodeData
{
public:
	NodeDataType type() const override
	{
		return NodeDataType {"DistanceFieldData", "     ", Qt::green};
	}
};

class DistanceFieldOutput : public NodeData
{
public:
	NodeDataType type() const override
	{
		return NodeDataType {"DistanceFieldData", "Result", Qt::green};
	}
};

class ScalarData : public NodeData
{
public:
	ScalarData() : m_value("0.0") {}
	ScalarData(const std::string &_v) : m_value(_v) {}
	NodeDataType type() const override
	{
		return NodeDataType {"Scalar", " ", Qt::red};
	}
	std::string value() const { return m_value; }
private:
	std::string m_value;
};

class VectorData : public NodeData
{
public:
	VectorData() : m_v(Vec4f()) {}
	VectorData(const std::string &_x, const std::string &_y, const std::string &_z) :
		m_v(Vec4f(_x, _y, _z, "1.0"))
	{}

	NodeDataType type() const override
	{
		return NodeDataType {"Vector", "Vec", Qt::yellow};
	}

	Vec4f vector() const
	{
    return m_v;
	}

private:
	Vec4f m_v;
};

class ColorData : public NodeData
{
public:

  ColorData() : m_cd(Vec4f()) {}
  ColorData(const std::string &_r, const std::string &_g, const std::string &_b) :
    m_cd(Vec4f(_r, _g, _b, "1.0")) {}

  NodeDataType type() const override
  {
		return NodeDataType {"Color", "Cd", Qt::white};
  }

  Vec4f color() const
  {
    return m_cd;
  }
private:
  Vec4f m_cd;
};

class GenericData : public NodeData
{
public:
	GenericData() {}
	NodeDataType type() const override {
		return NodeDataType {"Generic", "Out", Qt::gray};
	}
};

