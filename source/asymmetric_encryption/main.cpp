#include <iostream>
#include "openssl/evp.h"
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include <string>

int main()
{

	///生成公钥和私钥

	//读取和使用公钥和私钥

	//加密解密

	//签名

	//数字信封

	const EVP_CIPHER *ptr = EVP_get_cipherbyname("rsaEncryption");
	int nid =  EVP_CIPHER_nid(ptr);
	EVP_PKEY_CTX *ctx;
	EVP_PKEY *pkey = NULL;

	ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
	if (!ctx)
	{
				/* Error occurred */
		return 0;
	}

	if (EVP_PKEY_keygen_init(ctx) <= 0) {}
	/* Error */
	if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0) {
		return 0;
	}
	/* Error */

/* Generate key */
	if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
		return 0;
	}

	EVP_PKEY_CTX_free(ctx);
	EVP_PKEY_free(pkey);
	BIO * file;
	file = BIO_new_file("pub.pem", "w");
	PEM_write_bio_PUBKEY(file, pkey);
	BIO_free(file);

	EVP_PKEY *pkey2 = NULL;
	BIO * file1;
	file1 = BIO_new_file("pub.pem", "r");
	PEM_read_bio_PUBKEY(file1, &pkey2,nullptr,nullptr);
	BIO_free(file1);

	BIO * file3;
	file3 = BIO_new_file("pub3.pem", "w");
	PEM_write_bio_PUBKEY(file3, pkey2);
	BIO_free(file3);

	//FILE *f = fopen("pub.pem","w+");
	//PEM_write_PUBKEY(f,pkey);
	//fclose(f);
	////OPENSSL_Uplink(00007FFFB5C59D30,08): no OPENSSL_Applink


	////size_t len = 0;
	////int ret = EVP_PKEY_get_raw_private_key(pkey, nullptr,
	////	&len);
	////uint8_t *piv = new uint8_t[len];
	////EVP_PKEY_get_raw_private_key(pkey, piv,
	////	&len);


	////int x = EVP_PKEY_get_raw_public_key(pkey, nullptr,
	////	&len);
	////uint8_t *pub = new uint8_t[len];
	////EVP_PKEY_get_raw_public_key(pkey, pub,
	////	&len);
//	BIO *pBio = BIO_new_file("public.pem", "wb");
//
//	if (pBio == NULL)
//	{
//		printf("BIO_new_file = %s  error", "public.pem");
//		return -2;
//	}
//
//
//
//	if (PEM_write_bio_RSAPublicKey(pBio, pkey) == 0)
//	{
//		printf("write public key error");
//		return -3;
//	}
//	BIO_free_all(pBio);
//
//
////加密
//	if (EVP_PKEY_encrypt_init(ctx) <= 0) {}
//
//	EVP_PKEY_encrypt(ctx, );
//
////解密
//	if (EVP_PKEY_decrypt_init(ctx) <= 0) {}
//
//	EVP_PKEY_decrypt(ctx, );

//签名
	//EVP_PKEY_sign_init
	//EVP_PKEY_sign

	//EVP_SignInit_ex
//验证
	//EVP_VerifyInit

	return 0;
}