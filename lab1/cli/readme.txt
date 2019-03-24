src 文件夹包含了全部的源代码、Makefile

编译方式：
 - windows：
	 - 执行命令 `g++ *.cpp -o Wordlist.exe` （需要 MinGW）
 - linux:
	 - 执行 `make` 编译
	 - 执行 `make clean` 清理

使用方式：
 - windows：
	 - Wordlist {-w|-c} <input_file> [-h <first_character>] [-t <last_character>] [-n <word_num>]
 - linux:
	 - ./Wordlist {-w|-c} <input_file> [-h <first_character>] [-t <last_character>] [-n <word_num>]

功能说明：
	找到最长（字符数或单词数）单词链 / 所有固定长度（字符数或单词数）单词链
	[选项]
	-w|-c <input_file>		-w 指定单词数量模，-c 指定字符数量模式，二选一，后面加上输入文件路径。可与 -h -t -n 配合使用
	-h <first_character>		指定单词链开头字母，为可选项，可与 -n -t 配合使用
	-t <last_character>		指定单词链结尾字母，为可选项，可与 -n -h 配合使用
	-n <word_num>		当 -n 存在时，会找到所有固定单词数（-w）或固定字符数（-c）的单词链。-n 不存在则找到一个最长单词/字符链。

输出说明：
	成功：在可执行文件同目录输出文件 solution.txt 表示搜索结果
	失败：在命令行窗口输出错误信息
