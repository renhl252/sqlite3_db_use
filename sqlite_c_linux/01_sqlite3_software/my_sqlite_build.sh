
BUILD_PATH=`pwd`

echo "==Clean sqlite ========================================================"
rm -rf build sqlite-autoconf-3180000
ls
sleep 1

echo "==Unpackage sqlite ========================================================"
#icu
tar -zxvf sqlite-autoconf-3180000.tar.gz
sleep 1


#Conifguration 
echo "==Conifguration sqlite========================================================"
cd $BUILD_PATH/sqlite-autoconf-3180000
./configure --prefix=$BUILD_PATH/../02_common/
sleep 1

echo "==Compile sqlite========================================================"
make
sleep 1

echo "==Install sqlite========================================================"
make install

echo "==Clean sqlite ========================================================"
cd $BUILD_PATH
rm -rf build sqlite-autoconf-3180000
ls
sleep 1

cp $BUILD_PATH/../02_common/bin/sqlite3 /usr/bin/
sleep 1
