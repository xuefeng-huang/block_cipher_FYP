#include "DES.h"
#include <stdio.h>
#include <string.h>

#define PLAIN_FILE_OPEN_ERROR -1

#define KEY_FILE_OPEN_ERROR -2

#define CIPHER_FILE_OPEN_ERROR -3

#define OK 1;


/* IP table */

int IP_Table[64] = { 57,49,41,33,25,17,9,1,

                     59,51,43,35,27,19,11,3,

                     61,53,45,37,29,21,13,5,

                     63,55,47,39,31,23,15,7,

                     56,48,40,32,24,16,8,0,

                     58,50,42,34,26,18,10,2,

                     60,52,44,36,28,20,12,4,

                     62,54,46,38,30,22,14,6};

/* inverse permutation table */

int IP_1_Table[64] = {39,7,47,15,55,23,63,31,

                      38,6,46,14,54,22,62,30,

                      37,5,45,13,53,21,61,29,

                      36,4,44,12,52,20,60,28,

                      35,3,43,11,51,19,59,27,

                      34,2,42,10,50,18,58,26,

                      33,1,41,9,49,17,57,25,

                      32,0,40,8,48,16,56,24};


/* Expansion table */

int E_Table[48] = {31, 0, 1, 2, 3, 4,

                   3, 4, 5, 6, 7, 8,

                   7, 8,9,10,11,12,

                   11,12,13,14,15,16,

                   15,16,17,18,19,20,

                   19,20,21,22,23,24,

                   23,24,25,26,27,28,

                   27,28,29,30,31, 0};


/* P table in F function */

int P_Table[32] = {15,6,19,20,28,11,27,16,

                   0,14,22,25,4,17,30,9,

                   1,7,23,13,31,26,2,8,

                   18,12,29,5,21,10,3,24};


/* SBox */

int S[8][4][16] =/* S1 */

{{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},

{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},

{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},

{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},

    /* S2 */

{{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},

{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},

{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},

{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},

    /* S3 */

{{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},

{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},

{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},

{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},

    /* S4 */

{{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},

{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},

{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},

{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},

    /* S5 */

{{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},

{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},

{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},

{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},

    /* S6 */

{{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},

{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},

{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},

{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},

    /* S7 */

{{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},

{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},

{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},

{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},

    /* S8 */

{{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},

{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},

{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},

{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}};

/* PC1 table*/

int PC_1[56] = {56,48,40,32,24,16,8,

                0,57,49,41,33,25,17,

                9,1,58,50,42,34,26,

                18,10,2,59,51,43,35,

                62,54,46,38,30,22,14,

                6,61,53,45,37,29,21,

                13,5,60,52,44,36,28,

                20,12,4,27,19,11,3};


/* PC2 table */

int PC_2[48] = {13,16,10,23,0,4,2,27,

                14,5,20,9,22,18,11,3,

                25,7,15,6,26,19,12,1,

                40,51,30,36,46,54,29,39,

                50,44,32,46,43,48,38,55,

                33,52,45,41,49,35,28,31};


/* number of left rotation in sub key */

int MOVE_TIMES[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int ByteToBit(ElemType ch, ElemType bit[8]){

  int cnt;

  for(cnt = 0;cnt < 8; cnt++){

      *(bit + cnt) = (ch >> cnt) & 1;//save 8 bits into char array

    }

  return 0;

}


/* array of bit to byte */

int BitToByte(ElemType bit[8],ElemType *ch){

  int cnt;

  for(cnt = 0;cnt < 8; cnt++){

      *ch |= *(bit + cnt) << cnt;//bitwise OR with each bit in array

    }

  return 0;

}


/* convert 8 chars to 64 bits chars */

int Char8ToBit64(ElemType ch[8],ElemType bit[64]){

  int cnt;

  for(cnt = 0; cnt < 8; cnt++){

      ByteToBit(*(ch+cnt),bit+(cnt<<3));

    }

  return 0;

}


/* convert 64 bit to 8 bit char */

int Bit64ToChar8(ElemType bit[64],ElemType ch[8]){

  int cnt;

  memset(ch,0,8);//set arry to 0

  for(cnt = 0; cnt < 8; cnt++){

      BitToByte(bit+(cnt<<3),ch+cnt);

    }

  return 0;

}


/* generate sub key */

int DES_MakeSubKeys(ElemType key[64],ElemType subKeys[16][48]){

  ElemType temp[56];

  int cnt;

  DES_PC1_Transform(key,temp);/* PC1 */

  for(cnt = 0; cnt < 16; cnt++){/* generate 16 sub keys */

      DES_ROL(temp,MOVE_TIMES[cnt]);/* rotate left */

      DES_PC2_Transform(temp,subKeys[cnt]);/* PC2 */

    }

  return 0;

}


/* PC1 */

int DES_PC1_Transform(ElemType key[64], ElemType tempbts[56]){

  int cnt;

  for(cnt = 0; cnt < 56; cnt++){

      tempbts[cnt] = key[PC_1[cnt]];

    }

  return 0;

}


/* PC2 */

int DES_PC2_Transform(ElemType key[56], ElemType tempbts[48]){

  int cnt;

  for(cnt = 0; cnt < 48; cnt++){

      tempbts[cnt] = key[PC_2[cnt]];

    }

  return 0;

}


/* left rotation */

int DES_ROL(ElemType data[56], int time){

  ElemType temp[56];


  /* save those bits going to right to temp */

  memcpy(temp,data,time);

  memcpy(temp+time,data+28,time);



  /* rotate front 28 bits */

  memcpy(data,data+time,28-time);

  memcpy(data+28-time,temp,time);


  /* rotate back 28 bits */

  memcpy(data+28,data+28+time,28-time);

  memcpy(data+56-time,temp+time,time);


  return 0;

}


/* IP */

int DES_IP_Transform(ElemType data[64]){

  int cnt;

  ElemType temp[64];

  for(cnt = 0; cnt < 64; cnt++){

      temp[cnt] = data[IP_Table[cnt]];

    }

  memcpy(data,temp,64);

  return 0;

}


/* Inverse IP */

int DES_IP_1_Transform(ElemType data[64]){

  int cnt;

  ElemType temp[64];

  for(cnt = 0; cnt < 64; cnt++){

      temp[cnt] = data[IP_1_Table[cnt]];

    }

  memcpy(data,temp,64);

  return 0;

}


/* expansion in F function */

int DES_E_Transform(ElemType data[48]){

  int cnt;

  ElemType temp[48];

  for(cnt = 0; cnt < 48; cnt++){

      temp[cnt] = data[E_Table[cnt]];

    }

  memcpy(data,temp,48);

  return 0;

}


/* Permutation in F function */

int DES_P_Transform(ElemType data[32]){

  int cnt;

  ElemType temp[32];

  for(cnt = 0; cnt < 32; cnt++){

      temp[cnt] = data[P_Table[cnt]];

    }

  memcpy(data,temp,32);

  return 0;

}




int DES_XOR(ElemType R[48], ElemType L[48], int count){

  int cnt;

  for(cnt = 0; cnt < count; cnt++){

      R[cnt] ^= L[cnt];

    }

  return 0;

}


/* SBox operation */

int DES_SBOX(ElemType data[48], const component_selection *user_choice){

  int cnt;

  int row,col,output;

  int cur1,cur2;

  for(cnt = 0; cnt < 8; cnt++){

      cur1 = cnt*6;//cur1 is index for every 6 bits

      cur2 = cnt<<2;//cur2 is index for every 4 bits



      /* compute row and col in SBox array */

      row = (data[cur1]<<1) + data[cur1+5];

      col = (data[cur1+1]<<3) + (data[cur1+2]<<2)

          + (data[cur1+3]<<1) + data[cur1+4];

      output = S[user_choice ->sbox[cnt]][row][col];


      /* convert to 4 bit binary */

      data[cur2] = (output & 0X08)>>3;

      data[cur2+1] = (output & 0X04)>>2;

      data[cur2+2] = (output & 0X02)>>1;

      data[cur2+3] = output & 0x01;

    }

  return 0;

}




int DES_Swap(ElemType left[32], ElemType right[32]){

  ElemType temp[32];

  memcpy(temp,left,32);

  memcpy(left,right,32);

  memcpy(right,temp,32);

  return 0;

}


/* encrypt single block */

int DES_EncryptBlock(ElemType plainBlock[8], ElemType subKeys[16][48], ElemType cipherBlock[8],
const component_selection *user_choice){

  ElemType plainBits[64];

  ElemType copyRight[48];

  int cnt;


  Char8ToBit64(plainBlock,plainBits);

  /* IP */
  if(user_choice -> IP){
      DES_IP_Transform(plainBits);
    }


  /* get rounds of operation */
  int rounds = user_choice ->num_of_rounds;
  for(cnt = 0; cnt < rounds; cnt++){

      memcpy(copyRight,plainBits+32,32);

      /* expand right half, 32 bit to 48 bits */

      DES_E_Transform(copyRight);

      /* XOR expanded right half with sub key */

      DES_XOR(copyRight,subKeys[cnt],48);

      /* go through SBox */

      DES_SBOX(copyRight, user_choice);

      /* Permutation */
      if(user_choice ->permutation_internal){
          DES_P_Transform(copyRight);
        }

      /* XOR left half with result from F function */

      DES_XOR(plainBits,copyRight,32);

      if(cnt != (rounds - 1)){

          /* swap left and right half */
          if(user_choice ->feistel_swap){
              DES_Swap(plainBits,plainBits+32);
            }
        }

    }

  /* inverse permutation */
  if(user_choice ->inverse_permutation){
      DES_IP_1_Transform(plainBits);
    }

  Bit64ToChar8(plainBits,cipherBlock);

  return 0;

}


/* decrypt single block */

int DES_DecryptBlock(ElemType cipherBlock[8], ElemType subKeys[16][48],
ElemType plainBlock[8], const component_selection *user_choice){

  ElemType cipherBits[64];

  ElemType copyRight[48];

  int cnt;


  Char8ToBit64(cipherBlock,cipherBits);

  /* IP */
  if(user_choice ->inverse_permutation){
      DES_IP_Transform(cipherBits);
    }


  /* 16 rounds */
  int rounds = user_choice ->num_of_rounds;
  for(cnt = (rounds - 1); cnt >= 0; cnt--){

      memcpy(copyRight,cipherBits+32,32);

      /* expansion */

      DES_E_Transform(copyRight);

      /* XOR with sub key */

      DES_XOR(copyRight,subKeys[cnt],48);

      /* go through SBox */

      DES_SBOX(copyRight, user_choice);

      /* Permutation */
      if(user_choice ->permutation_internal){
          DES_P_Transform(copyRight);
        }

      /* XOR with left half */

      DES_XOR(cipherBits,copyRight,32);

      if(cnt != 0){

          /* swap left and right */
          if(user_choice ->feistel_swap){
              DES_Swap(cipherBits,cipherBits+32);
            }

        }

    }

  /* inverse permutation */
  if(user_choice ->IP){
      DES_IP_1_Transform(cipherBits);
    }

  Bit64ToChar8(cipherBits,plainBlock);

  return 0;

}



int DES_Encrypt(const char *plainFile, const char *keyStr, const char *cipherFile,
                const component_selection *user_choice){

  FILE *plain,*cipher;

  int count;

  ElemType plainBlock[8],cipherBlock[8],keyBlock[8];

  ElemType bKey[64];

  ElemType subKeys[16][48];

  if((plain = fopen(plainFile,"rb")) == NULL){
      return PLAIN_FILE_OPEN_ERROR;

    }

  if((cipher = fopen(cipherFile,"wb")) == NULL){

      return CIPHER_FILE_OPEN_ERROR;

    }

  /* get keyBlock */

  memcpy(keyBlock,keyStr,8);

  /* convert to binary bits */

  Char8ToBit64(keyBlock,bKey);

  /* generate sub key */

  DES_MakeSubKeys(bKey,subKeys);



  while(!feof(plain)){

      /* read 8 bytes from plaintext */

      if((count = fread(plainBlock,sizeof(char),8,plain)) == 8){

          DES_EncryptBlock(plainBlock,subKeys,cipherBlock, user_choice);

          fwrite(cipherBlock,sizeof(char),8,cipher);

        }

    }

  if(count){

      /* ANSI X.923 padding */

      memset(plainBlock + count,'\0',7 - count);

      /* last byte is the number of bytes padded */

      plainBlock[7] = 8 - count;

      DES_EncryptBlock(plainBlock,subKeys,cipherBlock, user_choice);

      fwrite(cipherBlock,sizeof(char),8,cipher);

    }

  fclose(plain);

  fclose(cipher);

  return OK;

}




int DES_Decrypt(const char *cipherFile, const char *keyStr, const char *plainFile,
                const component_selection *user_choice){

  FILE *plain, *cipher;

  int count = 0;

  long fileLen;
  long times = 0;

  ElemType plainBlock[8],cipherBlock[8],keyBlock[8];

  ElemType bKey[64];

  ElemType subKeys[16][48];

  if((cipher = fopen(cipherFile,"rb")) == NULL){

      return CIPHER_FILE_OPEN_ERROR;

    }

  if((plain = fopen(plainFile,"wb")) == NULL){

      return PLAIN_FILE_OPEN_ERROR;

    }


  /* copy key string */

  memcpy(keyBlock,keyStr,8);

  /* convert to 64 bit char array */

  Char8ToBit64(keyBlock,bKey);

  /* generate sub key */

  DES_MakeSubKeys(bKey,subKeys);


  /* get file length     */

  fseek(cipher,0,SEEK_END);    /* change pointer to end */

  fileLen = ftell(cipher);

  rewind(cipher);                /* set pointer to the beginning */

  while(1){



      fread(cipherBlock,sizeof(char),8,cipher);

      DES_DecryptBlock(cipherBlock,subKeys,plainBlock, user_choice);

      times += 8;

      if(times < fileLen){

          fwrite(plainBlock,sizeof(char),8,plain);

        }

      else{

          break;

        }

    }

  /* check whether padding exists */

  if(plainBlock[7] < 8){

      for(count = 8 - plainBlock[7]; count < 7; count++){

          if(plainBlock[count] != '\0'){

              break;

            }

        }

    }

  if(count == 7){/* padding exists */

      fwrite(plainBlock,sizeof(char),8 - plainBlock[7],plain);

    }

  else{/* no padding */

      fwrite(plainBlock,sizeof(char),8,plain);

    }


  fclose(plain);

  fclose(cipher);

  return OK;

}
