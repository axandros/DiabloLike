// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GenericDungeon.h"
#include "SimpleDungeonDesigner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIABLOLIKE_API USimpleDungeonDesigner : public UObject
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable)
		static void MakeDungeon(UGenericDungeon*& dungeon);

	UFUNCTION(BlueprintCallable)
		static void SpelunkyWander(int dimensions,UGenericDungeon*& dungeon);

private:
	static bool SpelunkyUp(UGenericDungeon* dungeon, int xPos, int yPos);
	static bool SpelunkyRight(UGenericDungeon* dungeon, int xPos, int yPos);
	static bool SpelunkyDown(UGenericDungeon* dungeon, int xPos, int yPos);
};
