# COMP9337
# 1. Goal
use and compare three techniuqes to encrypt: DES, RSA, SHA-1 with OpenSSL.
# 2. DES encryption / decryption
coding a tool to encrypt and decrypt files using DES
in mode CBC (Cipher Block Chaining)
# 3. Method
extend skeleton code to take an arbitrarily sized input file and encrypt/decrypt it, by implementing the Cipher Block Chaining DES mode of operation.
# 4. Check
test.txt & test.des
# 5. Requirements
## 1. Use the built-in functions
## 2.  form
./tempdes
iv
key
inputfile
outputfile
# 6. Performance measures for DES, RSA and SHA1
The final part of this lab consists of measuring the time DES, RSA and SHA-1 take to
process files of different sizes.

a. Generate text files with the following sizes:
- For DES (in bytes): 8, 64, 512, 4096, 32768, 262144, 2047152
- For SHA-1 (in bytes): 8, 64, 512, 4096, 32768, 262144, 2047152
- For RSA (in bytes): 2, 4, 8, 16, 32, 64, 128

b. Encrypt and decrypt all these files using the DES function that you wrote in part 3. Measure the time it takes to encrypt and decrypt each of the files. To do this, you might want to use the C function “gettimeofday.” Add these timing functions to your implementation of part 3

Measure the time for RSA and SHA-1 encryption and decryption for the file sizes listed in part a.

## des cbc
DES CBC（密文分组链接方式）它的实现机制使加密的各段数据之间有了联系。其实现的机理如下：


加密步骤如下：


1）首先将数据按照8个字节一组进行分组得到D1D2......Dn（若数据不是8的整数倍，用指定的PADDING数据补位）


2）第一组数据D1与初始化向量I异或后的结果进行DES加密得到第一组密文C1（初始化向量I为全零）


3）第二组数据D2与第一组的加密结果C1异或以后的结果进行DES加密，得到第二组密文C2


4）之后的数据以此类推，得到Cn


5）按顺序连为C1C2C3......Cn即为加密结果。


 


解密是加密的逆过程，步骤如下：


1）首先将数据按照8个字节一组进行分组得到C1C2C3......Cn


2）将第一组数据进行解密后与初始化向量I进行异或得到第一组明文D1（注意：一定是先解密再异或）


3）将第二组数据C2进行解密后与第一组密文数据进行异或得到第二组数据D2


4）之后依此类推，得到Dn


5）按顺序连为D1D2D3......Dn即为解密结果。


这里注意一点，解密的结果并不一定是我们原来的加密数据，可能还含有你补得位，一定要把补位去掉才是你的原来的数据


加密块链模式CBC:
     与ECB模式最大的不同是加入了初始向量

     定义：

           Enc(X,Y)是加密函数

           Dec(X,Y)是解密函数

           Key是加密密钥；

           Pi ( i = 0,1…n)是明文块，大小为64bit；

           Ci ( i = 0,1…n)是密文块，大小为64bit;

           XOR(X,Y)是异或运算；

           IV是初始向量（一般为64位）；

    ECB加密算法可表示为：

          C0 = Enc(Key, XOR(IV, P0)

            Ci = Enc(Key, XOR(Ci-1, Pi)

    ECB解密算法可以表示为：

           P0 = XOR(IV, Dec(Key, C0))

            Pi = XOR(Ci-1, Dec(Key,Ci))

算法特点:

每次加密的密文长度为64位(8个字节);
当相同的明文使用相同的密钥和初始向量的时候CBC模式总是产生相同的密文;
密文块要依赖以前的操作结果,所以，密文块不能进行重新排列;
可以使用不同的初始化向量来避免相同的明文产生相同的密文,一定程度上抵抗字典攻击;
一个错误发生以后,当前和以后的密文都会被影响;

dd if=/dev/zero of=tmp.128bytes bs=1c count=128

# DES
gcc -o out temp.des4.c -lcrypto

      8, 64, 512, 4096, 32768, 262144, 2047152
      8: ./out 40fedf386da13d57 fedcba9876543210 8bytes.txt output.des
      enc dec
      the time difference is 58 microsecond
      8:3 4
      64: 4 6
      512: 10 10
      4096: 72 70
      32768: 480 437
      262144: 4076 3399
      2047152: 4495 3925

# SHA1
      gcc -o out tempsha1.c -lcrypto
      ./out tmp.8bytes

      8, 64, 512, 4096, 32768, 262144, 2047152
      8: 3693
      64: 3609
      512: 3697
      4096: 3585
      32768: 3698
      262144: 3783
      2047152: 3729
# RSA
      For RSA (in bytes): 2, 4, 8, 16, 32, 64, 128
      gcc -o out temprsa.c -lcrypto
      ./out tmp.2bytes

      2: 20 1188
      4: 21 1198
      8: 20 1177
      16: 22 1227
      32: 20 1183
      64: 23 1269
      128: 29 1248
```
a.
Suppose the DES mangler function (or function F) mapped every 32-bit value to
zero, regardless of the value of its input. How does the output after Round 16 of
DES compare to the input at the start of Round 1 of DES? Show your work and
provide appropriate explanations.

http://www.cs.umd.edu/~shankar/414-Notes/Hw/hw-1-v2-sol.pdf

With a mangler function that outputs 0 always, each
 DES round just swaps L and R.   
So after 16 (even number) DES rounds, the initial 6
4-bit word would be unchanged

b.
Consider the following message digest (hash) function: Take the input messages,
divide it into 128-bit chunks. XOR all the chunks together to get a 128-bit result.
Run a standard message digest algorithm on the result. Is this a good message
digest function?
https://cs.iupui.edu/~durresi/CSC4601_07/Problems1_4601_07.pdf
No, it is fairly easy to generate another message with the 
same 128 bit⊕

c.
Perform encryption and decryption using the RSA algorithm for the
following: p = 3, q = 11, e =7, M = 5. Please show all the steps systematically,
like on page 270 of the Stallings textbook (scan of this page is included in
homework1.zip).
```
n = p*q = 33
L = (p-1)*(q-1) = 20
d * e mod L = 1, d = 3
Therefore, public key PR = {7,33}, private key PR = {3,33}.
encryption:
Ciphertext C = 5^7 mod 33 = 14
PlainText  M = C^3 mod 33 = 5
```
d.
In the public-key system using RSA, you intercept the ciphertext C=10 sent to a
user whose public key is e=5, n=35. What is the plaintext M? Show the steps.
```
assume q = 5, p = 7, p*q = 35
L = (p-1)*(q-1) = 24
e = 35, gcd(L,e) = 1, therefore aussumption holds.
d * e mod L = 1, d = 5
So private key PR = {5,35}
M = C^5 MOD 35 = 5.
```
```