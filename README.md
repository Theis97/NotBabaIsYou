# Not (Quite) Baba Is You

Not (Quite) Baba Is You is a C++ implementation of the core mechanics of the game *Baba Is You*. It's a puzzle game where the player can manipulate the rules of the game by moving around blocks of text to break the given rules or make their own.

While there's nothing actually playable here, the code in this repo can be used to simulate the first few levels of the original game.

## How the Game Works

In *Baba Is You* just because something looks like it will behave a certain way doesn't mean it will. The only things that can mechanically distinguish `BABA` from `WALL` are the rules that apply to them in the moment. Almost every kind of entity in the game is the same in this way (aside from a few special ones, such as `TEXT`). You can take control of all the rocks, turn all the walls into flags, even turn *everything* into baba. It all depends on the rules.

Currently, the only rules that Not Baba supports are of the form `{noun} IS {property}` or `{noun} IS {noun/otherNoun}`.

`{noun} IS {property}` means that entities of the type indicated by `noun` have that property. What this means for how those entities behave while that rule is active depends on what that property is. For example, an entity that is `PUSH` can be pushed around the level. A full list of the properties currently implemented in Not Baba can be found below.

`{noun} IS {otherNoun}` transforms all entities of the type `noun` into the type `otherNoun`. This typically happens immediately when the rule is formed. An entity can only be transformed once per player action, so if there is a chain of transformations, the player has to move (or use a "wait" action) before the subsequent transformations happen. For example, say we have the rule `FLAG IS WALL`. If we then form the rule `ROCK IS FLAG`, any rocks will turn into flags. Those flags will turn into walls the next time the player does something.

`{sameNoun} IS {sameNoun}` will prevent entities of type `sameNoun` from being transformed by any other rules. 

## How this Code Works

Here's a breakdown of what each class in this repo does:

* **Entity**: Keeps track of the state of a single entity in the level. 
* **Tile**: Keeps track of the state of a single tile in the level. Lets Level know about local interactions between entities.
* **Ruleset**: Responsible for understanding how to read rules and for keeping track of what rules are currently in play. Tile and Level consult this class to understand how entities should behave.
* **Level**: Keeps track of the state of the level as a whole, responsible for updating the state of the level in response to player actions. In charge of moving entities from tile to tile, spawning new entities, finding pieces of text that might form a rule to give to Ruleset.

More details can be found in the source code.

## Features

* Properties
  * `YOU` - The player controls this entity's movements
  * `WIN` - The level is won if an entity with the property `YOU` lands on the same tile as an entity with this property
  * `STOP` - No entities can enter the tile of any entity with this property
  * `PUSH` - This entity can be pushed by other entities, typically a player controlled entity
* Other Mechanics
  * Transform entities from one type to another
  * Entities can be prevented from transforming to another type

Now, if you haven't already, please check out [the original game by Hempuli!](https://hempuli.com/baba/)
