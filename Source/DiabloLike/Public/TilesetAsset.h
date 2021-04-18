

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TilesetAsset.generated.h"

/** Stores lists of levels for the 16 cardinal direction combinations a tile can go. */
UCLASS()
class DIABLOLIKE_API UTilesetAsset : public UPrimaryDataAsset //UDataAsset
{
public:
	GENERATED_BODY()
	/** World tiles with no exits */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "0 Exits")
		TArray<TSoftObjectPtr<UWorld>> NoExit_Tiles;
	/** World tiles with one exit to the North */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "1 Exit")
		TArray<TSoftObjectPtr<UWorld>> N_Tiles;
	/** World tiles with one exit to the East */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "1 Exit")
		TArray<TSoftObjectPtr<UWorld>> E_Tiles;
	/** World tiles with one exit to the South */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "1 Exit")
		TArray<TSoftObjectPtr<UWorld>> S_Tiles;
	/** World tiles with one exit to the West */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "1 Exit")
		TArray<TSoftObjectPtr<UWorld>> W_Tiles;

	/** World tiles with two exits to the North and East */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> NE_Tiles;
	/** World tiles with two exits to the North and South */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> NS_Tiles;
	/** World tiles with two exits to the North and West */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> NW_Tiles;
	/** World tiles with two exits to the East and South */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> ES_Tiles;
	/** World tiles with two exits to the East and West */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> EW_Tiles;
	/** World tiles with two exits to the South and West */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> SW_Tiles;

	/** World tiles with three exits to the North, East, and South */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "3 Exits")
		TArray<TSoftObjectPtr<UWorld>> NES_Tiles;
	/** World tiles with three exits to the North, East, and West */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "3 Exits")
		TArray<TSoftObjectPtr<UWorld>> NEW_Tiles;
	/** World tiles with three exits to the North, South, and West */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "3 Exits")
		TArray<TSoftObjectPtr<UWorld>> NSW_Tiles;
	/** World tiles with three exits to the East, South, and West */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "3 Exits")
		TArray<TSoftObjectPtr<UWorld>> ESW_Tiles;

	/** World tiles with all four exits to the North, East, South, and West */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "4 Exits")
		TArray<TSoftObjectPtr<UWorld>> NESW_Tiles;
};
