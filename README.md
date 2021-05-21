# toy-shell

##- implement simple shell forked from professor Jong Chan Kim.
##- OS version : Ubuntu Linux 18.04 

#### Implemented Command Lines
- exit : exit shell
- cd : change directories
	ex> cd .. / cd [dir]
	+> if the directory doesn't exist, an error exist
- ls : list
	ex> ls / ls -al / ls -l   etc... (every option)
	+> if there is no commands option, an error exist
- mkdir : make directory
	ex> mkdir [dir], mkdir -m [dir], mkdir -v [dir] ...etc (every option) 
- rmdir : remove directory
	ex> rmdir [dir], rmdir -p [dir], rmdir -v [dir] (every option)
