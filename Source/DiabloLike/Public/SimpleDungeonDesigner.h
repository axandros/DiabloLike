// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GenericDungeon.h"
#include "SimpleDungeonDesigner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIABLOLIKE_API USimpleDungeonDesigner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimpleDungeonDesigner();

	UFUNCTION(BlueprintCallable)
		UGenericDungeon* GetDungeon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UGenericDungeon* _dungeon;

	UFUNCTION(BlueprintCallable)
	void MakeDungeon();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
