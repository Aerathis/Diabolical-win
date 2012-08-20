#ifndef _ROTATION_H
#define _ROTATION_H

#include "Vector3.h"

// A clearly separated from normal Vector rotation. 
// This can also add some rotation specific things.
struct Rotation
{
	union 
	{
		struct 
		{
			float s; // Real component
			Vector3 v; // Imaginary components
		};
		struct
		{
			float elem[4];
		};
	};

	// Standard constructorization
	Rotation() {}
	Rotation(float real, float x, float y, float z): s(real),v(x,y,z) {}
	Rotation(float real, const Vector3 &i):s(real),v(i) {}

	// From 3 Euler angles
	Rotation(float theta_z, float theta_y, float theta_x)
	{
		float cos_z_2 = (float)cos(0.5*theta_z);
		float cos_y_2 = (float)cos(0.5*theta_y);
		float cos_x_2 = (float)cos(0.5*theta_x);

		float sin_z_2 = (float)sin(0.5*theta_z);
		float sin_y_2 = (float)sin(0.5*theta_y);
		float sin_x_2 = (float)sin(0.5*theta_x);

		// Computation of quaternion
		s = cos_z_2 * cos_y_2 * cos_x_2 + sin_z_2 * sin_y_2 * sin_x_2;
		float newx = cos_z_2 * cos_y_2 * sin_x_2 - sin_z_2 * sin_y_2 * cos_x_2;
		float newy = cos_z_2 * sin_y_2 * cos_x_2 + sin_z_2 * cos_y_2 * sin_x_2;
		float newz = sin_z_2 * cos_y_2 * cos_x_2 - cos_z_2 * sin_y_2 * sin_x_2;
		v = Vector3(newx,newy,newz);
	}

	// Basic operators
	Rotation &operator=(const Rotation &q)
	{
		s = q.s;
		v = q.v;
		return *this;
	}

	const Rotation operator+(const Rotation &q) const
	{
		return Rotation(s+q.s,v+q.v);
	}

	const Rotation operator-(const Rotation &q) const
	{
		return Rotation(s-q.s,v-q.v);
	}

	const Rotation operator*(const Rotation &q) const
	{
		return Rotation(s*q.s - v*q.v,
			v.y*q.v.z-v.z*q.v.y+s*q.v.x+v.x*q.s,
			v.z*q.v.x-v.x*q.v.z+s*q.v.y+v.y*q.s,
			v.x*q.v.y-v.y*q.v.x+s*q.v.z+v.z*q.s);
	}

	const Rotation operator/(const Rotation &q) const
	{
		Rotation p(q);
		p.invert();
		return *this * p;
	}

	const Rotation operator*(float scale) const
	{
		return Rotation(s*scale,v*scale);
	}

	const Rotation operator/(float scale) const
	{
		return Rotation(s/scale,v/scale);
	}

	const Rotation operator-() const
	{
		return Rotation(-s,-v);
	}

	const Rotation &operator+=(const Rotation &q)
	{
		v += q.v;
		s += q.s;
		return *this;
	}

	const Rotation &operator-=(const Rotation &q)
	{
		v -= q.v;
		s -= q.s;
		return *this;
	}

	const Rotation &operator*=(const Rotation &q)
	{
		float x=v.x,y=v.y,z=v.z,sn=s*q.s-v*q.v;
		v.x = y*q.v.z-z*q.v.y+s*q.v.x+x*q.s;
		v.y = z*q.v.x-x*q.v.z+s*q.v.y+y*q.s;
		v.z = x*q.v.y-y*q.v.x+s*q.v.z+z*q.s;
		s=sn;
		return *this;
	}

	const Rotation &operator*=(float scale)
	{
		v *= scale;
		s *= scale;
		return *this;
	}

	const Rotation &operator/=(float scale)
	{
		v /= scale;
		s /= scale;
		return *this;
	}

	// Get Rotation length
	float length() const
	{
		return (float)sqrt(s*s+v*v);
	}

	float length_squared() const
	{
		return (float)(s*s+v*v);
	}

	// Normalize the Rotation
	void normalize()
	{
		*this /= length();
	}

	Rotation normalized() const
	{
		return *this/length();
	}

	// Computes the conjugate
	void conjugate()
	{
		v = -v;
	}

	// Inverts the Rotation
	void invert()
	{
		conjugate();
		*this/=length_squared();
	}

	Rotation log() const
	{
		float a = (float)acos(s);
		float sina = (float)sin(a);
		Rotation result;

		result.s = 0;
		if (sina > 0)
		{
			result.v.x = a*v.x/sina;
			result.v.y = a*v.y/sina;
			result.v.z = a*v.z/sina;
		}
		else
		{
			result.v.x = result.v.y = result.v.z = 0;
		}
		return result;
	}

	Rotation exp() const
	{
		float a = (float)v.length();
		float sina = (float)sin(a);
		float cosa = (float)cos(a);
		Rotation result;

		result.s = cosa;
		if (a > 0)
		{
			result.v.x = sina*v.x/a;
			result.v.y = sina*v.y/a;
			result.v.z = sina*v.z/a;
		}
		else
		{
			result.v.x = result.v.y = result.v.z = 0;
		}
		return result;
	}
};

#endif //ROTATION_H