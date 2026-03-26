**Programming Assignment 1 – Text Parser**

**Course:** CSE 535 / CSCE 5200 – Information Retrieval
**Student Name:** Rithvik Reddy Krishnaraj Rajmohan
**Student ID:** 11817971

---

### Overview

This project implements the **Text Parser component** of an Information Retrieval (IR) system. The parser reads documents from the TREC FT911 dataset, processes the text, and generates two dictionaries: a **term dictionary** and a **document dictionary**.

The program performs tokenization, removes stopwords, ignores numbers, converts words to lowercase, and assigns unique IDs to both terms and documents. The results are written to an output file called **parser_output.txt**.

---

### Requirements

Before running the program, make sure the following are available:

* A C++ compiler that supports C++11 or later (such as **g++**).
* The dataset folder **ft911** containing the files `ft911_1` through `ft911_15`.
* The file **stopwordlist.txt** containing the list of stopwords.

All these files should be located in the same project directory as the source file.

Example directory structure:

project_folder
│
├── parser.cpp
├── stopwordlist.txt
├── parser_output.txt (generated after execution)
│
└── ft911
  ├── ft911_1
  ├── ft911_2
  ├── ft911_3
  ├── ...
  └── ft911_15

---

### Compilation

Open a terminal or command prompt in the project directory and compile the program using the following command:

g++ parser.cpp -o parser

If the compilation is successful, an executable file named **parser** (or **parser.exe** on Windows) will be created.

---

### Running the Program

After compilation, execute the program using:

parser

or on Linux/macOS:

./parser

The parser will read the dataset files, process the content inside the `<TEXT>` tags, and build the dictionaries.

---

### Output

After execution, the program generates a file named:

parser_output.txt

This file contains two sections:

1. **Term Dictionary**
   A list of unique tokens and their assigned IDs.

2. **Document Dictionary**
   A list of document identifiers and their corresponding numeric IDs.



