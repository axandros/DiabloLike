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
	const FGenericTile* operator[](int index);

		bool SetStartTile(const FIntVector& tileIndex);
	UFUNCTION(BlueprintCallable)
		bool SetStartTile(int X, int Y);
		bool SetGoalTile(const FIntVector& tileIndex);
	UFUNCTION(BlueprintCallable)
		bool SetGoalTile(int X, int Y);
	UFUNCTION(BlueprintCallable)
		bool SetDungeonDimensions(int width, int height);

	UFUNCTION(BlueprintCallable)
		bool SetTile(int x, int y, FGenericTile tile);
	bool SetTile(int x, int y, bool North, bool South, bool East, bool West);

	UFUNCTION(BlueprintCallable)
		void GetAdjacentTileIndices(TArray<FIntVector>& AdjacentTileIndices, int x, int y);
	void GetAdjacentTileIndices(TArray<FIntVector>& AdjacentTileIndices, const FIntVector& originIndex);

	UFUNCTION(BlueprintCallable)
		void GetAdjacentTiles(TArray<FGenericTile> AdjacentTiles, const FIntVector& originIndex);
	void GetAdjacentTiles(TArray<FGenericTile> AdjacentTiles, int x, int y);

	// Blueprint Pure
	
	/// Get the tile at X, Y
	/// Returns true if in bounds, false if outof bounds.
	UFUNCTION(BlueprintPure)
		bool GetTile(FGenericTile& tile, int x, int y);

	UFUNCTION(BlueprintPure)
		void GetAllTiles(TArray<FGenericTile>& TileList);

	UFUNCTION(BlueprintPure)
		void ConvertIntToCoordinates(int i, int& x, int& y);

	UFUNCTION(BlueprintPure)
		int ConvertCoordToInt(int x, int y);

	UFUNCTION(BlueprintPure)
		int GetWidth();
	UFUNCTION(BlueprintPure)
		int GetHeight();

	UFUNCTION(BlueprintPure)
		int GetNumberOfTiles();

	UFUNCTION(BLUEPRINTPURE)
		int ConvertCoordToIntF(FIntVector index);

	UFUNCTION(BLUEPRINTPURE)
		const bool IsOutOfBounds(int X, int Y);
		const bool IsOutOfBounds(int index);
		const bool IsOutOfBounds(FIntVector& index);

	UFUNCTION(BLUEPRINTPURE)
		void GetStartTile(int& x, int& y);
	UFUNCTION(BLUEPRINTPURE)
		void GetGoalTile(int& x, int& y);

	UFUNCTION(BLUEPRINTPURE)
		int GetDungeonWidth();
	UFUNCTION(BLUEPRINTPURE)
		int GetDungeonHeight();

	
	

	void Initialize();
	
protected:
	TArray<FGenericTile> _dungeonArray;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int _dungeonWidth;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int _dungeonHeight;
	
	FIntVector _startTile;
	FIntVector _goalTile;
	
private:
};
