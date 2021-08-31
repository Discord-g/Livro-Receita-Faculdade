#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

struct Livro
{
	char receita[30];
	char tempo[20];
	char ingredientes[500];
	char modo[500];
	char nomem[30];
	int nota;
	int feito; 
	
	struct Livro *next;
	struct Livro *back;
};

typedef struct Livro Livro;

void ordenar(Livro **Primeiro, Livro **NovaReceita, Livro **ReceitaAtual)
{
	int Cont = 0;
	Livro *aux = *Primeiro;
	
	if(*Primeiro == NULL)
	{
		(*NovaReceita)->back = *NovaReceita;
		(*NovaReceita)->next = *NovaReceita;
		
		*ReceitaAtual = *NovaReceita;
		*Primeiro = *NovaReceita;
	}
	else if((*Primeiro)->next == *Primeiro)
	{
		(*NovaReceita)->next = *Primeiro;
		(*NovaReceita)->back = *Primeiro;
		(*Primeiro)->next = *NovaReceita;
		(*Primeiro)->back = *NovaReceita;
		
		if(strcmp((*Primeiro)->receita, (*NovaReceita)->receita)>0)
		{
			*Primeiro = *NovaReceita;
		}
	}
	else
	{
		while(strcmp(aux->receita, (*NovaReceita)->receita)<=0)
		{
			aux = aux->next;
			Cont++;
			if(aux == *Primeiro)
			{
				break;
			}
		}
		
		aux->back->next = *NovaReceita;
		(*NovaReceita)->back = aux->back;
		aux->back = *NovaReceita;
		(*NovaReceita)->next = aux;
		
		if(Cont == 0)
		{
			*Primeiro = *NovaReceita;
		}
	}
}

void LerArquivo(FILE *Arquivo, Livro **LivroAtual, Livro **Primeiro, int *Contador)
{
	int I;
	char select;
	Livro *Aux;
	int Cont = 0;
	
	Arquivo = fopen("Livro", "rb");
	
	if(Arquivo == NULL)
	{
		return;
	}
	
	*Contador = fgetc(Arquivo);
	
	while(!feof(Arquivo) && Cont < (*Contador))
	{
		Aux = malloc(sizeof(Livro));
		fread(Aux, sizeof(struct Livro), 1, Arquivo);
		
		ordenar(Primeiro, &Aux, LivroAtual);
		Cont++;
	}
	fclose(Arquivo);
}

void SalvaArquivo(FILE *Arquivo, Livro **Primeiro, int *Contador)
{
	Livro *Aux;
	
	Aux = *Primeiro;
	
	if(*Primeiro != NULL)
	{
		Arquivo = fopen("Livro", "wb");
		
		if(Arquivo == NULL)
		{
			return;
		}

		fputc((*Contador), Arquivo);
		
		do
		{
			fwrite(Aux, sizeof(struct Livro), 1, Arquivo);
			Aux = Aux->next;
		}while(Aux != *Primeiro);
	
		fclose(Arquivo);
	}
}

void alterar(Livro **ReceitaAtual, Livro **Primeiro)
{
	char Op;
	system("cls");
	fflush(stdin);
	
	if(*ReceitaAtual != NULL)
	{
		Livro *aux = *ReceitaAtual;
		printf("Alteração da receita %s\n\n", (*ReceitaAtual)->receita);
		printf("\n Alterar o Tempo de preparo? (S/N)\n");
		Op = getch();
		if(Op == 'S')
		{
			printf(" >> ");
			gets(aux->tempo);
		}
	
		printf("\n Alterar os Ingredientes? (S/N)\n");
		Op = getch();
		if(Op == 'S')
		{
			printf(" >> ");
			fflush(stdin);
			gets(aux->ingredientes);
		}
	
		printf("\n Alterar o Modo de preparo? (S/N)\n");
		Op = getch();
		if(Op == 'S')
		{
			printf(" >> ");
			gets(aux->modo);
		}
	
		printf("\n Alterar o Nome do criador? (S/N)\n");
		Op = getch();
		if(Op == 'S')
		{
			printf(" >> ");
			gets(aux->nomem);
		}
	
		printf("\n Alterar a Nota de 0 à 10? (S/N)\n");
		Op = getch();
		if(Op == 'S')
		{
			printf(" >> ");
			scanf("%d", &aux->nota);
		}
		
		if((*ReceitaAtual) == *Primeiro)
		{
			*Primeiro = aux;
		}
		*ReceitaAtual = aux;
	}
}

void apagar(Livro **ReceitaAtual, Livro **Primeiro, int *Contador)
{
	Livro *aux;
	system("cls");
	
	if((*ReceitaAtual) == NULL)
	{
		printf("Não tem receita para apagar.");
		getch();
	}
	else if((*ReceitaAtual)->next == *ReceitaAtual)
	{
		free(*ReceitaAtual);
		*ReceitaAtual = NULL;
		*Primeiro = NULL;
		*Contador = (*Contador) - 1;	
	}
	else
	{
		if(*ReceitaAtual == *Primeiro)
		{
			aux = (*ReceitaAtual)->next;
			(*ReceitaAtual)->back->next = aux;
			aux->back = (*ReceitaAtual)->back;
			free(*ReceitaAtual);
			*ReceitaAtual = aux;
			*Primeiro = aux;
		}
		else
		{
			aux = (*ReceitaAtual)->next;
			(*ReceitaAtual)->back->next = aux;
			aux->back = (*ReceitaAtual)->back;
			free(*ReceitaAtual);
			*ReceitaAtual = aux;
		}
		*Contador = (*Contador) - 1;
	}
}

void nova_receita(Livro **ReceitaAtual, Livro **Primeiro, int *Contador)
{
	system("cls");
	fflush(stdin);
	Livro *novaReceita = NULL;
	novaReceita = malloc(sizeof(Livro));
	
	printf("\n Nome da Receita: ");
	gets(novaReceita->receita);
	
	printf("\n Tempo de preparo : ");
	gets(novaReceita->tempo);
	
	printf("\n Ingredientes: ");
	gets(novaReceita->ingredientes);
	
	printf("\n Modo de preparo: ");
	gets(novaReceita->modo);
	
	printf("\n Nome do criador: ");
	gets(novaReceita->nomem);
	
	printf("\n Nota de 0 à 10: ");
	scanf("%d", &(novaReceita->nota));
	if(novaReceita->nota >10)
	{
		novaReceita->nota = 10;
	}
	if(novaReceita->nota < 0)
	{
		novaReceita->nota = 0;
	}

	novaReceita->feito = 0;
	
	*Contador = (*Contador) + 1;

	ordenar(Primeiro, &novaReceita, ReceitaAtual);
}

void navegar(int direcao, Livro **ReceitaAtual)
{
	if(*ReceitaAtual != NULL)
	{
		if(direcao == 1)
		{
			*ReceitaAtual = (*ReceitaAtual)->back;
		}
		else if(direcao == 2)
		{
			*ReceitaAtual = (*ReceitaAtual)->next;
		}
	}
}

void Adiciona(Livro **ReceitaAtual)
{
	if(*ReceitaAtual != NULL)
	{
		(*ReceitaAtual)->feito = ((*ReceitaAtual)->feito)+1;
	}
}

int menu(char select, Livro *ReceitaAtual)
{
	system("cls");
	fflush(stdin);
	printf(" LIVRO DE  RECEITAS ");
	printf("\n\n Opcões: ");
	printf("\n < > - Navegar.");
	printf("\n a - Alterar.");
	printf("\n * - Marcar como usada.");
	printf("\n ! - Apagar receita.");
	printf("\n + - Inserir receita.");
	printf("\n S - Sair do livro de receitas.");
	
	if(ReceitaAtual == NULL)
	{
		printf("\n\n Nenhuma receita escrita.");
	}
	else
	{
		printf("\n\n Receita: %s", ReceitaAtual->receita);
		printf("\n\n Tempo de preparo: %s", ReceitaAtual->tempo);
		printf("\n\n Ingredientes: %s", ReceitaAtual->ingredientes);
		printf("\n\n Modo de Preparo: %s", ReceitaAtual->modo);
		printf("\n\n Nome do Criador: %s", ReceitaAtual->nomem);
		printf("\n\n Nota da Receita: %d/10", ReceitaAtual->nota);
		printf("\n\n Vezes de preparo: %d", ReceitaAtual->feito);
	}
	
	printf("\n\n ");	
	select = getch();
	
	return (select);
}

int main() 
{
	FILE *Arquivo;
	setlocale(LC_ALL, "Portuguese");
	char select;
	int Contador = 0;
	
	Livro *Primeiro = NULL;
	Livro *ReceitaAtual = NULL;
	
	LerArquivo(Arquivo, &ReceitaAtual, &Primeiro, &Contador);
	
	do
	{		
		select = menu(select, ReceitaAtual);
		
		switch(select)
		{
			case '<':
			navegar(1, &ReceitaAtual);
			break;
				
			case '>':	
			navegar(2, &ReceitaAtual);
			break;
			
			case '+':
			nova_receita(&ReceitaAtual, &Primeiro, &Contador);
			break;
			
			case '*':
			Adiciona(&ReceitaAtual);	
			break;
			
			case '!':
			apagar(&ReceitaAtual, &Primeiro, &Contador);
			break;
			
			case 'a':
			alterar(&ReceitaAtual, &Primeiro);
			break;
		}
		
		
	}
	while(select != 'S');
	
	SalvaArquivo(Arquivo, &Primeiro, &Contador);

	return 0;
}



