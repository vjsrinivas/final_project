# CS302/307 Final Project - Space Cowboys
##### Created by: Vijay Rajagopal, Josh Spangler, John Pi
-----------
## Table of Contents:
   - #### [Timelog](#timelog-1)
   - #### [Compiling/Running](#compilingrunning-1)
   - #### [Code Documentation](#code-documentation-1)
   - #### [How to Play](#how-to-play-1)
-----------
## Timelog:
### Members:
- Vijay Rajagopal [[Milestone](https://github.com/vjsrinivas/final_project/blob/vijay_wip/milestone_VR.txt)] [[Branch](https://github.com/vjsrinivas/final_project/tree/vijay_wip)]
- Josh Spangler [[Milestone](LINK)] [[Branch](https://github.com/vjsrinivas/final_project/tree/josh_wip)]
- John Pi [[Milestone](LINK)] [[Branch](https://github.com/vjsrinivas/final_project/tree/jpi_wip)]

### Timesheet:
#### Vijay Rajagopal:
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


#### Josh Spangler:
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

#### John Pi:
| Date (MM/DD/YY) | Time (hours) 	|
|--------------------	|--------------------	|               	
|3/25/19     | 3 hours |
|3/26/19     | 1 hour  | 
|3/28/19     | 2 hours |
|3/29/19     | 2 hours |
|4/12/19     | 2 hours |
|4/14/19     | 2 hours |
|4/20/19     | 2 hours |
|4/22/19     | 3 hours |
|4/24/19     | 4 hours |

-----------

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

------
## Code Documentation
------

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
- characters (directory): all of the ingame characters' textures (player + enemies) included
- items (directory): all of the ingame items' textures
- assets/[non-directory-files]: all the different terrain texture files
- enemy.txt (plaintext): contains all the metadata for each enemy type
- items.txt (plaintext): contains all the metadata for each item type
- game.cpp/game.h (code file): cpp and header file that calls the main SDL2 libraries
- ltexture.cpp/ltexture.h (code file): cpp and header file that is a wrapper for SDL texture creation and rendering
- ltimer.cpp/ltimer.h (code file): cpp and header file that is a wrapper for the SDL time function (relating to threading)
- player.cpp/player.h (code file): cpp and header file that contains item struct/player class/enemy class/item functions
- map.cpp/map.h (code file): cpp and header that contains the Map and Dot class; responsible for rendering map, player, NPCs, and items
- heaps.cpp (code file): unfinished code that would allow us to sort the inventory of the player in realtime
- test_map.txt (plaintext): simple file that contains the metadata for the only level in the game (contains terrain, item type/placement, and enemy type/placememnt)
- Makefile (make): allows easy compilation of code
- main.cpp (code file): cpp file that brings together all the game logic and data; runs entire game; contains GameState class
- OpenSans-Bold.ttf (font file): main font used in this game

### Known bugs:
1. When mashing the movement keys, you can unintentionally "jump" over a wall that you're not supposed to (does not apply to the edges of the map).
2. When mashing the up and left movement keys at the start of the gamae, you can unintentionally "leave" the map area

------

## How to Play

------
