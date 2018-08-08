export KIND="Unix Makefiles"
export OUTDIR=vining_vm

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
cmake ../../ -G "$KIND" -DCMAKE_TOOLCHAIN_FILE=../../cmake/vining_vm.cmake
echo cmake ../../ -G \"$KIND\"  > rebuild.sh
