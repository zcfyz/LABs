# makefile

# Имя компилятора
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17

# Исходные файлы
SOURCES = main.cpp DynamicArray.cpp DoubleLinkedList.cpp Stack.cpp ReversePolishNotation.cpp

# Объектные файлы
OBJECTS = $(SOURCES:.cpp=.o)

# Имя исполняемого файла
EXECUTABLE = calc

# Цель по умолчанию
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(CXXFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)