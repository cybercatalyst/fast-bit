# Prerequisites
version="0.1"
architecture="amd64" 
echo "Build debian binary package with version $version.."
packagename="fastbit-$version-1_$architecture"

# Check whether the specified directory exists, in that case we could
# overwrite something accidentally.
if test -e "$packagename"; then
 echo "A directory with the specified packagename already exists. For safety reasons, please move or delete the folder $packagename manually and run this script again."
 exit 0
fi

# If theres is no binary, build it.
if ! test -e "fastbit"; then
  echo "Building binary."
  cd "source"
   qmake-qt4
   make
  cd ".."
fi

# Build package directory structure
mkdir "$packagename" "$packagename/usr" "$packagename/usr/bin"
mkdir "$packagename/DEBIAN"

# Generate control file
controlfile="$packagename/DEBIAN/control"
echo \
"Package: fastbit
Version: $version-1
Section: base
Priority: optional
Architecture: $architecture
Depends:
Maintainer: Jacob Dawid <jacob.dawid@googlemail.com>
Description: fastbit Image Processing
 fastbit is an application for advanced image processing. It features
 a script engine and can handle various image formats. The source can
 always be retrieved at https://github.com/jacobdawid/fast-bit." \
>> $controlfile

# Copy files
cp fastbit "./$packagename/usr/bin"

# Use dpkg-deb go build the deb.-file
dpkg-deb --build $packagename 

# Clean up
rm -r -f $packagename
