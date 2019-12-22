#include <iostream>
using namespace std;

#include "Calc.h"

int main(int argc, char* argv[])
{
   Calc* C = new Calc(argc, argv);
   
   C->DisplayInFix();
   
   C->InFixToPostFix();
   
   C->DisplayPostFix();
   
   C->Evaluate();
   
   
   
   delete C;
   return 0;
}
