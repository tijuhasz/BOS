export KIND="Unix Makefiles"
export OUTDIR=linux

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
cmake ../../ -G "$KIND" -DCMAKE_TOOLCHAIN_FILE=../../cmake/linux32.cmake
echo cmake ../../ -G \"$KIND\"  > rebuild.sh
