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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild"

# Include any dependencies generated for this target.
include src/libs/serialize/CMakeFiles/serialize.dir/depend.make

# Include the progress variables for this target.
include src/libs/serialize/CMakeFiles/serialize.dir/progress.make

# Include the compile flags for this target's objects.
include src/libs/serialize/CMakeFiles/serialize.dir/flags.make

src/libs/serialize/CMakeFiles/serialize.dir/source/serialize.cpp.o: src/libs/serialize/CMakeFiles/serialize.dir/flags.make
src/libs/serialize/CMakeFiles/serialize.dir/source/serialize.cpp.o: ../src/libs/serialize/source/serialize.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/libs/serialize/CMakeFiles/serialize.dir/source/serialize.cpp.o"
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/serialize" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serialize.dir/source/serialize.cpp.o -c "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/src/libs/serialize/source/serialize.cpp"

src/libs/serialize/CMakeFiles/serialize.dir/source/serialize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serialize.dir/source/serialize.cpp.i"
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/serialize" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/src/libs/serialize/source/serialize.cpp" > CMakeFiles/serialize.dir/source/serialize.cpp.i

src/libs/serialize/CMakeFiles/serialize.dir/source/serialize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serialize.dir/source/serialize.cpp.s"
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/serialize" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/src/libs/serialize/source/serialize.cpp" -o CMakeFiles/serialize.dir/source/serialize.cpp.s

# Object files for target serialize
serialize_OBJECTS = \
"CMakeFiles/serialize.dir/source/serialize.cpp.o"

# External object files for target serialize
serialize_EXTERNAL_OBJECTS =

src/libs/serialize/libserialize.a: src/libs/serialize/CMakeFiles/serialize.dir/source/serialize.cpp.o
src/libs/serialize/libserialize.a: src/libs/serialize/CMakeFiles/serialize.dir/build.make
src/libs/serialize/libserialize.a: src/libs/serialize/CMakeFiles/serialize.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libserialize.a"
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/serialize" && $(CMAKE_COMMAND) -P CMakeFiles/serialize.dir/cmake_clean_target.cmake
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/serialize" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serialize.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/libs/serialize/CMakeFiles/serialize.dir/build: src/libs/serialize/libserialize.a

.PHONY : src/libs/serialize/CMakeFiles/serialize.dir/build

src/libs/serialize/CMakeFiles/serialize.dir/clean:
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/serialize" && $(CMAKE_COMMAND) -P CMakeFiles/serialize.dir/cmake_clean.cmake
.PHONY : src/libs/serialize/CMakeFiles/serialize.dir/clean

src/libs/serialize/CMakeFiles/serialize.dir/depend:
	cd "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend" "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/src/libs/serialize" "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild" "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/serialize" "/home/nick/Desktop/МГТУ/Технопарк/Программирование на C и CPP/twitter-backend/mybuild/src/libs/serialize/CMakeFiles/serialize.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/libs/serialize/CMakeFiles/serialize.dir/depend

