CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -Weffc++ -Wpedantic \
           -Wold-style-cast -Winit-self -Wno-unused -Wshadow \
           -Wno-parentheses -Wlogical-op -Wredundant-decls \
           -Wcast-align -Wsign-promo -Wmissing-include-dirs \
           -Woverloaded-virtual -Wctor-dtor-privacy

EXECUTABLE = raii
SOURCES = ${wildcard *.cpp}
HEADERS = ${wildcard *.h}
OBJECTS = ${SOURCES:.cpp=.o}

.PHONY: all
all: ${EXECUTABLE}

$(EXECUTABLE): $(OBJECTS) buildnumber.num
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDXXFLAGS) -o $@
	@echo "-- Build: " $$(cat buildnumber.num)

# Create dependency file compiler option -MM
depend: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM  $^ > $@

-include depend

# Buildnumber
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

