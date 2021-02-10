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
	// ������   0���ܣ�1����   ����  Դ��ַ Ŀ�ĵ�ַ
	//std::cerr << "" << std::endl;
	//auto func = []() {
	//	std::cerr << "��������" << std::endl;
	//	std::cerr << "ʹ�÷������£�" << std::endl;
	//	std::cerr << "������   0���ܣ�1����   ����  Դ��ַ Ŀ�ĵ�ַ" << std::endl;
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
		std::cerr << "��ӭʹ�ã�"<< std::endl;

		std::string input;
		std::cerr << "������Դ�ļ��ļ�ȫ·����" << std::endl;
		std::cin >> input;
		src = input;
		std::cerr << "������Ŀ���ļ�ȫ·����" << std::endl;
		std::cin >> input;
		dst = input;
		std::cerr << "���������룺" << std::endl;
		std::cin >> input;
		passwd = input;
		std::cerr << "������ 0-���� 1-���ܣ�" << std::endl;
		std::cin >> input;
		type = std::stoi(input);
		std::cerr << "����������㷨��" << std::endl;
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
		std::cerr << "������ɣ��˳������� -1,�������ּ���" << std::endl;
		std::cin >> input;
		if (input == "-1")
		{
			break;
		}
	} while (true);

	return 0;
}