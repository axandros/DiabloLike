
#include "GenericDungeon.h"
#include "DungeonSpawner.h"

UDungeonSpawner::UDungeonSpawner()
{
}

UDungeonSpawner::~UDungeonSpawner()
{
}

void UDungeonSpawner::SpawnDungeon(FVector StartLocation)
{
}

void UDungeonSpawner::SpawnDungeon(FVector StartLocation, FGenericDungeon* dungeon)
{
}

FGenericDungeon* UDungeonSpawner::GetDungeon()
{
	return _dungeon;
}

void UDungeonSpawner::SetDungeon(FGenericDungeon* dungeon)
{
}

void UDungeonSpawner::SpawnTile(FGenericTile tile, int gridX, int gridY)
{
}

TSoftObjectPtr<UWorld> UDungeonSpawner::RandomTile(TArray<TSoftObjectPtr<UWorld>> tilesetCollection)
{
	return TSoftObjectPtr<UWorld>();
}

float UDungeonSpawner::percentLoadedLevels()
{
	return 0.0f;
}
