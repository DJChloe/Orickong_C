# OricKong-C
OricKong-C is an open source game project created by Chloé Avrillon (aka LadyWasky/Waskol) for the [Oric Atmos 48K computer](https://en.wikipedia.org/wiki/Oric#Oric_Atmos).

OricKong-C is based on the same name type-in BASIC program made by Bertrand RAVEL and published in the french magazine ["Tilt", #11, page 49, in 1984](http://www.abandonware-magazines.org/affiche_mag.php?mag=28&num=330&album=ou). Oric Kong is a Donkey Kong clone, with foor colorfull levels.

OricKong-C is written in C, using the [Oric Software Development Kit (OSDK)](http://osdk.defence-force.org/), a complete cross-development system allowing to create software for the Oric 1, Oric Atmos, and Oric Telestrat computers.
BASIC, C and a bit of assembly language were used for this project.

The original game, in BASIC, was slow and difficult to play.
This rewrite aims to improve the gameplay, some graphical animations were added, a lot of bugs were fixed during the retro-engineering phase.
The project is not completely finalized.


## OSDK fixes :
Once the OSDK downloaded, and properly installed and configured, at this time two small fixes must be applied to OSDK v1.12 :
* **macro.h**, in <Your OSDK Path>\macro directory : EQ0W_C code generator macro is missing, and must be added. (see [this topic](http://forum.defence-force.org/viewtopic.php?f=24&t=1869&p=18000#p18000) on the [defence-force.org](http://www.defence-force.org/) forum)
* **lib.h**, in <Your OSDK Path>\include directory : the rand function declared at the far end of the file is broken, and this line must be commented.

The two fixed files are in the **./Fixes for OSDK** directory of the project.

## How to compile and build the tape file for Oric Kong :
Simply use the batch file **make_all.bat**, located in the **.\src** (sources) directory the project.
After a couple of seconds, a new directory, **release**, will appear with two files in it. Those are the file tapes that can be used with an Oric emulator such like Euphoric (DOS) or Oricutron (Windows, Linux, ...).
One of the file is the english version of the game, the other is the french version.

## Thanks
I wish to thank some people of the Oric community that helped me in a way or another in elaborating this game, and my kids who encouraged me to do it.
Those people are credited with their pseudo appearing in the High-scores.

* MAXIMUS, who animated Oricgames.com and wrote [an article](http://callmekenneth.pagesperso-orange.fr/edito,en,112,92.html) on the Donky Kong like games available for the Oric computer.
* KENNETH, who has ressurected [OricGames](http://callmekenneth.pagesperso-orange.fr/) back from the graves. 
* DBUG, who is the main maintainer of the OSDK, founder of Defence-force.org, and who helped me to fix those two nasty bugs in the OSDK. One of the best demo-maker in the Oric community.
* XERON who developped the Oricutron emulator
* SYMOON, who have provided to Oricgames a lot of tape files, and the Oric Kong tape file. 
* TILT, the magazine, and its team, in which the original game was published.

Special thanks to :
* Bertrand RAVEL, credited in Tilt as the author of Oric Kong
* Ibisum for testing and feedback
* Iss, for, well... I don't remember for what, but he noticed me that Oricutron was from Xeron. And many thanks to his support. 
* My sons (Hugo, Tom and Eliot) for their support.
* Github for hosting the project.
