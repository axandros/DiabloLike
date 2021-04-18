// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GenericDungeon.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(Dungeon, Log, All);

UENUM(BlueprintType)
enum ECardinalDirections { NORTH, SOUTH, EAST, WEST };

/** A Generic representation of a tile in the dungeon map. */
USTRUCT(BlueprintType)
struct FGenericTile {
	GENERATED_BODY()

public:
	/** Does this tile have an exit to the North? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exits")
		bool North = false;
	/** Does this tile have an exit to the South? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exits")
		bool South = false;
	/** Does this tile have an exit to the East? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exits")
		bool East = false;
	/** Does this tile have an exit to the West? */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exits")
		bool West = false;
	/** Should this tile exist?  If not, there should be an empty void in the world. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Exits")
		bool Void = true;

	/** Bit flag for North */
	static const unsigned int fNORTH = 0b01;
	/** Bit flag for East */
	static const unsigned int fEAST = 0b010;
	/** Bit flag for South */
	static const unsigned int fSOUTH = 0b0100;
	/** Bit flag for West */
	static const unsigned int fWEST = 0b01000;

	/** Return the boolean flags matching this tile's exits. */
	unsigned int GetExitFlags();

	/** Returns true if North, East, South, and West are all false */
	bool NoExits() { return !North && !South && !East && !West; }

	FGenericTile MakeCopy();
};

/** Describes a rectangular map of rectangulr tiles with up to four possible exits. *
  * Includes start and end tile positions which include no additional functionality. */
UCLASS(Blueprintable)
class DIABLOLIKE_API UGenericDungeon : public UObject
{
	GENERATED_BODY()

public:
	UGenericDungeon();
	
	/** Accessor for the dungeon tiles.  Width then height order. */
	const FGenericTile* operator[](int index);

	/** Set the start tile coordinate using an FIntVector.  */
	bool SetStartTile(const FIntVector& tileIndex);
	/** Set the start tile coordinate using an x and y coordinate. Returns true if successful. */
	UFUNCTION(BlueprintCallable)
		bool SetStartTile(int X, int Y);
	/** Set the goal tile coordinate using an FIntVector. Returns true if successful. */
		bool SetGoalTile(const FIntVector& tileIndex);
	/** Set the goal tile coordinate using an x and y coordinate. Returns true if successful. */
	UFUNCTION(BlueprintCallable)
		bool SetGoalTile(int X, int Y);
	/** Set the width and height of the dungeon.  Returns true if success.  False value means it has been set. */
	UFUNCTION(BlueprintCallable)
		bool SetDungeonDimensions(int width, int height);

	/** Set a tile in the map at the x, y coordinate value.  Returns false if the coordinates are out of bounds. */
	UFUNCTION(BlueprintCallable)
		bool SetTile(int x, int y, FGenericTile tile);

	/** Set a tile in the map at the x, y coordinate value.  Returns false if the coordinates are out of bounds. */
	bool SetTile(int x, int y, bool North, bool South, bool East, bool West, bool Empty = false);

	/** Returns a list of adjacent indices surrounding position x,y through the AdjacentTileIndices parameter. *
	  * Example: position 0, 1 will have adjacent incidces of(0,0), (1, 1), and (2, 1) */
	UFUNCTION(BlueprintCallable)
		void GetAdjacentTileIndices(TArray<FIntVector>& AdjacentTileIndices, int x, int y);

	/** Returns a list of adjacent indices surrounding position x,y through the AdjacentTileIndices parameter *
	  * Example: position 0, 1 will have adjacent incidces of(0,0), (1, 1), and (2, 1) */
	void GetAdjacentTileIndices(TArray<FIntVector>& AdjacentTileIndices, const FIntVector& originIndex);

	/** Returns a list of adjacent tiles surrounding position x,y through the AdjacentTileIndices parameter *
	  * Example: position 0, 1 will have adjacent tiles at indices of(0,0), (1, 1), and (2, 1) */
	UFUNCTION(BlueprintCallable)
		void GetAdjacentTiles(TArray<FGenericTile> AdjacentTiles, const FIntVector& originIndex);

	/** Returns a list of adjacent tiles surrounding position x,y through the AdjacentTileIndices parameter *
	  * Example: position 0, 1 will have adjacent tiles at indices of(0,0), (1, 1), and (2, 1) */
	void GetAdjacentTiles(TArray<FGenericTile> AdjacentTiles, int x, int y);

	/** Set the tiles at all indices on the map to a non-void tile with no exits. */
	UFUNCTION(BlueprintCallable)
		void FillWithEmptyTiles();

	//================
	// Blueprint Pure
	//================
	
	/** Get the tile at X, Y. 
	  Returns true if in bounds, false if out of bounds. */
	UFUNCTION(BlueprintPure)
		bool GetTile(FGenericTile& tile, int x, int y);

	/** Get a complete copy of all of the tiles through the TileList parameter */
	UFUNCTION(BlueprintPure)
		void GetAllTiles(TArray<FGenericTile>& TileList);

	/** Convert the given integer to integer coordinates in the dungeon's grid, using the x and y paramter */
	UFUNCTION(BlueprintPure)
		void ConvertIntToCoordinates(int i, int& x, int& y);

	/** Returns the integer value for the array using a two dimensional x and y coordinate system. */
	UFUNCTION(BlueprintPure)
		int ConvertCoordToInt(int x, int y);

	/** Returns the integer value for the array using a two dimensional x and y coordinate system. */
	UFUNCTION(BLUEPRINTPURE)
		int ConvertCoordToIntF(FIntVector index);

	/** Return the Width of the Dungeon. */
	UFUNCTION(BlueprintPure)
		int GetWidth();
	/** Return the Height of the Dungeon. */
	UFUNCTION(BlueprintPure)
		int GetHeight();

	/** Return the total number of tiles in the Dungeon. */
	UFUNCTION(BlueprintPure)
		int GetNumberOfTiles();

	/** Returns true if the given x and y coordinates are out of bounds of the grid.*/
	UFUNCTION(BLUEPRINTPURE)
		const bool IsOutOfBounds(int X, int Y);
	/** Returns true if the given index is out of bounds of the grid.*/
		const bool IsOutOfBounds(int index);
	/** Returns true if the given x and y coordinates are out of bounds of the grid.*/
		const bool IsOutOfBounds(FIntVector& index);

	/** Return the coordinates of the start tile using out parameters. */
	UFUNCTION(BLUEPRINTPURE)
		void GetStartTile(int& x, int& y);
	/** Return the coordinates of the goal tile using out parameters. */
	UFUNCTION(BLUEPRINTPURE)
		void GetGoalTile(int& x, int& y);

	/** Return the Width of the Dungeon. */
	UFUNCTION(BLUEPRINTPURE)
		int GetDungeonWidth();
	/** Return the Height of the Dungeon. */
	UFUNCTION(BLUEPRINTPURE)
		int GetDungeonHeight();

	
protected:
	/** The Array storing all of the tiles of the dungeon */
	TArray<FGenericTile> _dungeonArray;

	/** The width of the dungeon. */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int _dungeonWidth;
	/** The height of the dungeon. */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		int _dungeonHeight;
	
	/** The dungeon's start tile */
	FIntVector _startTile;
	/** The dungeon's goal tile */
	FIntVector _goalTile;
	
private:
};
