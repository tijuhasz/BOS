
export KIND="Unix Makefiles"
export OUTDIR=cyclone

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
cmake ../../ -G "$KIND" -DCMAKE_TOOLCHAIN_FILE=../../cmake/cyclone.cmake
echo cmake ../../ -G \"$KIND\"  > rebuild.sh
