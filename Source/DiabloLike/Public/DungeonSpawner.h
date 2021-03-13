

#pragma once

#include "CoreMinimal.h"
#include "DungeonSpawner.generated.h"

class FGenericDungeon;
struct FGenericTile;

/**
 * 
 */
UCLASS(Blueprintable)
class DIABLOLIKE_API UDungeonSpawner : public UObject
{
public:
	GENERATED_BODY()
	UDungeonSpawner();
	~UDungeonSpawner();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnDungeon(FVector StartLocation);
	void SpawnDungeon(FVector StartLocation, FGenericDungeon* dungeon);

	FGenericDungeon* GetDungeon();
	void SetDungeon(FGenericDungeon* dungeon);

private:
	FGenericDungeon* _dungeon;

	void SpawnTile(FGenericTile tile, int gridX, int gridY);
	TSoftObjectPtr<UWorld> RandomTile(TArray<TSoftObjectPtr<UWorld>> tilesetCollection);
	float percentLoadedLevels();
};
