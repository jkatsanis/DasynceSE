# A Game once started in Unity will now continue in the best game engine (real!!)

## How do i start a game? 
- ❗ Its **REQUIRED** to download the Core+Editor (SpriteEngineUI) and open the game with the editor; this will set the path to the core library in the game project. If you try to build the game without opening it in the Editor once, it won't work! 
  - Build the SpriteEngine with the instruction above. 
  - You can open the game in the editor and click on the top right button to play the game. 
- **COMPILING** the game on the first time will take quite alot of time, the editor freezes while the game runs, and while the game builds. 

- ⚠️ **BUILDING IN RELEASE** If you want to build in **RELEASE**, you need to go into the top CMake file and change the `CMAKE_BUILD_TYPE` to Release, CMake doesn't update it in their cache when you change it in Visual Studio to Release, so it will copy Debug DLL's in the Release folder on the costum POST_BUILD command. It's **DEBUG** by default, you don't need to do anything if you want to build in DEBUG.


## How to build 
- mkdir build
- cd build
- cmake ..

This game is still in development, so it has alot of bugs and wierd things. 