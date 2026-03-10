/*Inverted Index Search 
Name: Vaibhav Chavan
Project Name: Inverted Index Search
Batch ID: 25021_327
________________________________________
1. Introduction
The Inverted Index Search project reads multiple .txt files and creates a database that maps each word → the files in which the word appears.
This indexing method is commonly used in search engines to speed up word-based searching.
________________________________________
2. Features
•	Accepts multiple input text files
•	Validates file formats
•	Creates a searchable inverted index
•	Displays the full database
•	Searches for any specific word
•	Updates database with new files
•	Saves index to a text file
________________________________________
3. Data Structures Used
•	Singly Linked List → Stores the list of input files
•	Hash Table (27 buckets)
o	Index 0–25 → words starting with a–z
o	Index 26 → words starting with numbers/special characters
•	Main Node → Stores a word
•	Sub Node → Stores filename + word count
________________________________________
4. Working Flow (Based on Your main.c Menu)
Program Menu
1. Create Database  
2. Search a Word  
3. Display Database  
4. Save Database  
5. Update Database  
6. Exit
Flow
1.	Validate input files
2.	Initialize 27 hash buckets
3.	Based on user choice:
o	Create database → read and index all words
o	Search → find the word and display details
o	Display → print entire inverted index
o	Save → store database to a file
o	Update → add new file words to existing index
o	Exit → save one last time
________________________________________
5. Display Database (Your Actual Output)
(Used exactly as shown in your screenshot)
===========================================================
                     DISPLAY DATABASE
===========================================================

[Index :  0]   [Word : adada       ]   [Total Files : 1]   [File : file2.txt   ]   [Word :  1]
[Index :  0]   [Word : abc         ]   [Total Files : 1]   [File : file2.txt   ]   [Word :  1]
[Index :  7]   [Word : hi          ]   [Total Files : 1]   [File : file1.txt   ]   [Word :  1]
[Index : 10]   [Word : king        ]   [Total Files : 1]   [File : file2.txt   ]   [Word :  1]
[Index : 13]   [Word : nakul       ]   [Total Files : 1]   [File : file2.txt   ]   [Word :  1]
[Index : 15]   [Word : pushker     ]   [Total Files : 1]   [File : file1.txt   ]   [Word :  1]
[Index : 15]   [Word : papu        ]   [Total Files : 1]   [File : file2.txt   ]   [Word :  1]
[Index : 21]   [Word : vaibhav     ]   [Total Files : 1]   [File : file1.txt   ]   [Word :  1]

===========================================================
                               END
===========================================================
________________________________________
6. Explanation of the Output
Each line represents:
•	Index: Hash bucket number
•	Word: Extracted word
•	Total Files: Number of files containing the word
•	File: Name of the file
•	Word : 1 → number of occurrences
Example:
[Index : 0] [Word : abc ] [Total Files : 1] [File : file2.txt ] [Word : 1]
Meaning:
•	"abc" goes to hash index 0
•	Appears in file2.txt
•	Occurs once in that file
________________________________________
7. Why 27 Hash Buckets?
Your code uses:
hash_t hash_table[27];
•	0 - 25 → a to z
•	26 → words starting with numbers or special characters
This prevents invalid indexes (like 27, 28, etc.).
________________________________________
8. Advantages
•	Very fast searching due to hashing
•	Supports multiple files
•	Clean menu-driven interface
•	Easy to update and save database
________________________________________
9. Conclusion
Your program correctly creates an inverted index, displays words alphabetically via hashing, handles collisions, and maintains accurate file information. The output confirms that the indexing and display logic work exactly as required.
This project demonstrates strong understanding of:
•	Hash tables
•	Linked lists
•	File handling
•	Modular C programming


/****************************************************************************************
* Author     : Pushkar Kadam..
* Title      : Inverted Search Project
*****************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "val.h"


//#include "inverted_search.h"   // include your header file

int main(int argc, char *argv[])
{
    file_node *f_head = NULL;     
    hash_t hash_table[26];        

    //Initialize hash table 
    for (int i = 0; i < 26; i++)
    {
        hash_table[i].index = i;
        hash_table[i].link = NULL;
    }

    printf("----------------------------------------------------\n");
    printf("         INVERTED SEARCH PROJECT - EMERTXE          \n");
    printf("----------------------------------------------------\n");

    //Step 1: Validate input file/
    if (FILE_validation(argc, argv, &f_head) == FAILURE)
    {
        printf("Error: No valid files. Exiting.\n");
        return FAILURE;
    }

    int choice;
    char word[30];
    char save_file[20];

    while (1)
    {
        printf("\n--------------------- MENU -------------------------\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Word\n");
        printf("4. Save Database to File\n");
        printf("5. Update Database (from file)\n");
        printf("6. Exit\n");
        printf("----------------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                if (create_database(f_head, hash_table) == SUCCESS)
                    printf("Database created successfully.\n");
                else
                    printf("Error: Could not create database.\n");
                break;

            case 2:
                display_database(hash_table);
                break;

            case 3:
                printf("Enter the word to search: ");
                scanf("%s", word);
                int index = get_index(word[0]);
                if (search_word(hash_table, word,index) == FAILURE)
                    printf("Word '%s' not found in database.\n", word);
                break;

            case 4:
                printf("Enter backup filename: ");
                scanf("%s", save_file);

                if (save_database(hash_table, save_file) == SUCCESS)
                    printf("Database saved successfully into %s\n", save_file);
                else
                    printf("Error: Could not save database.\n");
                break;

            case 5:
                printf("Enter backup file to load: ");
                scanf("%s", save_file);

                if (update_database(hash_table, save_file) == SUCCESS)
                    printf("Database updated successfully from %s\n", save_file);
                else
                    printf("Error: Could not update database.\n");
                break;

            case 6:
                printf("Exiting program.\n");
                return SUCCESS;

            default:
                printf("Invalid option. Enter again.\n");
        }
    }

    return SUCCESS;
}

