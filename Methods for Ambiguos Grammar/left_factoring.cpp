#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(){

  char productions[100][100];
  int num;

  cout<<"Enter the number of productions in the grammar"<<endl;
  cin>>num;

  cout<<"Enter the productions in the form of E->E+T|.."
  for(int i = 0;i < num;i++){
               cin>>productions[i];
  }

  char start_symbol = productions[0][0];

  FILE* fp;
  fp = fopen("grammar.txt",w+);

  int total = 0;
  for(int i = 0;i < num;i++){


                char common[100][100];
                int l = 0;
                int j = 0;
                while(k < productions[i].length()){
                        int k = 3;

                        if(productions[i][k] == '|'){
                            common[l][j] = '\0'
                            j = 0;
                            l++;
                        }
                        else{
                            common[l][j++] = productions[i][k++];
                        }
               }

               total = l;
  }

  char str[100];
  int found_at[total];

  for(int i = 0;i < common[0].length() || i < common[1].length();i++){
              if(common[0][i] == common[1][i]){
                      str[i] = common[0][i];
              }
  }

  string alpha =  str;
  for(int i = 0;i < total;i++){
          size_t found = common[i].find(alpha);
          if(found != string::npos){
                found_at[i] = found;
          }
          else{
                found_at[i] = -1;
          }

  }

  //removing common part and appending it to the new grammar
  char new_grammar[100];
  new_grammar[0] = start_symbol;
  new
  for(int i = 3;i < alpha.length();i++){
               new_grammar[i] = alpha[i];
  }
  new_grammar[alpha.length() + 1] = 'X';





  return 0;
}
