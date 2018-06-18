# fonttest
Tool used to examine geometry of fonts available to Qt apps, like mythtv
========================================================================

## Build as follows:
qmake  
make  

## Use as follows:
./fonttest [-w width] [-h height] [-f file]
-w, --width width   Scene width  
                    Default: 1280  
-h, --height height Scene height  
                    Default: 720  
-f, --file file     Input file to display in scene  
                    Default: all CC characters in 15x32 grid  

## Example input files:
cols-32.txt 32 columns by 15 rows
cols-42.txt 42 columns by 15 rows
utf-8.txt   UTF-8 character set
utf-8-15.txt UTF-8 character set, duplicated rows to 15
