CXX=g++ -std=c++11 -ggdb3
OBJS=couple.cpp dance.cpp follow.cpp lead.cpp
SYSLIBS=

main: $(OBJS)
	$(CXX)  $(^) Source.cpp -o main $(SYSLIBS)

%.o: %.cpp
	$(CXX) -c $(^) -o $(@) $(SYSLIBS) 

clean:
	rm main
