// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericDungeon.h"
#include "DiabloLog.h"
#include "FVector2DInt.h"

DEFINE_LOG_CATEGORY(Dungeon);

UGenericDungeon::UGenericDungeon() {
	
	_dungeonArray = TArray<FGenericTile>();
	_dungeonArray.Empty();
}

bool UGenericDungeon::IsOutOfBounds(int X, int Y) const
{
	bool Xzed = X >= 0;
	bool Yzed = Y >= 0;
	bool XTop = X < _dungeonWidth;
	bool YTop = Y < _dungeonHeight;
	bool ICheck = ConvertCoordToInt(X, Y) < _dungeonArray.Num();
	return !(Xzed && Yzed && XTop && YTop && ICheck);
}

bool UGenericDungeon::SetStartTile(int X, int Y)
{
	_startTile[0] = X;
	_startTile[1] = Y;
	return true;
}

bool UGenericDungeon::SetGoalTile(int X, int Y)
{
	_goalTile[0] = X;
	_goalTile[1] = Y;
	return true;
}

bool UGenericDungeon::SetDungeonDimensions(int width, int height)
{
	UE_LOG(Dungeon, Warning, TEXT("Setting dungeon dimensions: %i, %i"), width, height)
	bool ret = false;
	FString retString = "false";
	if (_dungeonArray.Num() == 0) {
		UE_LOG(Dungeon, Warning, TEXT("Setting is allowed."))
		_dungeonWidth = width;
		_dungeonHeight = height;
		_dungeonArray.SetNum(width * height);
		ret = true;
		retString = "true";

		_dungeonArray.SetNum(_dungeonWidth * _dungeonHeight);

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

bool UGenericDungeon::SetDungeonDimensions(int widthAndHeight)
{
	return SetDungeonDimensions(widthAndHeight, widthAndHeight);
}

void UGenericDungeon::GetStartTileCoord(int& x, int& y) const
{
	x = _startTile[0];
	y = _startTile[1];
}

void UGenericDungeon::GetGoalTileCoord(int& x, int& y) const
{
	x = _goalTile[0];
	y = _goalTile[1];
}

TArray<FVector2D> UGenericDungeon::GetAdjacentTileIndices(int x, int y) const
{
	UE_LOG(DungeonGen, Log, TEXT("Getting Adjacent Tiles for %i, %i"), x, y)
		TArray< FVector2D> ret;
	for (int i = 0; i < 4; i++) {
		ret.Add({ -1,-1 });
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
	return ret;
}

TArray<FGenericTile> UGenericDungeon::GetAdjacentTiles(int x, int y)
{
	TArray<FVector2D> adjacentIndices = GetAdjacentTileIndices(x, y);
	TArray<FGenericTile> ret = TArray<FGenericTile>();
	ret.SetNum(4);
	for (int i = 0; i < adjacentIndices.Num(); i++) {
		if (!IsOutOfBounds(adjacentIndices[i].X, adjacentIndices[i].Y)) {
			ret[i] = _dungeonArray[ConvertCoordToInt(adjacentIndices[i].X, adjacentIndices[i].Y)];
		}
		else {
			ret[i] = FGenericTile();
		}
	}
	return ret;
}

FGenericTile UGenericDungeon::GetTile(int x, int y) const
{
	FGenericTile ret;
	if (!IsOutOfBounds(x, y)) {
		int index = ConvertCoordToInt(x, y);
		UE_LOG(Dungeon, Warning, TEXT("Getting tile %i, %i | index: %i"), x, y, index)
		ret = _dungeonArray[index];
	}
	else {
		UE_LOG(Dungeon, Error, TEXT("!! %i, %i is out of bounds!"), x, y)
	}
	UE_LOG(Dungeon, Warning, TEXT("Returning Tile"))
	return ret;
}

bool UGenericDungeon::SetTile(int x, int y, FGenericTile tile)
{
	bool ret = false;
	if (!IsOutOfBounds(x, y)) {
		_dungeonArray[ConvertCoordToInt(x, y)] = tile;
		ret = true;
	}

	return ret;;
}

TArray<FGenericTile> UGenericDungeon::GetTileArray() const
{
	TArray<FGenericTile> ret = TArray<FGenericTile>();
	for (int i = 0; i < _dungeonArray.Num(); i++) {
		ret.Add(_dungeonArray[i]);
	}
	return ret;
}

void UGenericDungeon::ConvertIntToCoordinates(int i, int& x, int& y)
{
	y = i / _dungeonWidth;
	x = i - y * _dungeonWidth;
}

int UGenericDungeon::ConvertCoordToInt(int x, int y) const
{
	return y * _dungeonWidth + x;;
}

int UGenericDungeon::GetWidth() const
{
	return _dungeonWidth;
}

int UGenericDungeon::GetHeight() const
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
