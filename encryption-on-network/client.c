#include "headerfiles.h"

#define MAXDATASIZE 256  


int main(int argc, char *argv[])
{
    
    int sockfd;
    int numbytes;
    int port;
    int in_len;
    int  out_len;
    int bytes_sent;
    double my_id=1245;
    char buf[MAXDATASIZE];
    char *target;
    char mykey[EVP_MAX_KEY_LENGTH]="hardtobreak";
    char iv[EVP_MAX_IV_LENGTH] = "aniv";
    EVP_CIPHER_CTX ctx;

   printf("Before sprintf\n");
   sprintf(buf,"%f",my_id);
   printf("After sprintf\n");

    in_len=strlen(buf);

    target=malloc(16);
    /*----------------------------------------------------------------------*/

     	EVP_CIPHER_CTX_init(&ctx);
	printf("Works\n");
	EVP_EncryptInit_ex(&ctx,EVP_aes_128_cbc(),NULL,mykey,iv);
	printf("Works\n");
	EVP_EncryptUpdate(&ctx,target,&out_len,buf,in_len);
	printf("Works\n");
	EVP_EncryptFinal_ex(&ctx,target,&out_len);	
	printf("Works\n");

    /*----------------------------------------------------------------------*/


    printf("Length of encypted data: %d\n",out_len);
    printf("Encrypted Text is: %s\n",target);

    struct hostent *he;
    struct sockaddr_in serverAddress; 

    
    if (argc != 3) {
         fprintf(stderr,"usage: client hostname\n");
         exit(1);
    }

    

    serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
    he=gethostbyaddr((char *) &serverAddress.sin_addr.s_addr,sizeof(serverAddress.sin_addr.s_addr),AF_INET);
   
    
    port=atoi(argv[2]);

     

     if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
         perror("socket");
         exit(1);
     }
   
    
     serverAddress.sin_family = AF_INET;    
     serverAddress.sin_port = htons(port); 
     serverAddress.sin_addr = *((struct in_addr *)he->h_addr);

     
     
     memset(serverAddress.sin_zero, '\0', sizeof serverAddress.sin_zero);

     

     if (connect(sockfd, (struct sockaddr *)&serverAddress,sizeof (serverAddress)) == -1) {
         perror("connect");
         exit(1);
     }
    
    
  /*  if ((numbytes=recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
         perror("recv");
         exit(1);
     }*/
    

     bytes_sent=send(sockfd, target,   16, 0) ;

	 printf("Sent Data: %d\n",bytes_sent);

    if (bytes_sent==-1){

                 perror("send");
   }

   
  /* buf[numbytes] = '\0';
	
   
     printf("Received: %s",buf);*/
  
   
     close(sockfd);
     return 0;
 }


