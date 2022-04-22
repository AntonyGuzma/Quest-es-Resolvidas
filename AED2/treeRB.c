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
	struct no *y = x->dir;	//Aux que recebe o No a Direita

	x->dir = y->esq;	//X recebe o filho esquerdo de Y

	if (x->dir != NULL)	//Se filho esquerdo de Y existe
	{
		x->dir->Pai = x; //O pai passa a ser o X 
	}

	y->Pai = x->Pai; //Y recebe o pai de X

	if (x->Pai == NULL)//Se o pai for null entao a Raiz passa a ser Y
	{	
		(*Raiz) = y;
	}
		
	else if (x == x->Pai->esq)	//No Rotacionado é Filho a esquerda
	{
		x->Pai->esq = y;	
	}
		
	else	////No Rotacionado é Filho a Direita
	{
		x->Pai->dir = y;
	}

	y->esq = x;	//Y passa a ser pai de X

	x->Pai = y;	//X passa  a ser filho de Y
}

void RotacaoDireita(struct no **Raiz, struct no *y)
{
	struct no *x = y->esq;	//Aux que recebe o No a Direita
	y->esq = x->dir;		
	
	if (x->dir != NULL)
	{
		x->dir->Pai = y;
	}
	
	x->Pai = y->Pai; //X recebe o pai de Y
	
	if (x->Pai == NULL)	//Se o pai for null entao a Raiz passa a ser X
	{
		(*Raiz) = x;
	}
		
	else if (y == y->Pai->esq) //Se Y for filho a esquerda 
	{
		y->Pai->esq = x;//O Novo filho a esquerda passa a ser X
	}
		
	else	//Se Y for filho a direita
	{
		y->Pai->dir = x;	//O Novo filho a direita passa a ser X
	}
		
	x->dir = y;	//X passa a ser pai de Y
	y->Pai = x;	//Y passa a ser filho de X
}

void balanceamento(struct no **Raiz, struct no *z) 
{
	while (z != *Raiz && z->Pai->cor == 'R')
	{
		struct no *y;

		// Find uncle and store uncle in y
		if (z->Pai == z->Pai->Pai->esq) //Se o pai do No For um filho a esquerda 
			y = z->Pai->Pai->dir;	
		else							//Se o pai do No For um filho a direita
			y = z->Pai->Pai->esq;

		if (y != NULL)	//Se tio Existe
		{
			if (y->cor == 'R')	//Se tio é Rubro
			{
				y->cor = 'B';	//Tio Fica Negro
				z->Pai->cor = 'B';	//Pai Fica Negro
				z->Pai->Pai->cor = 'R';	//Avo Fica Rubro
				z = z->Pai->Pai;	//Z passa a ser o avo 
			}
			else
			{
				return;
			}
		}

		else
		{
			if (z->Pai == z->Pai->Pai->esq && z == z->Pai->esq)	//Tiver alinhado a Esquerda
			{
				char ch = z->Pai->cor;	//Salva a Cor do Pai
				z->Pai->cor = z->Pai->Pai->cor;	// Pai recebe cor do Avo
				z->Pai->Pai->cor = ch;	// e Avo Recebe Cor do Pai
				RotacaoDireita(Raiz, z->Pai->Pai);	//Realiza a rotação a direita
			}

			else if (z->Pai == z->Pai->Pai->esq && z == z->Pai->dir)	//Tiver Pai a Esquerda e Avo a Direita
			{
				char ch = z->cor;	//Salva a Cor do Filho
				z->cor = z->Pai->Pai->cor;	//Filho Recebe a cor do Avo
				z->Pai->Pai->cor = ch;	//Avo Recebe a Cor de Filho
				RotacaoEsquerda(Raiz, z->Pai);	//Realiza a Rotaçaõ Dupla a Direita
				RotacaoDireita(Raiz, z->Pai);
			}

			else if (z->Pai == z->Pai->Pai->dir && z == z->Pai->dir)	//Tiver alinhado a Direita
			{
				char ch = z->Pai->cor;	//Salva a Cor do Pai
				z->Pai->cor = z->Pai->Pai->cor;	// Pai recebe cor do Avo
				z->Pai->Pai->cor = ch;	// e Avo Recebe Cor do Pai
				RotacaoEsquerda(Raiz, z->Pai->Pai);	// Realiza a rotação a esquerda
			}

			else if (z->Pai == z->Pai->Pai->dir && z == z->Pai->esq)	//Tiver Pai a Direita e Avo a Esquerda
			{
				char ch = z->cor;	//Salva a Cor do Filho
				z->cor = z->Pai->Pai->cor; //Filho Recebe a cor do Avo
				z->Pai->Pai->cor = ch;	//Avo Recebe a Cor de Filho
				RotacaoDireita(Raiz, z->Pai);	//Realiza a Rotação dupla a Esquerda
				RotacaoEsquerda(Raiz, z->Pai);	
			}
		}
	}
	
	(*Raiz)->cor = 'B';	//Faz a Raiz se Negra no Final de Tudo
}

//Função pra inserir NO na Arvore Rubro Negra
void insere(struct no **Raiz, int valor) {	
	struct no *z = (struct no*) malloc(sizeof(struct no));	//alocaçao pro novo No
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
			y = x;	//Guarda a posição do pai do novo NO
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

