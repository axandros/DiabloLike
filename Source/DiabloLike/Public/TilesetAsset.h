

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TilesetAsset.generated.h"

/**
 * 
 */
UCLASS()
class DIABLOLIKE_API UTilesetAsset : public UPrimaryDataAsset //UDataAsset
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "0 Exits")
		TArray<TSoftObjectPtr<UWorld>> NoExit_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "1 Exit")
		TArray<TSoftObjectPtr<UWorld>> N_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "1 Exit")
		TArray<TSoftObjectPtr<UWorld>> E_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "1 Exit")
		TArray<TSoftObjectPtr<UWorld>> S_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "1 Exit")
		TArray<TSoftObjectPtr<UWorld>> W_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> NE_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> NS_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> NW_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> ES_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> EW_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "2 Exits")
		TArray<TSoftObjectPtr<UWorld>> SW_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "3 Exits")
		TArray<TSoftObjectPtr<UWorld>> NES_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "3 Exits")
		TArray<TSoftObjectPtr<UWorld>> NEW_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "3 Exits")
		TArray<TSoftObjectPtr<UWorld>> NSW_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "3 Exits")
		TArray<TSoftObjectPtr<UWorld>> ESW_Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "4 Exits")
		TArray<TSoftObjectPtr<UWorld>> NESW_Tiles;
};
