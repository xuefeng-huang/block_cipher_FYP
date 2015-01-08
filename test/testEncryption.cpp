#include <QtTest/QtTest>
#include "../DES.h"

class TestEncryption: public QObject
{
  Q_OBJECT
private slots:
  void encryption();
  void decryption();

private:
  bool encrypt_block();
  bool decrypt_block();
  void fill_key_block(char* key_byte);
  void fill_sub_key(char* key, char sub_key[16][48]);
  void fill_plain_block(char* plain);
  void fill_cipher_block(char* cipher);
};

void TestEncryption::encryption()
{
  QCOMPARE(encrypt_block(), true);
}

void TestEncryption::decryption(){
  QCOMPARE(decrypt_block(), true);
}

bool TestEncryption::encrypt_block(){
  component_selection user_choice;
  char key_block[8];
  char sub_key[16][48];
  char plain_block[8];
  char cipher_block[8];

  fill_key_block(key_block);
  fill_sub_key(key_block, sub_key);
  fill_plain_block(plain_block);

  user_choice.feistel_swap = true;
  user_choice.inverse_permutation = true;
  user_choice.IP = true;
  user_choice.num_of_rounds = 16;
  user_choice.permutation_internal = true;
  user_choice.sbox[0] = 0;
  user_choice.sbox[1] = 1;
  user_choice.sbox[2] = 2;
  user_choice.sbox[3] = 3;
  user_choice.sbox[4] = 4;
  user_choice.sbox[5] = 5;
  user_choice.sbox[6] = 6;
  user_choice.sbox[7] = 7;

  DES_EncryptBlock(plain_block, sub_key, cipher_block, &user_choice);

  //compare each byte of cipher block
  if(cipher_block[0] == (char)0x3f && cipher_block[1] == (char)0x84 &&
     cipher_block[2] == (char)0x8f && cipher_block[3] == (char)0x01 &&
     cipher_block[4] == (char)0xb1 && cipher_block[5] == (char)0xa3 &&
     cipher_block[6] == (char)0x99 && cipher_block[7] == (char)0x7e){
      return true;
    }
  return false;
}

void TestEncryption::fill_key_block(char* key_byte){
  key_byte[0] = 0x5e;
  key_byte[1] = 0xf7;
  key_byte[2] = 0x20;
  key_byte[3] = 0x15;
  key_byte[4] = 0x37;
  key_byte[5] = 0x98;
  key_byte[6] = 0x38;
  key_byte[7] = 0x3b;
}

void TestEncryption::fill_sub_key(char *key, char sub_key[16][48]){
  char bit_key[64];

  Char8ToBit64(key, bit_key);
  DES_MakeSubKeys(bit_key, sub_key);
}

void TestEncryption::fill_plain_block(char* plain){
  for(int i =  0; i < 8; i++){
      plain[i] = 0x12;
    }
}

bool TestEncryption::decrypt_block(){
  component_selection user_choice;
  char key_block[8];
  char sub_key[16][48];
  char plain_block[8];
  char cipher_block[8];

  //set the same key and cipher text
  fill_key_block(key_block);
  fill_sub_key(key_block, sub_key);
  fill_cipher_block(cipher_block);

  user_choice.feistel_swap = true;
  user_choice.inverse_permutation = true;
  user_choice.IP = true;
  user_choice.num_of_rounds = 16;
  user_choice.permutation_internal = true;
  user_choice.sbox[0] = 0;
  user_choice.sbox[1] = 1;
  user_choice.sbox[2] = 2;
  user_choice.sbox[3] = 3;
  user_choice.sbox[4] = 4;
  user_choice.sbox[5] = 5;
  user_choice.sbox[6] = 6;
  user_choice.sbox[7] = 7;

  DES_DecryptBlock(cipher_block, sub_key, plain_block, &user_choice);

  //plain block should each contains the same byte 0x12
  for(int i = 0; i < 8; i++){
      if(plain_block[i] != (char)0x12)
        return false;
    }
  return true;
}

void TestEncryption::fill_cipher_block(char *cipher){
  cipher[0] = 0x3f;
  cipher[1] = 0x84;
  cipher[2] = 0x8f;
  cipher[3] = 0x01;
  cipher[4] = 0xb1;
  cipher[5] = 0xa3;
  cipher[6] = 0x99;
  cipher[7] = 0x7e;
}

QTEST_MAIN(TestEncryption)
#include "testEncryption.moc"
