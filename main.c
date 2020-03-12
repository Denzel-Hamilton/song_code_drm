#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "aes.h"
#include "ecdh.h"
#include "utils.h"
#include "constantsA.h"
#include "song.h"
#include "map.h"

#define KEYS 16


int main(){

    // mapping needs
    //char mster = "master";
    uint8_t * master_key[KEYS] = {0x65,0x37,0x36,0x30,0x03,0x53,0x13,0x40,0x12,0x43,0x23,0x06,0x54,0xc6,0xff,0x9f};

    //song needs
    //step1: put actual song
    //step2: add demo
    //step3: run complete code (checking enc/dec)
    //step4: change example song with encrypted song
    //step5: change mipod.h so it can decrypt
    //step6: start changing mipod struct (add enc/dec key)
    uint8_t * raw_song[KEYS] ={0x00,0x01, 0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0X0B,0X0C,0X0D,0X0E,0X0F};
    uint8_t * enc_song[KEYS];
    uint8_t sharedkey[6*ECC_PUB_KEY_SIZE];

    //encrypt/decrypt needs
    /*87 407C DF6E DDEB 8E8B C1D3 3AA3 */
    static uint8_t pub_key[ECC_PUB_KEY_SIZE]; //output from keygen
    static uint8_t  pub_key2[ECC_PUB_KEY_SIZE]; //output from keygen
    static uint8_t  priv_key2[ECC_PRV_KEY_SIZE] = {0x95,0xff,0x72,0x56,0x3e,0x57,0x3c,0x35,0xbe,0x35,0x7e,0xd3,0x32,0xb8,0xaa,0x09,0x54,0x57,0xd2,0x93,0x57,0xd2,0x93,0x56}; // input to key gen (user must provide)
    static uint8_t mpriv_key[ECC_PRV_KEY_SIZE] = {0x55,0xff,0x72,0x56,0x3e,0x87,0x3c,0xc3,0xbe,0x29,0x7e,0xd3,0x32,0x52,0x87,0x74,0x37,0xa9,0x9f,0x81,0xb8,0x7d,0x09,0x54};
    //static uint8_t * mpriv_key[ECC_PRV_KEY_SIZE] = {0x55,0xff,0x72,0x56,0x3e,0x87,0x3c,0xc3,0xbe,0x29,0x7e,0xd3,0x32,0x52,0x87,0x74,0x37,0xa9,0x9f,0x81,0xb8,0x7d,0x09,0x54,0x57,0xd2,0x93,0x56};

    //structure needs
    struct user *master;// = {mpriv_key, pub_key}; //handling master key for encryption 
    master= malloc(200*sizeof(char *));
    memcpy(master -> priv_key,mpriv_key,sizeof(mpriv_key));
    memcpy(master -> pub_key,pub_key,sizeof(pub_key));

    struct user *aaron;
    aaron = malloc(200*sizeof(char * ));
    memcpy(aaron -> pub_key, pub_key2,sizeof(pub_key2));
    memcpy(aaron -> priv_key, priv_key2,sizeof(priv_key2));

    assert(key_gen(master -> pub_key, master -> priv_key));
 /*
    printf("master priv: ");
        for(uint32_t i = 0; i <ECC_PRV_KEY_SIZE; i++)
    {
        printf("%x",master -> priv_key[i]);
    }
    printf("\n");

    printf("master pub: ");
    for (uint32_t i = 0; i <ECC_PUB_KEY_SIZE; i++)
    {
        printf("%x",master -> pub_key[i]);
    }
    printf("\n");   
*/
    assert(key_gen(aaron->pub_key, aaron->priv_key));
/*
    printf("aaron priv: ");
    for(uint32_t i = 0; i <ECC_PRV_KEY_SIZE; i++)
    {
        printf("%x",(aaron->priv_key)[i]);
    }
    printf("\n");

     printf("Aaron pub: ");
    for (uint32_t i = 0; i <ECC_PUB_KEY_SIZE; i++)
    {
        printf("%x",(aaron->pub_key)[i]);
    }
    printf("\n");  
*/
    printf("master key: ");
    for (int i = 0; i <  16; i++)
    {
        printf("%2C", master_key[i]);
    }
    printf("\n");
    printf("raw song: ");
    for (int i = 0; i <  16; i++)
    {
        printf("%2x", raw_song[i]);
    }
    printf("\n");
 
    assert(encrypt_song (master_key,raw_song, enc_song));

    printf("encrypted song: ");
    for (int i = 0; i <  16; i++)
    {
        printf("%02x", enc_song[i]);
    }
    printf("\n");

    free(aaron);
    

}
