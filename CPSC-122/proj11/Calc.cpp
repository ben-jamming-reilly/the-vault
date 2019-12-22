//Calc.cpp
#include <iostream>
#include <cstring>
using namespace std;

#include "Calc.h"

Calc::Calc(int argCIn, char* argvIn[])
{
   //myArgc now holds the number of command line arguments
   myArgc = argCIn;
   
   //declare storage for myArgv, a point to an array of pointers to char
   myArgv = new char*[myArgc];
   
   //copy command line arguments into member variable
   for (int i = 0; i < myArgc; i++)
   {
   //declare storage for argument i
   myArgv[i] = new char[strlen(argvIn[i]) + 1]; 
   //copy command line argument i to member variable
   strcpy(myArgv[i],argvIn[i]);	
   }
   
   Parse(myArgv, myArgc);
}

void Calc::DisplayInFix()
{
   int i = 0;
   while(inFix[i] != '\0')
   {
      cout<<inFix[i];
      i += 1;
   }
   cout<<endl;
}

void Calc::DisplayPostFix()
{
   int i = 0;
   while(postFix[i] != '\0')
   {
      cout<<postFix[i];
      i += 1;
   }
   cout<<endl;
}

void Calc::InFixToPostFix()
{
   int i = 0;
   int j = 0;
   char *sto = new char[strlen(inFix)];
   
   stk = new Stack;
   
   while(inFix[i] != '\0')
   {
      if(inFix[i] >= 'A' && inFix[i] <= 'Z')
      {
         sto[j] = inFix[i];
         j += 1;
      }
      else if(inFix[i] == ')')
      {
         sto[j] = stk->Peek();
         stk->Pop();
         j += 1;
      }
      else
      {
         switch(inFix[i])
         {
            case '+':
               stk->Push('+');
               break;
            case '-':
               stk->Push('-');
               break;
            case '*':
               stk->Push('*');
               break;
            case '/':
               stk->Push('/');
               break;
         }
      }
      i += 1;
   }
   sto[j] = '\0';
   
   postFix = new char[strlen(sto) + 1];
   strcpy(postFix, sto);
   
   delete sto;
   delete stk;
}

void Calc::Evaluate()
{
   int i = 0, valueA, valueB, result;
   stk = new Stack;
   
   while(postFix[i] != '\0')
   {
      if(postFix[i] >= 'A' && postFix[i] <= 'Z')
      {
         stk->Push(hashTble[postFix[i] % 'A']);
      }
      else
      {
         valueA = stk->Peek();
         stk->Pop();
         
         valueB = stk->Peek();
         stk->Pop();
         
         switch(postFix[i])
         {
            case '+':
               result = valueA + valueB;
               break;
            case '-':
               result = valueB - valueA;
               break;
            case '*':
               result = valueA * valueB;
               break;
            case '/':
               result = valueB / valueA;
               break;
         }
         stk->Push(result);
      }
      i += 1;
   }
   result = stk->Peek();
   stk->Pop();
   cout<<"Evaluation: "<<result<<endl;
   delete stk;
}

//Private Methods

void Calc::Parse(char* cmdLineInp[], int num_cmd_line_args)
{
   int i = 0, j = 2;
   if(CheckTokens() && CheckParens())
   {
      inFix = new char[strlen(cmdLineInp[1]) + 1];
      inFix[strlen(cmdLineInp[1])] = '\0';
      strcpy(inFix, cmdLineInp[1]);
      
      hashTble = new int[26];
      
      for(int index = 0; index < 26; index++)
      {
         hashTble[index] = 0;
      }
      
      while(inFix[i] != '\0')
      {
         if(inFix[i] >= 'A' && inFix[i] <= 'Z')
         {
            hashTble[inFix[i] % 'A'] = atoi(cmdLineInp[j]);
            j += 1;
         }
         i += 1;
      }
   }
   else
   {
      exit(1);
   }
}

bool Calc::CheckTokens() 
{
   int i = 0;
   while(myArgv[1][i] != '\0')
   {
      if(myArgv[1][i] < 'A' || myArgv[1][i] > 'Z')
      {
         switch(myArgv[1][i])
         {
            case '(':
            case ')':
            case '+':
            case '-':
            case '*':
            case '/':
               break;
            default:
               return false;
         }
      }
      i += 1;
   }
   return true;
}

bool Calc::CheckParens()
{
   bool valid = true;
   int i = 0;
   stk = new Stack;
   
   while(myArgv[1][i] != '\0')
   {
      if(myArgv[1][i] == '(')
      {
         stk->Push('(');
      }
      else if(myArgv[1][i] == ')')
      {
         if(stk->IsEmpty())
         {
            valid = false;
            break;
         }
         
         stk->Pop();
      }
      i += 1;
   }
   if(valid != false)
   {
      valid = stk->IsEmpty();
   }
   
   delete stk;
   return valid;
}
