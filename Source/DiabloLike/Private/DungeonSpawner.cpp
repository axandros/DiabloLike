
#include "DungeonSpawner.h"
#include "GenericDungeon.h"
#include "TilesetAsset.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/World.h"

ADungeonSpawner::ADungeonSpawner()
{
	levelsLoading = TArray<ULevelStreamingDynamic*>();
}

ADungeonSpawner::~ADungeonSpawner()
{
}

void ADungeonSpawner::SpawnDungeon(FVector StartLocation, bool surroundWithEmpty)
{
	SpawnLocation = StartLocation;
	if (Tileset != NULL) {
		int dungeonSize = _dungeon->GetNumberOfTiles();
		TArray<FGenericTile> tiles = TArray<FGenericTile>();
		_dungeon->GetAllTiles(tiles);
		for (int index = 0; index < dungeonSize-1; index++) {
			int x, y = 0;
			_dungeon->ConvertIntToCoordinates(index, x, y);
			SpawnTile(tiles[index], x, y);
		}
		if (surroundWithEmpty) {
			SurroundWithEmpty();
		}
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("DungeonSpawner: No Tileset Set"))
	}
}

void ADungeonSpawner::SpawnDungeon(FVector StartLocation, UGenericDungeon* dungeon, bool surroundWithEmpty)
{
	SetDungeon(dungeon);
	SpawnDungeon(StartLocation, surroundWithEmpty);
}

UGenericDungeon* ADungeonSpawner::GetDungeon()
{
	return _dungeon;
}

void ADungeonSpawner::SetDungeon(UGenericDungeon* dungeon)
{
	UE_LOG(LogTemp, Log, TEXT("DungeonSpawner: Setting dungeon."))
	if (dungeon != NULL) { _dungeon = dungeon; }
	else{UE_LOG(LogTemp, Error, TEXT("DungeonSpawner: Attempted to set dungeon to null value.")) }
}
/*
void ADungeonSpawner::SpawnTile(FGenericTile tile, int gridX, int gridY)
{
	if (Tileset != NULL) {
		FVector worldPosition = FVector(gridX + TileSize, gridY + TileSize, 0);
		worldPosition += SpawnLocation;
		unsigned int flags = tile.GetExitFlags();
		const int NORTH = FGenericTile::fNORTH;
		const int EAST = FGenericTile::fEAST;
		const int SOUTH = FGenericTile::fSOUTH;
		const int WEST = FGenericTile::fWEST;

		TSoftObjectPtr<UWorld> worldToSpawn;

		switch (flags) {
		case 0: // none
			worldToSpawn = RandomTile(Tileset->NoExit_Tiles);
			break;
		case NORTH:
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
		case (NORTH | EAST):
			worldToSpawn = RandomTile(Tileset->NE_Tiles);
			break;
		case (NORTH | SOUTH):
			worldToSpawn = RandomTile(Tileset->NS_Tiles);
			break;
		case (NORTH | WEST):
			worldToSpawn = RandomTile(Tileset->NW_Tiles);
			break;
		case (EAST | SOUTH):
			worldToSpawn = RandomTile(Tileset->ES_Tiles);
			break;
		case (EAST | WEST):
			worldToSpawn = RandomTile(Tileset->EW_Tiles);
			break;
		case (SOUTH | WEST):
			worldToSpawn = RandomTile(Tileset->SW_Tiles);
			break;
		case (NORTH | EAST | SOUTH):
			worldToSpawn = RandomTile(Tileset->NES_Tiles);
			break;
		case (NORTH | EAST | WEST):
			worldToSpawn = RandomTile(Tileset->NEW_Tiles);
			break;
		case (NORTH | SOUTH | WEST):
			worldToSpawn = RandomTile(Tileset->NSW_Tiles);
			break;
		case (EAST | SOUTH | WEST):
			worldToSpawn = RandomTile(Tileset->ESW_Tiles);
			break;
		case (NORTH | EAST | SOUTH | WEST):
			worldToSpawn = RandomTile(Tileset->NESW_Tiles);
			break;
		}

		FVector Location = FVector(0, 0, 0);
		FRotator Rotation = FRotator();
		bool bOutSuccess = true;
		if (worldToSpawn.IsValid()) {
			ULevelStreamingDynamic* level = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(GetWorld(), worldToSpawn,
				Location, Rotation, bOutSuccess);

			UE_LOG(LogTemp, Warning, TEXT("Adding tile to world."))

				if (level) {
					level->OnLevelLoaded.AddDynamic(this, &ADungeonSpawner::AreAllLevelsLoaded);
					levelsLoading.Add(level);
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Tile failed to be created."))
				}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("World To Load not valid"))
		}
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Tileset not set."))
	}
	
}*/

TSoftObjectPtr<UWorld> ADungeonSpawner::RandomTile(TArray<TSoftObjectPtr<UWorld>> tilesetCollection)
{
	int size = tilesetCollection.Num();
	int randNum = FMath::RandRange(0, size-1);
	UE_LOG(LogTemp, Warning, TEXT("TilesetCollection Size: %i, Rand: %i"),size, randNum );
	TSoftObjectPtr<UWorld> ret = tilesetCollection[randNum];
	if (!ret.IsValid()) {
		UE_LOG(LogTemp, Warning, TEXT("RandomTile: World not valid"))
	}
	return ret;
}

void ADungeonSpawner::SurroundWithEmpty()
{
	int width = _dungeon->GetWidth();
	int height = _dungeon->GetHeight();
	FGenericTile emptyTile = FGenericTile();
	emptyTile.Void = false;

	// Do the East/West Edges and the four corners.
	for (int x = -1; x < height + 1; x++) {
		SpawnTile(emptyTile, x, -1);
		SpawnTile(emptyTile, x, width);
	}

	// Do the North/South Edges
	for (int y = 0; y < width; y++) {
		SpawnTile(emptyTile, -1, y);
		SpawnTile(emptyTile,height, y);
	}
}

float ADungeonSpawner::percentLoadedLevels()
{
	int loaded = 0;
	int num = levelsLoading.Num();
	for (int i = 0; i < num; i++) {
		ULevelStreamingDynamic* level = levelsLoading[1];
		if (level->IsLevelLoaded()) {
			loaded++;
		}
	}
	return float(loaded)/ float(num);
}

/*
void ADungeonSpawner::AreAllLevelsLoaded()
{
	UE_LOG(LogTemp, Warning, TEXT("Called are all levels loaded"));
	bool levelsLoaded = true;
	int num = levelsLoading.Num();
	for (int i = 0; i < num && levelsLoaded; i++) {
		//(ULevelStreamingDynamic in levelsLoading)
		ULevelStreamingDynamic* level = levelsLoading[i];
		if (! level->IsLevelLoaded()) {
			levelsLoaded = false;
		}
	}

	if (levelsLoaded) {
		AllLevelsLoaded();
	}

	return;
}
*/
//void ADungeonSpawner::AllLevelsLoaded() {}

float ADungeonSpawner::PercentLevelsLoaded() {
	int numOfLevels = levelsLoading.Num();
	int numLoaded = 0;
	for (int i = 0; i < numOfLevels; i++) {
		if (levelsLoading[i]->IsLevelLoaded()) {
			numLoaded++;
		}
	}

	
	float percent = 0;
	if (numOfLevels != 0) {
		percent = (float)numLoaded / (float)numOfLevels;
	}
		UE_LOG(LogTemp, Warning, TEXT("Num Levels: %i | Num Loaded: %i | Percent Loaded: %f"), numOfLevels, numLoaded, percent)

	return percent;
}