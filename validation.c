#include "val.h" 

int FILE_validation(int count ,char *argv[],file_node **head){

    int filecount =0;
    for(int i=1;i<count;i++){

        char *file_name = argv[i];

        if((strstr(file_name,".txt"))== NULL){
            printf("Error: '%s' is not a '.txt' file.\n", file_name);
            continue;
        }

        FILE *fp = fopen(file_name,"r");
        if(!fp){
            printf("Error: File '%s' does not exist.\n", file_name);
            continue;
        }

        fseek(fp,0,SEEK_END);
        long size = ftell(fp);
        
        fclose(fp);
        if(size == 0){
            printf("Error: File '%s' is empty.\n", file_name);
            continue;
        }

        if (Check_Duplicate_File(head, file_name) == SUCCESS)
        {
            printf("Error: Duplicate file '%s' ignored.\n", file_name);
            continue;
        }

        Insert_last(head,file_name);
        
        
        filecount++;

    }


    if(!filecount){
        printf("No valid files found.\n");
        return FAILURE;
    }

    return SUCCESS;
}

int Insert_last(file_node **head, char *file_name){

    if (head == NULL || file_name == NULL)
    return FAILURE; 

    file_node *new_node = malloc(sizeof(file_node));
    if(new_node == NULL) return 0;

    strcpy(new_node->file_name,file_name);
    new_node->link = NULL;

    if(*head == NULL){
        *head = new_node;
        return SUCCESS;
    }
    file_node *temp = *head;
    while(temp->link != NULL){
        temp = temp ->link;
    }
    temp->link =new_node;
    return SUCCESS;
}
int Check_Duplicate_File(file_node **head , char *file_name){

    if(*head == NULL){
        return FAILURE;
    }
    file_node *temp = *head;
    while(temp){

        if(strcmp(temp->file_name,file_name)==0){
            return SUCCESS;
        }
        temp =temp->link;
    }
    return FAILURE;
}