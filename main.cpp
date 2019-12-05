//CPSC 323
//programmed by Justin Drouin
//September 28th, 2019
//Assignment 1 Lexer

#include "lexer.h"

int main(int argc,  char *argv[]){
//initialize lexer
token lexer;
char str;
//open input file & file for tokens and lexemes
ifstream infile (argv[1]);
ofstream outfile ("tokenOutput.txt");

//check if file is open
if (infile.is_open()){
//pass class object and files to lexer
      lexer.lex(str, lexer, outfile, infile);

//close files
  infile.close();
  outfile.close();
}
else cout << "Unable to open file";

return 0;
}
