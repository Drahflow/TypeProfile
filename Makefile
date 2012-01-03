CCFLAGS=-W -Wall -Wextra -Werror

all: typeprofile typemeasure

typeprofile: typeprofile.o Profile.o
	g++ $(CCFLAGS) $^ -o $@

typemeasure: typemeasure.o Profile.o ProfileArray.o
	g++ $(CCFLAGS) $^ -o $@

%.o: %.c++
	g++ $(CCFLAGS) -c -o $@ $^

.PHONY: all
