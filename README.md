# CS302/307 Final Project - Space Cowboys
##### Created by: Vijay Rajagopal, Josh Spangler, John Pi
-----------
## Table of Contents:
   - #### [Timelog](#timelog-1)
   - #### [Compiling/Running](#compilingrunning-1)
   - #### [Code Documentation](#code-documentation-1)
   - #### [How to Play](#how-to-play-1)

## Timelog:
### Members:
- Vijay Rajagopal [[Milestone](https://github.com/vjsrinivas/final_project/blob/vijay_wip/milestone_VR.txt)] [[Branch](https://github.com/vjsrinivas/final_project/tree/vijay_wip)]
- Josh Spangler [[Milestone](LINK)] [[Branch](https://github.com/vjsrinivas/final_project/tree/josh_wip)]
- John Pi [[Milestone](LINK)] [[Branch](https://github.com/vjsrinivas/final_project/tree/jpi_wip)]

### Timesheet:
#### Vijay Rajagopal: 37.5 hours
| Date (MM/DD/YY) | Time (hours) 	|
|--------------------	|--------------------	|
| 03/25/2019 | 3 hours |
| 03/27/2019 | 2 hours |
| 03/28/2019 | 2 hours |
| 03/29/2019 | 3 hours |
| 04/11/2019 | 5 hours |
| 04/14/2019 | 5 hours |
| 4/21/2019  | 5 hours |
| 4/22/2019  | 4.5 hours |
| 4/24/2019  | 6 hours |
| 4/25/2019  | 2 hours |


#### Josh Spangler: 28.5 hours
| Date (MM/DD/YY) | Time (hours) 	|
|--------------------	|--------------------	|
| 3/22/2019 | 4 hours |
| 3/25/2019 | 3 hours |
| 3/26/2019 | 1 hour  |
| 3/30/2019 | 2 hours |
| 4/1/2019  | 1 hour  |
| 4/12/2019 | 1 hour  |
| 4/14/2019 | 2 hours |
| 4/15/2019 | 2 hours |
| 4/22/2019 | 4 hours |
| 4/23/2019 | 2 hours |
| 4/24/2019 | 4.5 hours |
| 4/25/2019 | 2 hours |

#### John Pi: 24 hours
| Date (MM/DD/YY) | Time (hours) 	|
|--------------------	|--------------------	|               	
|3/25/2019   | 3 hours |
|3/26/2019   | 1 hour  | 
|3/28/2019   | 2 hours |
|3/29/2019   | 2 hours |
|4/12/2019   | 2 hours |
|4/14/2019   | 2 hours |
|4/20/2019   | 2 hours |
|4/22/2019   | 3 hours |
|4/24/2019   | 6 hours |
|4/25/2019   | 1 hour  |


## Compiling/Running
### Game Requirements:
- SDL2 (Simple DirectMedia Layer) libraries
    - Specific libraries:
        - lSDL2 (main SDL2 library)
        - lSDL2_image (loading/rendering textures)
        - lSDL2_ttf (font rendering)
- G++ compiler and C++11
- Linux/UNIX computer with ``Make`` installed

### How to compile code:
The ``Makefile`` should be included with GitHub repository. Simply type "make" into your command console, and it will compile and create an executable called ``main``.

### How to run code:
Type: ``./main `` to run the program


## Code Documentation


### File structure:
```
+-- assets
|   +-- characters
|       +-- ...
|   +-- items 
|       +-- ...
|   +-- ...
+-- enemy.txt
+-- items.txt
+-- game.cpp/game.h
+-- ltexture.cpp/ltexture.h
+-- ltimer.cpp/ltimer.h
+-- player.cpp/player.h
+-- map.cpp/map.h
+-- heaps.cpp
+-- test_map.txt
+-- Makefile
+-- main.cpp
+-- OpenSans-Bold.ttf
```

### Legend:
- **characters (directory)**: all of the ingame characters' textures (player + enemies) included
- **items (directory)**: all of the ingame items' textures
- **assets/[non-directory-files]**: all the different terrain texture files
- **enemy.txt (plaintext)**: contains all the metadata for each enemy type
- **items.txt (plaintext)**: contains all the metadata for each item type
- **game.cpp/game.h (code file)**: cpp and header file that calls the main SDL2 libraries
- **ltexture.cpp/ltexture.h (code file)**: cpp and header file that is a wrapper for SDL texture creation and rendering
- **ltimer.cpp/ltimer.h (code file)**: cpp and header file that is a wrapper for the SDL time function (relating to threading)
- **player.cpp/player.h (code file)**: cpp and header file that contains item struct/player class/enemy class/item functions
- **map.cpp/map.h (code file)**: cpp and header that contains the Map and Dot class; responsible for rendering map, player, NPCs, and items
- **heaps.cpp (code file)**: unfinished code that would allow us to sort the inventory of the player in realtime
- **test_map.txt (plaintext)**: simple file that contains the metadata for the only level in the game (contains terrain, item type/placement, and enemy type/placememnt)
- **Makefile (make)**: allows easy compilation of code
- **main.cpp (code file)**: cpp file that brings together all the game logic and data; runs entire game; contains GameState class
- **OpenSans-Bold.ttf (font file)**: main font used in this game

### Known bugs:
1. When mashing the movement keys, you can unintentionally "jump" over a wall that you're not supposed to (does not apply to the edges of the map).
2. When mashing the up and left movement keys at the start of the gamae, you can unintentionally "leave" the map area

## How to Play

### At Launch:
After launching the game, the player should be presented with two windows: the main map window and an inventory window:
![Window of Game](https://i.imgur.com/WGX5fug.png)

### Movement:
You can move around and explore the dungeon area with the following keys:
- ↑ `up arrow` - allows player to move one cell up
- ↓ `down arrow` - allows player to move one cell down
- → `right arrow` - allows player to move one cell to the right
- ← `left arrow` - allows player to move one cell to the left

Other tips while traveling through the map:
- You can traverse through any type of terrain other than the grey blocks.
- **To fight**: simply move next to an enemy and the enemies within a block radius will automatically start engaging you. You will also automatically fight back. The fighting is based on random damages with influence from max/min damages from weapons and max defense from shields.


### Items:
Items are extremely important in fighting and surviving through the map. You can pick up items by simply moving over them. The items that are picked up will show up on the inventory window. **Items do not automatically equip**, and you will have to manually click on the type of sword and shield you want to fight with. **Potions, such as light and health potions, will be automatically used when picked up**.

![alt text][stick]  **Stick**: Just a stick of wood. First weapon you will encounter, but it's pretty weak so find another weapon quickly!

![alt text][sword]  **Normal Sword**: A good sword for beginners and against Grunts but will fail against anything better.

![alt text][raj]**Sword of Raj**: A extremely powerful sword but quite exotic so it'll be kind of tricky to find.

![alt text][lance]**Lance**: A light-weight weapon with good stopping-power. Another weapon good against Grunts!

![alt text][john]**Sword of John**: One of the most powerful weapons in the game. Something that will allow you to stand up against the Excommunicator

![alt text][shield1]**Shield 1**: Just a standard shield. Better than nothing

![alt text][shield2]**Shield 2**: The best shield in the game, and it is something that will allow you to fight very powerful enemies and survive through it.

![alt text][light]**Light Potion**: This potion will allow you see further into the darkness and increases your ability to pick the fights you want.

![alt text][health]**Health Potion**: This potion will give back 30+ health if your health is below 100. If your health is at 100, then you will be "supercharged" by 20 health points each time you pick a health potion up.


### Characters:
![alt text][mc]  **Robot Cowboy** (You): A rouge robot cowboy trying to escape a dungeon made by his creator

![alt text][grunt]  **Grunt**: A common enemy you will find around the game. He is considered an easy target to take down if you have the right weapon/shield

![alt_text][ex]  **Excommunicator**: A **very powerful** enemy that will kill you without hestitation if you do not have some of the most powerful weapons/shields in the game. (Having a HP over 100 is also recommended). He stands in a T-pose, imposing a great fear into anybody who dares to fight.

![alt_text][eye]  **Eye of Emrich**: An enemy that is just a giant eye ball. It has a lot of health but does very little damage. Can be found guarding some good items.

![alt_text][key]  **Key Boy**: This enemy has the keys to escape the dungeon and won't give it you to voluntarily, so you need to end him. **You have to fight and win against this enemy to win the game**.

[mc]: https://github.com/vjsrinivas/final_project/blob/master/assets/characters/cs317_enemy_1.png "Robot Cowboy"
[grunt]: https://github.com/vjsrinivas/final_project/blob/master/assets/characters/enemy_2.png "Grunt"
[ex]: https://github.com/vjsrinivas/final_project/blob/master/assets/characters/enemy_3.png "Excommunicator"
[eye]: https://github.com/vjsrinivas/final_project/blob/master/assets/characters/enemy_4.png "Eye of Emrich"
[key]: https://github.com/vjsrinivas/final_project/blob/master/assets/characters/enemy_5.png "Key Boy"

[sword]: https://github.com/vjsrinivas/final_project/blob/master/assets/items/sword_5.png "Normal Sword"
[raj]: https://github.com/vjsrinivas/final_project/blob/master/assets/items/sword_3.png "Sword of Raj"
[shield1]: https://github.com/vjsrinivas/final_project/blob/master/assets/items/shield_1.png "Shield 1"
[shield2]: https://github.com/vjsrinivas/final_project/blob/master/assets/items/shield_2.png "Shield 2"
[stick]: https://github.com/vjsrinivas/final_project/blob/master/assets/items/sword_6.png "Stick"
[lance]: https://github.com/vjsrinivas/final_project/blob/master/assets/items/sword_4.png "Lance"
[john]: https://github.com/vjsrinivas/final_project/blob/master/assets/items/sword_2.png "Sword of John"
[light]: https://github.com/vjsrinivas/final_project/blob/master/assets/items/light_potion.png "Light Potion"
[health]: https://github.com/vjsrinivas/final_project/blob/master/assets/items/health_potion.png "Health Potion"
