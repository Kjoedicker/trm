# TRM [![Build Status](https://travis-ci.com/Kjoedicker/trm.svg?branch=master)](https://travis-ci.com/Kjoedicker/trm)
A simple cli trash manager.

## About
Allows you to delete, restore and view deleted files.

## Installation

```
$ git clone https://github.com/Kjoedicker/trm.git
$ cd trm
$ make
$ sudo install ./trm /usr/bin/
```


create an enviromental variable known as ```$Trash_Folder```, so trm has a location to place your ```.trash``` folder[0]

[0] // TODO(#23): Standardize this for ```$HOME/.local/share/Trash```


## Use

#### Deleting files

By default ./trm will delete a file

```
$ ./trm <file_name>
```

you can be more verbose and specify

```
$ ./trm -d <file_name>
```

#### Viewing deleted files

View files in the ```$Trash_Folder``` path

```
$ ./trm -v
```

View files with the file size also listed 

```
$ ./trm -V
```

If files of the same name are deleted, a ```_re``` is appended upon deletion.

```
$ touch 1
$ ./trm 1
$ touch 1
$ ./trm 1
$ ./trm -v 
$ 1 1_re
```

#### Restoring files 

When a file is deleted, a trace file containing its original location is created. 

```
$ ./trm -r <file_name> <$TRASH_FOLDER/.trace/file_name>
```

If you want to restore a file to a specific path, the ```-R``` flag is used with the destination specified

```
$ ./trm -R <file_name> <destination>
```
