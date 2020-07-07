// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FVector2DInt.generated.h"

USTRUCT(BlueprintType)
struct FVector2DInt{
	GENERATED_BODY();

public:
	FVector2DInt();
	FVector2DInt(int a, int b);
	FVector2DInt(const FVector2D& floatVec);
	FVector2DInt(const FVector2DInt& IntVecCopy);
	~FVector2DInt();

	FVector2DInt& operator=(const FVector2DInt& b);
	//FVector2D& operator=(const FVector2DInt& other);
	FVector2DInt& operator=(const FVector2D& other);
	FVector2D ToFVector2D();

	int X;
	int Y;

	const float Magnitude();

	static const float DotProduct(FVector2DInt a, FVector2DInt b);
	// static const FVector2DInt CrossProduct(FVector2DInt a, FVector2DInt b); // - Only for 3D?

protected: 
	
};
