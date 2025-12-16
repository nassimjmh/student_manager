# Student Management System

## Project Description

This project is a comprehensive student management system developed in C as part of the Advanced C Programming course at CY Tech. It handles student data, courses, grades, and provides various analysis features.

## Features

### Core Functionality
- **Data Structures**: Optimized structures for grades, courses, students, and cohorts
- **File Parsing**: Reads student data from text files with custom format
- **Grade Management**: Automatic calculation of course averages and weighted overall averages
- **Binary Persistence**: Save and load data in efficient binary format
- **Student Rankings**: Generate top 10 students and top 3 per course

### Advanced Features
- Modular architecture with separate compilation
- Comprehensive Doxygen documentation
- Generic Makefile with multiple build targets
- Robust error handling and memory management
- Protection against memory leaks

## Project Structure

```
student_management/
├── src/              # Source files (.c)
│   ├── structures.c  # Core data structures
│   ├── parser.c      # File parsing functions
│   ├── save_load.c   # Binary save/load
│   ├── display.c     # Display functions
│   ├── sort.c        # Sorting and ranking
│   └── main.c        # Main program
│
├── include/          # Header files (.h)
│   ├── structures.h
│   ├── parser.h
│   ├── save_load.h
│   ├── display.h
│   └── sort.h
│
├── obj/              # Object files (generated)
├── bin/              # Binary executable (generated)
├── doc/              # Documentation (generated)
├── Makefile          # Build system
├── Doxyfile          # Doxygen configuration
├── README.md         # This file
└── data.txt          # Sample data file
```

## Data File Format

The input file (`data.txt`) follows this structure:

```
ETUDIANTS
numero;prenom;nom;age
226345678;Alexander;Müller;19
...

MATIERES
nom;coef
Mathematiques;2.25
Physique;1.75
...

NOTES
id;nom;note
226767522;Geographie;18.3
226112457;Mathematiques;2.2
...
```

## Compilation

### Requirements
- GCC compiler (C11 standard)
- Make utility
- Doxygen (optional, for documentation generation)

### Build Commands

```bash
# Basic compilation
make

# Build and run
make run

# Debug build with symbols
make debug

# Optimized release build
make release

# Generate documentation
make doc

# Clean object files
make clean

# Clean everything
make fclean

# Rebuild from scratch
make re

# Show help
make help
```

## Usage

### Basic Execution

```bash
# Run with default data file (data.txt)
./bin/student_manager

# Run with custom data file
./bin/student_manager my_data.txt
```

### Program Output

The program performs the following operations:
1. Loads student data from file
2. Tests binary save/load functionality
3. Displays sample students
4. Shows top 10 students by average
5. Shows top 3 students in Mathematics
6. Shows top 3 students in Computer Science
7. Cleans up all allocated memory

## Memory Management

All dynamically allocated memory is properly freed:
- Student names and surnames
- Course names
- Grade arrays
- Course arrays
- Student arrays
- Cohort structures

## Implementation Details

### Question 1: Data Structures
- `Grades`: Dynamic array of float values
- `Course`: Course information with grades
- `Student`: Student with multiple courses
- `Prom`: Cohort of students

### Question 2: Parsing and Display
- `parseStudentLine()`: Parse student data
- `parseCourseLine()`: Parse course data
- `parseAndAddGrade()`: Parse and add grades
- `loadFile()`: Load entire data file
- Various display functions

### Question 3: Binary Persistence
- `saveProm()`: Save cohort to binary file
- `loadProm()`: Load cohort from binary file

### Question 4: Rankings
- `getTop10Students()`: Top 10 by overall average
- `getTop3InCourse()`: Top 3 in specific course

## Error Handling

The program includes comprehensive error checking:
- File access validation
- Memory allocation verification
- NULL pointer checks
- Invalid data handling
- Informative error messages to stderr

## Documentation

Generate and view the full API documentation:

```bash
make doc
firefox doc/html/index.html  # Or your preferred browser
```

## Author

Nassim Jamhour - Advanced C Programming Course

## License

Educational project - CY Tech 2025
