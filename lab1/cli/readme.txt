src �ļ��а�����ȫ����Դ���롢Makefile

���뷽ʽ��
 - windows��
	 - ִ������ `g++ *.cpp -o Wordlist.exe` ����Ҫ MinGW��
 - linux:
	 - ִ�� `make` ����
	 - ִ�� `make clean` ����

ʹ�÷�ʽ��
 - windows��
	 - Wordlist {-w|-c} <input_file> [-h <first_character>] [-t <last_character>] [-n <word_num>]
 - linux:
	 - ./Wordlist {-w|-c} <input_file> [-h <first_character>] [-t <last_character>] [-n <word_num>]

����˵����
	�ҵ�����ַ����򵥴����������� / ���й̶����ȣ��ַ����򵥴�����������
	[ѡ��]
	-w|-c <input_file>		-w ָ����������ģ��-c ָ���ַ�����ģʽ����ѡһ��������������ļ�·�������� -h -t -n ���ʹ��
	-h <first_character>		ָ����������ͷ��ĸ��Ϊ��ѡ����� -n -t ���ʹ��
	-t <last_character>		ָ����������β��ĸ��Ϊ��ѡ����� -n -h ���ʹ��
	-n <word_num>		�� -n ����ʱ�����ҵ����й̶���������-w����̶��ַ�����-c���ĵ�������-n ���������ҵ�һ�������/�ַ�����

���˵����
	�ɹ����ڿ�ִ���ļ�ͬĿ¼����ļ� solution.txt ��ʾ�������
	ʧ�ܣ��������д������������Ϣ
