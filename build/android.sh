export KIND="Unix Makefiles"
export OUTDIR=Android

if [ -d $OUTDIR ]
then
  rm -R $OUTDIR
fi
mkdir $OUTDIR
cd $OUTDIR

export ANDROID_NDK=/opt/android/android-ndk-r9/
cmake ../.. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=../../cmake/android.cmake -DBUILD_SHARED=FALSE -DWITH_USB=FALSE

