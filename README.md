# General Journal to Trial Balance and T-Account Converter

I created this project for my Object Oriented Programming and Accounting Fundamentals course. It is a c++ application which help in reducing the task of a general accountant. 

## Features

- **Create General Journal Entries**: Add new credit or debit transactions to the general journal.
- **Update Journal Entries**: Modify existing transactions in the journal.
- **Display Journal Entries**: View all transactions recorded in the journal.
- **Generate T-Accounts**: Create T-accounts based on the journal entries.
- **Generate Trial Balance**: Calculate and display the trial balance from the journal entries.

## Getting Started

### Prerequisites

To compile and run this project, you need:

- A C++ compiler (e.g., GCC)
- Make sure you are on a Windows system (as it uses `<conio.h>` and `<windows.h>` libraries).

### Compilation

To compile the project, you can use a C++ compiler 

## Object-Oriented Concepts Used
### Classes and Objects
-JG Class: Handles the details of each journal entry, including the month, description, credit, debit, and date. It encapsulates the properties of a journal entry and provides methods to set and get these properties.
-Accountant Class: Manages the journal entries, including initializing, updating, and displaying entries. It also handles password verification for account security.
-Taccount Class: Inherits from JG and is responsible for creating T-accounts based on the journal entries.
-Trailbal Class: Also inherits from JG and is used to calculate the trial balance from the journal entries.
### Encapsulation
-Each class encapsulates its data members and provides public methods for interacting with those data members. For example, JG has private data members such as month, credit, and debit, with public methods to set and get these values.
### Inheritance
-The Taccount and Trailbal classes inherit from the JG class. This demonstrates the use of inheritance to extend the functionality of the base class (JG) for specific purposes (creating T-accounts and calculating trial balance).
### Static Members
-The JG class uses a static member n to keep track of the number of journal entries across all instances of the class.
### File Handling
The program reads from and writes to various files (general_journal.csv, No_of_entries.txt, pass.txt, gj.txt) to persist journal entries, keep track of the number of entries, and store the password securely.
