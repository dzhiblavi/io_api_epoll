# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.0_1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.0_1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/main.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/main.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/main.cpp

CMakeFiles/server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/main.cpp > CMakeFiles/server.dir/main.cpp.i

CMakeFiles/server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/main.cpp -o CMakeFiles/server.dir/main.cpp.s

CMakeFiles/server.dir/dthread/dthread.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/dthread/dthread.cpp.o: ../dthread/dthread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/dthread/dthread.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/dthread/dthread.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/dthread/dthread.cpp

CMakeFiles/server.dir/dthread/dthread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/dthread/dthread.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/dthread/dthread.cpp > CMakeFiles/server.dir/dthread/dthread.cpp.i

CMakeFiles/server.dir/dthread/dthread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/dthread/dthread.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/dthread/dthread.cpp -o CMakeFiles/server.dir/dthread/dthread.cpp.s

CMakeFiles/server.dir/getaddrinfo_server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/getaddrinfo_server.cpp.o: ../getaddrinfo_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/getaddrinfo_server.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/getaddrinfo_server.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/getaddrinfo_server.cpp

CMakeFiles/server.dir/getaddrinfo_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/getaddrinfo_server.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/getaddrinfo_server.cpp > CMakeFiles/server.dir/getaddrinfo_server.cpp.i

CMakeFiles/server.dir/getaddrinfo_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/getaddrinfo_server.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/getaddrinfo_server.cpp -o CMakeFiles/server.dir/getaddrinfo_server.cpp.s

CMakeFiles/server.dir/src/address.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/address.cpp.o: ../src/address.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/src/address.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/address.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/address.cpp

CMakeFiles/server.dir/src/address.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/address.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/address.cpp > CMakeFiles/server.dir/src/address.cpp.i

CMakeFiles/server.dir/src/address.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/address.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/address.cpp -o CMakeFiles/server.dir/src/address.cpp.s

CMakeFiles/server.dir/src/io_api.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/io_api.cpp.o: ../src/io_api.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server.dir/src/io_api.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/io_api.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/io_api.cpp

CMakeFiles/server.dir/src/io_api.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/io_api.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/io_api.cpp > CMakeFiles/server.dir/src/io_api.cpp.i

CMakeFiles/server.dir/src/io_api.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/io_api.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/io_api.cpp -o CMakeFiles/server.dir/src/io_api.cpp.s

CMakeFiles/server.dir/src/socket.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/socket.cpp.o: ../src/socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server.dir/src/socket.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/socket.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/socket.cpp

CMakeFiles/server.dir/src/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/socket.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/socket.cpp > CMakeFiles/server.dir/src/socket.cpp.i

CMakeFiles/server.dir/src/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/socket.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/socket.cpp -o CMakeFiles/server.dir/src/socket.cpp.s

CMakeFiles/server.dir/src/timer.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/timer.cpp.o: ../src/timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/server.dir/src/timer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/timer.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/timer.cpp

CMakeFiles/server.dir/src/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/timer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/timer.cpp > CMakeFiles/server.dir/src/timer.cpp.i

CMakeFiles/server.dir/src/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/timer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/timer.cpp -o CMakeFiles/server.dir/src/timer.cpp.s

CMakeFiles/server.dir/src/poll.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/poll.cpp.o: ../src/poll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/server.dir/src/poll.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/src/poll.cpp.o -c /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/poll.cpp

CMakeFiles/server.dir/src/poll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/poll.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/poll.cpp > CMakeFiles/server.dir/src/poll.cpp.i

CMakeFiles/server.dir/src/poll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/poll.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/src/poll.cpp -o CMakeFiles/server.dir/src/poll.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/main.cpp.o" \
"CMakeFiles/server.dir/dthread/dthread.cpp.o" \
"CMakeFiles/server.dir/getaddrinfo_server.cpp.o" \
"CMakeFiles/server.dir/src/address.cpp.o" \
"CMakeFiles/server.dir/src/io_api.cpp.o" \
"CMakeFiles/server.dir/src/socket.cpp.o" \
"CMakeFiles/server.dir/src/timer.cpp.o" \
"CMakeFiles/server.dir/src/poll.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/main.cpp.o
server: CMakeFiles/server.dir/dthread/dthread.cpp.o
server: CMakeFiles/server.dir/getaddrinfo_server.cpp.o
server: CMakeFiles/server.dir/src/address.cpp.o
server: CMakeFiles/server.dir/src/io_api.cpp.o
server: CMakeFiles/server.dir/src/socket.cpp.o
server: CMakeFiles/server.dir/src/timer.cpp.o
server: CMakeFiles/server.dir/src/poll.cpp.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build /Users/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend
