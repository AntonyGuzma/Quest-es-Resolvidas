#include<stdio.h>
#include<stdlib.h>

/* Autores: Antony Gusmão, Mikael Hayden, Walter Jonas*/

struct no
{
	int info;
	char cor;	//B = Negro, R = Rubro
	struct no *esq, *dir, *Pai;
};


void RotacaoEsquerda(struct no **Raiz, struct no *x)
{
	struct no *y = x->dir;

	x->dir = y->esq;

	if (x->dir != NULL)
	{
		x->dir->Pai = x;
	}

	y->Pai = x->Pai;

	if (x->Pai == NULL)
	{
		(*Raiz) = y;
	}
		
	else if (x == x->Pai->esq)
	{
		x->Pai->esq = y;
	}
		
	else
	{
		x->Pai->dir = y;
	}

	y->esq = x;

	x->Pai = y;
}

void RotacaoDireita(struct no **Raiz, struct no *y)
{
	struct no *x = y->esq;
	y->esq = x->dir;
	
	if (x->dir != NULL)
	{
		x->dir->Pai = y;
	}
		
	x->Pai = y->Pai;
	
	if (x->Pai == NULL)
	{
		(*Raiz) = x;
	}
		
	else if (y == y->Pai->esq)
	{
		y->Pai->esq = x;
	}
		
	else
	{
		y->Pai->dir = x;
	}
		
	x->dir = y;
	y->Pai = x;
}

void balanceamento(struct no **Raiz, struct no *z) 
{
	while (z != *Raiz && z->Pai->cor == 'R')
	{
		struct no *y;

		// Find uncle and store uncle in y
		if (z->Pai == z->Pai->Pai->esq) //Se o pai do No For um filho a esquerda 
			y = z->Pai->Pai->dir;	
		else
			y = z->Pai->Pai->esq;

		if (y != NULL)
		{
			if (y->cor == 'R')
			{
				y->cor = 'B';
				z->Pai->cor = 'B';
				z->Pai->Pai->cor = 'R';
				z = z->Pai->Pai;
			}
			else
			{
				return;
			}
		}

		else
		{
			if (z->Pai == z->Pai->Pai->esq && z == z->Pai->esq)
			{
				char ch = z->Pai->cor;
				z->Pai->cor = z->Pai->Pai->cor;
				z->Pai->Pai->cor = ch;
				RotacaoDireita(Raiz, z->Pai->Pai);
			}

			else if (z->Pai == z->Pai->Pai->esq && z == z->Pai->dir)
			{
				char ch = z->cor;
				z->cor = z->Pai->Pai->cor;
				z->Pai->Pai->cor = ch;
				RotacaoEsquerda(Raiz, z->Pai);
				RotacaoDireita(Raiz, z->Pai);
			}

			else if (z->Pai == z->Pai->Pai->dir && z == z->Pai->dir)
			{
				char ch = z->Pai->cor;
				z->Pai->cor = z->Pai->Pai->cor;
				z->Pai->Pai->cor = ch;
				RotacaoEsquerda(Raiz, z->Pai->Pai);
			}

			else if (z->Pai == z->Pai->Pai->dir && z == z->Pai->esq)
			{
				char ch = z->cor;
				z->cor = z->Pai->Pai->cor;
				z->Pai->Pai->cor = ch;
				RotacaoDireita(Raiz, z->Pai);
				RotacaoEsquerda(Raiz, z->Pai);
			}
		}
	}
	
	(*Raiz)->cor = 'B';
}

//Função pra inserir NO na Arvore Rubro Negra
void insere(struct no **Raiz, int valor) {	
	struct no *z = (struct no*) malloc(sizeof(struct no));	//alocaçao pro novo ponteiro 
	z->info = valor;
	z->esq = NULL;
	z->dir = NULL;
	z->Pai = NULL;

	if (*Raiz == NULL)
	{	//se a raiz for nula, o novo ponteiro inserido passa a ser a raiz
		z->cor = 'B';	//cor da raiz é preta
		(*Raiz) = z;	//raiz passa a ser o no Z
	}
	 
	else 
	{
		struct no *y = NULL;
		struct no *x = (*Raiz);

		while (x != NULL) 
		{	//Verifica a localização do novo no a ser inserido 
			y = x;
			if((z->info) == (x->info)){
				printf("Valor ja Existe! \n");
				return ;
			}else
			if ((z->info) < (x->info)){ //Se o Novo no Inserido for menor que o no ja existente na arvore 
				x = x->esq;	//verifica com o No a esquerda
			}else 	//Se o Novo no Inserido for maior que o no ja existente na arvore
				x = x->dir; //Verifica com o No a Direita
		}
		
		z->Pai = y;	//Define o Pai do Novo No Inserido
		if (z->info > y->info)
			y->dir = z;
		else
			y->esq = z;
		z->cor = 'R';

		balanceamento(Raiz, z);
	}
}

void Preordem(struct no **Raiz) 
{
	if (*Raiz == NULL)
	{
		return;
	}
	
	else
	{
		printf(" %d(%c) ", (*Raiz)->info, (*Raiz)->cor);
		Preordem(&(*Raiz)->esq);
		Preordem(&(*Raiz)->dir);
	}
}

void visualizar_arvore(struct no **Raiz, int nivel) //Função para vizualizar os nós da arvore
{
    int i;
    if(*Raiz)
	{
        visualizar_arvore(&(*Raiz)->dir, nivel + 1);
        printf("\n\n");

       	for(i = 0; i < nivel; i++)
       	{
       		printf("\t");
    	}
       	
       	printf(" %d(%c) ", (*Raiz)->info, (*Raiz)->cor);
       	visualizar_arvore(&(*Raiz)->esq, nivel + 1);
    }
}

int main()
{
	struct no *raiz = NULL;
	int op, valor;
	
	do{
		printf("\n- - - - - - -MENU- - - - - -\n");
		printf("| 1 - Inserir\n| 2 - Visualizar\n| 3 - Visualizar Pre Ordem\n| 0 - Sair\n|- - - - - - - - - - - - - - \n");
		printf("Escolha Uma Opcao: \n");
		scanf("%d", &op);
		system("cls");
		switch (op){
			case 1:
				printf("valor a ser inserido: ");
				scanf("%d", &valor);
				system("cls");
				insere(&raiz, valor);
				break;
				
			case 2:
				printf("\n\nEstrutura Arvore Rubro Negra");
				visualizar_arvore(&raiz, 0);
				printf("\n\n");
				break;
				
			case 3:
				printf("\n\nPre ordem \n\n"); 
				Preordem(&raiz);
		}
		

	}while(op != 0);

	return 0;
}


