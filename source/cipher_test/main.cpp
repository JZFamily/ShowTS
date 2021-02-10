#include <iostream>
#include <fstream>
#include "cipher/i_cipher.h"
#include <string>

int Encrypt(const std::string& srcPath, const std::string& desPath, const std::string& passwd, const std::string& cipherName)
{
	auto cipher = getCipher(cipherName);
	if (cipher == nullptr)
	{
		std::cerr << "get cipher failed!" << std::endl;
		return -1;
	}
	cipher->Init(passwd);
	std::fstream  fr;
	std::fstream  fw;

	fr.open(srcPath, std::ios::binary| std::ios::in);
	fw.open(desPath, std::ios::binary | std::ios::out| std::ios::trunc);

	cipher->Update(fr,fw);
	cipher->Final(fw);

	return 0;
}

int Decrypt(const std::string& srcPath, const std::string& desPath, const std::string& passwd, const std::string& cipherName)
{
	auto cipher = getCipher(cipherName);
	if (cipher == nullptr)
	{
		std::cerr << "get cipher failed!" << std::endl;
		return -1;
	}
	cipher->Init(passwd,0);

	std::fstream  fr;
	std::fstream  fw;

	fr.open(srcPath, std::ios::binary | std::ios::in);
	fw.open(desPath, std::ios::binary | std::ios::out | std::ios::trunc);

	cipher->Update(fr, fw);
	cipher->Final(fw);
	return 0;
}



int main(char argc, char *argv[])
{
	// 程序名   0加密，1解密   密码  源地址 目的地址
	//std::cerr << "" << std::endl;
	//auto func = []() {
	//	std::cerr << "参数错误！" << std::endl;
	//	std::cerr << "使用方法如下：" << std::endl;
	//	std::cerr << "程序名   0加密，1解密   密码  源地址 目的地址" << std::endl;
	//	std::cerr << "cipher_test   0  mypass  c:\\test1 c:\\test2" << std::endl;
	//};

	//if (argc != 5)
	//{
	//	func();
	//	return -1;
	//}
	//int type = std::stoi(argv[1]);
	//std::string passwd = argv[2];
	//std::string src = argv[3];
	//std::string dst = argv[4];
	//if (type == 0)
	//{
	//	Encrypt(src, dst, passwd);
	//}
	//else if (type == 1)
	//{
	//	Decrypt(src, dst, passwd);
	//}
	//else
	//{
	//	func();
	//}

	int type = 0;
	std::string passwd = "hello";
	std::string src = "";
	std::string dst = "";
	std::string cipherName;
	do
	{
		std::cerr << "欢迎使用！"<< std::endl;

		std::string input;
		std::cerr << "请输入源文件文件全路径：" << std::endl;
		std::cin >> input;
		src = input;
		std::cerr << "请输入目标文件全路径：" << std::endl;
		std::cin >> input;
		dst = input;
		std::cerr << "请输入密码：" << std::endl;
		std::cin >> input;
		passwd = input;
		std::cerr << "请输入 0-解密 1-加密：" << std::endl;
		std::cin >> input;
		type = std::stoi(input);
		std::cerr << "请输入加密算法：" << std::endl;
		std::cin >> input;
		cipherName = input;
		if (type == 0)
		{
			Encrypt(src, dst, passwd, cipherName);
		}
		else if (type == 1)
		{
			Decrypt(src, dst, passwd, cipherName);
		}
		else
		{
			std::cerr << "" << std::endl;
		}
		std::cerr << "操作完成，退出请输入 -1,其他数字继续" << std::endl;
		std::cin >> input;
		if (input == "-1")
		{
			break;
		}
	} while (true);

	return 0;
}