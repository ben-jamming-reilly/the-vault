/*
Class: CPSC 122-01
Benjamin Reilly
GU Username: breilly4
Submitted By: Benjamin Reilly
File Name: proj10.h
To Execute: ./calc "(A+B) 7 12
*/

#ifndef CALC_H
#define CALC_H

#include "stack2.h"


class Calc 
{ 
  public: 
  /* 
  pre: none 
  post: instance of calculator created. valid in-fix expression stored in 
        inFix. Hash table has been created 
  */
  Calc(int argcIn, char* argvIn[]);

  /*
  pre: instance of calculator exists. 
  post: displays the infix expression
 */
  void DisplayInFix();
 

 private:
  /*
  pre:  instance of calculator exist and are valid
  post: creates a hash table for the input values
  */
  void CreateHash();
  /*
  pre:  instance of calculator exists
  post: returns true if all characters in the infix expression are legal,
        false otherwise  Legal characters are ')', '(', '+','-','*','/',
        'A' ... 'Z'   
  */
  bool CheckTokens();

  /*
   pre:  instance of calculator exists and all input tokens are legal
   post: Using the technique discussed in class, returns true if parentheses
         are balanced, false otherwise 
  */
  bool CheckParens();
  
  
  Stack* stk;  
  char*  inFix;    //null-terminated string that holds infix expression  
  char*  postFix;  //null-terminated string that holds the post-fix
  int*   hashTble; //pointer to hash table holding expression values
  int    myArgc;   //number of command line arguments
  char*  myArgv[];  //command line arguments 
};
#endif 

