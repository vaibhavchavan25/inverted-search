#include "val.h"

int create_database(file_node *f_head, hash_t hash_table[])
{
    // Implementation
    file_node *temp  = f_head;
    while(temp)
    {
        char *filename = temp->file_name;
        FILE *fp = fopen(filename,"r");
        char word[100];
        while(fscanf(fp,"%99s",word)==1)
        {
            int index = get_index(word[0]);
            insert_hash(hash_table,index,word,filename);
        }
        fclose(fp);
        temp = temp->link;
    }
    return SUCCESS;
}
int get_index(char ch)
{
    if(isupper((unsigned char)ch)){
        return ch - 'A';
    }
    else if(islower((unsigned char)ch)){
        return (ch - 'a');
    }
    else{
        return 26;
    }
}
int insert_hash(hash_t *hash_table, int index, char *word, char *filename)
{
    main_node *mtemp = hash_table[index].link;
    main_node *prev = NULL;

    while(mtemp)
    {
        if(strcmp(mtemp->word,word)==0)
        {
            sub_node *stemp = mtemp->s_link;
            while(stemp)
            {
                if(strcmp(stemp->filename,filename)==0)
                {
                    stemp->word_count++;
                    return SUCCESS;
                }
                stemp = stemp->link;
            }
            sub_node *new_sub = malloc(sizeof(sub_node));
            if(new_sub == NULL){
                return FAILURE;
            }
            new_sub->word_count = 1;
            strcpy(new_sub->filename,filename);
            new_sub->link = NULL;

            new_sub->link = mtemp->s_link;
            mtemp->s_link = new_sub;

            mtemp->file_count++;
            return SUCCESS;
        }
        prev = mtemp;
        mtemp = mtemp->m_link;
    }
    main_node *new_main = malloc(sizeof(main_node));
    if(new_main == NULL)
    {
        return FAILURE;
    }
    new_main->file_count = 1;
    strcpy(new_main->word,word);
    new_main->s_link = NULL;
    new_main->s_link=NULL;

    sub_node *new_sub = malloc(sizeof(sub_node));
    if(new_sub ==  NULL)
    {
        return FAILURE;
    }
    new_sub->word_count = 1;
    strcpy(new_sub->filename,filename);
    new_sub->link = NULL;

    new_main->s_link = new_sub;
    if(prev == NULL)
    {
        hash_table[index].link = new_main;
    }
    else
    {
        prev->m_link = new_main;
    }
    return SUCCESS;
}

int display_database(hash_t hash_table[])
{
    // Implementation
    printf("\n============================================================================================\n");
    printf("                                DISPLAY DATABASE\n");
    printf("\n============================================================================================\n");
    int flag = 0;
    for(int i=0;i<27;i++)
    {
        if(hash_table[i].link != NULL)
        {
            flag = 1;
            main_node *mtemp = hash_table[i].link;;
            while(mtemp)
            {
                printf("[index : %2d]   [word : %-12s]   [Total Files : %d] ",i,mtemp->word,mtemp->file_count);
                sub_node *stemp = mtemp->s_link;
                while(stemp)
                {
                    printf("[File : %-12s]  [word : %2d]",stemp->filename,stemp->word_count);
                    stemp = stemp->link;
                }
                printf("\n");
                mtemp = mtemp->m_link;
            }
        }
    }
    if(!flag)
    {
        return FAILURE;
    }
    printf("\n============================================================================================\n");
    printf("                                END\n");
    printf("\n============================================================================================\n");

    return SUCCESS;
}

int search_word(hash_t hash_table[], char *word, int index)
{
    // Implementation
     main_node *mtemp = hash_table[index].link;

     while(mtemp)
     {
        if(strcmp(mtemp->word,word)==0)
        {
            sub_node *stemp = mtemp->s_link;
            while(stemp)
            {
                printf("\n[ index : %d ] In file %s  %d time/s.\n",index,stemp->filename,stemp->word_count);
                stemp = stemp->link;
            }
            return SUCCESS;
        }
        mtemp = mtemp->m_link;
     }
    return FAILURE;
}

int save_database(hash_t hash_table[], char *save_file)
{
    // Implementation
    FILE *fp = fopen(save_file, "w");
    if (fp == NULL)
    {
        printf("Error: Could not open file %s for saving.\n", save_file);
        return FAILURE;
    }

    for (int i = 0; i < 27; i++)
    {
        main_node *mtemp = hash_table[i].link;

        while (mtemp)
        {
            // Write index and main node info
             
            fprintf(fp, "#%d;%s;%d;",i, mtemp->word, mtemp->file_count);

            // Write all subnodes
            sub_node *stemp = mtemp->s_link;
            while (stemp)
            {
                fprintf(fp, "%s;%d;", stemp->filename, stemp->word_count);
                stemp = stemp->link;
            }

            fprintf(fp, "#\n"); // Marks end of this main node

            mtemp = mtemp->m_link;
        }
    }

    fclose(fp);
    return SUCCESS;
}

int update_database(hash_t hash_table[], char *load_file)
{
    FILE *fp = fopen(load_file, "r");
    if (fp == NULL)
    {
        printf("Error: Could not open file %s\n", load_file);
        return FAILURE;
    }

    int index;
    char word[100];
    int file_count;

    while (fscanf(fp, "%d", &index) == 1)   // Read index
    {
        fscanf(fp, "%s %d", word, &file_count); // Read main node word + file count

        // Insert the main node manually
        main_node *new_main = malloc(sizeof(main_node));
        if (!new_main) return FAILURE;

        strcpy(new_main->word, word);
        new_main->file_count = file_count;
        new_main->m_link = NULL;
        new_main->s_link = NULL;

        // Insert into hash table list
        if (hash_table[index].link == NULL)
        {
            hash_table[index].link = new_main;
        }
        else
        {
            main_node *temp = hash_table[index].link;
            while (temp->m_link)
                temp = temp->m_link;
            temp->m_link = new_main;
        }

        // Read sub-nodes until "#"
        char filename[100];
        int word_count;

        while (1)
        {
            fscanf(fp, "%s", filename);
            if (strcmp(filename, "#") == 0)
                break;

            fscanf(fp, "%d", &word_count);

            // Create new sub node
            sub_node *new_sub = malloc(sizeof(sub_node));
            if (!new_sub) return FAILURE;

            strcpy(new_sub->filename, filename);
            new_sub->word_count = word_count;
            new_sub->link = NULL;

            // Insert into sub list
            if (new_main->s_link == NULL)
            {
                new_main->s_link = new_sub;
            }
            else
            {
                sub_node *stemp = new_main->s_link;
                while (stemp->link)
                    stemp = stemp->link;
                stemp->link = new_sub;
            }
        }
    }

    fclose(fp);
    return SUCCESS;
}
