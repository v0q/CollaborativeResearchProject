#pragma once

#include "nodeEditor/NodeData.hpp"

struct Vec4f
{
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_z = 0.0f;
	float m_w = 0.0f;

	Vec4f() {}
	Vec4f(float _x, float _y, float _z, float _w)
	{
		m_x = _x;
		m_y = _y;
		m_z = _z;
		m_w = _w;
	}

	Vec4f operator +(const Vec4f &_rhs) {
		m_x += _rhs.m_x;
		m_y += _rhs.m_y;
		m_z += _rhs.m_z;
		m_w += _rhs.m_w;

		return *this;
	}

	void operator =(const Vec4f &_rhs) {
		m_x = _rhs.m_x;
		m_y = _rhs.m_y;
		m_z = _rhs.m_z;
		m_w = _rhs.m_w;
	}
};

enum DFNodeType
{
	PRIMITIVE,
	TRANSFORM,
	MIX
};

class Mat4f
{
public:
	Mat4f();
	~Mat4f();

private:
	union
	{
		float m_m4f[4][4];
		float m_matrix[16] = {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		struct
		{
			struct
			{
				float m_00;
				float m_01;
				float m_02;
				float m_03;
				float m_10;
				float m_11;
				float m_12;
				float m_13;
				float m_20;
				float m_21;
				float m_22;
				float m_23;
				float m_30;
				float m_31;
				float m_32;
				float m_33;
			};
		};
	};
};


class DistanceFieldInput : public NodeData
{
public:

	NodeDataType
	type() const override
	{ return NodeDataType {"DistanceFieldData", "     "}; }

};

class DistanceFieldOutput : public NodeData
{
public:

	NodeDataType
	type() const override
	{ return NodeDataType {"DistanceFieldData", "Result"}; }
};

class VectorData : public NodeData
{
public:
	NodeDataType
	type() const override
	{ return NodeDataType {"Vector", "Vec"}; }

private:
	Vec4f m_v;
};

