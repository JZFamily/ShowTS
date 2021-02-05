# ShowTS
A joke.守教最高机密=，=

## 说明
需求是一个文件拆分加密，合并解密的工具


- @2021-02-02 说明
    - 加密解密选择了openssl库,这里首先对其进行一下验证和封装。
        - 主要有三种类型的算法
            - 对称加密算法
                - 四种加密模式
                    - ECB 电子密码本
                    - CBC 加密款链
                    - CFB 加密反馈
                    - OFB 输出反馈
                - 常用算法
                    - DES
                        - 已破解，不再安全，基本没有企业在用了
                        - 是对称加密算法的基石，具有学习价值
                    - 3DES
                        - 早于AES出现来替代DES
                        - 计算密钥时间太长
                        - 加密效率不高
                        - 所以也基本上不用
                    - RC4
                        - 算法简单，运行速度快，而且密钥长度是可变的，可变范围为1-256字节（8-2048bit）
                    - RC5
                    - RC6
                    - AES 高级加密标准，是下一代的加密算法标准，速度快，安全级别高
            - 摘要算法
                - md2
                - md4
                - md5  常用
                - sha1 常用
                - sha256
                - sha383
                - sha256
            - 非对称加密算法 （公钥算法）
                - RSA 当前最著名、最广泛的公钥系统
                - DSA 数字签名算法
                - DH 最早的公钥算法
                - ECC 椭圆曲线密码体制 目前没有有效攻击方法 移动设备用
                    - 优点
                        - 抗攻击性强
                        - 计算量小，速度快
                        - 存储空间占用小
                        - 带宽要求低
        - 
- @2021-02-02
    - 仿照python的hashlib进行了hashlib的封装
    - 进行了简单测试
- @2021-02-03
    - 进行了对称加密接口的验证
    - 可以用`EVP_get_digestbyname`接口进行hashlib的优化
- @2021-02-03 想法
    - 数字信封
        - 数字信封加密过程：
            - 发送方使用对称密钥key1加密明文p1,为密文c1
            - 发送方使用接收方公钥或者共享密钥key2加密key1为ckey1
            - 发送方发送 ckey1+c1
        - 数字信封解密过程：
            - 接收方使用接收方私钥或者共享密钥key3解密ckey1为key1
            - 接收方使用key1解密密文c1为明文p1
    - 数字签名
        - 签名过程：
            - 发送方对明文p1进行hash得到摘要md1
            - 发送方使用自己私钥对md1签名，得到ds1
            - 发送方发送ds1+p1
        - 校验过程：
            - 接收方使用发送方公钥对ds1解密得到摘要md1
            - 接收方对p1进行hash得到md2
            - 比较md1和md2,如果一致则数据未被篡改
    - 数字签名+数字信封
        - 为了保证信息传送的真实性、完整性和不可否认性，需要对要传送的信息进行数字加密和数字签名。其传送过程如下：
        - 发送者A：
            - A准备要传送的数字信息(明文)
            - A对数字信息(明文)进行哈希(hash)运算，得到一信息摘要。
            - A用自己的【私钥(SK)】对信息摘要进行加密得到A的数字签名，并将其附在数字信息上。（数字签名）
            - A随机产生一个加密钥(DES密钥)，并用此密钥对要发送的信息(明文)进行加密，形成密文。（对称加密）
            - A用B的【公钥(PK)】对刚才随机产生的加密密钥进行加密，将加密后的DES密钥连同密文一起传送给B。（数字信封）
        - 接收者B：
            - B收到A传送过来的密文和加过密的DES密钥，先用自己的私钥(SK)对加密的DES密钥进行解密，得到DES密钥。
            - B然后用DES密钥对受到的密文进行解密，得到明文的数字信息，然后将DES密钥抛弃(即DES密钥作废)。
            - B用A的公钥(PK)对A的数字签名进行解密，得到信息摘要。
            - B用相同的has算法对收到的明文再进行一次hash运算，得到一个新的信息摘要。
            - B将收到的信息摘要和新生成的信息摘要进行比较，如果一致，说明收到的信息没有被修改过。
    - 我的想法
        - 和上述的不同是，对明文加密不适用随机加密密钥
        - 发送方：
            - 对明文p1进行hash得到md1
            - 对md1用自己私钥加密，得到ckey1
            - 用ckey1对p1进行加密得到密文c1
            - 用接收方公钥对ckey1签名得到ckey2
            - 发送 ckey2+c1
        - 接收方：
            - 对ckey2使用自己的私钥进行解密得到ckey1
            - 用ckey1解密c1得到明文p1
            - 用发送方公钥对ckey1解密得到md1
            - 对p1进行hash得到md2
            - 对比md1和md2
- @2021-02-05 openssl-1.1.1i分析
    - 根据算法名称获取算法结构
        - EVP_get_digestbyname
        - EVP_get_cipherbyname
    - 根据算法NID获取算法结构
        - EVP_get_cipherbynid
    - 根据ASN1_OBJECT结构获取算法结构
        - EVP_get_cipherbyobj
    - 所在路径
        - openssl-1.1.1i\include\openssl\obj_mac.h
- @2021-02-05 加盐
    - EVP_BytesToKey 从各种参数派生密钥和IV
    -  函数分析 
        ```c++
        #include <openssl/evp.h>
        // type : 使用key和iv的加密算法
        // md   : 要使用的摘要算法
        // salt ：被用作推导盐，如果不使用盐应该指向一个8字节缓冲器或NULL。
        // data ：密码明文
        // data1: 密码明文长度
        // count: 迭代次数
        // key  : 派生的密钥将写入key.
        // iv   : 派生的IV将写入iv。
        int EVP_BytesToKey(const EVP_CIPHER *type, const EVP_MD *md,
                            const unsigned char *salt,
                            const unsigned char *data, int datal, int count,
                            unsigned char *key, unsigned char *iv);
        ```
    - 一篇知乎文章
        - >https://zhuanlan.zhihu.com/p/22860282?from_voters_page=true
        