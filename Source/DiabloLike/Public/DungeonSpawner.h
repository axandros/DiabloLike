

#pragma once

#include "CoreMinimal.h"
#include "GenericDungeon.h"
#include "DungeonSpawner.generated.h"

/// Note: Would have been a UObject, but needs to be an actor for level streaming.

class UTilesetAsset;
class ULevelStreamingDynamic;

/** Begins level streaming based on a given FTileset and UGenericDungeon */
UCLASS(Blueprintable)
class DIABLOLIKE_API ADungeonSpawner : public AActor
{
public:
	GENERATED_BODY()
	ADungeonSpawner();
	~ADungeonSpawner();

	/** Begin level streaming process, with 0,0 of the dungeon at StartLocation. */
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SpawnDungeon(FVector StartLocation, bool surroundWithEmpty = false);

	/** Begin level streaming process for the input dungeon, with 0,0 of the dungeon at StartLocation. 
	    Sets the dungeon as the internal dungeon for references.*/
	void SpawnDungeon(FVector StartLocation, UGenericDungeon* dungeon, bool surroundWithEmpty = false);

	/** Returns a pointer to the dungeon being used to generate dungeons. */
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		UGenericDungeon* GetDungeon();
	/** Set the dungeon for streaming. */
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SetDungeon(UGenericDungeon* dungeon);

	/** The tileset to use for level streaming. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTilesetAsset* Tileset;

	/** The size of the tiles for the tileset in Unreal Meters. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TileSize = 1000.0f;

	

	/** Streams in no exit worlds in the area around the dungeon. */
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SurroundWithEmpty();

	/** Returns true if all levels created by this spawner have finished loading. */
	UFUNCTION(BlueprintPure, Category = "Spawner")
		bool AreAllLevelsLoaded();

	/** Return a percentage of the number of levels that have loaded. */
	UFUNCTION(BlueprintPure, Category = "Spawner")
		float PercentLevelsLoaded();

private:
	UGenericDungeon* _dungeon;

protected:
	/** Performs blueprint actions for when all levels have finished loading in.  Must be called in blueprint. */
	UFUNCTION(BlueprintImplementableEvent)
		void AllLevelsLoaded();

	/** Spawn a random world object at the grid location x,y based on the input tile. */
	UFUNCTION(BlueprintImplementableEvent)
		void SpawnTile(FGenericTile tile, int gridX, int gridY);

	/** An array to store references to the levels that have begun streaming. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ULevelStreamingDynamic*> levelsLoading;
	/** The world location where 0,0 will be streamed in. Set by methods. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector SpawnLocation;

	/** Return a random world reference from the list of world references. */
	UFUNCTION(BlueprintCallable)
	TSoftObjectPtr<UWorld> RandomTile(TArray<TSoftObjectPtr<UWorld>> tilesetCollection);
};
