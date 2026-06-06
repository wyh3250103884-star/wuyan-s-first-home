CXX = gcc     #确定编译器是gcc，先把它写在一个变量里，后面如果想要改编译器的话直接改CXX这个变量的value就可以
TARGET = main #确定最后生成可执行文件的名称，也是方便后续更改所以放在一个变量里
SRC = $(wildcard *.c) #开始抽象了，这里wildcard是通配符，表示“*”这个符号具有通配符的功能，*.c可以表示当前目录下的所有.c文件，$()表示括号内的内容是SRC所表示的部分
OBJ = $(patsubst %.c, %.o, $(SRC)) #更抽象了，这里patsubst是一个把SRC中所有的.c文件替换成.o文件的函数

CXXFLAGS = -c -Wall #这句话的意思是用CXXFLAGS这个变量去替换-c -Wall这两个命令，-c是编译compile，-Wall是显示所有的warning（例如变量未使用之类的）

$(TARGET): $(OBJ)   #这两行的意思是，TARGET是依赖于OBJ的，也就是最后的.exe文件依赖于所有的.o文件，下面的$@表示目标文件，$^表示所有的依赖文件，%<表示第一个依赖文件，这两行翻译过来就是：gcc main.c print.c print1.c -c，也就是把所有的.c文件全都编译
    $(CXX) -o $@ $^
#这两行翻译过来就是：gcc -c -Wall main.o print.o print1.o -o main
%.o: %.c         
    $(CXX) $(CXXFLAGS) $< -o $@
#.PHONY表示后面那个目标（这里就是clean）是个伪文件目标，也就是说它没有依赖文件，是一个只执行的命令，不会出现对应的clean文件
.PHONY: clean 
#说明clean这个命令具体要干什么事情，下面那一行表示把TARGET下所有的.o文件都删除，方便下一次更改文件后重新编译
clean:
    rm -f *.o $(TARGET)