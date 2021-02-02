#include "openssl/evp.h"
#include "hashlib.h"
#include <sstream>


IHashLib * getHashLib(const DigestType& type)
{
	hashlib::HashLib* phashlib = new hashlib::HashLib(type);
	if (phashlib == nullptr)
	{
		return phashlib;
	}

	phashlib->init();
}

namespace hashlib {
	HashLib::HashLib()
		:m_digestType(MD_MD5)
		, m_blockSize(1024)
		, m_pMdCtx(nullptr)
	{
		m_pMdCtx = EVP_MD_CTX_create();
		if (m_pMdCtx == nullptr)
		{
			throw std::runtime_error("create ctx failed!");
		}
		EVP_MD_CTX_init(m_pMdCtx);
	}

	HashLib::HashLib(const DigestType & type)
		:m_digestType(type)
		, m_blockSize(1024)
		, m_pMdCtx(nullptr)
	{
		m_pMdCtx = EVP_MD_CTX_create();
		if (m_pMdCtx == nullptr)
		{
			throw std::runtime_error("create ctx failed!");
		}
		EVP_MD_CTX_init(m_pMdCtx);
	}

	HashLib::~HashLib()
	{
		if (m_pMdCtx != nullptr)
		{
			EVP_MD_CTX_destroy(m_pMdCtx);
		}
	}

	const int HashLib::getDigestSize() const
	{
		return static_cast<int>(m_disgest.length());
	}

	const uint32_t HashLib::getBlockSize() const
	{
		// TODO: �ڴ˴����� return ���
		return m_blockSize;
	}

	void HashLib::setBlockSize(const uint32_t & blkSize)
	{
		if (blkSize == 0)
		{
			return;
		}
		m_blockSize = blkSize;
	}
	const DigestType & HashLib::getType() const
	{
		// TODO: �ڴ˴����� return ���
		return m_digestType;
	}
	void HashLib::setType(const DigestType & type)
	{
		m_digestType = type;
	}
	bool HashLib::init()
	{
		switch (m_digestType)
		{
		case MD_MD5:
		{
			EVP_DigestInit(m_pMdCtx, EVP_md5());
		}
		break;
		case MD_SHA1:
		{
			EVP_DigestInit(m_pMdCtx, EVP_sha1());
		}
		break;
		case MD_SHA224:
		{
			EVP_DigestInit(m_pMdCtx, EVP_sha224());
		}
		break;
		case MD_SHA256:
		{
			EVP_DigestInit(m_pMdCtx, EVP_sha256());
		}
		break;
		case MD_SHA384:
		{
			EVP_DigestInit(m_pMdCtx, EVP_sha384());
		}
		break;
		case MD_SM3:
		{
			//EVP_DigestInit(m_pMdCtx, EVP_sha384());
			throw std::logic_error("not impl!");
		}
		break;
		default:
			return false;
			break;
		}

		return true;
	}
	int HashLib::update(const std::string & data)
	{
		return EVP_DigestUpdate(m_pMdCtx, data.data(), data.length());;
	}
	bool HashLib::digest(std::string & digest)
	{
		EVP_DigestFinal();
		digest = m_disgest;
		return true;
	}
	bool HashLib::hexdigest(std::string & digest)
	{
		std::stringstream ss;
		for (auto& item : m_disgest)
		{
			ss << std::hex << (uint32_t)(uint8_t)item;
		}
		digest = ss.str();
		return true;
	}
	bool HashLib::copy(std::string & digest)
	{
		digest = m_disgest;
		return true;
	}
};

