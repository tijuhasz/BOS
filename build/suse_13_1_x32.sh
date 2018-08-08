export KIND="Unix Makefiles"
export OUTDIR=suse_13_1_x32

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
cmake ../../ -G "$KIND" -DCMAKE_TOOLCHAIN_FILE=../../cmake/suse_13_1_x32.cmake 
echo cmake ../../ -G \"$KIND\"  > rebuild.sh
