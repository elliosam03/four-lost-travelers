TARGET_EXEC := main


# Find all the C and C++ files we want to compile
SRCS := $(wildcard *.cpp)
# Create the object targets
OBJS := $(SRCS:%=%.o)

CPPFLAGS :=  -pedantic-errors -fdiagnostics-color=always -g

# The final build step.
$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)


# Build step for C++ source
%.cpp.o: %.cpp	
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r *.o *.d main 


