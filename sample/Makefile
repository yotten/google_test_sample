TARGET = sampleTest
GTEST_HEADERS = ./test
GTEST_DIR = ./test/gtest
CXX = g++
CPPFLAGS += -isystem $(GTEST_HEADERS)
CXXFLAGS += -g -Wall -Wextra -pthread
CC = gcc

all : $(TARGET)

gtest-all.o : $(GTEST_DIR)/gtest-all.cc
	$(CXX) -I$(GTEST_HEADERS) -c $(GTEST_DIR)/gtest-all.cc
#g++ -I./ -c gtest/gtest-all.cc
gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_HEADERS) $(CXXFLAGS) -c $(GTEST_DIR)/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

sampleTest.o : sampleTest.c $(GTEST_HEADERS)
	$(CXX) -I$(GTEST_HEADERS) $(CPPFLAGS) $(CXXFLAGS) -c sampleTest.c

sample.o : sample.c $(GTEST_HEADERS)
	$(CC) -I./sample.h $(CPPFLAGS) $(CXXFLAGS) -c sample.c
$(TARGET) : sample.o sampleTest.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@


clean :
	$(RM) $(TARGET) gtest.a gtest_main.a *.o
