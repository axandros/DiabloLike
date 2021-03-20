
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
	const int NORTH = FGenericTile::fNORTH;
	const int EAST = FGenericTile::fEAST;
	const int SOUTH = FGenericTile::fSOUTH;
	const int WEST = FGenericTile::fWEST;

	switch (flags) {
		case 0 : // none
			break;
		case NORTH : 
			break;
		case EAST: // East only
			break;
		case SOUTH: // South only
			break;
		case WEST: // West only
			break;
		case (NORTH|EAST):
			break;
		case (NORTH|SOUTH):
			break;
		case (NORTH|WEST):
			break;
		case (EAST|SOUTH):
			break;
		case (EAST|WEST):
			break;
		case (SOUTH|WEST):
			break;
		case (NORTH|EAST|SOUTH):
			break;
		case (NORTH|EAST|WEST):
			break;
		case (NORTH|SOUTH|WEST):
			break;
		case (EAST|SOUTH|WEST):
			break;
		case (NORTH|EAST | SOUTH | WEST):
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
