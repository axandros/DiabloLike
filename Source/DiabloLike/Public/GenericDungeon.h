// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FVector2DInt.h"
#include "GenericDungeon.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Dungeon, Log, All);

UENUM(BlueprintType)
enum ECardinalDirections { NORTH, SOUTH, EAST, WEST };


USTRUCT(BlueprintType)
struct FGenericTile {
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exits")
		bool North = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exits")
		bool South = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exits")
		bool East = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exits")
		bool West = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exits")
		bool Void = true;

	bool NoExits() { return !North && !South && !East && !West; }

	FGenericTile MakeCopy();
};

UCLASS(Blueprintable)
class DIABLOLIKE_API UGenericDungeon : public UObject
{
	GENERATED_BODY()

public:
	UGenericDungeon();
	// operator= already declared?  In GENERATED_BODY?
	//UGenericDungeon& operator=(const UGenericDungeon& other);

	UFUNCTION(BlueprintCallable)
		FGenericTile GetTile(int x, int y);

	UFUNCTION(BlueprintCallable)
		bool SetTile(int x, int y, bool North, bool South, bool East, bool West);

	UFUNCTION(BlueprintCallable)
		TArray<FGenericTile> GetAllTiles();

	UFUNCTION(BlueprintPure)
		void ConvertIntToCoordinates(int i, int& x, int& y);

	UFUNCTION(BlueprintPure)
		int ConvertCoordToInt(int x, int y);

	UFUNCTION(BlueprintPure)
		int ConvertCoordToIntF(FVector2DInt index);

	UFUNCTION(BlueprintCallable)
		bool GetTileArray(TArray<FGenericTile>& OutArray);

	UFUNCTION(BlueprintPure)
		int GetWidth();
	UFUNCTION(BlueprintPure)
		int GetHeight();

	UFUNCTION(BlueprintPure)
		int GetNumberOfTiles();

	const FGenericTile operator[](FVector2DInt index);
	const FGenericTile operator[](int index);

	bool IsOutOfBounds(int X, int Y);
	bool IsOutOfBounds(FVector2DInt tileIndex);

	bool SetStartTile(const FVector2DInt& tileIndex);
	bool SetStartTile(int X, int Y);
	bool SetGoalTile(const FVector2DInt& tileIndex);
	bool SetGoalTile(int X, int Y);
	bool SetDungeonDimensions(int width, int height);
	bool SetDungeonDimensions(int widthAndHeight);

	void SetTile(int x, int y, FGenericTile tile);

	FVector2DInt GetStartTile();
	FVector2DInt GetGoalTile();

	int GetDungeonWidth();
	int GetDungeonHeight();

	TArray<FVector2DInt> GetAdjacentTileIndices(int x, int y);
	TArray<FVector2DInt> GetAdjacentTileIndices(const FVector2DInt& originIndex);

	TArray<FGenericTile> GetAdjacentTiles(const FVector2DInt& originIndex);
	TArray<FGenericTile> GetAdjacentTiles(int x, int y);

	

	void Initialize();
	
protected:
	TArray<FGenericTile> _dungeonArray;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int _dungeonWidth;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int _dungeonHeight;

	FVector2DInt _startTile;
	FVector2DInt _goalTile;
	
private:
};
