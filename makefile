src = $(wildcard ./*.cpp)  # 鎼滅储璇ョ洰褰曚笅鎵€鏈夌殑cpp鏂囦欢
obj = $(patsubst %.cpp, %.o, $(src))  # 灏嗘瘡涓猚pp鏂囦欢閮芥浛鎹�涓簅鏂囦欢,涓嬮潰鐨勬柟娉曚篃鍙�
#obj = $(src:%.cpp=%.o)  
target = app  # 瑕佺敓鎴愮殑鐩�鏍囧悕绉�
CC = g++  # 缂栬瘧鍣�

$(target): $(obj)  # 鐢熸垚鏈€缁堟枃浠�
	$(CC) $(obj) -o $(target)  

%.o: %.cpp  # 鍏朵粬cpp鏂囦欢
	$(CC) -c $< -o $@  

.PHONY: clean  # clean鎸囦护
clean:  
	del $(target) *o
