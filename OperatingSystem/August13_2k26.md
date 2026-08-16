# T26049 Yashank
### Basic Linux Terminal Command
- ```ls```: List the contents of your home directory, use ```ls-l``` to list the files in sorted order
- ```free```: Amount of free Used RAM, Cache Memory details
- ```df```, ```lsblk``` : Secondary Storage, storage type more similar details
- ```lscpu```: CPU Details Clock speed and similar
- ```uname```: Tell's what Linux distro you are using
- ```ip addr```: Ip address of the user
- ```ping```: Use to ping a Ip Address to know how well it send receive signals, for ex, ```ping google.com```
- ```echo $0```: use to know what shell I am using
- ``` python --version```: to know what python version I am using , I am using Python 3 so for me command will be ```python3 --version```
- ```who```: tell me who I am in the order ``` USER Device(terminal using) Time Logged in```
- ```less```: Linus uses this command to view a File Page Wise it lets you scroll forward, backward... Use ```Ctrl + z``` to end the file
- ```cat```: Lets you view the file within the terminal itself, Unless ```less``` it does not open the interactive page by page viewer rather it directly prints the whole document in the terminal itself
- ```cp```: Copies Files or Directories from one location to another, ```cp source.txt destination.txt``` for files and use ```cp -r source_dir destination_dir``` for directories
- ```mkdir```: Creates new Directory, ```mkdir folder_name```
- ```mv```: moves or renames files, ```mv old_name new_name```
- ```rm```: used to delete/remove files or directories
- ```wc```: It counts lines, words, bytes in the text file Use ``` wc -l text.txt``` to only get number of lines
- ```piped text```: when we use ```cat``` to directly feed the file's content to ```wc``` to count lines, words and characters without opening it separately

### Linux and C
- ```gcc lab.c```: Convert ```lab.c``` file into ```lab.o``` file which is an object when given to linker is then converted to an executable file ```a.out```
- ```gcc lab.c -o my_program```: When you don't want the executable file to be as ```a.out``` we use ```-o``` to provide a custom name to the file
- ```gcc -Wall```: Used to display all Compiler Warnings
- ```gcc -g```: embeds extra debugging information about the code
- ```gcc -O```: Optimizes the code to make it run faster

#### Linking with Libraries
- ```man```: this shell prompt gives out description about a particular function allows you to understand the use case in CPP and what are the libraries you need to include before using them in your function. for eg. if you want to use ```fork()``` in your program you may understand about it using ```man fork```

#### Statically-linked (.a) and Dynamically-linked Libraries (.so)
- Statically Linked Libraries are directly attached to your executable by linker, resulting in a longer binary object but at the same time less performance cost
- whereas, Dynamically on the other hand improves on this by referencing to a program library in your executable when the program runs, the operating system loader dynamically links in the library but we have to pay some performance cost
- To Link with some libraries for instance ```math``` library we need to invoke ```gcc``` with right flags, ```gcc -o lab lab.c -Wall -lm```, Now the flag could be anything like ```-lXXX```
- ```-static``` this flag can be used to force static library
- ```-I /path/to/header```: this is used to specify a custom header path as gcc won't be able to find them automatically
- ```-L /path/to/library```: this is used to specify a custom library path as gcc won't be able to find them automatically

#### Separate Compilation
Once a program starts to get large enough, you may want to split it into separate files, compiling each separately, and then link them together
```
gcc -Wall -O -c hw.c
gcc -Wall -O -c helper.c
gcc -o hw hw.o helper.o -lm
```
- ```-c``` flag tells the compiler just to produce an object file
- To combine the object files into an executable, you have to “link” them together
- Of course, you could just specify all the C source files on a single line ```gcc -Wall -O -o hw hw.c helper.c```, but this requires the system to recompile every source-code file, which can be a time-consuming process.
- By compiling each individually, you can save time by only recompiling those files that have changed during your editing, and thus increase your productivity
- This process is best managed by another program, ```make```
#### Makefiles
The program ```make``` lets you automate much of your build process, and is thus a crucially important tool for any serious program




