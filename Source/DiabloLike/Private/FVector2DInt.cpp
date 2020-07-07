// Fill out your copyright notice in the Description page of Project Settings.


#include "FVector2DInt.h"

FVector2DInt::FVector2DInt()
{
}

FVector2DInt::FVector2DInt(int a, int b)
{
	X = a;
	Y = b;
}

FVector2DInt::FVector2DInt(const FVector2D& floatVec)
{
	X = floatVec.X;
	Y = floatVec.Y;
}


FVector2DInt::FVector2DInt(const FVector2DInt& IntVecCopy)
{
	X = IntVecCopy.X;
	Y = IntVecCopy.Y;
}


FVector2DInt::~FVector2DInt()
{
}

FVector2DInt& FVector2DInt::operator=(const FVector2DInt& other)
{
    if (this != &other) { // self-assignment check expected
		X = other.X;
		Y = other.Y;
    }
    return *this;
}

FVector2DInt& FVector2DInt::operator=(const FVector2D& other)
{
	X = int(other.X);
	Y = int(other.Y);

	return *this;
}

FVector2D FVector2DInt::ToFVector2D()
{
	FVector2D ret = FVector2D();
	ret.X = this->X;
	ret.Y = this->Y;

	return ret;
}

const float FVector2DInt::Magnitude()
{
	return FMath::Sqrt(X*X + Y*Y);
}

const float FVector2DInt::DotProduct(FVector2DInt a, FVector2DInt b)
{
	return a.X*b.X + a.Y*b.Y;
}

