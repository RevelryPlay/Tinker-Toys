# Use cmake to build the project in the ArgoDraft directory
# copy the output .a, .so, and .lib files to the lib directory of the Net Toys, OpenGL/Imgui, OpenGL/UI-Basics, and Threaded directories
# copy the files in ArgoDraft/include directory to the Net Toys, OpenGL/Imgui, OpenGL/UI-Basics, and Threaded include/ArgoDraft directories

projectDirectories=("NetToys" "OpenGL/Imgui" "OpenGL/UI-Basics" "Threaded")
currentDirectory=$(pwd)

cd ArgoDraft

# Build the project in the ArgoDraft directory to a build/debug and build/release directory
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build/debug
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release

# Remove the existing ArgoDraft lib files and include/ArgoDraft directories in the project directories
for projectDirectory in "${projectDirectories[@]}"
do
    rm -rf $currentDirectory/$projectDirectory/lib/ArgoDraft.* || true
    rm -rf $currentDirectory/$projectDirectory/include/ArgoDraft || true
done

# Create the include/ArgoDraft directories in the project directories
for projectDirectory in "${projectDirectories[@]}"
do
    mkdir $currentDirectory/$projectDirectory/include || true
    mkdir $currentDirectory/$projectDirectory/include/ArgoDraft || true
done

# Create the lib directories in the project directories
for projectDirectory in "${projectDirectories[@]}"
do
    mkdir $currentDirectory/$projectDirectory/lib || true
done

# Copy the ArgoDraft lib files and include/ArgoDraft directories to the project directories
for projectDirectory in "${projectDirectories[@]}"
do
    cp -r $currentDirectory/ArgoDraft/build/debug/libArgoDraft.* $currentDirectory/$projectDirectory/lib/ || true
    cp -r $currentDirectory/ArgoDraft/build/debug/ArgoDraft.* $currentDirectory/$projectDirectory/lib/ || true
    cp -r $currentDirectory/ArgoDraft/include/* $currentDirectory/$projectDirectory/include/ArgoDraft/  || true
done

cd $currentDirectory
