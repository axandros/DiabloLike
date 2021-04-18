

#pragma once

#include "CoreMinimal.h"
#include "GenericDungeon.h"
#include "DungeonSpawner.generated.h"

//class UGenericDungeon;
class UTilesetAsset;
//struct FGenericTile;
class ULevelStreamingDynamic;

/**
 * 
 */
UCLASS(Blueprintable)
class DIABLOLIKE_API ADungeonSpawner : public AActor
{
public:
	GENERATED_BODY()
	ADungeonSpawner();
	~ADungeonSpawner();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SpawnDungeon(FVector StartLocation, bool surroundWithEmpty = false);
	void SpawnDungeon(FVector StartLocation, UGenericDungeon* dungeon, bool surroundWithEmpty = false);

	UFUNCTION(BlueprintCallable, Category = "Spawner")
		UGenericDungeon* GetDungeon();
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SetDungeon(UGenericDungeon* dungeon);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTilesetAsset* Tileset;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TileSize = 1000.0f;

	UFUNCTION(BlueprintImplementableEvent)
		void AllLevelsLoaded();

	// These two should be BlueprintNativeEvent, but that won't compile.
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnTile(FGenericTile tile, int gridX, int gridY);
	UFUNCTION(BlueprintImplementableEvent)
		void AreAllLevelsLoaded();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SurroundWithEmpty();

	UFUNCTION(BlueprintPure, Category = "Spawner")
		float PercentLevelsLoaded();

private:
	UGenericDungeon* _dungeon;

protected:
	float percentLoadedLevels();
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ULevelStreamingDynamic*> levelsLoading;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector SpawnLocation;

	UFUNCTION(BlueprintCallable)
	TSoftObjectPtr<UWorld> RandomTile(TArray<TSoftObjectPtr<UWorld>> tilesetCollection);
};
