// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleDungeonDesigner.h"


void USimpleDungeonDesigner::MakeDungeon(UGenericDungeon*& _dungeon) {
	_dungeon = NewObject<UGenericDungeon>();//CreateDefaultSubobject<UGenericDungeon>(TEXT("The Dungeon"));
	_dungeon->Initialize();
	_dungeon->SetDungeonDimensions(5, 5);

	UE_LOG(LogTemp, Warning, TEXT("Simple Designer: Dimensions Set"))
		_dungeon->SetStartTile(0, 0);
	_dungeon->SetGoalTile(0, 0);

	_dungeon->SetTile(0, 0, false, false, true, false);
	_dungeon->SetTile(0, 1, true, false, false, true);
	_dungeon->SetTile(1, 1, true, true, true, false);
	_dungeon->SetTile(2, 1, false, true, true, false);
	_dungeon->SetTile(2, 2, false, false, true, true);
	_dungeon->SetTile(2, 3, false, false, true, true);
	_dungeon->SetTile(2, 4, true, false, false, true);
	_dungeon->SetTile(3, 4, true, true, false, false);
	_dungeon->SetTile(4, 4, false, true, false, false);

	_dungeon->SetStartTile(0, 0);
	_dungeon->SetGoalTile(4, 4);
}

void USimpleDungeonDesigner::SpelunkyWander(int dimensions, UGenericDungeon*& _dungeon) {
	_dungeon = NewObject<UGenericDungeon>();
	_dungeon->Initialize();
	_dungeon->SetDungeonDimensions(5, 5);
	_dungeon->FillWithEmptyTiles();
	
	// Define local variables
	int xPos, yPos = 0;

	// Choose the Start Tile
	xPos = FMath::RandRange(0,dimensions);
	_dungeon->SetStartTile(xPos, 0);
	
	while (yPos < dimensions) {
		int direction = FMath::RandRange(0, 2);
		switch (direction) {
		case 0:
			if (SpelunkyUp(_dungeon, xPos, yPos))
			{
				xPos += 1;
			}
			break;
		case 1:
			SpelunkyRight(_dungeon, xPos, yPos);
			yPos += 1;
			break;
		case 2:
			if (SpelunkyDown(_dungeon, xPos, yPos)) {
				xPos -= 1;
			}
			break;
		}
	}
	
	_dungeon->SetGoalTile(xPos, yPos-1);
	
}

bool USimpleDungeonDesigner::SpelunkyUp(UGenericDungeon* dungeon, int xPos, int yPos)
{
	bool ret = false;
	if (!dungeon->IsOutOfBounds(xPos+1, yPos)) {
		FGenericTile tile;
		// This tile
		dungeon->GetTile(tile, xPos, yPos);
		tile.North = true;
		tile.Void = false;
		dungeon->SetTile(xPos, yPos, tile);

		// The neighbor 
		dungeon->GetTile(tile, xPos+1, yPos);
		tile.South = true;
		tile.Void = false;
		dungeon->SetTile(xPos+1, yPos, tile);
		ret = true;
	}
	return ret;
}

bool USimpleDungeonDesigner::SpelunkyRight(UGenericDungeon* dungeon, int xPos, int yPos)
{
	bool ret = false;
	if (!dungeon->IsOutOfBounds(xPos, yPos+1)) {
		FGenericTile tile;
		// This tile
		dungeon->GetTile(tile, xPos, yPos);
		tile.East = true;
		tile.Void = false;
		dungeon->SetTile(xPos, yPos, tile);

		// The neighbor 
		dungeon->GetTile(tile, xPos , yPos+1);
		tile.West = true;
		tile.Void = false;
		dungeon->SetTile(xPos , yPos+1, tile);
		ret = true;

		ret = true;
	}
	return ret;
}

bool USimpleDungeonDesigner::SpelunkyDown(UGenericDungeon* dungeon, int xPos, int yPos)
{
	bool ret = false;
	if (!dungeon->IsOutOfBounds(xPos-1, yPos)) {
		FGenericTile tile;
		// This tile
		dungeon->GetTile(tile, xPos, yPos);
		tile.South = true;
		tile.Void = false;
		dungeon->SetTile(xPos, yPos, tile);

		// The neighbor 
		dungeon->GetTile(tile, xPos - 1, yPos);
		tile.North = true;
		tile.Void = false;
		dungeon->SetTile(xPos - 1, yPos, tile);
		ret = true;
	}
	return ret;
}
