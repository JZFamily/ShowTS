#include <iostream>
#include "openssl/evp.h"
#include <string>
#include <vector>
int main()
{
	auto x = EVP_get_digestbyname("sha512");
	if (x == nullptr)
	{
		return 0;
	}
	std::string message = "hello world!";
	std::string digest;
	EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_des_ecb(), nullptr, (const unsigned char*)"hello", nullptr);
	//int outl = 0;
	//int blkLen = EVP_CIPHER_CTX_block_size(ctx);
	//std::vector<unsigned char> out(message.length()+blkLen,0);
	//
	//EVP_EncryptUpdate(ctx, out.data(), &outl, (const unsigned char*) message.data(), message.length());
	//for (auto& item : out)
	//{
	//	std::cout << std::hex << (uint32_t)item;
	//}
	//std::cout << std::endl;
	//EVP_EncryptFinal_ex(ctx, out.data(), &outl);

	//for (auto& item : out)
	//{
	//	std::cout << std::hex << (uint32_t)item;
	//}
	//std::cout << std::endl;
	int olen = 0;
	unsigned char tmpOut[1024] = { 0 };
	EVP_EncryptUpdate(ctx, tmpOut, &olen, (const unsigned char*)message.data(), message.length());
	for (int i = 0; i < olen; i++)
	{
		std::cout << std::hex << (uint32_t)tmpOut[i];
	}
	std::cout << std::endl;
	int temp = 0;
	//EVP_EncryptFinal_ex(ctx, tmpOut+olen, &temp);

	for (int i = 0; i < olen+temp; i++)
	{
		std::cout << std::hex << (uint32_t)tmpOut[i];
	}
	std::cout << std::endl;
	//fc3ff98e8c6ad3087d515c0473f8677
	EVP_CIPHER_CTX_free(ctx);


	EVP_CIPHER_CTX* ctx2 = EVP_CIPHER_CTX_new();
	EVP_DecryptInit_ex(ctx2, EVP_des_ecb(), nullptr, (const unsigned char*)"hello", nullptr);

	int olen2 = 0;
	unsigned char tmpOut2[1024] = { 0 };
	EVP_DecryptUpdate(ctx2, tmpOut2, &olen2,tmpOut, olen /*+ temp*/);
	std::cout << (char *)tmpOut2 <<std::endl;
	int temp2 = 0;
	EVP_DecryptFinal_ex(ctx2, tmpOut2 + olen2, &temp2);

	std::cout << (char *)tmpOut2 << std::endl;
	std::cout << std::endl;
	//fc3ff98e8c6ad3087d515c0473f8677
	EVP_CIPHER_CTX_free(ctx);
	return 0;
}