# toy-shell

#### - Class of Professor JongChan Kim.

#### - Project : Make your own shell 

#### - OS version : Ubuntu Linux 18.04 

- Maintain the existing shell's frame.

- Doesn't modify the output from the shell in the existing frame.

- In shell's prompt, user, host and cwd are showed. and they could be distinguished by their specified colors.

--------------------------


##  
## Supported Commands in this shell
##  

- [ exit ] : exit shell


- [ cd ] : change directories
~~~
   ex> cd .. / cd [dir]
       +> if the directory doesn't exist, an error exist
~~~

- [ ls ] : list
~~~    
   ex> ls / ls -al / ls -l   etc... (every option)
    	 +> if there is no commands option, an error exist
~~~

- [ mkdir ] : make directory
~~~
   ex> mkdir [dir], mkdir -m [dir], mkdir -v [dir] ...etc (every option) 
~~~

- [ rmdir ] : remove directory
~~~
   ex> rmdir [dir], rmdir -p [dir], rmdir -v [dir] (every option)
~~~
- [ rm ] : remove files or directory
~~~ 
   ex> rm [file], rm -f [file], rm -i [file] ...etc (every option)
~~~
- [ mv ] : move files or directory to another directory
~~~
   ex> mv [file], mv -b [file], mv -f [file] ...etc (every option)
~~~
- [ echo ] : print texts or input string combined " "
~~~
   ex> echo [input], echo -n [input], echo -e [with commands like \a, \v, \r, \t, \c...] ...etc (every option except *)
~~~
- [ sleep ] : stop (sleep) the shell for a given time (input)
~~~
   ex> sleep 1s (second), sleep 1m (minute) ...etc (every option)
~~~

- [ date ] : Today's year, month, day, day, time, etc. are printed.
~~~
   ex> date
~~~

- [ touch ] : Initialize the timestamp of the file to the current or create a new file
~~~
   ex> touch [file], touch [file1] [file2] ...etc (support until 3 files)
~~~

- [ chmod ] : Change the file's or directory's mode (authority)
~~~
   ex> chmod [mode] [file], chmod 777 a.out, chmod +x a.out ...etc
~~~

--------------------------

##  
### + Simple command to apply creating pipe and closing pipe in shell.
##  
- [ pipe_write ] : using [ popen ] function with 'writing mode' and [ pclose ] to print out list of current directory. [ls -l]

- [ pipe_read ] : using [ popen ] function with 'reading mode' and [ pclose ] to print out the date command. [date]
##  
~~~
   ex> type [ pipe_write ] or [ pipe_read ] in the shell and check the result.
~~~
