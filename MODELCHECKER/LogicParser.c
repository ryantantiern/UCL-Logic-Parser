#include <stdio.h>
#include <string.h>

/*  The main program calls procedures parse, partone, parttwo and bin which are not implemented here.*/
char Fsize[50];
int number = -1; // global variable to check if formula fails (=0)

int parse(char *g){
/* returns 0 for non-formulas, 1 for atoms, 2 for negations, 3 for binary connective fmlas, 4 for existential and 5 for universal formulas.*/
    int length = strlen(g);

    // Atomic Formula
    if(g[0] == 'X'){
      if(g[1] == '['){
        if(g[2] == 'x' || g[2] == 'y' || g[2] == 'z'){
          if(g[3] == 'x' || g[3] == 'y' || g[3] == 'z'){
            if(g[4] == ']'){
              if(length == 5){ // Base/Edge condition
              // There is no formula after ']'
                if(number == 0){
                // Fail formula
                    return number;
                  }
                  else{
                // Pass formula
                    number = 1;
                  }
              }
              else{
                parse(g+5); // Recur /*In the middle of recursion, if number = 0, function above it will */
                if(number == 0){   /*read next line as number = 0, and keep returning 0 until it reaches the top.*/
                    return number;
                }
                else{
                  number = 1;
                  return number;
                }
              }
    }}}}}

    // Negated Formula
    else if(g[0] == '-'){
      if(length == 1){
        number = 0;
        return number;
      }
      else{
        parse(g+1);
        if(number == 0){
          return number;
        }
        else{
          number = 2;
          return number;
        }
    }}

    // Binary Connective Formula
    else if(g[0] == '(' && g[length-1] == ')'){
      int i = 0, posBC = -1, count = 0,found = 0;
      for(i = 0; i < length; i++){;
        // Search for Binary Connective
        if(g[i] == '('){
          count += 1;
        }
        else if (g[i] == ')'){
          count -= 1;
        }
        if(count == 1){
          // Takes Binary Connective if it sees one
          if(g[i] == 'v' || g[i] == '^' || g[i] == '>'){
            posBC = i;
            found += 1;
          }
        }}

      if(count == 0 && found == 1){

      // Store the first and second halves of BC formula
      char size1[50];
      char* firstFormula =(char *)malloc(sizeof(size1));
      for(i = 0; i < posBC-1 ; i++){
          firstFormula[i] = g[i+1];
      }
      firstFormula[posBC-1] = '\0';

      char size2[50];
      char* secondFormula =(char *)malloc(sizeof(size2));
      for(i = 0; i < length - posBC - 2 ; i++){
      secondFormula[i] = g[posBC+i+1];
       }
      secondFormula[length - posBC - 2] = '\0';
        // Applies recursion
        parse(firstFormula);
        if (number != 0){
        parse(secondFormula);
        }
            if(number == 0){
              return number;
            }
            else{
              number = 3;
              return number;
            }}
        else{
        number = 0;
        }
    }




    // Existential Formula
    else if (g[0] == 'E'){
      if(g[1] == 'x' || g[1] == 'y' || g[1] == 'z'){
        if(length == 2){
          number = 0;
          return number;
        }
        else{
          parse(g+2);
          if(number == 0){
            return number;
          }
          else{
            number = 4;
            return number;

          }
        }
    }}

    // Universal Formula
   else if (g[0] == 'A'){
      if(g[1] == 'x' || g[1] == 'y' || g[1] == 'z'){
        if(length == 2){
          number = 0;
          return number;
        }
        else{
          parse(g+2);
          if(number == 0){
            return number;
          }
          else{
            number = 5;
            return number;
            }
          }
    }}
   else {
    number = 0;
    return number;
   }

   if(number == 0 || number == -1){
    number = 0;
    return 0;
   }
    // Check number if fail formula fails before recursion
   return 0;
}

char *partone(char *g){
// Return the first part of binary connective formula
  int length = strlen(g);
  int i, posBC, count = 0;
  for(i = 0; i < length; i++){
    if(count == 1){
      if(g[i] == 'v' || g[i] == '^' || g[i] == '>'){
        posBC = i;
        break;
      }
      else if (g[i] == '('){
        count += 1;
      }
      else if (g[i] == ')') {
        count -= 1;
      }
    }
    else{
      if (g[i] == '('){
        count += 1;
      }
      else if (g[i] == ')'){
        count -= 1;
      }
    }}

  char size1[50];
  char* firstFormula =(char *)malloc(sizeof(size1));
  for(i = 0; i < posBC-1 ; i++){
      firstFormula[i] = g[i+1];
  }
  firstFormula[posBC-1] = '\0';
  return firstFormula;
}

char *parttwo(char *g)
// Return the formula after binary connective in binary connective formula
{
  int length = strlen(g);
  int i, posBC, count = 0;
  for(i = 0; i < length; i++){
    if(count == 1){
      if(g[i] == 'v' || g[i] == '^' || g[i] == '>'){
        posBC = i;
      }
      else if (g[i] == '('){
        count += 1;
      }
        else if (g[i] == ')') {
        count -= 1;
      }
    }
      else{
      if (g[i] == '('){
        count += 1;
      }
      else if (g[i] == ')'){
        count -= 1;
      }
  }}
  char size2[50];
  char* secondFormula =(char *)malloc(sizeof(size2));
  for(i = 0; i < length - posBC - 2 ; i++){
      secondFormula[i] = g[posBC+i+1];
  }
  secondFormula[length - posBC - 2] = '\0';
  return secondFormula;
}

char bin(char *g){
  // Return binary connective
  int length = strlen(g);
  int i, posBC, count = 0;
  for(i = 0; i < length; i++){
    if(count == 1){
      if(g[i] == 'v' || g[i] == '^' || g[i] == '>'){
        posBC = i;
        break;
      }
      else if (g[i] == '('){
        count += 1;
      }
      else if (g[i] == ')') {
        count -= 1;
      }
    }
    else{
      if (g[i] == '('){
        count += 1;
      }
      else if (g[i] == ')'){
        count -= 1;
      }
    }}

  char binaryConnective = g[posBC];
  return binaryConnective;
}


int main(){
  /*Input a string and check if its a formula*/
  char *name=(char *)malloc(sizeof(Fsize));
  printf("Enter a formula:\n");
  scanf("%s", name);
  int p = parse(name);


  switch(p){
    case 0: printf("Not a formula \n");break;
    case 1: printf("An atomic formula \n");break;
    case 2: printf("A negated formula \n");break;
    case 3: printf("A binary connective formula \n");break;
    case 4: printf("An existential formula \n");break;
    case 5: printf("A universal formula \n" );break;
    default: printf("Not a formula \n");break;
    }

  if (p==3){
    printf("The first part is %s, the binary connective is %c, the second part is %s", partone(name), bin(name), parttwo(name));
    }
  free(name);
  return 1;
}
