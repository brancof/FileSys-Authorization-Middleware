#include "verify.h"


char* generateCode()
{   
    int byte_count = 20;
        
    char data[byte_count];
    
    char num [] = "1234567890";
    char let [] = "abcdefghijklmnoqprstuvwyzx";
    char Caplet [] = "ABCDEFGHIJKLMNOQPRSTUYWVZX";
    srand(time(0));
    for (int i = 0; i < byte_count; i++)
    {       
            int x = rand() % 3;
            if(x == 0)
                    data[i] = let[rand() % 26];
            else if (x == 1)
                    data[i] = Caplet[rand() % 26];
            else
            {
                    data[i] = num[rand() % 10];
            }
            
    }    
    return strdup(data);
}


//Error
//EMAIL
char* le_email(char* owner)
{   
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char* resEmail = "Error";

    fp = fopen(DATABASE, "r");
    if (fp == NULL){
        printf("No such file or directory");
    }else{
        //HEADER
        getline(&line, &len, fp);
        //Le o restante user|email
        while ((read = getline(&line, &len, fp)) != -1) {
            char* username = strtok(line, "|");
            char* email = strtok(NULL, "\n\r");
            if(!strcmp(owner, username)){
                resEmail = strdup(email);
            }

        }
    }

    fclose(fp);
    return resEmail;
}

//int i = 0 - Erro
//int i = 1 - Tudo ok
//int i = 2 - Timeout
int loop_get_verify(char* code){

    int ciclos = WAIT_TIME/5;
    for(int i = 0; i < ciclos; i++){
        char* resGet = realiza_get(REST_URL);
        if(!strcmp(resGet,"Error")){
            return 0;
        }
        else if(!strcmp(resGet,code)){
            return 1;
        }
        else sleep(5);
    }
    return 2;
    
}
