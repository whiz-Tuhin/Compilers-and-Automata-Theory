//TODO := Change the code to include multiple alphas & beta
//FIXME := The file output isn't working quite well so... structure it


#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

int main(){


      char productions[10][100];
      int index[10];
      int p=0;
      char filename[100] = "grammar.txt";

      int num = 0,f = 0;
      char non_terminal;
      int k = 3;
      int count = 0;
      printf("Enter the number of productions in grammar\n");
      scanf("%d",&num);

      printf("Enter the grammar in production form... e.g (E->E+T) => \n");

      for(int i = 0;i < num;i++){
                   scanf("%s",productions[i]);
      }


      FILE* fp;
      fp = fopen(filename,"w+");

      for(int i = 0;i < num;i++){

                   char final[2][100];
                   char alpha[10],beta[10],lambda[7] = "lambda";
                   if(productions[i][0] == productions[i][k]){

                                    printf("Production[%d] ==> %s Contains Left Recursion\n",i+1,productions[i]);

                                    non_terminal = productions[i][0];
                                    int l = i,j = k+1,h = 0;

                                    //setting the value for alpha
                                    while(productions[l][j] != '|'){
                                                alpha[h++] = productions[l][j];
                                                j++;
                                    }
                                    h = 0;
                                    j+=1;
                                    while(productions[l][j] != '\0'){
                                                beta[h++] = productions[l][j];
                                                j++;
                                    }

                                    printf("%c -> %s%c'\n%c' -> %s%c' | lambda\n",non_terminal,beta,non_terminal,non_terminal,alpha,non_terminal);

                                     printf("\n\n");
                                     printf("Check the file for the whole grammar...\n");

                                     final[0][0] = non_terminal;
                                     final[0][1] = '-';final[0][2] = '>';

                                     int len = strlen(alpha);
                                     int m = 0;
                                     while(m < strlen(alpha )){
                                              final[0][m+3] = alpha[m];
                                              m++;
                                     }
                                     final[0][m+3] = non_terminal;final[i+f][m+4] = '1';


                                     final[1][0] = non_terminal;final[1][1] = '1';
                                     final[1][2] = '-';final[1][3] = '>';

                                     m = 0;

                                     while(m < strlen(beta)){
                                              final[1][m+4] = beta[m];
                                              m++;
                                     }
                                     final[1][m+4] = non_terminal;final[1][m+5] = '1';
                                     final[1][m+6] = '|';

                                     for(int t = 0;t < 6;t++){
                                                  final[1][m+t+7] = lambda[t];
                                     }

                                     //printf("final[0] ==> %s\nfinal[1] ==> %s\n",final[0],final[1]);

                                     fputs(strcat(final[0],"\n"),fp);
                                     fputs(strcat(final[1],"\n"),fp);



                   }
                   else{

                          printf("Production[%d] is left recursion free...\n",i+1);
                          index[p++] = i;
                          count++;
                   }

      }

      // for(int i = 0;i < 2*num
      //   ;i++){
      //              printf("%s\n",final[i]);
      // }

      for(int i = 0;i < p;i++)
                   fputs(productions[index[i]],fp);

      if(count == num){
              printf("The Given Grammar is Left Recursion Free\n");
      }

      fclose(fp);


      return 0;



}
