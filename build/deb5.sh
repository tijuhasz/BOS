export KIND="Unix Makefiles"
export OUTDIR=deb5

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
cmake ../../ -G "$KIND" -DCMAKE_TOOLCHAIN_FILE=../../cmake/deb5.cmake 
echo cmake ../../ -G \"$KIND\"  > rebuild.sh
