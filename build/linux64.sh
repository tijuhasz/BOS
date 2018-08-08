export KIND="Unix Makefiles"
export OUTDIR=linux64

export LD_LIBRARY_PATH=H/opt/sw/gcc-4.7.2/lib32:/opt/sw/gcc-4.7.2/lib64
export PATH=/opt/sw/gcc-4.7.2/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

echo path = $PATH
echo ld lib path = $LD_LIBRARY_PATH

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi

mkdir $OUTDIR
cd $OUTDIR
cmake ../../ -G "$KIND" -DCMAKE_TOOLCHAIN_FILE=../../cmake/linux64.cmake -DBoost_DEBUG=1 -DBoost_ADDITIONAL_VERSIONS="1.61.0 1.61" -DBOOST_ROOT=/opt/boost/boost_1_61_0_x64
