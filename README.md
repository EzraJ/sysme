# sysme

sysme is a basic program that will take a list of files and output their contents. The inteneded usage is to call it at the end of something like .bashrc,
and to put files for someone like a new system admin to read. 

# How to use
sysme simply needs to be called and it will run

# Configurations
Upon running sysme for the first time, ~/.sysme will be created with a file called files.cfg
Each line will be read, if a line contains "file.txt", file.txt will be read out when called upon.
Note that each line is case-sensative, make sure to have no spaces at the ends of your file names