/***********************************************/
/* Arvore Binaria - AVL                        */
/* objetivo: registro de códigos               */
/* programador: Daniela Bagatini               */
/* criado em: 11/11/2020                       */
/* data da última alteracao: 30/10/2023        */
/***********************************************/

#include <stdio.h>        // printf e scanf
#include <conio.h>        // getch
#include <string.h>       // strcmp
#include <stdlib.h>       // exit
#include <locale.h>       // setlocale

#define FALSE   0         // constante falsa
#define TRUE   !FALSE     // constante verdadeira


/***********************************************/
/* Definicao dos Registros                     */
/***********************************************/
typedef struct {          // registro
       int  codigo;
	   int  altura;       // utilizado para balanceamento
	   int  fatbal;       // utilizado para balanceamento
} INFORMACAO;

typedef struct arv {
       INFORMACAO info;   // dados do registro
       struct arv* subd;  // ponteiro para o nodo da direita
       struct arv* sube;  // ponteiro para o nodo da esquerda
} ARVORE;



/***********************************************/
/* Definicao das Funcoes                       */
/***********************************************/
void entrada_dados   ( ARVORE* aux );         // leitura dos dados de entrada
void imprime_ARVORE  ( ARVORE* aux );         // visualiza arvore em tela, todos os registros
void cria_ARVORE     ( ARVORE** r );          // inicializa arvore com NULL
void insere          ( ARVORE** r );          // inclui um novo registro na arvore, sempre na folha
int  busca           ( int matricula, ARVORE** a, ARVORE** p ); // procura na arvore um codigo
void sucessor        ( ARVORE* p, ARVORE** q, ARVORE** b );     // procura registro posterior de um codigo
void antecessor      ( ARVORE* p, ARVORE** q, ARVORE** b );     // procura registro anterior de um codigo
void remove          ( ARVORE** r );          // exclui um regitro por codigo
void insere_recursivo( ARVORE** r, int cod ); // inclui um novo registro na arvore
void busca_recursivo ( ARVORE *p, int cod );  // procura na arvore um codigo
void remove_recursivo( ARVORE **p, int cod ); // exclui um regitro por codigo
// Funcoes de balanceamento
void calcula_altura  ( ARVORE **r );          // calcula e atualiza a altura e fator de balancemaento de um nodo
int  altura_arvore   ( ARVORE *p );           // atualiza a altura do nodo
void verifica_balanceamento( ARVORE **r );    // verifica balanceamento da arvore
void rotacao_direita ( ARVORE **p );          // rotacao para balanceamento
void rotacao_esquerda( ARVORE **p );          // rotacao para balanceamento
// Funcoes para salvar e carregar
void salva_arvore    ( ARVORE *r );           // salva a lista para um txt
void salva_codigo( ARVORE *r, FILE *arquivo); // salva um codigo no txt
void carrega_arvore  ( ARVORE **r );          // le uma lista de um txt
void carrega_codigo( ARVORE **r, ARVORE *no); // carrega um codigo do txt


/***********************************************/
/* Programa Principal                          */
/***********************************************/
int main( void ){

    char op;                                  // opcao do menu
    ARVORE* r, *p;                            // declaracao da ARVORE, variável do tipo ARVORE = ARVORE de ponteiros
    int cod, fatbal= 0, altura_esq= 0, altura_dir= 0;  // variaveis de balanceamento

    setlocale(LC_ALL, "Portuguese");
    cria_ARVORE( &r );
    while( 1 ){
         printf( "\n /---------------------------------------------------/" );
         printf( "\n Programa de registros - Menu                         " );
         printf( "\n [1] Cria ARVORE                                      " );
         printf( "\n [2] Insere                                           " );
         printf( "\n [3] Remove                                           " );
         printf( "\n [4] Imprime                                          " );
         printf( "\n [5] Insere recursivo                                 " );
         printf( "\n [6] Busca recursivo                                  " );
         printf( "\n [7] Remove recursivo                                 " );
         printf( "\n [8] Salva lista                                     " );
		 printf( "\n [9] Carrega lista                                   " );
         printf( "\n [0] Para sair do programa                            " );
         printf( "\n /---------------------------------------------------/" );
         printf( "\n Opcao: " );
         op = getche(); // tecla de opcao do menu

        switch( op ) {
           case '1':   // rotina cria ARVORE
                   cria_ARVORE( &r );
                   break;

           case '2':   // rotina inclui nodo no final da ARVORE (folha)
                   insere( &r );
                   break;

           case '3':   // rotina exclui nodo da ARVORE
                   remove( &r );
                   break;

           case '4':   // rotina imprime nodos da ARVORE
                   printf("\n");
                   imprime_ARVORE( r );
                   break;

           case '5':  // rotina recursiva do inclui nodo da ARVORE
                   printf("\n Digite o novo codigo: ");
                   scanf("%d", &cod);
                   insere_recursivo( &r, cod );
                   calcula_altura( &r );         // calcula e armazena a altura de cada no
                   verifica_balanceamento( &r ); // verifica balanceamento da ARVORE
                   break;

           case '6':  // rotina recursiva que busca um registro da ARVORE
                   printf("\n Buscar o codigo: ");
                   scanf("%d", &cod);
                   busca_recursivo( r, cod );
                   break;

           case '7':  // rotina recursiva que busca um registro da ARVORE
                   printf("\n Remove codigo: ");
                   scanf("%d", &cod);
                   remove_recursivo( &r, cod );
				   calcula_altura( &r );
                   break;

            case '8': // rotina salva a ARVORE em um arquivo txt
                    salva_arvore( r );
                    break;

            case '9': // rotina carrega uma ARVORE existente de um txt
                    carrega_arvore( &r );
                    calcula_altura( &r );         // calcula e armazena a altura de cada no
                    verifica_balanceamento( &r ); // verifica balanceamento da ARVORE
                    break;

           case '0':  // termino do programa
                   exit( 1 );
                   break;

           default :
                   printf( "\n Digite uma opcao!" );
                   break;
        } // switch( op )

        fflush( stdin ); // limpa buffer do teclado, funciona junto com entrada de dados
        getchar();       // parada da tela
        printf( "\n" );
     } // fim do while( 1 )

 return 0;
} // fim do programa principal



/************************************************
 * entrada_dados                                *
 * objetivo: rotina para ler dados              *
 * entrada : nodo (ponteiro para o novo espaco) *
 * saida   : nodo com dados                     *
 ************************************************/
void entrada_dados( ARVORE* aux ){

	/*  printf( "\n\n Codigo: %d", aux->info.codigo ); */
    aux->subd = NULL;    // nao aponta
    aux->sube = NULL;    // nao aponta
}



/*************************************************
 * imprime_ARVORE                                *
 * objetivo: rotina para imprimir dados          *
 * entrada : ARVORE                              *
 * saida   : dados em tela                       *
 *************************************************/
void imprime_ARVORE( ARVORE* aux ){
     if (aux == NULL)
        printf("\n Árvore está vazia!.");
     else{
        if (aux->sube != NULL){
            imprime_ARVORE(aux->sube);
        }
        printf("%d ", aux->info.codigo);

        if (aux->subd != NULL)
            imprime_ARVORE(aux->subd);
     }
}



/************************************************
 * cria_ARVORE                                   *
 * objetivo: rotina para inicializar a ARVORE    *
 * entrada : nenhuma                             *
 * saida   : NULL (inicializa ARVORE)            *
 ************************************************/
void cria_ARVORE( ARVORE** r ){

    *r = NULL; // arvore criada, raiz nao aponta
    printf( "\n Arvore criada!" );
}



/*************************************************
 * insere                                        *
 * objetivo: rotina para inserir no fim da ARVORE*
 * entrada : ARVORE                              *
 * saida   : ARVORE com mais um registro         *
 *************************************************/
void insere( ARVORE** r ){
    ARVORE* p;                           // ponteiro auxiliar
    ARVORE* a;                           // ponteiro auxiliar para anterior de p (nodo pai)
    int cod, achou;                      // cod = dado de entrada; achou = informa se codigo ja existe na estrutura

    printf("\n Digite o novo codigo: ");
    scanf("%d", &cod);

    p = *r;                              // posiciona ponteiro auxiliar
    achou = busca( cod, &a, &p );        // verifica se codigo a ser inserido ja existe na arvore, "a" e o nodo pai
    if( !achou ){                        // se nao achou o codigo, insere
         ARVORE* no = ( ARVORE * ) malloc ( sizeof( ARVORE )); // aloca novo espaco em memoria

         if( no != NULL ){               // se conseguiu alocar memoria, insere
                 no->info.codigo = cod;  // preenche o novo registro com o codigo ja informado
                 entrada_dados( no );    // entrada do usuario
                 if( *r == NULL )        // verifica se a arvore esta vazia
                     *r = no;            // o registro sera o primeiro, atualiza a raiz
                 else
                      if ( no->info.codigo > a->info.codigo )
                           a->subd = no;  // insere a direita do registro folha
                      else
                           a->sube = no;  // insere a esquerda do registro folha
         } // fim if( no != NULL )
    } // fim if( !achou )
    else
        printf( "\n Registro ja existe!" );
}



/************************************************
 * busca                                        *
 * objetivo: achar nodo                         *
 * entrada : ARVORE e codigo a ser excluido     *
 * saida   : posicao ou NULL (nao encontrou)    *
 ************************************************/
int busca( int cod, ARVORE** a, ARVORE** p ){
   int achou = FALSE;                      // achou = indica se encontrou o codigo na estrutura

   *a = NULL;                              // ponteiro auxiliar para o anterior
   while( ( *p != NULL ) && ( !achou ) )
           if ( (*p)->info.codigo == cod ) // veririfica se encontrou o codigo
                achou = TRUE;              // encontrou a matricula na estrutura
           else {
                *a = *p;                   // posiciona ponteiro auxiliar no anterior de p
                if( (*p)->info.codigo > cod )
                    *p = (*p)->sube;       // anda com o ponteiro p para a esquerda, pois o codigo procurada e menor
                else
                    *p = (*p)->subd;       // anda com o ponteiro p para a direita, pois o codigo procurada e maior
           } // fim if ((*p)->info.codigo == cod)

   return achou;
}



/***************************************************
 * remove                                          *
 * objetivo: rotina para excluir nodo da ARVORE    *
 * entrada : ARVORE                                *
 * saida   : ARVORE                                *
 ***************************************************/
void remove( ARVORE** r ){
    ARVORE* p;                         // ponteiro auxiliar
    ARVORE* q;                         // ponteiro auxiliar
    ARVORE* b;                         // ponteiro auxiliar
    ARVORE* a;                         // ponteiro auxiliar para anterior
    int cod, achou;                    // cod = dado de entrada; achou = informa se codigo ja existe na estrutura

    if ( *r == NULL )
         printf("\n Arvore vazia!");
    else
       {
        printf("\n Codigo de referencia: ");
        fflush( stdin );               // limpa buffer do teclado e faz a entrada de dados
        scanf( "%d", &cod );

        p = *r;                        // posiciona ponteiro auxiliar
        achou = busca( cod, &a, &p );  // verifica se codigo a ser inserida ja existe na arvore
        if( achou ){                   // se achou o codigo, remove
            if((( p->sube != NULL ) && ( p->subd != NULL )) || (( p->subd != NULL ) && ( p->sube == NULL ))){
                 sucessor( p, &q, &b );
                 p->info= q->info;     // substitui o codigo
                 a= b;                 // ponteiros auxiliares sao posicionados na subarvore
                 p= q;

                 if( p->sube != NULL ) // ajusta subarvore
                     b= p->sube;
                 else
                     b= p->subd;

                 if( p->info.codigo >= a->info.codigo )
                     a->subd= b;
                 else
                     a->sube= b;
            }

            else
               if(( p->subd == NULL ) && ( p->sube != NULL )){
                    antecessor( p, &q, &b );
                    p->info= q->info;     // substitui o codigo
                    a= b;                 // ponteiros auxiliares sao posicionados na subarvore
                    p= q;

                    if( p->subd != NULL ) // ajusta subarvore
                        b= p->subd;
                    else
                        b= p->sube;

                    if( p->info.codigo >= a->info.codigo )
                        a->sube= b;
                    else
                        a->subd= b;
               }
               else
                  if(( p->subd == NULL ) && ( p->sube == NULL ))
                       if( p == *r )     // remove a raiz quando nao tem filhos
                           *r= NULL;
                       else
                           if( p->info.codigo >= a->info.codigo )
                               a->subd= NULL;
                           else
                               a->sube= NULL;

            free( p ); // remove registro que substituiu o excluido
       }
   }
}



/***************************************************
 * sucessor                                        *
 * objetivo: rotina para descobrir nodos filhos    *
 * entrada : ARVORE, ponteiros auxiliares q e b    *
 * saida   : ponteiros auxiliares q e b            *
 ***************************************************/
void sucessor( ARVORE* p, ARVORE** q, ARVORE** b ){
 *b= p;
 *q= p->subd;
 while( (*q)->sube != NULL ){          // caminha pela esquerda ate encontrar folha
         *b= *q;                       // atualiza ponteiro para guardar endereco do pai
         *q= (*q)->sube;               // caminha para a esquerda
 }
}



/***************************************************
 * antecessor                                      *
 * objetivo: rotina para descobrir nodos filhos    *
 * entrada : ARVORE, ponteiros auxiliares q e b    *
 * saida   : ponteiros auxiliares q e b            *
 ***************************************************/
void antecessor( ARVORE* p, ARVORE** q, ARVORE** b ){
 *b= p;
 *q= p->sube;
 while( (*q)->subd != NULL ){        // caminha pela direita ate encontrar folha
         *b= *q;                     // atualiza ponteiro para guardar endereco do pai
         *q= (*q)->subd;             // caminha para a direita
 }
}



/*************************************************
 * insere_recursivo                              *
 * objetivo: rotina para inserir no fim da ARVORE*
 * entrada : ARVORE e cod                        *
 * saida   : ARVORE com mais um registro         *
 *************************************************/
void insere_recursivo( ARVORE** p, int cod ){
    if ((*p) == NULL){
        ARVORE *novo = (ARVORE*) malloc(sizeof(ARVORE));
        novo->info.codigo = cod;
        novo->sube = NULL;
        novo->subd = NULL;
        (*p) = novo;
        printf("Número inserido com sucesso!");
    }else {
        if (cod < (*p)->info.codigo){
            insere_recursivo(&((*p)->sube), cod);
        } else if (cod > (*p)->info.codigo){
            insere_recursivo(&((*p)->subd), cod);
        }
    }
} // desempilha



/***************************************************
 * busca_recursivo                                 *
 * objetivo: rotina para buscar registro por codigo*
 * entrada : ARVORE e cod                          *
 * saida   : ARVORE com mais um registro           *
 ***************************************************/
void busca_recursivo( ARVORE *p, int cod ){
    if (p == NULL){
       printf("Número não encontrado!");
    }else {
        if (p->info.codigo==cod)
            printf("Código está presente!");
        if (cod < p->info.codigo){
            busca_recursivo(p->sube, cod);
        } else if (cod > p->info.codigo){
            busca_recursivo(p->subd, cod);
        }
    }
} // desempilha



/****************************************************
 * remove_recursivo                                 *
 * objetivo: rotina para remover registro por codigo*
 * entrada : ARVORE e cod                           *
 * saida   : ARVORE com registro removido           *
 ****************************************************/
void remove_recursivo( ARVORE **p, int cod ){

        if ((*p) == NULL){ //Verifica se a arvore esta vazia
            printf("Árvore está vazia!");
            return;
    }

    ARVORE *temp = NULL; //Criação de variável temporária

     if (cod < (*p)->info.codigo) {     //Se o codigo for menor que o codigo da arvore, chama a funcao novamente, alterando o parametro, passando o valor a esquerda
        remove_recursivo(&((*p)->sube), cod);
    } else if (cod > (*p)->info.codigo) {  //Se o codigo for maior que o codigo da arvore, chama a funcao novamente, alterando o parametro, passando o valor a direita
        remove_recursivo(&((*p)->subd), cod);
    } else{     //A partir daqui o valor ja foi encontrado
            if ((*p)->sube == NULL && (*p)->subd == NULL){  //Se ele for uma folha (sem filhos), apenas remove ele
                temp = *p;
                (*p) = NULL;
            }else if ((*p)->sube == NULL){  //Se tiver um filho a direita, seu valor sera substituido por ele
                temp = *p;
                *p = (*p)->subd;
            }else if ((*p)->subd == NULL){  //Se tiver um filho a esquerda, seu valor sera substituido por ele
                temp = *p;
                *p = (*p)->sube;
            }else{  //A partir daqui o valor necessariamente tem 2 filhos
                ARVORE **auxiliar = &((*p)->subd);  //Criando uma variável auxiliar, é um ponteiro para o ponteiro que aponta para esse filho direito.
                while ((*auxiliar)->sube != NULL){  //Buscamos o menor valor a direita, esse valor ira substituir o valor que queremos remover
                    auxiliar = &((*auxiliar)->sube); //Recebe o proximo...
                }
                (*p)->info=(*auxiliar)->info;   //Valor a ser removido recebera o valor auxiliar (menor a direita)
                temp = *auxiliar;    //Variavel temporaria recebe esse valor da folha (sera removido)
                *auxiliar=(*auxiliar)->subd;    //Reconecta a subárvore direita do sucessor
            }
            free(temp); //Liberamos espaço de memória do nó removido
    }
    printf("\nRemoção feita com sucesso!\n");
} // desempilha




/****************************************************
 * calcula_altura                                   *
 * objetivo: rotina para calcular a altura da arvore*
 * entrada : ARVORE                                 *
 * saida   : ARVORE com campo altura atualizado     *
 ****************************************************/
void calcula_altura( ARVORE **r ){
	ARVORE *aux= *r;                            // ponteiro auxiliar para percorrer a arvore

    if( aux != NULL ){                          // verifica se a raiz e diferente de NULL
        aux->info.altura= altura_arvore( aux ); // verifica a altura do no
        aux->info.fatbal= ( altura_arvore( aux->subd ) + 1 ) - ( altura_arvore( aux->sube ) + 1 ); // calcula fator de balanceamento (fatbal) do no
        //printf("\n Cod:%i  A:%i  Fatbal:%i  \n", aux->info.codigo, aux->info.altura, fatbal);
   	    calcula_altura( &aux->subd );          // recursivo, segue pelo caminho da direita do no
        calcula_altura( &aux->sube );          // recursivo, segue pelo caminho da esquerda do no
    }
}


/****************************************************
 * verifica_balanceamento                           *
 * objetivo: rotina para calcular o balancemaneto   *
 * entrada : ARVORE                                 *
 * saida   : ARVORE balanceada                      *
 ****************************************************/
void verifica_balanceamento( ARVORE **r ){
	ARVORE *aux= *r;                                // cria ponteiro auxiliar para percorrer a arvore

    if( aux != NULL ){                              // verifica se ponteiro e diferente de NULL
		if( aux->info.fatbal >= 2 && ( aux->subd->info.fatbal != 2 && aux->subd->info.fatbal != -2 ) ){ // verifica fator de balanceamento no no pai e filho, se no pai for maior do que 1, a rotacao sera a esquerda
	        if( aux->subd->info.fatbal < 0 ){       // se sinal do fatbal do no filho for negativo, realiza rotacao dupla
	            rotacao_direita( &aux->subd );	    // rotacao esquerda - dupla
		        rotacao_esquerda( &aux );
			}else                                   // se sinal do fatbal do no filho for positivo, realiza rotacao simples
    			rotacao_esquerda( &aux );
	    }else
            if( aux->info.fatbal <= -2 && ( aux->sube->info.fatbal != 2 && aux->sube->info.fatbal != -2 ) ){ // verifica fator de balanceamento no no pai e filho, se no pai for menor do que 1, a rotacao sera a direita
		        if( aux->sube->info.fatbal > 0 ){   // se sinal do fatbal do no filho for positvo, realiza rotacao dupla
		            rotacao_esquerda( &aux->sube ); // rotacao direita - dupla
			        rotacao_direita( &aux );
				}else
	    			rotacao_direita( &aux );        // se sinal do fatbal do no filho for positivo, realiza rotacao simples
			}else{
					verifica_balanceamento( &aux->sube ); // continua verificando balanceamento a esquerda
					verifica_balanceamento( &aux->subd ); // continua verificando balanceamento a direita
			}
		calcula_altura( &aux );	                    // atualiza a altura dos nos da arvore apos rotacao
   }
   *r= aux;                                         // atualiza a raiz apos rotacao
}


/****************************************************
 * altura_arvore                                    *
 * objetivo: rotina para calcular a altura da arvore*
 * entrada : ARVORE                                 *
 * saida   : altura                                 *
 ****************************************************/
int altura_arvore( ARVORE *p ){
	 int altura_esq, altura_dir;
	 if( p == NULL  )                           // finaliza o percurso
	     return -1;
     else{
          altura_dir= altura_arvore( p->subd ); // percorre a direita
	 	  altura_esq= altura_arvore( p->sube ); // percorre a esquerda
          if( altura_dir > altura_esq )         // se altura da direita maior, soma mais um nivel a direita
              return altura_dir + 1;
          else                                  // se altura da esquerda maior, soma mais um nivel a esquerda
              return altura_esq + 1;
     }
}


/****************************************************
 * rotacao_direita                                  *
 * objetivo: rotina para rotacionar arvore          *
 * entrada : ARVORE                                 *
 * saida   : ARVORE rotacionada                     *
 ****************************************************/
void rotacao_direita( ARVORE **p ){
	 ARVORE *aux;
	 if( *p != NULL ){                            // percurso ate NULL
	 	  aux= (*p)->sube;                        // aponta a esquerda
		  (*p)->sube= aux->subd;                  // no filho a direita
		  aux->subd= *p;                          // raiz passa a ser no filho
		  *p= aux;                                // aux passa ser a nova raiz
     }
}



/****************************************************
 * rotacao_esquerda                                 *
 * objetivo: rotina para rotacionar arvore          *
 * entrada : ARVORE                                 *
 * saida   : ARVORE rotacionada                     *
 ****************************************************/
void rotacao_esquerda( ARVORE **p ){
	 ARVORE *aux;
	 if( *p != NULL ){                            // percurso ate NULL
	 	  aux= (*p)->subd;                        // ponteiro auxiliar e posicionado no no filho da direita
		  (*p)->subd= aux->sube;                  // ajusta apontamento, ponteiro direito pai aponta para ponteiro esquerdo do filho
		  aux->sube= *p;                          // ponteiro a esquerda no filho aponta para no pai
		  *p= aux;                                // reposiciona p
     }
}



/************************************************
 * salva_arvore                                 *
 * objetivo: salva a ARVORE em formato de txt   *
 * entrada : ARVORE                             *
 * saida   : txt com os dados da ARVORE         *
 ***********************************************/
void salva_arvore( ARVORE *r ){
    char nome_arquivo[30];
    FILE *arquivo;                             // declada o ponteiro para o arquivo

    if( r == NULL ){                           // verifica se a arvore esta vazia
        printf( "\n Nao e possivel salvar uma arvore vazia!" );
        getchar();                             // parada da tela
        return;
    }

    printf( "\n Nomeie o arquivo.: " );
    scanf( "%s", &nome_arquivo );
    strcat( nome_arquivo, ".txt" );            // define o arquivo como .txt, concatena .txt ao nome

    arquivo = fopen( nome_arquivo, "w" );      // abre o arquivo em modo de escrita
    if( arquivo == NULL ){                     // verifica se o arquivo foi criado corretamente
        printf( "\n Erro ao criar arquivo!" );
        getchar();                             // parada da tela
        return;
    }
    salva_codigo( r, arquivo );                // salva os codigos de maneira recursiva no txt

    fclose( arquivo );                         // fecha o arquivo
    printf( "\n Arvore salva com sucesso!" );
    getchar();                                 // parada da tela
}



/************************************************
 * salva_codigo                                 *
 * objetivo: salva o codigo atual no txt        *
 * entrada : ARVORE e arquivo.txt               *
 * saida   : codigo salvo no txt                *
 ***********************************************/
void salva_codigo( ARVORE *r, FILE *arquivo ){
    fprintf( arquivo, "%d\n", r->info.codigo );

    if( r->sube != NULL )                      // verifica se o caminho esquerdo esta vazio, se nao continua por ele
        salva_codigo( r->sube, arquivo );      // salva o valor que estiver no caminho esquerdo

    if( r->subd != NULL )                      // verifica se o caminho direito esta vazio, se nao continua por ele
        salva_codigo( r->subd, arquivo );      // salva o valor que estiver no caminho direito
}



/************************************************
 * carrega_arvore                               *
 * objetivo: carregar uma ARVORE existente      *
 * entrada : ARVORE                             *
 * saida  : ARVORE preenchida com dados         *
 ***********************************************/
void carrega_arvore( ARVORE **r ){
    char nome_arquivo[30];
    FILE *arquivo;                             // declada o ponteiro para o arquivo

    printf( "\n Informe o arquivo: " );
    scanf( "%s", &nome_arquivo );
    strcat( nome_arquivo, ".txt" );            // define o arquivo como .txt, concatena .txt ao nome

    arquivo = fopen( nome_arquivo, "r" );      // abre o arquivo em modo de leitura
    if ( arquivo == NULL ){                    // verifica se o arquivo foi aberto corretamente
        printf( "\n Arquivo nao encontrado!" );
        return;
    }

    cria_ARVORE( &(*r) );                      // cria uma nova ARVORE a fim de evitar conflitos
    int cod;
    while( fscanf( arquivo, "%d", &cod ) == 1 ){
        ARVORE *no = ( ARVORE * ) malloc ( sizeof( ARVORE )); // aloca novo espaco em memoria
        if( no != NULL ){                      // se conseguir alocar memoria, insere
                no->info.codigo = cod;         // preenche o novo registro com o codigo lido
                no->subd = NULL;
                no->sube = NULL;
                carrega_codigo( r, no );       // insere o codigo na arvore
        }
    }

    fclose( arquivo );                         // fecha o arquivo
    printf( "\n Lista carregada com sucesso!" );
    getchar();                                 // parada da tela
}



/************************************************
 * carrega_codigo                               *
 * objetivo: carregar uma codigo para a ARVORE  *
 * entrada : ARVORE e no com o codigo           *
 * saida   : ARVORE com o novo no               *
 ***********************************************/
void carrega_codigo( ARVORE **r, ARVORE *no){
    if( *r == NULL){                          // verifica se o no esta vazio
        *r = no;                              // se sim, preenche o no
        return;
    }

    if ( no->info.codigo > (*r)->info.codigo) // verifica se o codigo carregado e maior que o atual no
        carrega_codigo( &(*r)->subd, no);     // se sim, segue a direita desse no
    else
        carrega_codigo( &(*r)->sube, no);     // se nao, segue a esquerda desse no
}
