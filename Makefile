# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/joao/Desktop/Joao_Redesign

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joao/Desktop/Joao_Redesign

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/joao/Desktop/Joao_Redesign/CMakeFiles /home/joao/Desktop/Joao_Redesign/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/joao/Desktop/Joao_Redesign/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named FaceRec

# Build rule for target.
FaceRec: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 FaceRec
.PHONY : FaceRec

# fast build rule for target.
FaceRec/fast:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/build
.PHONY : FaceRec/fast

Source/Detection.o: Source/Detection.cpp.o

.PHONY : Source/Detection.o

# target to build an object file
Source/Detection.cpp.o:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Detection.cpp.o
.PHONY : Source/Detection.cpp.o

Source/Detection.i: Source/Detection.cpp.i

.PHONY : Source/Detection.i

# target to preprocess a source file
Source/Detection.cpp.i:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Detection.cpp.i
.PHONY : Source/Detection.cpp.i

Source/Detection.s: Source/Detection.cpp.s

.PHONY : Source/Detection.s

# target to generate assembly for a file
Source/Detection.cpp.s:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Detection.cpp.s
.PHONY : Source/Detection.cpp.s

Source/Feature.o: Source/Feature.cpp.o

.PHONY : Source/Feature.o

# target to build an object file
Source/Feature.cpp.o:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Feature.cpp.o
.PHONY : Source/Feature.cpp.o

Source/Feature.i: Source/Feature.cpp.i

.PHONY : Source/Feature.i

# target to preprocess a source file
Source/Feature.cpp.i:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Feature.cpp.i
.PHONY : Source/Feature.cpp.i

Source/Feature.s: Source/Feature.cpp.s

.PHONY : Source/Feature.s

# target to generate assembly for a file
Source/Feature.cpp.s:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Feature.cpp.s
.PHONY : Source/Feature.cpp.s

Source/MainDetector.o: Source/MainDetector.cpp.o

.PHONY : Source/MainDetector.o

# target to build an object file
Source/MainDetector.cpp.o:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/MainDetector.cpp.o
.PHONY : Source/MainDetector.cpp.o

Source/MainDetector.i: Source/MainDetector.cpp.i

.PHONY : Source/MainDetector.i

# target to preprocess a source file
Source/MainDetector.cpp.i:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/MainDetector.cpp.i
.PHONY : Source/MainDetector.cpp.i

Source/MainDetector.s: Source/MainDetector.cpp.s

.PHONY : Source/MainDetector.s

# target to generate assembly for a file
Source/MainDetector.cpp.s:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/MainDetector.cpp.s
.PHONY : Source/MainDetector.cpp.s

Source/Track.o: Source/Track.cpp.o

.PHONY : Source/Track.o

# target to build an object file
Source/Track.cpp.o:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Track.cpp.o
.PHONY : Source/Track.cpp.o

Source/Track.i: Source/Track.cpp.i

.PHONY : Source/Track.i

# target to preprocess a source file
Source/Track.cpp.i:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Track.cpp.i
.PHONY : Source/Track.cpp.i

Source/Track.s: Source/Track.cpp.s

.PHONY : Source/Track.s

# target to generate assembly for a file
Source/Track.cpp.s:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Track.cpp.s
.PHONY : Source/Track.cpp.s

Source/Util.o: Source/Util.cpp.o

.PHONY : Source/Util.o

# target to build an object file
Source/Util.cpp.o:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Util.cpp.o
.PHONY : Source/Util.cpp.o

Source/Util.i: Source/Util.cpp.i

.PHONY : Source/Util.i

# target to preprocess a source file
Source/Util.cpp.i:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Util.cpp.i
.PHONY : Source/Util.cpp.i

Source/Util.s: Source/Util.cpp.s

.PHONY : Source/Util.s

# target to generate assembly for a file
Source/Util.cpp.s:
	$(MAKE) -f CMakeFiles/FaceRec.dir/build.make CMakeFiles/FaceRec.dir/Source/Util.cpp.s
.PHONY : Source/Util.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... FaceRec"
	@echo "... edit_cache"
	@echo "... Source/Detection.o"
	@echo "... Source/Detection.i"
	@echo "... Source/Detection.s"
	@echo "... Source/Feature.o"
	@echo "... Source/Feature.i"
	@echo "... Source/Feature.s"
	@echo "... Source/MainDetector.o"
	@echo "... Source/MainDetector.i"
	@echo "... Source/MainDetector.s"
	@echo "... Source/Track.o"
	@echo "... Source/Track.i"
	@echo "... Source/Track.s"
	@echo "... Source/Util.o"
	@echo "... Source/Util.i"
	@echo "... Source/Util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

