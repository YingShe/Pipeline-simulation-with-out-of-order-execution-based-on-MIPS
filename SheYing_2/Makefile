CXX = g++
CXXFLAGS = -g -Wall

vpath %.cpp src

sourcefile = $(wildcard src/*.cpp)
objectfile = $(patsubst %.cpp, %.o, $(patsubst src%, obj%, $(sourcefile)))


bin/MIPSsim: $(objectfile)
	$(CXX) -o $@ $(objectfile)

obj/%.o: %.cpp
	$(CXX) -c $^ -o $@ -Iinclude

.PHONY:	clean cleanall
clean:
	-rm -rf $(objectfile)
cleanall:
	-rm -rf $(objectfile) bin/MIPSsim
