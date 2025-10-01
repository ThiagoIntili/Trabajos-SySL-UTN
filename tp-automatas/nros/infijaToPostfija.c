#include <stdlib.h>
#define MAX_ELEMENTOS 10
#define MAX_LEN 50

typedef struct pila{
      int indice;
      int total;
      //char datos[MAX_ELEMENTOS]; chau
      char datos[MAX_ELEMENTOS][MAX_LEN];
}Pila;
Pila * crear(){
	Pila *p;
	p=(Pila *)malloc(sizeof(Pila));
	p->indice=0;
	p->total=0;
	return p;
}

int estaVacia(Pila pila){
	if(pila.total==0){
		return 1;
	}else{
		return 0;
	}
}

int estaLlena(Pila pila){
	if(pila.total==MAX_ELEMENTOS){
		return 1;
	}else{
		return 0;
	}
}

int push(Pila *pila, char* dato){ //chau Pila *pila, char dato
	if(pila->total<MAX_ELEMENTOS){
		strcpy(pila->datos[pila->indice], dato);//pila->datos[pila->indice]=dato;
		pila->indice++;
		pila->total++;
		return 1;
	}else{
		return 0;
	}
}

/*char pop(Pila *pila){
	int aux;
	if(pila->total>0){
		aux=pila->datos[pila->indice-1];
		pila->indice--;
		pila->total--;
		return aux;
	}else{
		return -1;
	}
} chau*/
int pop(Pila *pila, char* buffer){
    if (pila->total > 0) {
        strcpy(buffer, pila->datos[pila->indice - 1]);
        pila->indice--;
        pila->total--;
        return 1;
    } else {
        return 0;
    }
}
int nivelDePrecedencia(char* operador){
	//int nivel=0;
	/*switch(operador){
		case "(": nivel =0;
		          break;
		case "+": nivel =1;
		          break;
		case "-": nivel =1;
		          break;
		case "*": nivel =2;
		          break;
		case "/": nivel =2;
		          break;
		case "$": nivel =3;//NOS SERVIRÁ PARA LA POTENCIA
		          break;
	} chau*/
	if(strcmp(operador, "(") == 0){
	    return 0;
	}
	if(strcmp(operador, "+") == 0 || strcmp(operador, "-") == 0){
	    return 1;
	}

	if(strcmp(operador, "*") == 0 || strcmp(operador, "/") == 0){
	    return 2;
	}
	if(strcmp(operador, "$") == 0){
	    return 3;
	}
}

int tieneMayorOIgualPrioridad(char* operador1, char* operador2){
	int precedenciaPrimerOperador=nivelDePrecedencia(operador1);
	int precedenciaSegundoOperador=nivelDePrecedencia(operador2);
	if(precedenciaPrimerOperador>=precedenciaSegundoOperador){
		return 1;
	}else{
		return 0;
	}
}

int esOperador(char* elemento){
	if(strcmp(elemento, "+") == 0 ||
	   strcmp(elemento, "-") == 0 ||
	   strcmp(elemento, "*") == 0 ||
	   strcmp(elemento, "/") == 0 ||
	   strcmp(elemento, "$") == 0
	   ){
		return 1;
	}else{
		return 0;
	}
}

int esOperando(char* elemento){ //char elemento chau

    if(string_a_int(elemento)!=-1){
        return 1;
    }else{
        return 0;
    }

	/*if(elemento >='0' && elemento <='9'){ chau
		return 1;
	}else{
		return 0;
	}*/
}

int infijaToPostfija(char infija[][MAX_LEN], int longitud,char postfija[][MAX_LEN]){ //chau: char* infija[]

	char elemento[MAX_LEN],operador[MAX_LEN]; //char elemento,operador; chau

	//char  *postfija;
	//postfija=malloc(sizeof(char)*100);

	int j=0;
	int i=0;
	Pila *pila=crear();

	//int longitud= strlen(infija);

	while (i<longitud){
		//elemento = infija[i];
		strcpy(elemento, infija[i]);
		i++;

		if(esOperando(elemento)){
			//postfija[j]=elemento;

			strcpy(postfija[j], elemento);
			j++;
		}else if (esOperador(elemento)){
			if(!estaVacia(*pila)){
				int seDebeContinuar;
				do{
					int value=pop(pila,operador);//operador=pop(pila);
				    if(tieneMayorOIgualPrioridad(operador, elemento)){
						//postfija[j]=operador;
						strcpy(postfija[j], operador);
						j++;
						seDebeContinuar=1;
					}else{
						seDebeContinuar=0;
						push(pila,operador);
					}
				}while(!estaVacia(*pila) && seDebeContinuar);
			}
			push(pila,elemento);
		}else if (elemento == "("){
			push(pila,elemento);
		}else if (elemento == ")"){
			//operador=pop(pila);
			int value=pop(pila,operador);
			while(!estaVacia(*pila) && operador!="(") {
				strcpy(postfija[j], operador);
				j++;
				int value=pop(pila,operador);//operador=pop(pila);
			}
		}
	}
	while(!estaVacia(*pila)) {
		int value=pop(pila,operador);//operador=pop(pila);
		strcpy(postfija[j], operador);//postfija[j]=operador;
		//printf("--nroEntre: %s\n",postfija[j]);
		j++;
	}
	//postfija[j]='\0';
    //return postfija;
    return j;
}

