
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

	TSoftObjectPtr<UWorld> worldToSpawn;

	switch (flags) {
		case 0 : // none
			worldToSpawn = RandomTile(Tileset->NoExit_Tiles);
			break;
		case NORTH : 
			worldToSpawn = RandomTile(Tileset->N_Tiles);
			break;
		case EAST: // East only
			worldToSpawn = RandomTile(Tileset->E_Tiles);
			break;
		case SOUTH: // South only
			worldToSpawn = RandomTile(Tileset->S_Tiles);
			break;
		case WEST: // West only
			worldToSpawn = RandomTile(Tileset->W_Tiles);
			break;
		case (NORTH|EAST):
			worldToSpawn = RandomTile(Tileset->NE_Tiles);
			break;
		case (NORTH|SOUTH):
			worldToSpawn = RandomTile(Tileset->NS_Tiles);
			break;
		case (NORTH|WEST):
			worldToSpawn = RandomTile(Tileset->NW_Tiles);
			break;
		case (EAST|SOUTH):
			worldToSpawn = RandomTile(Tileset->ES_Tiles);
			break;
		case (EAST|WEST):
			worldToSpawn = RandomTile(Tileset->EW_Tiles);
			break;
		case (SOUTH|WEST):
			worldToSpawn = RandomTile(Tileset->SW_Tiles);
			break;
		case (NORTH|EAST|SOUTH):
			worldToSpawn = RandomTile(Tileset->NES_Tiles);
			break;
		case (NORTH|EAST|WEST):
			worldToSpawn = RandomTile(Tileset->NEW_Tiles);
			break;
		case (NORTH|SOUTH|WEST):
			worldToSpawn = RandomTile(Tileset->NSW_Tiles);
			break;
		case (EAST|SOUTH|WEST):
			worldToSpawn = RandomTile(Tileset->ESW_Tiles);
			break;
		case (NORTH|EAST | SOUTH | WEST):
			worldToSpawn = RandomTile(Tileset->NESW_Tiles);
			break;
	}
}

TSoftObjectPtr<UWorld> UDungeonSpawner::RandomTile(TArray<TSoftObjectPtr<UWorld>> tilesetCollection)
{
	int size = tilesetCollection.Num();
	int randNum = FMath::RandRange(0, size);
	return tilesetCollection[randNum];
}

float UDungeonSpawner::percentLoadedLevels()
{
	return 0.0f;
}
