#include <stdlib.h>
#include  <openssl/evp.h>
#include <string.h>

int main(){

	//declaring the variables

	char source[]="helloworld";
	char *target;	
	char *output;
	int in_len, out_len;

	//Declaring EVP variables
	char mykey[EVP_MAX_KEY_LENGTH]="hardtobreak";
	char iv[EVP_MAX_IV_LENGTH] = "aniv"; 	
        EVP_CIPHER_CTX ctx; 

	target=malloc(sizeof(source));
	output=malloc(sizeof(source));
	in_len=strlen(source);

	printf("This is the text before ciphering: %s\n",source);
	printf("The length of the string is: %d\n",in_len);

	//starting the encryption process

	EVP_CIPHER_CTX_init(&ctx);

	EVP_EncryptInit_ex(&ctx,EVP_aes_128_cbc(),NULL,mykey,iv);
	EVP_EncryptUpdate(&ctx,target,&out_len,source,in_len);
	EVP_EncryptFinal_ex(&ctx,target,&out_len);

	printf("The length of encrypted text is: %d\n",out_len);

	//printf("The char array contains: %s\n",source);
	in_len=strlen(target);
	//out_len=strlen(output);

	//printf("The ouput contains: %s\n",output);	
	//starting the decryption process
	EVP_DecryptInit_ex(&ctx,EVP_aes_128_cbc(),NULL,mykey,iv);
	EVP_DecryptUpdate(&ctx,output,&out_len,target,in_len);
	EVP_DecryptFinal_ex(&ctx,output,&out_len);

	//Terminating The Buffer with Null Terminator
	output[out_len]='\0';

	printf("The Decipher text is : %s\n",output);
	printf("The length of the decipher text is: %d\n",strlen(output));
	printf("Program is working\n");

return 0;

}
