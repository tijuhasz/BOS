export KIND="Unix Makefiles"
export OUTDIR=deb8u3

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
cmake ../../ -G "$KIND" -DCMAKE_TOOLCHAIN_FILE=../../cmake/deb8u3.cmake
echo cmake ../../ -G \"$KIND\"  > rebuild.sh
