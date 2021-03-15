
#include "DungeonSpawner.h"
#include "GenericDungeon.h"
#include "TilesetAsset.h"

UDungeonSpawner::UDungeonSpawner()
{
}

UDungeonSpawner::~UDungeonSpawner()
{
}

void UDungeonSpawner::SpawnDungeon(FVector StartLocation)
{
	SpawnLocation = StartLocation;
	if (Tileset != NULL) {
		int dungeonSize = _dungeon->GetNumberOfTiles();
		TArray<FGenericTile> tiles = TArray<FGenericTile>();
		_dungeon->GetAllTiles(tiles);
		for (int index = 0; index < dungeonSize; index++) {
			int x, y = 0;
			_dungeon->ConvertIntToCoordinates(index, x, y);
			SpawnTile(tiles[index], x, y);
		}
	}
}

void UDungeonSpawner::SpawnDungeon(FVector StartLocation, UGenericDungeon* dungeon)
{
	SetDungeon(dungeon);
	SpawnDungeon(StartLocation);
}

UGenericDungeon* UDungeonSpawner::GetDungeon()
{
	return _dungeon;
}

void UDungeonSpawner::SetDungeon(UGenericDungeon* dungeon)
{
	if (dungeon != NULL) { _dungeon = dungeon; }
}

void UDungeonSpawner::SpawnTile(FGenericTile tile, int gridX, int gridY)
{
	FVector worldPosition = FVector(gridX + TileSize, gridY + TileSize, 0);
	worldPosition += SpawnLocation;
	unsigned int flags = tile.GetExitFlags();
	switch (flags) {
		case 0 : // none
			break;
		case 0b01 : // North only
			break;
		case 0b010: // East only
			break;
		case 0b0100: // South only
			break;
		case 0b01000: // West only
			break;

	}
}

TSoftObjectPtr<UWorld> UDungeonSpawner::RandomTile(TArray<TSoftObjectPtr<UWorld>> tilesetCollection)
{
	return TSoftObjectPtr<UWorld>();
}

float UDungeonSpawner::percentLoadedLevels()
{
	return 0.0f;
}
