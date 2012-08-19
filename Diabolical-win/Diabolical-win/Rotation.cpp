#include "stdafx.h"

#include "Rotation.h"

Rotation::Rotation() : Vector3()
{
	
}

Rotation::Rotation(float inx, float iny, float inz) : Vector3(inx, iny, inz)
{
}

const Rotation Rotation::operator=(Vector3 other)
{
	this->setVector(other.getX(), other.getY(), other.getZ());
	return *this;
}

//TODO: Some sort of actual rotation addition
const Rotation Rotation::operator+(Rotation other)
{
	Rotation self = *this;
}