// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
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

	UFUNCTION(BlueprintPure)
		FGenericTile GetTile(int x, int y) const;

	UFUNCTION(BlueprintPure)
		void GetStartTileCoord(int& x, int& y) const;
	UFUNCTION(BlueprintPure)
		void GetGoalTileCoord(int& x, int& y) const;

	UFUNCTION(BlueprintPure)
		int GetWidth() const;
	UFUNCTION(BlueprintPure)
		int GetHeight() const;

	UFUNCTION(BlueprintPure)
		void ConvertIntToCoordinates(int i, int& x, int& y);
	UFUNCTION(BlueprintPure)
		int ConvertCoordToInt(int x, int y) const;
	UFUNCTION(BlueprintCallable)
		bool IsOutOfBounds(int x, int y) const;

	UFUNCTION(BlueprintPure)
		int GetNumberOfTiles();

	UFUNCTION(BlueprintCallable)
		bool SetStartTile(int X, int Y);
	UFUNCTION(BlueprintCallable)
		bool SetGoalTile(int X, int Y);

	UFUNCTION(BlueprintCallable)
		bool SetTile(int x, int y, FGenericTile tile);

	UFUNCTION(BlueprintCallable)
		TArray<FGenericTile> GetTileArray();

	UFUNCTION(BlueprintCallable)
		bool SetDungeonDimensions(int width, int height);
	bool SetDungeonDimensions(int widthAndHeight);

	const FGenericTile operator[](int index);

	void GetAdjacentTileIndices(int x, int y, int& Xout, int& Yout);
	TArray<FGenericTile> GetAdjacentTiles(int x, int y);

	void Initialize();
	
protected:
	TArray<FGenericTile> _dungeonArray;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int _dungeonWidth;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int _dungeonHeight;

	int _startTile [2];
	int _goalTile [2];
	
private:
};
