#include <stdio.h>
#include <stdlib.h>

/* Autores: Antony Gusmão, Mikael Hayden, Walter Jonas*/

typedef struct no
{
    int valor;	//variavel que vai receber o valor a ser inserido na arvore
    struct no *esq, *dir; //struct no a esquerda e a direita
    int altura_no;	//variavel que vai armazenar as alturas das subarvores
}No;

No* novoNo(int valor) //Função que cria um novo nó e insere o valor recebido como parameto
{
    No *novo = malloc(sizeof(No)); //alocação dinamica para o novo NO 
    if(novo == NULL)
	{
       	printf("\nERRO ao alocar!\n");
    }
    else
    {
    	novo->valor = valor; //Insere valor x no novo nó criado
        novo->esq = NULL; //esq aponta para NULL
        novo->dir = NULL; //dir aponta para NULL
        novo->altura_no = 0; //Inicializa a altura das subarvores      
    }
    return novo;
}

int maiorAltura(int a, int b) //Retorna o maior entre dois valores a, b -> altura de dois nós da árvore
{
	if(a<b)
	{
		return b;
	}
	else
	{
		return a;
	}
}

int alturaNo(No *no) //Retorna a altura de um nó ou -1 caso ele seja null
{
    if(no == NULL)
    {
    	return -1;  	
    }   	
    else
    {
    	return no->altura_no;
    }
}

//Rotações
//Função para a rotação à esquerda
No* rotacaoEsquerda(No *r)
{
    No *y, *f; //Cria o ponteiro y e o ponteiro f

    y = r->dir; //O ponteiro y recebe o valor que a raiz tá apontando a sua direita
    f = y->esq; //O ponteiro f recebe o valor que o y tá apontando a sua esquerda

    y->esq = r; //O y seta esquerda recebe a raiz atual
    r->dir = f; //A raiz seta direita recebe o f, com isso a rotação já foi feita

	//Raliza o calulo da altura de y e r que foram rotacionados
    r->altura_no = maiorAltura(alturaNo(r->esq), alturaNo(r->dir)) + 1;
    y->altura_no = maiorAltura(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y; //retorna a nova raiz
}

//Função para a rotação à direita
No* rotacaoDireita(No *r)
{
    No *y, *f;

    y = r->esq; //O ponteiro y recebe o valor que a raiz tá apontando a sua esquerda
    f = y->dir; //O ponteiro f recebe o valor que o y tá apontando a sua direita

    y->dir = r; //O y seta direita recebe a raiz atual
    r->esq = f; //A raiz seta esquerda recebe o f, com isso a rotação já foi feita
	
	//Raliza o calulo da altura de y e r que foram rotacionados
    r->altura_no = maiorAltura(alturaNo(r->esq), alturaNo(r->dir)) + 1;
    y->altura_no = maiorAltura(alturaNo(y->esq), alturaNo(y->dir)) + 1;

    return y; //retorna a nova raiz
}

//Função de Rotação dupla - Esquerda e Direita
No* rotacaoEsquerdaDireita(No *r)
{
    r->esq = rotacaoEsquerda(r->esq);	//Pega o NO ao lado esquerdo da raiz e realiza a rotação a esquerda chamando a propria função o de rotação a esquerda,
    return rotacaoDireita(r);			// e depois retorna realizando uma rotação a direita na raiz chamando a funçao de rotacionar a direita
}

//Função de Rotação dupla - Esquerda e Direita
No* rotacaoDireitaEsquerda(No *r)
{
    r->dir = rotacaoDireita(r->dir);	//pega o NO a direita da raiz e raliza a rotação a direita chamando a propria função o de rotação a direita,
    return rotacaoEsquerda(r);			// e depois retorna realizando uma rotação a esquerda na raiz chamando a funçao de rotacionar a esquerda
}

/* Função para realizar o balanceamento da árvore após uma inserção ou remoção, 
recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento   
*/
No* balancear(No *raiz) 
{
    int fb = fatorBalanceamento(raiz); 
   
    if(fb > 1 && fatorBalanceamento(raiz->esq) >= 0) //Rotação a direita
    {
    	raiz = rotacaoDireita(raiz);
    }
    
    else if(fb < -1 && fatorBalanceamento(raiz->dir) <= 0) //Rotação a esquerda
    {
    	raiz = rotacaoEsquerda(raiz);
    }
   	 
    else if(fb < -1 && fatorBalanceamento(raiz->dir) > 0) //Rotação dupla a direita
    {
    	raiz = rotacaoDireitaEsquerda(raiz);
    }   
    
    else if(fb > 1 && fatorBalanceamento(raiz->esq) < 0) //Rotação dupla a esquerda
    {
    	raiz = rotacaoEsquerdaDireita(raiz);
    }   
    return raiz;
}

No* insercao(No *raiz, int valor) /*Função que insere um novo nó na arvore
	Parametros:  
	raiz -> raiz da arvore
    valor -> valor a ser inserido 	*/
{
    if(raiz != NULL) 
    {
    	//Inserção será à esquerda ou à direita
    	if(valor < raiz->valor)
    	{
    		raiz->esq = insercao(raiz->esq, valor);
    	}           
        else if(valor > raiz->valor)
        {
        	raiz->dir = insercao(raiz->dir, valor);
        }         
        else
        {
        	printf("\nInsercao nao realizada!\nO elemento %d ja existe!\n", valor);	
        }  	
	}
    else //arvore vazia
	{ 
      	return novoNo(valor);
    }

    //Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura_no = maiorAltura(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;

    //Verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);
    return raiz; //nova raiz após o balanceamento
}

int fatorBalanceamento(No *no) 
{
    if(no == NULL)
    {
		return 0;
    	 
    }       
    else
    {
    	return (alturaNo(no->esq) - alturaNo(no->dir)); //Calcula e retorna o fator de balanceamento de um nó
    }
}

No* remocao(No *raiz, int valor) //Função para remover um nó da Árvore binária balanceada
{
    if(raiz != NULL) //Procura o nó a remover
	{
		if(raiz->valor == valor)
		{        
        	if(raiz->esq == NULL && raiz->dir == NULL) //remove nós folhas
			{
                free(raiz);
                printf("Elemento removido!\n");
                return NULL;
            }
            else
			{          
                if(raiz->esq != NULL && raiz->dir != NULL) //remover nós que possuem 2 filhos
				{
                    No *aux = raiz->esq;
                    while(aux->dir != NULL)
                    {
                    	aux = aux->dir;
                    }                        
                   	raiz->valor = aux->valor;
                    aux->valor = valor;
                    //printf("Elemento trocado: %d !\n", valor);
                    raiz->esq = remocao(raiz->esq, valor);
                    return raiz;
                }
                else
				{
                    //remover nós que possuem apenas 1 filho
                    No *aux;
                    if(raiz->esq != NULL)
                    {
                    	aux = raiz->esq;
                    }                       
                    else
                    {
                    	aux = raiz->dir;
                    }                     
                    free(raiz);
                    printf("Elemento removido!\n");
                    return aux;
                }
            }
        } 
		else 
		{
            if(valor > raiz->valor)
            {
            	raiz->dir = remocao(raiz->dir, valor); //Recursividade
            }
            else
            {
                raiz->esq = remocao(raiz->esq, valor); //Recursividade
            }
        }
        
        //Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
        //Função que recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura_no = maiorAltura(alturaNo(raiz->esq), alturaNo(raiz->dir)) + 1;        
        raiz = balancear(raiz); //Verifica a necessidade de rebalancear a árvore
        return raiz; //Retornamos a raiz       
    } 
	else 
	{ 
        printf("Valor nao existe na arvore!\n");
        return NULL;
    }
}

void visualizar_arvore(No *raiz, int nivel) //Função para vizualizar os nós da arvore
{
    int i;
    if(raiz)
	{
        visualizar_arvore(raiz->dir, nivel + 1);
        printf("\n\n");

       	for(i = 0; i < nivel; i++)
       	{
       		printf("\t");
       	}
       	
        printf("[%d]", raiz->valor);
        visualizar_arvore(raiz->esq, nivel + 1);
    }
}

int main()
{
    int op = 1 , valor;
    No *raiz = NULL;
    while(op != 0)
	{
    	printf("\n\n|--------------MENU-------------|");
        printf("\n|\t\t\t\t|\n|\t0 - Sair\t\t|\n|\t1 - Inserir\t\t|\n|\t2 - Remover\t\t|\n|\t3 - Imprimir\t\t|\n|\t\t\t\t|\n|\t\t\t\t|\n|-------------------------------|\n");
        scanf("%d", &op);
		system("cls"); //serve para limpar tela
        if(op == 0)
		{
            exit(0);
        }
        else if(op == 1)
        {
            printf("\tDigite o valor a ser inserido: ");
            scanf("%d", &valor);
            raiz = insercao(raiz, valor);
        }
        else if(op == 2)
        {
            printf("\tDigite o valor a ser removido: ");
            scanf("%d", &valor);
            raiz = remocao(raiz, valor);
        }
        else if(op == 3)
        {
            visualizar_arvore(raiz, 1);
        }
        else
        {
            printf("\nOpcao invalida!\n");
        }
    }
    return 0;
}