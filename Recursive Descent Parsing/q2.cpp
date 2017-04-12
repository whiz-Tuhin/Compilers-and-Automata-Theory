#include <cstdio>
#include <cstdlib>
#include <string>


char input[100];
char* lookahead;

void E();
void E1();
void T();
void T1();
void F();

void pointer_position(){
	printf("pointer position => %c\n",*lookahead);
}

void match_token(){
	printf("symbol matched => %c\n",*lookahead);
}

void success(){
	printf("Input belongs to L(G)\n");
}

void failure(){
	printf("Input doesn't belong to L(G)\n");
}

void E(){

	if(*lookahead == '('){
		match_token();
		lookahead++;

		if(lookahead == '$')
			success();

		pointer_position();
		E1();
	}
	if(*lookahead == 'i' && *(lookahead+1) == 'd'){
		printf("symbol matched => id\n");
		lookahead += 2;
		pointer_position();
		E1();
	}
	else{
		failure();
	}
}

void E1(){

	if(*lookahead == '+'){
		match_token();
		lookahead++;
		T();

	}
	else if(*lookahead == ')'){
		match_token();
		lookahead++;

		if(lookahead == '$'){
			success()
			exit(0);
		}
		else{
			failure();
			exit(0);
		}
	}
	else{
		failure();
		exit(0);
	}
}

void T(){

   if(*lookahead == '('){
      match_token();
      lookahead++;

      if(*lookahead == '$'){
            success();
            exit(0);
      }
      else{
            pointer_position();
            T1();
      }
   }

   else if(*lookahead == 'i' && *(lookahead+1) == 'd'){
            pointer_position();
            printf("symbol matched => id\n");
            lookahead += 2;

            T1();
   }

   else{
        failure();
        exit(0);
   }

}

void T1(){

        pointer_position();

        if(*lookahead == '*'){

              match_token();
              lookahead++;
              F();

        }
        else if(*lookahead == '+' || *lookahead == ')'){

              match_token();
              lookahead++;

              if(*lookahead == '$'){
                      success();
                      exit(0);
              }
              else{
                      failure();
                      exit(0);
              }

        }

}


//FIXME //continuation from code from here don't forget the recursive function call back to T1()
//TODO ==> Handle all cases of strings

void F(){

        pointer_position();

        if(*lookahead == '(' || )
}




int main(){


	printf("Grammar is\n E -> E+T | T\n T -> T*F | F\n F -> (E) | id\n\n");

	printf("Removing Left Recursion..........\n");

	printf("Enter the input string of terminals\n");

	scanf("%s",input);

	lookahead = &input[0];
	pointer_position();
	E();

	return 0;
}
