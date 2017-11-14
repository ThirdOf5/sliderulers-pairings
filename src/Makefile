CXX=g++ -std=c++11
OBJS=couple.cpp dance.cpp follow.cpp lead.cpp
SYSLIBS=

main: $(OBJS)
	$(CXX)  $(^) Source.cpp -o main $(SYSLIBS)

%.o: %.cpp
	$(CXX) -c $(^) -o $(@) $(SYSLIBS) 

clean:
	rm main *.o
