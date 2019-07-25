src=$(wildcard ./*.cpp)
obj=$(patsubst %.cpp,%.o,$(src))
target=app
$(target):$(obj)
	g++ $(obj) -o $(target) -levent -ljson -lpthread 
%.o:%.c
	g++ -c $< -o $@ 
localClient:
	echo "makefile localClient"
.PHONY:clean
clean:
	-rm $(obj) $(target) -f

