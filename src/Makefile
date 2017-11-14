CXX=g++ -std=c++11
OBJS=
SYSLIBS=

main: $(OBJS)
	$(CXX)  $(^) Source.cpp -o Source $(SYSLIBS)

%.o: %.cpp
	$(CXX) -c $(^) -o $(@) $(SYSLIBS) 

clean:
	rm Source *.o
