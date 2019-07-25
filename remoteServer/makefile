src=$(wildcard ./*.cpp)
obj=$(patsubst %.cpp,%.o,$(src))
target=app
$(target):$(obj)
	g++ $(obj) -o $(target) -levent -ljson -lpthread `mysql_config --cflags --libs`
%.o:%.c
	g++ -c $< -o $@ 
remoteServer:
	echo "makefile remoteServer"
.PHONY:clean
clean:
	-rm $(obj) $(target) -f

