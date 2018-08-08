export KIND="MinGW Makefiles"
export OUTDIR=mingw

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
echo cmake ../../ -G "$KIND"
cmake ../../ -G "$KIND"
echo cmake ../../ -G \"$KIND\"  > rebuild.sh
cmake ../../ -G "$KIND"
