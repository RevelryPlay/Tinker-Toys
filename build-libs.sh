# Use cmake to build the project in the ArgoDraft directory
# copy the output .a, .so, and .lib files to the lib directory of the Net Toys, OpenGL/Imgui, OpenGL/UI-Basics, and Threaded directories
# copy the files in ArgoDraft/include directory to the Net Toys, OpenGL/Imgui, OpenGL/UI-Basics, and Threaded include/ArgoDraft directories

projectDirectories=("NetToys" "OpenGL/Imgui" "OpenGL/UI-Basics" "Threaded")
isRelease=false

  cd ArgoDraft || exit
  
  # Build the project in the ArgoDraft directory to a ArgoDraft/build/debug and ArgoDraft/build/release directory
  if [ "$1" == "release" ]; then
    isRelease=true
            
    # If Windows
    if [[ "$OSTYPE" == "msys" ]]; then
        # Remove the existing build directory
        rm -rf build || true
        
        echo "Building release on Windows"
        # Currently the other projects are only linking correctly for .a files and I am not sure how to link the 
        # .lib or .dll files in the other projects. I will need to figure this out later.
        cmake -DCMAKE_BUILD_TYPE=Release -S . -B build/release
    else
        # Remove the existing build directory
        rm -rf build || true
      
        echo "Building release on Unix"
        cmake -DCMAKE_BUILD_TYPE=Release -S . -B build/release
    fi 
      
    cmake --build build/release
      
  else
    if [[ "$OSTYPE" == "msys" ]]; then
      # Remove the existing build directory
      rm -rf build || true
      
      echo "Building debug on Windows"
      # Currently the other projects are only linking correctly for .a files and I am not sure how to link the 
      # .lib or .dll files in the other projects. I will need to figure this out later.
      cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug
    else
      # Remove the existing build directory
      rm -rf build || true
      
      echo "Building debug on Unix"
      cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build/debug
    fi
    
    cmake --build build/debug
  fi
  
  # Remove the existing ArgoDraft lib files and include/ArgoDraft directories in the project directories
  for projectDirectory in "${projectDirectories[@]}"
  do
      echo "Removing existing files in $projectDirectory"
      rm -rf "../$projectDirectory/lib/ArgoDraft.*" || true
      rm -rf "../$projectDirectory/lib/libArgoDraft.*" || true
      rm -rf "../$projectDirectory/include/ArgoDraft" || true
  done
  
  # Create the include/ArgoDraft directories in the project directories
  for projectDirectory in "${projectDirectories[@]}"
  do
      echo "Creating include directories in $projectDirectory"
      mkdir "../$projectDirectory/include" || true
      mkdir "../$projectDirectory/include/ArgoDraft" || true
  done
  
  # Create the lib directories in the project directories
  for projectDirectory in "${projectDirectories[@]}"
  do
      echo "Creating lib directory in $projectDirectory"
      mkdir "../$projectDirectory/lib" || true
  done
  
  # Copy the ArgoDraft lib files and include/ArgoDraft directories to the project directories
  for projectDirectory in "${projectDirectories[@]}"
  do
      echo "Copying lib files to $projectDirectory"
      
      if [ "$isRelease" = true ]; then
        echo "Copying release files"
        
        # If Windows there is an additional Release directory
        if [ -d "build/release/Release" ]; then
          cp -r build/release/Release/ArgoDraft.* "../$projectDirectory/lib/" || true
        else
          cp -r build/release/ArgoDraft.* "../$projectDirectory/lib/" || true
          cp -r build/release/libArgoDraft.* "../$projectDirectory/lib/" || true
        fi
      else
        echo "Copying debug files"
        
        # If Windows there is an additional Debug directory
        if [ -d "build/debug/Debug" ]; then
          cp -r build/debug/Debug/ArgoDraft.* "../$projectDirectory/lib/" || true
        else
          cp -r build/debug/ArgoDraft.* "../$projectDirectory/lib/" || true
          cp -r build/debug/libArgoDraft.* "../$projectDirectory/lib/" || true
        fi
      fi
      
      echo "Copying include files"
      cp -r include/* "../$projectDirectory/include/ArgoDraft/" || true
  done
  
  cd "../" || exit
