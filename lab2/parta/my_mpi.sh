#!/bin/bash
#
#$ -cwd
##$ -j y
#$ -S /bin/bash
#$ -M carlislk@uci.edu
#$ -pe openmpi 4
#$ -i fartico_aniketsh_input_partA.txt
#$ -o out.txt
#$ -e error.err

module load sge
module load openmpi/1.6

mpirun -np 4 ProgramA fartico_aniketsh_input_partA.txt OUT.txt
