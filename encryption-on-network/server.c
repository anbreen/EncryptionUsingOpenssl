#include "headerfiles.h"

#define SERVER_PORT 9990 
#define BACKLOG 10    
#define MAX_SIZE 500 

 int main(void)
 {
	
     int listenSocket;
     int activeSocket;
     int numberOfBytes; 
     int socketOption;
     int bindCheck;
     int listenCheck;
     int sendCheck;
     int out_len,in_len;
     int yes=1;
     char buffer[MAX_SIZE];
     char mykey[EVP_MAX_KEY_LENGTH]="hardtobreak";
     char iv[EVP_MAX_IV_LENGTH] = "aniv"; 
     char *output;
     socklen_t client_size;
     EVP_CIPHER_CTX ctx;
	
     struct sockaddr_in serverAddress; 
     struct sockaddr_in clientAddress; 

    EVP_CIPHER_CTX_init(&ctx);
      

     listenSocket = socket(AF_INET, SOCK_STREAM, 0);

	

     if(listenSocket==-1){

         perror("socket");
         exit(1);
     }
      
     socketOption=setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

     
     
     if(socketOption==-1){

         perror("setsockopt");
         exit(1);
     }

     bzero(&serverAddress,sizeof(serverAddress));    

     serverAddress.sin_family = AF_INET;         
     serverAddress.sin_port = htons(SERVER_PORT);     
     serverAddress.sin_addr.s_addr = INADDR_ANY; 
     
     bindCheck=bind(listenSocket, (struct sockaddr *)&serverAddress, sizeof (serverAddress));

    
    
     if(bindCheck==-1){
	
         perror("bind");
         exit(1);
     }

     
     listenCheck=listen(listenSocket, BACKLOG);

      
      if(listenCheck==-1){

         perror("listen");
         exit(1);
     }
     
     
     for(;;) { 

	
         client_size = sizeof (clientAddress);

	 
         activeSocket = accept(listenSocket, (struct sockaddr *)&clientAddress,  &client_size);

	
	if(activeSocket==-1){

             perror("accept");
             continue;
         }
	
     
	
	numberOfBytes=recv(activeSocket, buffer,36 ,MSG_WAITALL);



	printf("Number of Bytes: %d\n",numberOfBytes);

	printf("Buffer: %s\n",buffer);

	
	if(numberOfBytes==-1) 
	{
         perror("recv");
         exit(1);
     	}

	in_len=strlen(buffer);	

	
	printf("Buffer Length: %d\n",in_len);
	
	buffer[16]='\0';

	in_len=strlen(buffer);

	printf("Buffer Length: %d\n",in_len);

	output=malloc(in_len);


	/*-----------------Decryption-------------------------------*/
		
		//printf("Works\n");
		EVP_DecryptInit_ex(&ctx,EVP_aes_128_cbc(),NULL,mykey,iv);
		//printf("Works\n");
		EVP_DecryptUpdate(&ctx,output,&out_len,buffer,in_len);
		//printf("Works\n");
		EVP_DecryptFinal_ex(&ctx,output,&out_len);


       /*-----------------------------------------------------------*/
	
      // output[out_len] = '\0';

       printf("Received Length: %d\n",out_len);
       printf("Received: %s\n",output);

      
     }

  
  close(activeSocket);
	     
return 0;
 }



