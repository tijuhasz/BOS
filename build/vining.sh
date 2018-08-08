export KIND="Unix Makefiles"
export OUTDIR=vining

export STAGING_DIR=/opt/vining_sdk

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
cmake ../../ -G "$KIND" -DCMAKE_TOOLCHAIN_FILE=../../cmake/vining.cmake
echo cmake ../../ -G \"$KIND\"  > rebuild.sh
