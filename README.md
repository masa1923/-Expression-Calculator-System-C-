# -Expression-Calculator-System-C-



Overview

A calculator system that reads a file of infix-notation math expressions (with () and [] grouping) and processes each one: validating its syntax, converting valid expressions to postfix, evaluating the result, and building an expression tree from it.

Features
Reads any number of equations from a user-specified input file
Validates each equation and reports why an invalid one failed (e.g. missing operator, unclosed parenthesis), not just that it failed
Converts valid infix expressions to postfix notation
Evaluates postfix expressions and prints each result
Prints a report of all invalid equations found in the file
Builds an expression tree for a chosen equation and prints its:
Inorder traversal (infix form)
Preorder traversal (prefix form)
Postorder traversal (postfix form)
Writes a full report of all equations (valid/invalid, postfix form, result) to output.txt
Design notes
Built entirely with linked-list-based data structures rather than arrays — including for parsing and expression tree construction — as a constraint of the assignment, reinforcing dynamic memory management and pointer manipulation.
Tech

C, custom expression tree, custom stack/queue structures via linked lists, file I/O, recursive tree traversal.

Build & run
bash
gcc calculator.c -o calculator
./calculator

You'll be prompted for the name of the input file containing the equations.

Context

Built for COMP2421 (Data Structures), Birzeit University 
