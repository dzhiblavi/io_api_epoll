# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/test_main.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/test_main.cpp.o: ../test_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/test_main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/test_main.cpp.o -c /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/test_main.cpp

CMakeFiles/test.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/test_main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/test_main.cpp > CMakeFiles/test.dir/test_main.cpp.i

CMakeFiles/test.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/test_main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/test_main.cpp -o CMakeFiles/test.dir/test_main.cpp.s

CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.o: /home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.o -c /home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc

CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc > CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.i

CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc -o CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.s

CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.o: /home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.o -c /home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc

CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc > CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.i

CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc -o CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.s

CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.o: /home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.o -c /home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp

CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp > CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.i

CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp -o CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.s

CMakeFiles/test.dir/address.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/address.cpp.o: ../address.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/test.dir/address.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/address.cpp.o -c /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/address.cpp

CMakeFiles/test.dir/address.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/address.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/address.cpp > CMakeFiles/test.dir/address.cpp.i

CMakeFiles/test.dir/address.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/address.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/address.cpp -o CMakeFiles/test.dir/address.cpp.s

CMakeFiles/test.dir/unique_fd.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/unique_fd.cpp.o: ../unique_fd.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/test.dir/unique_fd.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/unique_fd.cpp.o -c /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/unique_fd.cpp

CMakeFiles/test.dir/unique_fd.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/unique_fd.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/unique_fd.cpp > CMakeFiles/test.dir/unique_fd.cpp.i

CMakeFiles/test.dir/unique_fd.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/unique_fd.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/unique_fd.cpp -o CMakeFiles/test.dir/unique_fd.cpp.s

CMakeFiles/test.dir/io_api.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/io_api.cpp.o: ../io_api.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/test.dir/io_api.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/io_api.cpp.o -c /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/io_api.cpp

CMakeFiles/test.dir/io_api.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/io_api.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/io_api.cpp > CMakeFiles/test.dir/io_api.cpp.i

CMakeFiles/test.dir/io_api.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/io_api.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/io_api.cpp -o CMakeFiles/test.dir/io_api.cpp.s

CMakeFiles/test.dir/socket.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/socket.cpp.o: ../socket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/test.dir/socket.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/socket.cpp.o -c /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/socket.cpp

CMakeFiles/test.dir/socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/socket.cpp > CMakeFiles/test.dir/socket.cpp.i

CMakeFiles/test.dir/socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/socket.cpp -o CMakeFiles/test.dir/socket.cpp.s

CMakeFiles/test.dir/getaddrinfo_server.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/getaddrinfo_server.cpp.o: ../getaddrinfo_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/test.dir/getaddrinfo_server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/getaddrinfo_server.cpp.o -c /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/getaddrinfo_server.cpp

CMakeFiles/test.dir/getaddrinfo_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/getaddrinfo_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/getaddrinfo_server.cpp > CMakeFiles/test.dir/getaddrinfo_server.cpp.i

CMakeFiles/test.dir/getaddrinfo_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/getaddrinfo_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/getaddrinfo_server.cpp -o CMakeFiles/test.dir/getaddrinfo_server.cpp.s

CMakeFiles/test.dir/timer.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/timer.cpp.o: ../timer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/test.dir/timer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/timer.cpp.o -c /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/timer.cpp

CMakeFiles/test.dir/timer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/timer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/timer.cpp > CMakeFiles/test.dir/timer.cpp.i

CMakeFiles/test.dir/timer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/timer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/timer.cpp -o CMakeFiles/test.dir/timer.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/test_main.cpp.o" \
"CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.o" \
"CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.o" \
"CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.o" \
"CMakeFiles/test.dir/address.cpp.o" \
"CMakeFiles/test.dir/unique_fd.cpp.o" \
"CMakeFiles/test.dir/io_api.cpp.o" \
"CMakeFiles/test.dir/socket.cpp.o" \
"CMakeFiles/test.dir/getaddrinfo_server.cpp.o" \
"CMakeFiles/test.dir/timer.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test: CMakeFiles/test.dir/test_main.cpp.o
test: CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest-all.cc.o
test: CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/gtest/gtest_main.cc.o
test: CMakeFiles/test.dir/home/dzhiblavi/Documents/prog/cpp/code/dthread/dthread.cpp.o
test: CMakeFiles/test.dir/address.cpp.o
test: CMakeFiles/test.dir/unique_fd.cpp.o
test: CMakeFiles/test.dir/io_api.cpp.o
test: CMakeFiles/test.dir/socket.cpp.o
test: CMakeFiles/test.dir/getaddrinfo_server.cpp.o
test: CMakeFiles/test.dir/timer.cpp.o
test: CMakeFiles/test.dir/build.make
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test

.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build /home/dzhiblavi/Documents/prog/cpp/code/io_api_epoll/build/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

