CC = g++
STD = -std=c++20
TARGET = UTaste
SRCS = main.cpp interface.cpp process.cpp software.cpp put.cpp get.cpp post.cpp delete.cpp resturan.cpp district.cpp discount.cpp user.cpp error.cpp output.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(STD) -g -o $(TARGET) $(OBJS)

%.o: %.cpp	
	$(CC) $(STD) -c $< -o $@

clean:	
	rm -f $(OBJS) 
