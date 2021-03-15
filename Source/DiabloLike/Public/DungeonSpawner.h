

#pragma once

#include "CoreMinimal.h"
#include "DungeonSpawner.generated.h"

class UGenericDungeon;
class UTilesetAsset;
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
	void SpawnDungeon(FVector StartLocation, UGenericDungeon* dungeon);

	UFUNCTION(BlueprintCallable, Category = "Spawner")
		UGenericDungeon* GetDungeon();
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SetDungeon(UGenericDungeon* dungeon);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTilesetAsset* Tileset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TileSize;

private:
	UGenericDungeon* _dungeon;
	FVector SpawnLocation;

	void SpawnTile(FGenericTile tile, int gridX, int gridY);
	TSoftObjectPtr<UWorld> RandomTile(TArray<TSoftObjectPtr<UWorld>> tilesetCollection);
	float percentLoadedLevels();
};
