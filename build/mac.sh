export OUTDIR=Mac

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
cmake ../../  -DCMAKE_TOOLCHAIN_FILE=../../cmake/iOS_Sim.cmake
