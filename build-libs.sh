# Use cmake to build the project in the ArgoDraft directory
# copy the output .a, .so, and .lib files to the lib directory of the Net Toys, OpenGL/Imgui, OpenGL/UI-Basics, and Threaded directories
# copy the files in ArgoDraft/include directory to the Net Toys, OpenGL/Imgui, OpenGL/UI-Basics, and Threaded include/ArgoDraft directories

projectDirectories=("NetToys" "OpenGL/Imgui" "OpenGL/UI-Basics" "Threaded")
currentDirectory=$(pwd)

isRelease=false

cd ArgoDraft

# Build the project in the ArgoDraft directory to a build/debug and build/release directory

if [ "$1" == "release" ]; then
    echo "Building release"
    isRelease=true
    
    cmake -DCMAKE_BUILD_TYPE=Release -S . -B build/release
    cmake --build build/release
else
    echo "Building debug"
    
    cmake -S . -B build/debug
    cmake --build build/debug
fi

# Remove the existing ArgoDraft lib files and include/ArgoDraft directories in the project directories
for projectDirectory in "${projectDirectories[@]}"
do
    echo "Removing existing files in $projectDirectory"
    rm -rf $currentDirectory/$projectDirectory/lib/ArgoDraft.* || true
    rm -rf $currentDirectory/$projectDirectory/include/ArgoDraft || true
done

# Create the include/ArgoDraft directories in the project directories
for projectDirectory in "${projectDirectories[@]}"
do
    echo "Creating include directories in $projectDirectory"
    mkdir $currentDirectory/$projectDirectory/include || true
    mkdir $currentDirectory/$projectDirectory/include/ArgoDraft || true
done

# Create the lib directories in the project directories
for projectDirectory in "${projectDirectories[@]}"
do
    echo "Creating lib directory in $projectDirectory"
    mkdir $currentDirectory/$projectDirectory/lib || true
done

# Copy the ArgoDraft lib files and include/ArgoDraft directories to the project directories
for projectDirectory in "${projectDirectories[@]}"
do
    echo "Copying lib files to $projectDirectory"
    
    if [ "$isRelease" = true ]; then
      echo "Copying release files"
      cp -r $currentDirectory/ArgoDraft/build/release/libArgoDraft.* $currentDirectory/$projectDirectory/lib/ || true
      cp -r $currentDirectory/ArgoDraft/build/release/ArgoDraft.* $currentDirectory/$projectDirectory/lib/ || true
    else
      echo "Copying debug files"
      cp -r $currentDirectory/ArgoDraft/build/debug/libArgoDraft.* $currentDirectory/$projectDirectory/lib/ || true
      cp -r $currentDirectory/ArgoDraft/build/debug/ArgoDraft.* $currentDirectory/$projectDirectory/lib/ || true
    fi
    
    echo "Copying include files"
    cp -r $currentDirectory/ArgoDraft/include/* $currentDirectory/$projectDirectory/include/ArgoDraft/  || true
done

cd $currentDirectory
