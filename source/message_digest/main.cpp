#include <iostream>
#include "openssl/evp.h"
#include "openssl/md5.h"
#include <string>
int main()
{
	std::string message = "hello world!";
	std::string digest;
	EVP_MD_CTX* mdctx = EVP_MD_CTX_create();
	EVP_MD_CTX_init(mdctx);
	EVP_DigestInit_ex(mdctx,EVP_md5(),nullptr);
	EVP_DigestUpdate(mdctx, message.data(), message.length());
	uint8_t md[16];
	uint32_t s;
	EVP_DigestFinal_ex(mdctx, md, &s);
	digest.assign((char*)md,s);
	for (auto& item : digest)
	{
		std::cout << std::hex << (uint32_t)(uint8_t)item;
	}
	std::cout << std::endl;

	for (auto& item : md)
	{
		std::cout << std::hex << (uint32_t)item;
	}
	std::cout << std::endl;
	//fc3ff98e8c6ad3087d515c0473f8677
	EVP_MD_CTX_destroy(mdctx);
	return 0;
}

//#include <iostream>
//#include "openssl/md5.h"
//#include <string>
//int main()
//{
//	//
//	std::string message = "hello world!";
//	std::string digest;
//	digest.assign((char *)MD5((const unsigned char *)message.data(), message.length(), nullptr), 16);
//	for (auto& item : digest)
//	{
//		std::cout << std::hex << (uint32_t)(uint8_t)item;
//	}
//	std::cout << std::endl;
//	return 0;
//}