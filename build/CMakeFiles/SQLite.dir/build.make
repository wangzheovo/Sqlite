# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/desktop/gitrep/Sqlite/Sqlite

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/desktop/gitrep/Sqlite/Sqlite/build

# Include any dependencies generated for this target.
include CMakeFiles/SQLite.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SQLite.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SQLite.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SQLite.dir/flags.make

CMakeFiles/SQLite.dir/main.c.o: CMakeFiles/SQLite.dir/flags.make
CMakeFiles/SQLite.dir/main.c.o: ../main.c
CMakeFiles/SQLite.dir/main.c.o: CMakeFiles/SQLite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/desktop/gitrep/Sqlite/Sqlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SQLite.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SQLite.dir/main.c.o -MF CMakeFiles/SQLite.dir/main.c.o.d -o CMakeFiles/SQLite.dir/main.c.o -c /home/desktop/gitrep/Sqlite/Sqlite/main.c

CMakeFiles/SQLite.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SQLite.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/desktop/gitrep/Sqlite/Sqlite/main.c > CMakeFiles/SQLite.dir/main.c.i

CMakeFiles/SQLite.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SQLite.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/desktop/gitrep/Sqlite/Sqlite/main.c -o CMakeFiles/SQLite.dir/main.c.s

CMakeFiles/SQLite.dir/Constants.c.o: CMakeFiles/SQLite.dir/flags.make
CMakeFiles/SQLite.dir/Constants.c.o: ../Constants.c
CMakeFiles/SQLite.dir/Constants.c.o: CMakeFiles/SQLite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/desktop/gitrep/Sqlite/Sqlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/SQLite.dir/Constants.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SQLite.dir/Constants.c.o -MF CMakeFiles/SQLite.dir/Constants.c.o.d -o CMakeFiles/SQLite.dir/Constants.c.o -c /home/desktop/gitrep/Sqlite/Sqlite/Constants.c

CMakeFiles/SQLite.dir/Constants.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SQLite.dir/Constants.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/desktop/gitrep/Sqlite/Sqlite/Constants.c > CMakeFiles/SQLite.dir/Constants.c.i

CMakeFiles/SQLite.dir/Constants.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SQLite.dir/Constants.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/desktop/gitrep/Sqlite/Sqlite/Constants.c -o CMakeFiles/SQLite.dir/Constants.c.s

CMakeFiles/SQLite.dir/REPL.c.o: CMakeFiles/SQLite.dir/flags.make
CMakeFiles/SQLite.dir/REPL.c.o: ../REPL.c
CMakeFiles/SQLite.dir/REPL.c.o: CMakeFiles/SQLite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/desktop/gitrep/Sqlite/Sqlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/SQLite.dir/REPL.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SQLite.dir/REPL.c.o -MF CMakeFiles/SQLite.dir/REPL.c.o.d -o CMakeFiles/SQLite.dir/REPL.c.o -c /home/desktop/gitrep/Sqlite/Sqlite/REPL.c

CMakeFiles/SQLite.dir/REPL.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SQLite.dir/REPL.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/desktop/gitrep/Sqlite/Sqlite/REPL.c > CMakeFiles/SQLite.dir/REPL.c.i

CMakeFiles/SQLite.dir/REPL.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SQLite.dir/REPL.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/desktop/gitrep/Sqlite/Sqlite/REPL.c -o CMakeFiles/SQLite.dir/REPL.c.s

CMakeFiles/SQLite.dir/SQLCompiler.c.o: CMakeFiles/SQLite.dir/flags.make
CMakeFiles/SQLite.dir/SQLCompiler.c.o: ../SQLCompiler.c
CMakeFiles/SQLite.dir/SQLCompiler.c.o: CMakeFiles/SQLite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/desktop/gitrep/Sqlite/Sqlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/SQLite.dir/SQLCompiler.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SQLite.dir/SQLCompiler.c.o -MF CMakeFiles/SQLite.dir/SQLCompiler.c.o.d -o CMakeFiles/SQLite.dir/SQLCompiler.c.o -c /home/desktop/gitrep/Sqlite/Sqlite/SQLCompiler.c

CMakeFiles/SQLite.dir/SQLCompiler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SQLite.dir/SQLCompiler.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/desktop/gitrep/Sqlite/Sqlite/SQLCompiler.c > CMakeFiles/SQLite.dir/SQLCompiler.c.i

CMakeFiles/SQLite.dir/SQLCompiler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SQLite.dir/SQLCompiler.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/desktop/gitrep/Sqlite/Sqlite/SQLCompiler.c -o CMakeFiles/SQLite.dir/SQLCompiler.c.s

CMakeFiles/SQLite.dir/Pager.c.o: CMakeFiles/SQLite.dir/flags.make
CMakeFiles/SQLite.dir/Pager.c.o: ../Pager.c
CMakeFiles/SQLite.dir/Pager.c.o: CMakeFiles/SQLite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/desktop/gitrep/Sqlite/Sqlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/SQLite.dir/Pager.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SQLite.dir/Pager.c.o -MF CMakeFiles/SQLite.dir/Pager.c.o.d -o CMakeFiles/SQLite.dir/Pager.c.o -c /home/desktop/gitrep/Sqlite/Sqlite/Pager.c

CMakeFiles/SQLite.dir/Pager.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SQLite.dir/Pager.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/desktop/gitrep/Sqlite/Sqlite/Pager.c > CMakeFiles/SQLite.dir/Pager.c.i

CMakeFiles/SQLite.dir/Pager.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SQLite.dir/Pager.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/desktop/gitrep/Sqlite/Sqlite/Pager.c -o CMakeFiles/SQLite.dir/Pager.c.s

CMakeFiles/SQLite.dir/BTree.c.o: CMakeFiles/SQLite.dir/flags.make
CMakeFiles/SQLite.dir/BTree.c.o: ../BTree.c
CMakeFiles/SQLite.dir/BTree.c.o: CMakeFiles/SQLite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/desktop/gitrep/Sqlite/Sqlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/SQLite.dir/BTree.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SQLite.dir/BTree.c.o -MF CMakeFiles/SQLite.dir/BTree.c.o.d -o CMakeFiles/SQLite.dir/BTree.c.o -c /home/desktop/gitrep/Sqlite/Sqlite/BTree.c

CMakeFiles/SQLite.dir/BTree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SQLite.dir/BTree.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/desktop/gitrep/Sqlite/Sqlite/BTree.c > CMakeFiles/SQLite.dir/BTree.c.i

CMakeFiles/SQLite.dir/BTree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SQLite.dir/BTree.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/desktop/gitrep/Sqlite/Sqlite/BTree.c -o CMakeFiles/SQLite.dir/BTree.c.s

CMakeFiles/SQLite.dir/Table.c.o: CMakeFiles/SQLite.dir/flags.make
CMakeFiles/SQLite.dir/Table.c.o: ../Table.c
CMakeFiles/SQLite.dir/Table.c.o: CMakeFiles/SQLite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/desktop/gitrep/Sqlite/Sqlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/SQLite.dir/Table.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SQLite.dir/Table.c.o -MF CMakeFiles/SQLite.dir/Table.c.o.d -o CMakeFiles/SQLite.dir/Table.c.o -c /home/desktop/gitrep/Sqlite/Sqlite/Table.c

CMakeFiles/SQLite.dir/Table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SQLite.dir/Table.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/desktop/gitrep/Sqlite/Sqlite/Table.c > CMakeFiles/SQLite.dir/Table.c.i

CMakeFiles/SQLite.dir/Table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SQLite.dir/Table.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/desktop/gitrep/Sqlite/Sqlite/Table.c -o CMakeFiles/SQLite.dir/Table.c.s

CMakeFiles/SQLite.dir/Cursor.c.o: CMakeFiles/SQLite.dir/flags.make
CMakeFiles/SQLite.dir/Cursor.c.o: ../Cursor.c
CMakeFiles/SQLite.dir/Cursor.c.o: CMakeFiles/SQLite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/desktop/gitrep/Sqlite/Sqlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/SQLite.dir/Cursor.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SQLite.dir/Cursor.c.o -MF CMakeFiles/SQLite.dir/Cursor.c.o.d -o CMakeFiles/SQLite.dir/Cursor.c.o -c /home/desktop/gitrep/Sqlite/Sqlite/Cursor.c

CMakeFiles/SQLite.dir/Cursor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/SQLite.dir/Cursor.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/desktop/gitrep/Sqlite/Sqlite/Cursor.c > CMakeFiles/SQLite.dir/Cursor.c.i

CMakeFiles/SQLite.dir/Cursor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/SQLite.dir/Cursor.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/desktop/gitrep/Sqlite/Sqlite/Cursor.c -o CMakeFiles/SQLite.dir/Cursor.c.s

# Object files for target SQLite
SQLite_OBJECTS = \
"CMakeFiles/SQLite.dir/main.c.o" \
"CMakeFiles/SQLite.dir/Constants.c.o" \
"CMakeFiles/SQLite.dir/REPL.c.o" \
"CMakeFiles/SQLite.dir/SQLCompiler.c.o" \
"CMakeFiles/SQLite.dir/Pager.c.o" \
"CMakeFiles/SQLite.dir/BTree.c.o" \
"CMakeFiles/SQLite.dir/Table.c.o" \
"CMakeFiles/SQLite.dir/Cursor.c.o"

# External object files for target SQLite
SQLite_EXTERNAL_OBJECTS =

db: CMakeFiles/SQLite.dir/main.c.o
db: CMakeFiles/SQLite.dir/Constants.c.o
db: CMakeFiles/SQLite.dir/REPL.c.o
db: CMakeFiles/SQLite.dir/SQLCompiler.c.o
db: CMakeFiles/SQLite.dir/Pager.c.o
db: CMakeFiles/SQLite.dir/BTree.c.o
db: CMakeFiles/SQLite.dir/Table.c.o
db: CMakeFiles/SQLite.dir/Cursor.c.o
db: CMakeFiles/SQLite.dir/build.make
db: CMakeFiles/SQLite.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/desktop/gitrep/Sqlite/Sqlite/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable db"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SQLite.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SQLite.dir/build: db
.PHONY : CMakeFiles/SQLite.dir/build

CMakeFiles/SQLite.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SQLite.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SQLite.dir/clean

CMakeFiles/SQLite.dir/depend:
	cd /home/desktop/gitrep/Sqlite/Sqlite/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/desktop/gitrep/Sqlite/Sqlite /home/desktop/gitrep/Sqlite/Sqlite /home/desktop/gitrep/Sqlite/Sqlite/build /home/desktop/gitrep/Sqlite/Sqlite/build /home/desktop/gitrep/Sqlite/Sqlite/build/CMakeFiles/SQLite.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SQLite.dir/depend
