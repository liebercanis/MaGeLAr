#!/bin/bash -l
#SBATCH --mail-type=begin,end,fail
#SBATCH --mail-user=mgold@unm.edu
#SBATCH --image docker:legendexp/legend-base:latest
#SBATCH --qos=shared
#SBATCH -C haswell
## shared qos means 1 node, with some number of tasks and cpus:
#SBATCH --nodes=1
#SBATCH --ntasks=1
## one core has 2 hyperthreads, which slurm views as "cpus":
#SBATCH --cpus-per-task=2
#SBATCH --time=3:00:00 # 3 hour
#SBATCH --mem=32G
#SBATCH --image=docker:legendexp/legend-base:latest
#SBATCH --export=LD_LIBRARY_PATH=/global/project/projectdirs/m2676/users/mgold/shifter/MGDO/lib:/opt/root/lib:/usr/lib64:/opt/clhep/lib:/opt/geant4/lib64:/opt/geant4/lib64:/opt/clhep/lib:/opt/hdf5/lib
#SBATCH --export=projectdir=/global/project/projectdirs/m2676/users/mgold/shifter/MaGe

export projectdir=/global/project/projectdirs/m2676/users/mgold/shifter/MaGe
echo "srun --output=$projectdir/TlSource-job31.log -n 1  -C haswell shifter --env-file=$projectdir/MaGeEnvirons $projectdir/bin/MaGe $projectdir/TlSource-job31.mac"
srun --output=$projectdir/TlSource-job31.log -n 1  -C haswell shifter --env-file=$projectdir/MaGeEnvirons $projectdir/bin/MaGe $projectdir/TlSource-job31.mac
