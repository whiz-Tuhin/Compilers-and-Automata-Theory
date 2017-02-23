#include <cstdio>
#include <cstdlib>
#include <string>

char input[100] = "a,$";
char* lookahead;

//prototypes defined
void T();
void T1();

void S(){

	if(*lookahead == 'a' || *lookahead == '@'){

			     printf("Matched Symbol => %c\n",*lookahead);
			     lookahead++;
			     printf("pointer position => %c\n",*lookahead);

			     if(*lookahead == '$'){
			     		printf("String belongs to L(G)\n");
			     		exit(0);
			     }

			     else{
			     		  printf("String doesn't belong to L(G)\n");
        		    		  exit(0);
			     }

        }
        else if(*lookahead == '('){
        		     printf("Matched Symbol => %c\n",*lookahead);
			     lookahead++;
			     printf("pointer position => %c\n",*lookahead);
			     T();
	}
	else if(*lookahead == '$'){
			    printf("String belongs to L(G)\n");
			    exit(0);
        }
        else{
        		    printf("String doesn't belong to L(G)\n");
        		    exit(0);
        }

}

void T(){

	if(*lookahead == 'a' || *lookahead == '@' || *lookahead == ')'){

			     printf("Matched Symbol => %c\n",*lookahead);
			     lookahead++;
			     printf("pointer position => %c\n",*lookahead);

			     if(*lookahead == '$'){
			     		printf("String belongs to L(G)\n");
			     		exit(0);
			     }
			     T1();
	}
}

void T1(){

	if(*lookahead == ',' || *lookahead == ')'){

			     printf("Matched Symbol => %c\n",*lookahead);
			     lookahead++;
			     S();
			     if(*lookahead == '$'){
			     		printf("String belongs to L(G)\n");
			     		exit(0);
			     }
			     T1();


	}
}



int main(){

	lookahead = &input[0];
	printf("pointer position => %c\n",input[0]);
	S();

	return 0;
}
