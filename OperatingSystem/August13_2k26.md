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


