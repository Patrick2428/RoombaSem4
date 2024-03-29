CXX = g++
INCLUDING = -I./../../MQTT-SenseHAT-Utils/_libUtils/SerialLink
CXXFLAGS = -std=c++17 -Wall -Wextra -Weffc++ -Wpedantic \
           -Wcast-align -Wcast-qual -Wctor-dtor-privacy \
           -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op \
           -Wmissing-include-dirs -Wnoexcept -Wold-style-cast \
           -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo \
           -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused \
           -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option \
           -D_GLIBCXX_USE_NANOSLEEP \
           -Os $(INCLUDING)
LDFLAGS = -lboost_system -pthread

EXECUTABLE = serialLinkDemo
SOURCES = ${wildcard *.cpp} \
          ${wildcard ../../MQTT-SenseHAT-Utils/_libUtils/SerialLink/*.cpp}
HEADERS = ${wildcard *.h} \
          ${wildcard ../../MQTT-SenseHAT-Utils/_libUtils/SerialLink/*.h}
OBJECTS = ${SOURCES:.cpp=.o}

.PHONY: all
all: ${EXECUTABLE}

$(EXECUTABLE): $(OBJECTS) buildnumber.num
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
	@echo "-- Build: " $$(cat buildnumber.num)

# Create dependency file using the compiler option -MM
depend: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM  $^ > $@

-include depend

# Buildnumber in text file
buildnumber.num: $(OBJECTS)
	@if ! test -f buildnumber.num; then echo 0 > buildnumber.num; fi
	@echo $$(($$(cat buildnumber.num)+1)) > buildnumber.num

# Create a clean environment
.PHONY: clean
clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

# Clean up dependency file
.PHONY: clean-depend
clean-depend: clean
	$(RM) depend
