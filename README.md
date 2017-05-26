# Furious5AVC
Repository for the Furious 5 AVC group.
---

### Deadlines

 Task | Due 
------|----
~~Project Plan~~    | ~~Fri 5 May~~ 
~~Progress Report~~ | ~~Mon 22 May~~ 
Final Report | Mon 19 Jun 

### Members
* [Henry Pettit](https://github.com/henry-g-c-pettit)
* [Jolon Behrent](https://github.com/JolonB)
* [Charlotte Gimblett](https://github.com/charlottegimblett)
* [Sopana Lim](https://github.com/Posmil)
* [Cayden Howes](https://github.com/cwohowes)

### Pi Dimensions
**L:** 115mm  
**W:** 70mm  
**H:** 75mm
<!--Protip: If you want to do a line break, put 2 spaces at the end of your sentence and press enter. Otherwise, press enter twice to 
create a new paragraph-->

### C++ Template
A template for your C++ code can be found [here](https://github.com/JolonB/Furious5AVC/blob/master/c%2B%2BTemplate.cpp). Make sure
you have the [E101.h](https://github.com/JolonB/Furious5AVC/blob/master/E101.h) library in the same folder as the code you write.

### Cloning/Downloading
#### Repository
In the terminal enter: `git clone http://www.github.com/JolonB/Furious5AVC/` or `git clone git@github.com:JolonB/Furious5AVC.git`. If you follow either of these with a file path on the Pi or your PC, it will save it there (e.g. `git clone http://www.github.com/JolonB/Furious5AVC/ Desktop/AVC/<foldername>`).

#### Branch
If you only want to clone a branch, enter: `git clone -b <branch> git@github.com:JolonB/Furious5AVC.git`.

#### File  
If you only need to clone a single file, enter: `git checkout <edit-id>`, where `<edit-id>` is the 7 character number for the file found
in the file's history.

Alternatively, you can just press the green Clone or download button in the repo and then press Download ZIP, however this doesn't work
on the Pi because the browser is out of date, so you have to use `git clone`.

---
### Running Code via SSH
#### SSH
*Note: The directory is now on the desktop. These instructions have been updated to match this.*  
SSH is pretty neat and we kind of have to be able to use it, so here's the steps for doing it:
1. Find the IP address of the Pi using `ifconfig` in the terminal. Last time I checked, it was *10.140.30.145*.
1. SSH into the Pi using `ssh pi@10.140.30.145` in the Linux terminal or by using [PuTTY](http://www.putty.org/) on Windows.
The password is `pi`.
1. The files are all in the a folder called *Furious5AVC* in the root. To access this in the terminal simply type `cd Desktop/AVC/WorkingCode` <!-- cd means change directory --> (case matters). To see all of the files in the folder, type `ls`. <!-- ls means list -->
#### Doing stuff to the code
Now that you've found the files, there are several things you can do:  
* To edit a file, type `nano <filename>.cpp` when in the correct directory. This will open a very primitive file editor. To edit stuff 
use the arrow keys to move the cursor. *ctrl+o* saves the file. Press enter to save it with the current file name. Note: The file
cannot be run.  
* If you edit a file or clone it from GitHub, you will need to compile it. Use `g++ -o <executable name> <filename>.cpp -le101`. The 
executable name doesn't matter, although it's probablt best to name it after the original C++ file.  
* You cannot run a *.cpp* file. You must compile it first to create an executable. To run the file, type `sudo ./<executable name>`.
For example, `sudo ./main` will run the main executable (the one with all the code). Make sure you don't forget to type sudo (at least
 for the first time you run it), otherwise you will get some errors and be forced to restart the terminal and go through the SSH process
 again.

---
Feel free to edit this ReadMe file. Markdown tips can be found [here](https://guides.github.com/features/mastering-markdown/) :ok_hand:
