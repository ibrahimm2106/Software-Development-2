README.md for Library Management System Project
Project Overview
This project involves developing a library management system for Stepwise University. It is designed to manage book registrations, borrowing and returns, and fine calculations. The system caters to two primary user groups: students and librarians, with distinct functionalities for each group.

System Requirements
Compiler: Microsoft’s standard C/C++ compiler (part of Visual Studio).
Platform: Developed and tested on Windows (compatible with the latest versions).
Dependencies: Uses only the standard C++ libraries.
Installation Instructions
Clone or download the repository:
Use Git to clone the repository or download the ZIP file directly from Moodle.
Open the project:
Open the solution file in Visual Studio.
Build the project:
Use the build option in Visual Studio to compile the project.
Usage
Start the application:
Run the compiled executable from Visual Studio or from the command line.
Navigating the system:
Use the menu options displayed on the terminal to interact with the system:
1 for Book Registration (Librarians only)
2 for Borrowing Books (Students and Librarians)
3 for Returning Books
4 for Fine Calculation
Exit the program:
Select the exit option from the menu to close the application.
Features
Book Registration: Enter details such as BookID, Title, Authors, etc., and store them in a CSV file.
Borrowing Books: Search for books by ID or title and borrow if available.
Returning Books: Return borrowed books and update the inventory.
Fine Calculation: Calculate fines for overdue books.
File Structure
/src: Contains all the C++ source code files.
/data: Stores CSV files for books, borrowing records, return logs, and fines.
/docs: Includes system documentation and user manuals.
Contributing
For any bugs or feature requests, please file an issue through the Moodle course forum.
Ensure any pull requests for new features include comprehensive tests and documentation.
Documentation
All functions and classes are documented within the code. Additional documentation is available in the /docs folder, detailing the system architecture and usage instructions.
