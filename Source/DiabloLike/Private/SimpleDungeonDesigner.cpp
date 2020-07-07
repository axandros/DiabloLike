// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleDungeonDesigner.h"

// Sets default values for this component's properties
USimpleDungeonDesigner::USimpleDungeonDesigner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_dungeon = CreateDefaultSubobject<UGenericDungeon>(TEXT("The Dungeon"));

	// ...
}


// Called when the game starts
void USimpleDungeonDesigner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FString compileDate = __DATE__;
	FString compileTime = __TIME__;
	UE_LOG(LogTemp, Warning, TEXT("Built %s %s"), *compileDate, *compileTime)

		if (_dungeon == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("Why is _dungron a nullptr?"))
		}
	MakeDungeon();
	UE_LOG(LogTemp, Warning, TEXT("Make Dungeon done."))
}


// Called every frame
void USimpleDungeonDesigner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USimpleDungeonDesigner::MakeDungeon() {
	
	_dungeon->Initialize();
	_dungeon->SetDungeonDimensions(5);
	
	UE_LOG(LogTemp, Warning, TEXT("Dimensions Set"))
	_dungeon->SetStartTile(0, 0);
	_dungeon->SetGoalTile(0, 0);
	
	/*
	_dungeon->SetTile(0, 0, false, false, true, false);
	_dungeon->SetTile(0, 1, true, false, false, true);
	_dungeon->SetTile(1, 1, true, true, true, false);
	_dungeon->SetTile(2, 1, false, true, true, false);
	_dungeon->SetTile(2, 2, false, false, true, true);
	_dungeon->SetTile(2, 3, false, false, true, true);
	_dungeon->SetTile(2, 4, true, false, false, true);
	_dungeon->SetTile(3, 4, true, true, false, false);
	_dungeon->SetTile(4, 4, false, true, false, false);
	*/
}

UGenericDungeon* USimpleDungeonDesigner::GetDungeon() {
	return _dungeon;
}