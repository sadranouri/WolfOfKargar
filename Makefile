CXX = g++
CXXFLAGS = -std=c++20 -Wall

TARGET = UTTrade

OBJS = buyOrder.o company.o readCSV.o sellOrder.o shareholder.o wolfOfKargar.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f *.o $(TARGET)