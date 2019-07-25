src=$(wildcard ./*.cpp)
obj=$(patsubst %.cpp,%.o,$(src))
target=app
$(target):$(obj)
	g++ $(obj) -o $(target) 
%.o:%.c
	g++ -c $< -o $@ 
selecter:
	echo "makefile selecter"
.PHONY:clean
clean:
	-rm $(obj) $(target) -f

