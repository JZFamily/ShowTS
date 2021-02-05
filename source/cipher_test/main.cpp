#include <iostream>
#include <fstream>
#include "i_cipher.h"
#include <string>
int Encrypt(const std::string& srcPath, const std::string& desPath, const std::string& passwd)
{
	auto cipher = getCipher("aes-128-ecb");
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
	if (fr.rdstate() != std::ios::goodbit || fw.rdstate() != std::ios::goodbit)
	{
		std::cerr << "open file failed!"  <<std::endl;
		return 0;
	}

	char buf[4096] = { 0 };
	int size = 0;
	std::string outData;
	while (fr.read(buf, 4096))
	{
		size = fr.gcount();
		outData.clear();
		cipher->Update(buf, size, outData);
		fw.write(outData.data(),outData.length());
	}
	if (fr.eof())
	{
		size = fr.gcount();
		outData.clear();
		cipher->Update(buf, size, outData);
		fw.write(outData.data(), outData.length());
	}
	outData.clear();
	cipher->Final(outData);
	fw.write(outData.data(), outData.length());
	return 0;
}
int Decrypt(const std::string& srcPath, const std::string& desPath, const std::string& passwd)
{
	auto cipher = getCipher("aes-128-ecb");
	if (cipher == nullptr)
	{
		std::cerr << "get cipher failed!" << std::endl;
		return -1;
	}
	cipher->Init(passwd,0);
	std::fstream  fr;
	std::fstream  fw;
	fr.open(srcPath, std::ios::binary | std::ios::in);
	fw.open(desPath, std::ios::binary | std::ios::out | std::ios::ate | std::ios::trunc);
	if (fr.rdstate() != std::ios::goodbit || fw.rdstate() != std::ios::goodbit)
	{
		std::cerr << "open file failed!" << std::endl;
		return 0;
	}

	char buf[4096] = { 0 };
	int size = 0;
	std::string outData;
	while (fr.read(buf, 4096))
	{
		size = fr.gcount();
		outData.clear();
		cipher->Update(buf, size, outData);
		fw.write(outData.data(), outData.length());
	}
	if (fr.eof())
	{
		size = fr.gcount();
		outData.clear();
		cipher->Update(buf, size, outData);
		fw.write(outData.data(), outData.length());
	}
	outData.clear();
	cipher->Final(outData);
	fw.write(outData.data(), outData.length());
	return 0;
}



int main(char argc, char *argv[])
{
	// 程序名   0加密，1解密   密码  源地址 目的地址
	std::cerr << "" << std::endl;
	auto func = []() {
		std::cerr << "参数错误！" << std::endl;
		std::cerr << "使用方法如下：" << std::endl;
		std::cerr << "程序名   0加密，1解密   密码  源地址 目的地址" << std::endl;
		std::cerr << "cipher_test   0  mypass  c:\\test1 c:\\test2" << std::endl;
	};
	if (argc != 5)
	{
		func();
		return -1;
	}
	int type = std::stoi(argv[1]);
	std::string passwd = argv[2];
	std::string src = argv[3];
	std::string dst = argv[4];
	if (type == 0)
	{
		Encrypt(src, dst, passwd);
	}
	else if(type == 1)
	{
		Decrypt(src, dst, passwd);
	}
	else
	{
		func();
	}
	return 0;
}