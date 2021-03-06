# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = g++
CC  = g++

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of GNU's libstdc++.
# -g is for debugging.
CPPFLAGS =  -std=c++11
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast 
CXXFLAGS += -std=c++11
CXXFLAGS += -g
LDFLAGS =   -g 
#CPPFLAGS += -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

# Targets
PROGS = src/client/news_client  src/server/news_server_file_storage src/server/news_server_cache_storage

all: $(PROGS)
	mv src/client/news_client bin/
	mv src/server/news_server_file_storage bin/
	mv src/server/news_server_cache_storage bin/

# Targets rely on implicit rules for compiling and linking
src/client/news_client: src/client/news_client.o src/client/client_command_handler.o src/common/message_handler.o src/common/connection.o src/client/user_input_handler.o
src/server/news_server_file_storage: src/server/news_server_file_storage.o src/server/news_server.o src/server/server_command_handler.o src/server/main_database.o src/common/server.o src/common/message_handler.o src/common/connection.o
src/server/news_server_cache_storage: src/server/news_server_cache_storage.o src/server/news_server.o src/server/server_command_handler.o src/server/cache_database.o src/common/server.o src/common/message_handler.o src/common/connection.o

# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f *.o $(PROGS)
	rm -f src/client/*.o
	rm -f src/server/*.o
	rm -f src/common/*.o
	rm -f src/common/exception/*.o
	rm -f *.d
	rm -f bin/news_client
	rm -f bin/news_server_cache_storage
	rm -f bin/news_server_file_storage
	
# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)