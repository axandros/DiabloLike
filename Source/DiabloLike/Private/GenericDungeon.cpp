// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericDungeon.h"
#include "DiabloLog.h"
#include "FVector2DInt.h"

DEFINE_LOG_CATEGORY(Dungeon);

UGenericDungeon::UGenericDungeon() {
	
	_dungeonArray = TArray<FGenericTile>();
	_dungeonArray.Empty();
}


const FGenericTile* UGenericDungeon::operator[](int LengthIndex)
{
	FGenericTile* ret = nullptr;
	if (!IsOutOfBounds(LengthIndex)) {
		//ret = _dungeonArray[LengthIndex];
	}
	return ret;
}


const bool UGenericDungeon::IsOutOfBounds(FIntVector& tileIndex)
{
	return IsOutOfBounds(int(tileIndex.X), int(tileIndex.Y));
}

const bool UGenericDungeon::IsOutOfBounds(int index)
{
	bool ret = false;
	if (index >= 0 && index < _dungeonArray.Num()){ ret = true;}
	return ret;
}

const bool UGenericDungeon::IsOutOfBounds(int X, int Y)
{
	bool Xzed = X >= 0;
	bool Yzed = Y >= 0;
	bool XTop = X < _dungeonWidth;
	bool YTop = Y < _dungeonHeight;
	bool ICheck = ConvertCoordToInt(X, Y) < _dungeonArray.Num();
	return !(Xzed && Yzed && XTop && YTop && ICheck);
}

bool UGenericDungeon::SetStartTile(const FIntVector& tileIndex)
{
	_startTile = tileIndex;
	return true;
}

bool UGenericDungeon::SetStartTile(int X, int Y)
{
	UE_LOG(Dungeon, Warning, TEXT("Setting Dungeon Start Tile: %i, %i"), X, Y)
	_startTile = FIntVector(X, Y, 0);
	UE_LOG(Dungeon, Warning, TEXT("Dungeon Start Tile Set: %i, %i"), _startTile.X, _startTile.Y)
	return true;
}

bool UGenericDungeon::SetGoalTile(const FIntVector& tileIndex)
{
	UE_LOG(Dungeon, Warning, TEXT("Setting Dungeon Goal Tile: %i, %i"), tileIndex.X, tileIndex.Y)
	_goalTile = tileIndex;
	UE_LOG(Dungeon, Warning, TEXT("Dungeon Start Goal Set: %i, %i"), _goalTile.X, _goalTile.Y)
	return true;
}

bool UGenericDungeon::SetGoalTile(int X, int Y)
{
	_goalTile = FIntVector(X, Y, 0);
	return true;
}

bool UGenericDungeon::SetDungeonDimensions(int width, int height)
{
	bool ret = false;
	UE_LOG(Dungeon, Warning, TEXT("Setting dungeon dimensions: %i, %i"), width, height)
	
	FString retString = "false";
	if (_dungeonArray.Num() == 0) {
		UE_LOG(Dungeon, Warning, TEXT("Setting is allowed."))
		_dungeonWidth = width;
		_dungeonHeight = height;
		_dungeonArray.SetNum(width * height);
		ret = true;
		retString = "true";

		/*
		for (int i = 0; i < _dungeonArray.Num(); i++) {
			UE_LOG(Dungeon, Warning, TEXT("Adding item %i"), i)
			_dungeonArray.Add(new FGenericTile());
		}
		*/
	}
	else {
		UE_LOG(Dungeon, Warning, TEXT("Setting not allowed.  Current Size = %i"),_dungeonArray.Num())
	}
	UE_LOG(Dungeon, Warning, TEXT("Returning from dimension set function %s"), *retString)

	return ret;
	
}

void UGenericDungeon::GetStartTile(int& x, int& y)
{
	x = _startTile.X;
	y = _startTile.Y;
}

void UGenericDungeon::GetGoalTile(int& x, int& y)
{
	x = _goalTile.X;
	y = _goalTile.Y;
}

int UGenericDungeon::GetDungeonWidth()
{
	return _dungeonWidth;
}

int UGenericDungeon::GetDungeonHeight()
{
	return _dungeonHeight;
}

void UGenericDungeon::GetAdjacentTileIndices(TArray<FIntVector>& AdjacentTileIndices, int x, int y)
{
	UE_LOG(DungeonGen, Log, TEXT("Getting Adjacent Tiles for %i, %i"), x, y)
		TArray< FIntVector> ret;
	for (int i = 0; i < 4; i++) {
		ret.Add(FIntVector( -1,-1, 0 ));
	}
	// North
	if (y < _dungeonHeight - 1) {
		ret[0].X = x + 1;
		ret[0].Y = y;
		UE_LOG(Dungeon, Warning, TEXT("### %f, %f"), ret[0].X, ret[0].Y)
	}
	// West
	if (x < _dungeonWidth - 1) {
		ret[3].X = x;
		ret[3].Y = y - 1;
		UE_LOG(Dungeon, Warning, TEXT("### %f, %f"), ret[3].X, ret[3].Y)
	}
	// South
	if (y >= 0) {
		ret[1].X = x - 1;
		ret[1].Y = y;
		UE_LOG(Dungeon, Warning, TEXT("### %f, %f"), ret[1].X, ret[1].Y)
	}
	// East
	if (x >= 0) {
		ret[2].X = x;
		ret[2].Y = y + 1;
		UE_LOG(Dungeon, Warning, TEXT("### %f, %f"), ret[2].X, ret[2].Y)
	}
}

void UGenericDungeon::GetAdjacentTileIndices(TArray<FIntVector>& AdjacentTileIndices, const FIntVector& originIndex)
{
	return GetAdjacentTileIndices(AdjacentTileIndices, originIndex.X, originIndex.Y);
}

void UGenericDungeon::GetAdjacentTiles(TArray<FGenericTile> AdjacentTiles, const FIntVector& originIndex)
{
	return GetAdjacentTiles(AdjacentTiles, originIndex.X, originIndex.Y);
}

void UGenericDungeon::GetAdjacentTiles(TArray<FGenericTile> AdjacentTiles, int x, int y)
{
	AdjacentTiles = TArray<FGenericTile>();
	TArray<FIntVector> adjacentIndices;
	GetAdjacentTileIndices(adjacentIndices, x, y);
	for (int i = 0; i < adjacentIndices.Num(); i++) {
		if (!IsOutOfBounds(adjacentIndices[i].X, IsOutOfBounds(adjacentIndices[i].Y))) {
			AdjacentTiles[i] = _dungeonArray[ConvertCoordToInt(adjacentIndices[i].X, adjacentIndices[i].Y)
			];
		}
		else {
			FGenericTile tile = FGenericTile();
			AdjacentTiles[i] = tile;
		}
	}
}


bool UGenericDungeon::GetTile(FGenericTile& tile, int x, int y)
{
	bool ret = true;
	if (!IsOutOfBounds(x, y)) {
		int index = ConvertCoordToInt(x, y);
		UE_LOG(Dungeon, Warning, TEXT("Getting tile %i, %i | index: %i"), x, y, index)
		tile = _dungeonArray[index];
	}
	else {
		UE_LOG(Dungeon, Error, TEXT("!! %i, %i is out of bounds!"), x, y)
			ret = false;
	}
	return ret;
}

bool UGenericDungeon::SetTile(int x, int y, bool North, bool South, bool East, bool West)
{
	bool ret = false;
	UE_LOG(Dungeon, Warning, TEXT("@ Setting %i, %i "), x, y)
		FGenericTile tile; // = FGenericTile();
	if(GetTile(tile, x, y)){
		tile.Void = true;
		tile.North = North;
		tile.South = South;
		tile.East = East;
		tile.West = West;
		ret = true;
	}

	UE_LOG(Dungeon, Warning, TEXT("@ Tile added."))
	return ret;
}
bool UGenericDungeon::SetTile(int x, int y, FGenericTile tile)
{
	bool ret = false;
	if (!IsOutOfBounds(x, y)) {
		ret = true;
		int c = ConvertCoordToInt(x, y);
		_dungeonArray[c] = tile;
	}

	UE_LOG(Dungeon, Warning, TEXT("@ Tile added."))
		return ret;
}

void UGenericDungeon::GetAllTiles(TArray<FGenericTile> &TileList)
{
	UE_LOG(Dungeon, Warning, TEXT("Getting _dungeonArray"))
		TileList = _dungeonArray;
}

void UGenericDungeon::ConvertIntToCoordinates(int i, int& x, int& y)
{
	y = i / _dungeonWidth;
	x = i - y * _dungeonWidth;
}

int UGenericDungeon::ConvertCoordToInt(int x, int y)
{
	return y * _dungeonWidth + x;;
}

int UGenericDungeon::ConvertCoordToIntF(FIntVector index)
{
	return index.Y * _dungeonWidth + index.X;
}

int UGenericDungeon::GetWidth()
{
	return _dungeonWidth;
}

int UGenericDungeon::GetHeight()
{
	return _dungeonHeight;
}

int UGenericDungeon::GetNumberOfTiles()
{
	return _dungeonArray.Num()+1;
}

void UGenericDungeon::Initialize() {
	UE_LOG(Dungeon, Warning, TEXT("Setting up Generic Dungeon."))
		//_dungeonArray = TArray<FGenericTile*>();
		UE_LOG(Dungeon, Warning, TEXT("_dungeonArray Num: %i"), _dungeonArray.Num())
		//_dungeonArray.SetNum(1, true);
		UE_LOG(Dungeon, Warning, TEXT("_dungeonArray Post Set 0 Num: %i"), _dungeonArray.Num())
}

FGenericTile FGenericTile::MakeCopy()
{
	FGenericTile ret;
	ret.North = North;
	ret.South = South;
	ret.East = East;
	ret.West = West;
	ret.Void = Void;
	return ret;
}
