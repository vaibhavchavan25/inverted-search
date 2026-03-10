# Inverted Search

## Overview

**Inverted Search** is a data structure–based project that implements an **inverted index** for fast word searching across multiple text files.
Instead of scanning each file every time a search is performed, the program creates a **mapping between words and the files in which they appear**, allowing efficient lookup.

This technique is widely used in **search engines, document indexing systems, and information retrieval applications**.

---

## Objective

The objective of this project is to build a system that:

* Reads multiple text files
* Extracts and indexes words
* Stores the mapping of words to files
* Allows quick searching of words across all indexed files

---

## Features

* Create a database from multiple text files
* Build an **inverted index**
* Display the indexed database
* Search for any word and identify the files containing it
* Save the database to a file
* Update the database from a saved file
* Efficient searching using hashing and linked lists

---

## How Inverted Search Works

Traditional Search:

```
Word → Search file1 → Search file2 → Search file3
```

Inverted Search:

```
Word → Directly find files containing the word
```

Example Index:

| Word      | File      | Count |
| --------- | --------- | ----- |
| data      | file1.txt | 3     |
| structure | file2.txt | 2     |
| search    | file1.txt | 1     |

---

## Project Structure

```
Inverted_Search/
│
├── main.c
├──database.c 
├──validation.c
└── README.md
``
---

## Data Structures Used

### Hash Table

Stores indexes of words based on hash values.

### Linked List

Used to maintain:

* File list
* Word list
* Occurrence count

Structure hierarchy:

```
Hash Table
   ↓
Word Node
   ↓
File Node
```

---

## Compilation

Use the GCC compiler.

```
gcc *.c -o inverted_search
```

---

## Execution

Run the program using:

```
./inverted_search file1.txt file2.txt file3.txt
```

---

## Program Menu

Typical options provided in the program:

```
1. Create Database
2. Display Database
3. Search Word
4. Save Database
5. Update Database
6. Exit
```

---

## Example Workflow

1. Provide input files during execution
2. Create the database
3. Display indexed words
4. Search for any word
5. Save database for later use

Example:

```
Enter word to search: data

Word found
File: file1.txt
Count: 3
```

---

## Applications

* Search engines
* Document indexing
* Log file analysis
* Text analytics systems
* Information retrieval systems

---

## Future Improvements

* Support for large datasets
* Case-insensitive searching
* Stop-word removal
* Web interface for search
* Multi-threaded indexing

---

## Author

**Vaibhav Chavan**

Project developed as part of learning **Data Structures and File Handling in C**.

---

## License

This project is for **educational purposes**.
