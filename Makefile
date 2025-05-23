CXX = g++

CXXFLAGS = -Wall -Wextra

SRCS = main.cpp

HEADERS = patient.h sorter.h

TARGET = lab1


$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Правило для очистки
clean:
	rm -f $(TARGET)
	rm -rf output
	rm -f output.py
#	rm -f *.o

.PHONY: all clean
