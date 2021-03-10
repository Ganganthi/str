CPP_FILES = $(wildcard *.cpp)

make:
	g++ -o exec $(CPP_FILES) -Wall -lrt
	sudo setcap cap_sys_nice=ep ./exec
	taskset -c 0 ./exec 

clean:
	rm -rf *.o exec 
	clear