export KIND="Unix Makefiles"
export OUTDIR=linux

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
cmake ../../ -G "$KIND" -DCMAKE_TOOLCHAIN_FILE=../../cmake/linux32.cmake -DWITHOUT_SVN=1
echo cmake ../../ -G \"$KIND\"  > rebuild.sh
