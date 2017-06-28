#! /bin/bash

if [ ! $# == 2 ]; then
    echo "Usage: $0 /path/to/directory target-cc"
    exit
fi

MAKEFLAGS="-j5"

BINUTILS_VER="2.28"
BINUTILS_FILENAME="binutils-$BINUTILS_VER.tar.gz"

GCC_VER="7.1.0"
GCC_FILENAME="gcc-$GCC_VER.tar.gz"

BASE_PATH="ftp://ftp.gnu.org/gnu"

GCC_PATH="$BASE_PATH/gcc/gcc-$GCC_VER/$GCC_FILENAME"
BINUTILS_PATH="$BASE_PATH/binutils/$BINUTILS_FILENAME"

TEMPDIR=/tmp
# echo $GCC_PATH
# echo $BINUTILS_PATH
# ftp://ftp.gnu.org/gnu/binutils/binutils-2.28.tar.gz
# ftp://ftp.gnu.org/gnu/gcc/gcc-7.1.0/gcc-7.1.0.tar.gz

export PREFIX=$(realpath $1)
export TARGET="$2"
export PATH="$PREFIX/bin:$PATH"

echo "Path is $PREFIX"
echo "Target is $TARGET"
echo

function download () {
    echo "Downloading $1 with filename $2"
    if [ -f $2 ]; then
        echo "File exists, therefore won't download again."
    else
        wget $1
    fi
}

echo "Entering $TEMPDIR to build our toolchain."
cd $TEMPDIR
download $GCC_PATH $GCC_FILENAME
echo
download $BINUTILS_PATH $BINUTILS_FILENAME
echo

function extract () {
    local EXTRACT_DIR=${1%-*}
    echo "Extracting $1 to $EXTRACT_DIR"
    mkdir -p $EXTRACT_DIR
    # -- strip 1 works here because they're folders contained in an archive.
    tar xf $1 -C $EXTRACT_DIR --strip 1
    eval $2=$EXTRACT_DIR
}

extract $BINUTILS_FILENAME BINUTILS_DIR
echo
extract $GCC_FILENAME GCC_DIR
echo
# BINUTILS_DIR="binutils"
# GCC_DIR="gcc"

function run_make () {
    echo "Running make for $1"
    mkdir -p build-$1
    cd build-$1
    if [[ $1 == *"binutils"* ]]; then
        sh ../$1/configure --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror
        make $MAKEFLAGS
        make $MAKEFLAGS install
    else
        sh ../$1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
        make $MAKEFLAGS all-gcc
        make $MAKEFLAGS all-target-libgcc
        make $MAKEFLAGS install-gcc
        make $MAKEFLAGS install-target-libgcc
    fi
    cd ..
}

run_make $BINUTILS_DIR
echo
run_make $GCC_DIR
echo

echo "Done!"

function print_path_info () {
    echo "To ensure that your new compiler is in your path, please add this to your ~/.bashrc or ~/.zshrc
export PATH=\"$PREFIX/bin:\$PATH\"
    "
}

echo
print_path_info
