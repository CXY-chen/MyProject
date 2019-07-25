src=$(wildcard ./*.cpp)
obj=$(patsubst %.cpp,%.o,$(src))
target=app
$(target):$(obj)
	g++ $(obj) -o $(target)  -levent -ljson -lpthread -lssl 
%.o:%.c
	g++ -c $< -o $@  
balanceServer:
	echo "makefile balanceServer"
.PHONY:clean
clean:
	-rm $(obj) $(target) -f

