/*
lexp -> aterm | list
aterm -> number | identifier
list -> (lexp_seq)
lexp_seq -> lexp A'
A' -> lexp A' | E
*/


#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;
#define BUFFER_SIZE 256

void getNextToken();
void list();
void aterm();
void lexpseq();
void lexpseq1();
void lexp();

char* input;
char* token_pointer;
char token[BUFFER_SIZE];

FILE* fp;

void current_token(){
    cout<<"Currently at token  => "<<token<<endl;
}

void getNextToken(){
      int k = 0;
      char c = fgetc(fp);
      if(c == '$'){
        token[k++] = c;
        token[k] = '\0';
      }
      else{
      while(c != ' '){
          token[k++] = c;
          c = fgetc(fp);
      }
      token[k] = '\0';
     }

      cout<<"Token = "<<token<<endl;
}

void lexp(){
    cout<<"Inside lexp"<<endl;
    current_token();
    if(strcmp(token,"(") == 0){
          list();
    } else if(strcmp(token,"number") == 0 || strcmp(token,"identifier") == 0){
          aterm();
    }else{
      cout<<"Error"<<endl;
    }
}

void list(){
    cout<<"Inside list"<<endl;
    if(strcmp(token,"(") == 0){
          //current_token();
          getNextToken();
          lexpseq();
          if(strcmp(token,")") == 0){
                cout<<"final stuffs"<<endl;
                getNextToken();
                current_token();
                if(strcmp(token,"$") == 0){
                        cout<<"Success"<<endl;
                        exit(0);
                }
          } else {
                  cout<<"Error"<<endl;
          }
    } else {
          cout<<"Error"<<endl;
    }
}

void aterm(){
      cout<<"Inside aterm"<<endl;
      if(strcmp(token,"number") == 0){
              getNextToken();
      } else if(strcmp(token,"identifier") == 0){
              getNextToken();
      } else{
          cout<<"Error"<<endl;
      }
}

void lexpseq(){
      cout<<"Inside lexpseq"<<endl;
      lexp();
      lexpseq1();
}

void lexpseq1(){
      cout<<"Inside lexpseq1"<<endl;
      if(strcmp(token,"(") == 0 || strcmp(token,"number") == 0 || strcmp(token,"identifier") == 0){
            lexp();
            lexpseq1();
      }
}


int main(){

        fp = fopen("input.txt","r");
        getNextToken();
        lexp();
        return 0;
}
