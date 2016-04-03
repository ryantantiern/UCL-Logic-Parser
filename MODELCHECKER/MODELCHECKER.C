#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* NOTE ** NOTE ** NOTE ** NOTE ** NOTE ** NOTE **NOTE ** NOTE ** NOTE **/
/* Base case is a variable assignment of atomic formula.
   ie. Universal Fmla => if ALL var assignment for all existing variables in list of edges ARE TRUE
   ie. Existential Fmla => if SOME var assignment for all existing variables in list of edges ARE TRUE
*/
char Fsize[50];
char BC[] = { 'V', '^', '>' };
char VAR[] = { 'x', 'y', 'z'}; // Not used
int no_edges;
int no_nodes;


int search_binConnective(char *g) {
	int bin_counter = 0;
	int i, j, bin_connective = 0;
	for (i = 0; i < strlen(g); i++) {

		if (bin_counter == 1) {
			for (j = 0; j < 3; j++) {
				if (g[i] == BC[j]) {
					bin_connective = i;
					break;
				}
			}
		}

		if (g[i] == '(') {
			bin_counter += 1;
		}
		else if (g[i] == ')') {
			bin_counter -= 1;
		}

		if (bin_connective > 0) {
			return bin_connective;
		}
	}

	return 0;
}

int parse(char *g){
	// Atomic Formula
	if (g[0] == 'X'){
        if (g[1] == '[') {
            if (g[2] == 'x' || g[2] == 'y' || g[2] == 'z') {
                if (g[3] == 'x' || g[3] == 'y' || g[3] == 'z') {
                    if (g[4] == ']') {
                        if (strlen(g) == 5) {
                            return 1;
                        }
	}}}}}

	// Negated Formula
	else if (g[0] == '-'){
		if(parse(g + 1) > 0){
			return 2;
		}
	}
	// Binary Connective Formula
	else if (g[0] == '(') {
		if (g[strlen(g) - 1] == ')') {
			int bin_connective = search_binConnective(g);

			if (bin_connective > 0) {
				char part1[50];
				char part2[50];
				int k = 0, l = 0;
				while (k < bin_connective - 1) {
					part1[k] = g[k + 1];
					k++;
				}
				part1[bin_connective - 1] = '\0';
				while (l < strlen(g) - (bin_connective + 1) - 1) {
					part2[l] = g[bin_connective + 1 + l];
					l++;
				}
				part2[strlen(g) - (bin_connective + 1) - 1] = '\0';

				if (parse(part1) > 0) {
					if (parse(part2) > 0) {
						return 3;
			}}
		}
	}}



	//Existensial Formula
	else if (g[0] == 'E') {
		if(g[1] == 'x' || g[1] == 'y' || g[1] == 'z' ) {
		 if (parse(g + 2) > 0) {
			return 4;
		}
	}}

	//Universal Formula
	else if (g[0] == 'A') {
		if (g[1] == 'x' || g[1] == 'y' || g[1] == 'z') {
			if (parse(g + 2) > 0) {
				return 5;
			}
	}}

	return 0;
}


char *partone(char *g){

	char size1[50]; int bin_connective = search_binConnective(g);
	char *part1 = (char *)malloc(sizeof(size1));
	int k = 0, l = 0;
	while (k < bin_connective - 1) {
		part1[k] = g[k + 1];
		k++;
	}
	part1[bin_connective - 1] = '\0';

	return part1;

}

char *parttwo(char *g){

	char size2[50]; int bin_connective = search_binConnective(g);
	char *part2 = (char *)malloc(sizeof(size2));
	int k = 0, l = 0;
	while (l < strlen(g) - (bin_connective + 1) - 1) {
		part2[l] = g[bin_connective + 1 + l];
		l++;
	}
	part2[strlen(g) - (bin_connective + 1) - 1] = '\0';

	return part2;
}

char bin(char *g){

	return g[search_binConnective(g)];
}
int var_assignment(char *E, int V[3], int edges[no_edges][2]){
    int i,j,k;
    int node1,node2;

    // Assign nodes respective values
    switch(E[0]){

        case 'x' : node1 = V[0]; break;
        case 'y' : node1 = V[1]; break;
        case 'z' : node1 = V[2]; break;
        default : return 0;

    }

    switch(E[1]){

        case 'x' : node2 = V[0]; break;
        case 'y' : node2 = V[1]; break;
        case 'z' : node2 = V[2]; break;
        default : return 0;

    }

    for( i = 0; i < no_edges ; i++){

        if (node1 == edges[i][0]){
            if(node2 == edges[i][1]){
                return 1;
        }}

    }

    return 0;

}

// Needs improvement
int universal_assignment(char *nm, int V[3], int edges[no_edges][2], char affected_var){
    int i,j,k;
    int var_index;
    int node_position;

    // Variable affected by Universal condition
    switch(affected_var){

        case 'x' : var_index = 0; break;
        case 'y' : var_index = 1; break;
        case 'z' : var_index = 2; break;
        default : return 0;

    }

    // Node to look at in list of nodes
    i = 0;
    while( nm[i] != 'X'){
        i++;
    }
    if( nm[ i + 2 ] == affected_var){
        node_position = 0;
    }
    else if( nm[ i + 3] == affected_var){
        node_position = 1;
    }
    // Check truth value
    for( j = 0; j < no_edges; j++){

        V[var_index] = edges[j][node_position];

        for( k = 0; k < no_edges; k++){

            if(edges[j][node_position] == edges[k][node_position]){

                if(eval(nm , edges[k], V) == 1){
                    break;
                }}
        }

        if( k == no_edges){

            return 0;
        }
    }
    return 1;

}

int existential_assignment(char *nm, int V[3], int edges[no_edges][2], char affected_var){
    int i,j,k;
    int var_index;
    int node_position;

    // Variable affected by Existential condition
    switch(affected_var){

        case 'x' : var_index = 0; break;
        case 'y' : var_index = 1; break;
        case 'z' : var_index = 2; break;
        default : return 0;

    }

    // Node to look at in list of nodes
    i = 0;
    while( nm[i] != 'X'){
        i++;
    }
    if( nm[ i + 2 ] == affected_var){
        node_position = 0;
    }
    else if( nm[ i + 3] == affected_var){
        node_position = 1;
    }

    // Check truth value
    for( j = 0; j < no_edges; j++){

        V[var_index] = edges[j][node_position];
        if(eval(nm, edges, V) == 1){
            return 1;
        }

    }
    return 0;

}

int atomic(char *nm, int edges[no_edges][2], int V[3]){

    char E[3];
    E[0] = nm[2];
    E[1] = nm[3];
    E[2] = '\0';

    return var_assignment(E, V, edges);

}

int negated(char *nm, int edges[no_edges][2], int V[3]){

    if(eval((nm+1), edges, V) == 1){

        return 0;
    }
    else{
        printf("Negation was called\n");
        return 1;
    }

}

int binary_connective(char *nm, int edges[no_edges][2],int V[3]){

    int A[3]; int B[3];
    int i = 0;
    for(i = 0; i < 3; i++){
        A[i] = V[i];
        B[i] = V[i];
    }


    int eval_partone = eval(partone(nm), edges, A);
    int eval_parttwo = eval(parttwo(nm), edges, B);

    switch(bin(nm)){

        case 'V' : if(eval_partone == 1 || eval_parttwo == 1){
                        return 1;
                    } break;
        case '^' : if(eval_partone == 1 && eval_parttwo == 1){
                        return 1;
                    } break;
        case '>' :  if(eval_partone == 1 && eval_parttwo == 1){
                        return 1;
                    }
                    else if(eval_partone == 0){
                        return 1;
                    }
                    else{
                        return 0;
                    } break;
        default : return 0;

    }
    return 0;
}

int existential(char *nm, int edges[no_edges][2], int V[3]){

    int i,j,k;
    char affected_var = nm[1];

    return existential_assignment((nm+2), V, edges, affected_var);
}

int universal(char *nm, int edges[no_edges][2], int V[3]){

    int i,j,k;
    char affected_var = nm[1];

    return universal_assignment((nm+2), V, edges, affected_var);
}

int eval(char *nm, int edges[no_edges][2], int V[3]){

	switch(parse(nm)){

	    case 1 : return atomic(nm, edges, V);
	    case 2 : return negated(nm, edges, V);
	    case 3 : return binary_connective(nm, edges, V);
	    case 4 : return existential(nm, edges, V);
	    case 5 : return universal(nm, edges,  V);
	    default : return 0;

	}

}



int main()
{
  /*Input a string and check if its a formula*/
  char *name=(char *)malloc(sizeof(Fsize));
  printf("Enter a formula:");
  scanf("%s", name);
  int p = parse(name);
  switch(p){

    case 0: printf("Not a formula");return 0;
    case 1: printf("An atomic formula");break;
    case 2: printf("A negated formula");break;
    case 3: printf("A binary connective formula");break;
    case 4: printf("An existential formula");break;
    case 5: printf("A universal formula");break;
    default: printf("Not a formula"); return 0;

    }

  /*Input a graph.  No. of nodes, edges, then input each edge.*/
  printf("\nHow many nodes in the graph?\n");
  scanf(" %d", &no_nodes);
  printf("The nodes are 0, 1, ..., %d\n", no_nodes-1);
  printf("Now the edges\n");
  printf("How many edges?\n");
  scanf(" %d", &no_edges);

  int edges[no_edges][2];  /*Store edges in 2D array*/
  int  i, k, j;

  for(i=0;i<no_edges;i++){

      printf("input a pair of nodes (<%d)\n", no_nodes);
      scanf(" %d", &j);scanf(" %d", &k);
      edges[i][0] = j; edges[i][1] = k;

    }

  int V[3];

  printf("Assign variables x, y, z\n");
  printf("x is ?(<%d)\n", no_nodes);scanf(" %d", &V[0]);
  printf("y is ?\n");scanf(" %d", &V[1]);
  printf("z is ?\n");scanf(" %d", &V[2]);


  if (eval(name, edges,  V) == 1){
    printf("The formula %s is true", name);
  }
  else{
    printf("The formula %s is false", name);
  }

  free(name);

  return 1;

}
