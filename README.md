 DiabloLike
A Diablo-like Map generator.  A learning project in procedural generation and level design.

# Technologies
* Unreal Engine 4.25
* C++

## Requirements
If you just want to look through blueprints then you can do that, but to see the visuals you'll need [Synty Studio's](https://www.syntystudios.com/) Adventure and Knight packages in the Content/Polygon/ directory
and the free [Water Planes](https://www.unrealengine.com/marketplace/en-US/product/water-planes) from Epic Games added to the project.
I do not have the right to distribute these assets.
To play the game in its current form, please download it from my [itch.io page](https://axandros.itch.io/diablo-like-level-generator).

## How it works
UGenericTile is a custom UStruct structure that has booleans tracking exits in the four cardinal directions, as well as an unused Void boolean to mark whether it should be rendered or not.
These custom c++ structs are integrated into the engine's API so they can be exposed to Blueprints.

UGenericDungeon is an unused c++ class to act as a larger container for managing the tiles.  Unfortunately, due to the way Unreal Engine 4 handles UStructs, my pointer and reference based designs would crash the engine.
In desperation, I created the `Dungeon` Blueprint to do the same thing.

### Level Generation
The `DungeonRenderer` Blueprint was originally intended just to stream any given dungeon to the world using the provided tileset, but has, for now, also served as the level generator.  I use the *Spelunky* algorithm, starting from the western edge of a 5x5 grid of tiles and randomly moving north, south, or east until the eastern edge is hit.  The last tile is marked as the exit tile.

The "*renderer*" then takes the completed dungeon and streams a level for each tile into the appropriate position in the world.  The main world contains all of the global lighting and information and the navigation mesh, wich is rebuilt dynamically to accomodate the new levels.  The renderer currently has several arrays for levels, one for each possible configuration of exits.  Any number of levels can be added to these arrays.

## Potential Improvements
* Seperate dungeon generation algorithm from the dungeon renderer.
* Create a `tileset` class/struct to hold the level arrays for different settings, then modify the renderer to read from this.
* Fix the C++ code that crashes and convert the Dungeon blueprint to C++.

## Sources
[Diablo Dungeon Design ft. Ed Hanes](https://www.youtube.com/watch?v=tUFvhDOPA_w&)
### Generation Algorithms
[Spelunky](https://www.youtube.com/watch?v=Uqk5Zf0tw3o)
