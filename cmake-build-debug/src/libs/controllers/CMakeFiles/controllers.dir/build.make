# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/nick/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.7223.86/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/nick/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.7223.86/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug"

# Include any dependencies generated for this target.
include src/libs/controllers/CMakeFiles/controllers.dir/depend.make

# Include the progress variables for this target.
include src/libs/controllers/CMakeFiles/controllers.dir/progress.make

# Include the compile flags for this target's objects.
include src/libs/controllers/CMakeFiles/controllers.dir/flags.make

src/libs/controllers/CMakeFiles/controllers.dir/source/controller_header.cpp.o: src/libs/controllers/CMakeFiles/controllers.dir/flags.make
src/libs/controllers/CMakeFiles/controllers.dir/source/controller_header.cpp.o: ../src/libs/controllers/source/controller_header.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/libs/controllers/CMakeFiles/controllers.dir/source/controller_header.cpp.o"
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug/src/libs/controllers" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/controllers.dir/source/controller_header.cpp.o -c "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/src/libs/controllers/source/controller_header.cpp"

src/libs/controllers/CMakeFiles/controllers.dir/source/controller_header.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/controllers.dir/source/controller_header.cpp.i"
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug/src/libs/controllers" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/src/libs/controllers/source/controller_header.cpp" > CMakeFiles/controllers.dir/source/controller_header.cpp.i

src/libs/controllers/CMakeFiles/controllers.dir/source/controller_header.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/controllers.dir/source/controller_header.cpp.s"
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug/src/libs/controllers" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/src/libs/controllers/source/controller_header.cpp" -o CMakeFiles/controllers.dir/source/controller_header.cpp.s

# Object files for target controllers
controllers_OBJECTS = \
"CMakeFiles/controllers.dir/source/controller_header.cpp.o"

# External object files for target controllers
controllers_EXTERNAL_OBJECTS =

src/libs/controllers/libcontrollers.a: src/libs/controllers/CMakeFiles/controllers.dir/source/controller_header.cpp.o
src/libs/controllers/libcontrollers.a: src/libs/controllers/CMakeFiles/controllers.dir/build.make
src/libs/controllers/libcontrollers.a: src/libs/controllers/CMakeFiles/controllers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcontrollers.a"
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug/src/libs/controllers" && $(CMAKE_COMMAND) -P CMakeFiles/controllers.dir/cmake_clean_target.cmake
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug/src/libs/controllers" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/controllers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/libs/controllers/CMakeFiles/controllers.dir/build: src/libs/controllers/libcontrollers.a

.PHONY : src/libs/controllers/CMakeFiles/controllers.dir/build

src/libs/controllers/CMakeFiles/controllers.dir/clean:
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug/src/libs/controllers" && $(CMAKE_COMMAND) -P CMakeFiles/controllers.dir/cmake_clean.cmake
.PHONY : src/libs/controllers/CMakeFiles/controllers.dir/clean

src/libs/controllers/CMakeFiles/controllers.dir/depend:
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend" "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/src/libs/controllers" "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug" "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug/src/libs/controllers" "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/cmake-build-debug/src/libs/controllers/CMakeFiles/controllers.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/libs/controllers/CMakeFiles/controllers.dir/depend

