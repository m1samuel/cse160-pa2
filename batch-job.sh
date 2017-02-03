#!/bin/bash
# This script is intepreted by the Bourne Shell, sh
#
# Documentation for SGE is found in:
# http://docs.oracle.com/cd/E19279-01/820-3257-12/n1ge.html
#
# Tell SGE which shell to run the job script in rather than depending
# on SGE to try and figure it out.
#$ -S /bin/bash
#
# Export all my environment variables to the job
#$ -V
# Tun the job in the same directory from which you submitted it
#$ -cwd
#
# Give a name to the job
#$ -N MSORT
#
# Specify a time limit for the job
#$ -l h_rt=00:02:00
#
# Join stdout and stderr so they are reported in job output file
#$ -j y
#
# Run on the debug queue; only one node may be used
#$ -l debug.q
#
# Specifies the circumstances under which mail is to be sent to the job owner
# defined by -M option. For example, options "bea" cause mail to be sent at the 
# begining, end, and at abort time (if it happens) of the job.
# Option "n" means no mail will be sent.
#$ -m a
#
# *** Change to the address you want the notification sent to, and
# *** REMOVE the blank between the # and the $
# $ -M someone@ucsd.edu
#

# Change to the directory where the job was submitted from
cd $SGE_O_WORKDIR

echo
echo " *** Current working directory"
pwd
echo
echo " *** Compiler"
# Output which  compiler are we using and the environment
gcc -v
echo
echo " *** Environment"
printenv

echo

echo ">>> Job Starts"
date

ls .
# Commands go here

#Public tests
# The -t flag works only on a multithreaded code, the reference
# will ignore it
./msort -n 67108864 -t 1 -g 262144 -g 262144  -s 1380501542  -v $PUB/HW/A2/out.67
./msort -n 67108864 -t 2 -s 789456 -g 262144  -s 1380501542
./msort -n 67108864 -t 4 -s 789456 -g 262144  -s 1380501542
./msort -n 67108864 -t 8 -s 789456 -g 262144  -s 1380501542

./msort -n 4096 -t 8 -s 789456 -g 262144  -s 1380501542 -o out.4K
./msort -n 4096 -t 8 -s 789456 -g 262144  -s 1380501542 -v out.4K

./msort -n 16 -t 1 -b
./msort -n 16 -t 1 -w

date
echo ">>> Job Ends"
