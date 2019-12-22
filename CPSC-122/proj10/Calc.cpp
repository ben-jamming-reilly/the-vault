#include "Calc.h"

#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

Calc::Calc(int argcIn, char* argvIn[])
{
   myArgc = argcIn;
   for(int i = 0; i < myArgc; i++)
   {
      myArgv[i] = new char[strlen(argvIn[1]) + 1];
      strcpy(myArgv[i], argvIn[i]);
   }
   
   if(CheckTokens() && CheckParens())
   {
      CreateHash();
      inFix = new char[strlen(myArgv[1]) + 1];
      inFix[strlen(myArgv[1])] = '\0';
      strcpy(inFix, myArgv[1]);
   }
   
   //NEWLY ADDED FOR TESTING
   //STARTS
   for(int i = 1; i < myArgc; i++)
   {
      cout<<myArgv[i]<<endl;
   }
   
   for(int i = 0; i < 26; i++)
   {
      cout<<static_cast<char>('A' + i)<<": "<<hashTble[i]<<'\t';
      if(!((i+1) % 3))
      {
         cout<<endl;
      }
   }
   cout<<endl;
   //ENDS
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

void Calc::CreateHash()
{
   int i = 0;
   int j = 2;
   hashTble = new int[26];
   
   for(int i = 0; i < 26; i++)
   {
      hashTble[i] = 0;
   }
   
   while(myArgv[1][i] != '\0')
   {
      if(myArgv[1][i] >= 'A' && myArgv[1][i] <= 'Z')
      {
         hashTble[myArgv[1][i] % 'A'] = atoi(myArgv[j]);
         j += 1;
      }
      i += 1;
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

