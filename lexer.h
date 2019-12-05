//CPSC 323
//programmed by Justin Drouin
//September 28th, 2019
//Assignment 1 Lexer

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <ctype.h>
#include <array>

using namespace std;
//token class
class token{
public:
  char Keywords[18][10] = {"int", "float", "bool", "if", "else", "then", "endif", "while", "whileend", "do",
   "doend", "for", "forend", "input", "output", "and", "or", "function"};
  string Oper = "*+-=/><%";
  string Separators = "'(){}[],.:;!";
  vector<string> Identifiers;
  int state;
  token();

  bool isKeyword(char temp[]);
  bool isOperator(char temp);
  bool isSeparator(char temp);
  int isValidIdentifier(char temp[], int state, int i);
  void lex(char str, token lexer, ofstream& outfile,ifstream& infile);
};


token::token(){state = 0;}

//bool, checks for operator
bool token::isOperator(char temp){
  for(int i = 0; i < 8; i++){
      if(temp == Oper[i]){
        return true;
      }
  }
  return false;
}

//bool, checks for separators
bool token::isSeparator(char temp){
  for(int i = 0; i < 12; i++){
    if(temp == Separators.at(i)){
      return true;
    }
  }
  return false;
}

//bool, checks for keywords
bool token::isKeyword(char temp[]){
  	for(int i = 0; i < 18; i++){
  		if(strcmp(Keywords[i], temp) == 0){
  			return true;
  		}
  	}
  	return false;
}

int token::isValidIdentifier(char temp[], int state, int i){
//FSM table for checking identifiers for validity
int validIdentifier[3][4] = {{1,2,2,2},{1,1,1,2},{2,2,2,2}};

      for( int j = 0; j < 4; j++){
          switch(j){
            case 0:
                if(isalpha(temp[i])){
                  state = validIdentifier[state][0];
                  return state;
                  }
                  break;
            case 1:
                if(isdigit(temp[i])){
                  state = validIdentifier[state][1];
                  return state;
                  }
                  break;
            case 2:
                if(temp[i]=='$'){
                  state = validIdentifier[state][2];
                  return state;
                  }
                  break;
            case 3:

                  state = validIdentifier[state][3];
                  return state;
                  break;
            default: return state;
            }
   }
return state;
}


//main lexer function
void token::lex(char str, token lexer, ofstream& outfile, ifstream& infile){
  int i, j = 0;
  char buff[10];

  outfile << "TOKENS               LEXEMES\n\n";

  while (!infile.eof()){
      str = infile.get(); //get char from file
      //flags for comments
      int flag;

      //if section is commented out; flags
      if ( str == '!'){
            flag++;
            flag = flag % 2;
      }

      //check flag and ignores char until second flag is found by prev check.
      if(str != '!' && flag == 0){
            //section for keywords and identifiers
            if((str == ' ' || str == '\n' || str == '('|| str == ')' || str ==',' ||
                str == '{'|| str == '}' || str =='.' || str == 39 || str == ';' ||
                str == ':' || str == '!' || str == '[' || str == ']') && (j != 0)){
                      buff[j] = '\0';
                      j = 0;

                      if(lexer.isKeyword(buff) == 1){
                          outfile << "KEYWORD        =     " << buff<< "\n";
                        }
                      else{

                        state = 0;
                          //call isValidIdentifier function to run FSM and check if valid
                         for(int i = 0; i < strlen(buff); i++){
                            state = isValidIdentifier(buff, state, i);
                          }
                          //check final state
                          switch(state){
                            case 1: { outfile << "IDENTIFIER     =     " << buff<<"\n";
                            //push identifiers
                            lexer.Identifiers.push_back(buff);
                            break;
                            }
                            case 2: { outfile << "INVALID ID     =     " << buff<<"\n";
                            break;
                            }
                            default: break;
                          }

                      }
              }

              if(lexer.isOperator(str) == 1){
                    outfile << "OPERATOR       =     " << str<<"\n";
              }

              //section for seperators
              if(lexer.isSeparator(str) == 1){
                    outfile << "SEPARATOR      =     " << str <<"\n";
              }
              //if char is alphanumeric or $, increments buffer index and adds char
              //used for identifiers
              if(isalnum(str) || str == '$'){
                    buff[j++] = str;
              }
        }
}
return;
}
