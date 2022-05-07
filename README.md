# Race-Game
A 2-player game is a race between 2 contestants competing against each other in the IIT campus, built using SDL2 for graphics and asyncio for networking. Please see the instruction manual to understand the rules of the game here: https://github.com/Sidawhiz/Race-Game/blob/master/Race%20Game.pdf

#### Instructions to run
1. Type `make` in the terminal to compile the files.
2. This will generate two executable files namely `game` and `server`
3. Then, run `./server` in the terminal.
4. Once game is over, close the server.

#### Instructions to install asio
1. Download asio from the link https://think-async.com/Asio/ based on your OS. Extract it in a folder of your choice.
2. Change the path `~/software/asio/asio-1.18.1/include` in makefile according to your asio location. Make sure you enter the path correctly.

#### Instructions to install SDL 2 and other libraries
1. Use the command `sudo apt-get install libsdl2-dev` to install SDL 2.
2. In order to run the game successfully, the following extra libraries are needed: SDL_image, SDL_ttf and SDL_mixer.
3. To install SDL_image, use `sudo apt-get install libsdl2-image-dev`.
4. Install SDL_ttf using `sudo apt-get install libsdl2-ttf-dev`.
5. Use `sudo apt-get install libsdl2-mixer-dev` to install SDL_mixer.

*The instructions mentioned above for various installations were used on Ubuntu and are meant only for such an OS.*

##### References
1. https://youtu.be/2hNdkYInj4g
2. https://youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx
3. https://lazyfoo.net/tutorials/SDL/index.php
4. https://github.com/Ramneet-Singh/Pacman-Multiplayer
