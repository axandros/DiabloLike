// Fill out your copyright notice in the Description page of Project Settings.

#include "GenericDungeon.h"
#include "DiabloLog.h"
#include "FVector2DInt.h"

DEFINE_LOG_CATEGORY(Dungeon);

UGenericDungeon::UGenericDungeon() {
	
	_dungeonArray = TArray<FGenericTile*>();
	_dungeonArray.Empty();
	_dungeonArray.Add(new FGenericTile);
}

/*
UGenericDungeon& UGenericDungeon::operator=(const UGenericDungeon& other)
{
	if (this != other) {
		_dungeonArray = other._dungeonArray;
		_dungeonWidth = other._dungeonWidth;
		_dungeonHeight = other._dungeonHeight;
		_startTile = other._startTile;
		_goalTile = other._goalTile;
	}
	return *this;
}
*/

FGenericTile* UGenericDungeon::operator[](FVector2DInt index)
{
	FGenericTile* ret = nullptr;
	if (!IsOutOfBounds(index)) {
		ret = _dungeonArray[ConvertCoordToInt(index.X, index.Y)];
	}
	return ret;
}
/*
FGenericTile& UGenericDungeon::operator[](int LengthIndex)
{
	FGenericTile ret = FGenericTile();
	if (!IsOutOfBounds(LengthIndex)) {
		ret = _dungeonArray[LengthIndex];
	}
	return ret;
}
*/

bool UGenericDungeon::IsOutOfBounds(FVector2DInt tileIndex)
{
	return IsOutOfBounds(int(tileIndex.X), int(tileIndex.Y));
}

bool UGenericDungeon::IsOutOfBounds(int X, int Y)
{
	bool Xzed = X >= 0;
	bool Yzed = Y >= 0;
	bool XTop = X < _dungeonWidth;
	bool YTop = Y < _dungeonHeight;
	bool ICheck = ConvertCoordToInt(X, Y) < _dungeonArray.Num();
	return !(Xzed && Yzed && XTop && YTop && ICheck);
}

bool UGenericDungeon::SetStartTile(const FVector2DInt& tileIndex)
{
	_startTile = tileIndex;
	return true;
}

bool UGenericDungeon::SetStartTile(int X, int Y)
{
	UE_LOG(Dungeon, Warning, TEXT("Setting Dungeon Start Tile: %i, %i"), X, Y)
	_startTile = FVector2DInt(X, Y);
	UE_LOG(Dungeon, Warning, TEXT("Dungeon Start Tile Set: %i, %i"), _startTile.X, _startTile.Y)
	return true;
}

bool UGenericDungeon::SetGoalTile(const FVector2DInt& tileIndex)
{
	UE_LOG(Dungeon, Warning, TEXT("Setting Dungeon Goal Tile: %i, %i"), tileIndex.X, tileIndex.Y)
	_goalTile = tileIndex;
	UE_LOG(Dungeon, Warning, TEXT("Dungeon Start Goal Set: %i, %i"), _goalTile.X, _goalTile.Y)
	return true;
}

bool UGenericDungeon::SetGoalTile(int X, int Y)
{
	return SetGoalTile(FVector2DInt(X, Y));
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

FVector2DInt UGenericDungeon::GetStartTile()
{
	return _startTile;
}

FVector2DInt UGenericDungeon::GetGoalTile()
{
	return _goalTile;
}

int UGenericDungeon::GetDungeonWidth()
{
	return _dungeonWidth;
}

int UGenericDungeon::GetDungeonHeight()
{
	return _dungeonHeight;
}

TArray<FVector2DInt> UGenericDungeon::GetAdjacentTileIndices(int x, int y)
{
	UE_LOG(DungeonGen, Log, TEXT("Getting Adjacent Tiles for %i, %i"), x, y)
		TArray< FVector2DInt> ret;
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

TArray<FVector2DInt> UGenericDungeon::GetAdjacentTileIndices(const FVector2DInt& originIndex)
{
	return GetAdjacentTileIndices(originIndex.X, originIndex.Y);
}

TArray<FGenericTile*> UGenericDungeon::GetAdjacentTiles(const FVector2DInt& originIndex)
{
	return GetAdjacentTiles(originIndex.X, originIndex.Y);
}

TArray<FGenericTile*> UGenericDungeon::GetAdjacentTiles(int x, int y)
{
	TArray<FVector2DInt> adjacentIndices = GetAdjacentTileIndices(x, y);
	TArray<FGenericTile*> ret = TArray<FGenericTile*>();
	ret.SetNum(4);
	for (int i = 0; i < adjacentIndices.Num(); i++) {
		if (!IsOutOfBounds(adjacentIndices[i])) {
			ret[i] = _dungeonArray[ConvertCoordToIntF(adjacentIndices[i])];
		}
		else {
			ret[i] = nullptr;
		}
	}
	return ret;
}

FGenericTile UGenericDungeon::GetTileReference(int x, int y)
{
	FGenericTile ret = *GetTile(x, y);
	return ret;
}

FGenericTile* UGenericDungeon::GetTile(int x, int y)
{
	FGenericTile* ret = nullptr;
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

FGenericTile* UGenericDungeon::GetTile(FVector2DInt coordinates)
{
	return GetTile(coordinates.X, coordinates.Y);
}

bool UGenericDungeon::SetTile(int x, int y, bool North, bool South, bool East, bool West)
{
	UE_LOG(Dungeon, Warning, TEXT("@ Setting %i, %i "), x, y)
	FGenericTile* tile = GetTile(x, y);
	UE_LOG(Dungeon, Warning, TEXT("@ Got Tile"))
	if (tile != nullptr) {
		tile->Void = true;
		tile->North = North;
		tile->South = South;
		tile->East = East;
		tile->West = West;
		//tile = new FGenericTile();
		UE_LOG(Dungeon, Warning, TEXT("@ Tile is null?"))
		//	if (tile == nullptr) {
		//		UE_LOG(Dungeon, Error, TEXT("@ Tile was NOT created successfully"))
		//	}
		}

	UE_LOG(Dungeon, Warning, TEXT("@ Tile added."))
	return true;
}

TArray<FGenericTile*> UGenericDungeon::GetAllTiles()
{
	UE_LOG(Dungeon, Warning, TEXT("Getting _dungeonArray"))
	return _dungeonArray;
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

int UGenericDungeon::ConvertCoordToIntF(FVector2DInt index)
{
	return index.Y * _dungeonWidth + index.X;
}

bool UGenericDungeon::GetTileArray(TArray<FGenericTile>& OutArray)
{
	
	UE_LOG(Dungeon, Warning, TEXT("Entering GetTileArray"))
	bool ret = false;
	UE_LOG(Dungeon, Warning, TEXT("Getting Tile Array for Blueprints"))
	OutArray = TArray<FGenericTile>();
	/*
	UE_LOG(Dungeon, Warning, TEXT("Getting Tile Array for Blueprints"))
	for (int i = 0; i < _dungeonArray.Num(); i++) {
		ret = true;
		UE_LOG(Dungeon, Warning, TEXT("Adding array item %i"), i)
			if (_dungeonArray[i] == nullptr) {
				OutArray.Add(FGenericTile());
			}
			else {
				try {
					FGenericTile* item = _dungeonArray[i];
					OutArray.Add(item->MakeCopy());
				}
				catch (int e) {
					UE_LOG(Dungeon, Warning, TEXT("Caught Exception %i"), e)
				}
			}
	}
	UE_LOG(Dungeon, Warning, TEXT("Returning Array"))
	*/
	return ret;
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
