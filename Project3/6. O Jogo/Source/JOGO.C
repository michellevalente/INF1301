/***************************************************************************
*  $MCI Módulo de implementação: JOGO Módulo Jogo
*
*  Arquivo gerado:          	JOGO.c
*  Letras identificadoras:  	DEF
*
*  Projeto: Trabalho 3 - Programação Modular
*  Autores: GB - Gustavo Bach
*       	JG - João Lucas Gardenberg
*       	MV - Michelle Valente
*
*  $HA Histórico de evolução:
*  	Versão   Autor  	Data      	Observações
*  	1.00 	GB,JG,MV   14/05/2014   início desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include "DESENHO.h"

/***** Variáveis encapsuladas no módulo *****/

	static ptDesenho pDesenho = NULL ;
	static DES_tpCondRet CondRetDES ;

/***************************************************************************
*
*  Função: JOGO  Posicao Valida
*  ****/

int PosicaoValida(int AlturaMatriz, int LarguraMatriz, int Linha, int Coluna)
{
	if( Linha > AlturaMatriz )
		return 1;
	else if( Coluna > LarguraMatriz )
		return 1;
	else if ( Linha <= 0 || Coluna <= 0)
		return 1;
	else
		return 0;
}

/***************************************************************************
*
*  Função: JOGO  Projeto
*  ****/

void Projeto(void){

	int Altura = 0, Largura = 0, Linha = 0, Coluna = 0, TestaValidez = -1, TestaFim = -1 ;
	char NomeArq[65] ;

	printf("Digite o tamanho do tabuleiro do seu nanograma.\nAltura => ");
	scanf("%d", &Altura);
	printf("Largura => ");
	scanf("%d", &Largura);
	printf("\n");

	if( Altura <= 0 || Largura <= 0 )
	{
		system("cls");
		printf("Valores invalidos para altura e/ou largura.\n");
		return Projeto();
	}

	CondRetDES = DES_GerarMatrizes( &pDesenho, Altura, Largura ) ;

	system("cls");
	CondRetDES = DES_DesenharCorreto(pDesenho);
	while( TestaValidez != 0 )
	{
		printf("Digite as coordenadas do quadrado a ser modificado. \nLinha => ");
		scanf("%d", &Linha );
		printf("Coluna => ");
		scanf("%d", &Coluna);
		printf("\n");
		TestaValidez = PosicaoValida(Altura, Largura, Linha, Coluna) ;
		if(TestaValidez == 1)
		{
			system("cls");
			CondRetDES = DES_DesenharCorreto(pDesenho);
			printf("Valor invalido de linha e/ou coluna.\n");
		}
	}

	CondRetDES = DES_AlterarEstadoCorreto(pDesenho,Linha,Coluna) ;
	system("cls");
	CondRetDES = DES_DesenharCorreto(pDesenho);
	while(TestaFim != 0 && TestaFim != 1)
	{
		printf("Digite uma das opcoes a seguir:\n (0) - Terminar o projeto.\n (1) - Modificar mais quadrados. \n => ");
		scanf("%d", &TestaFim);
		if(TestaFim!= 0 && TestaFim != 1)
		{
			system("cls");
			CondRetDES = DES_DesenharCorreto(pDesenho);
			printf("Opcao invalida!\n");
		}
	}

	while( TestaFim != 0 )
	{
		TestaValidez = 1 ;
		system("cls");
		CondRetDES = DES_DesenharCorreto(pDesenho);
		while( TestaValidez != 0 )
		{
			printf("Digite as coordenadas do quadrado. \nLinha => ");
			scanf("%d", &Linha );
			printf("Coluna => ");
			scanf("%d", &Coluna);
			printf("\n");
			TestaValidez = PosicaoValida(Altura, Largura, Linha, Coluna) ;
			if(TestaValidez == 1)
			{
				system("cls");
				CondRetDES = DES_DesenharCorreto(pDesenho);
				printf("Valor invalido de linha e/ou coluna, quadrado nao foi computado.\n");
			}
		}

		CondRetDES = DES_AlterarEstadoCorreto(pDesenho,Linha,Coluna) ;
		
		TestaFim = 2;
		system("cls");
		CondRetDES = DES_DesenharCorreto(pDesenho);
		while(TestaFim != 0 && TestaFim != 1)
		{
			printf("Digite uma das opcoes a seguir:\n (0) - Terminar o projeto.\n (1) - Modificar mais quadrados. \n => ");
			scanf("%d", &TestaFim);
			if(TestaFim!= 0 && TestaFim != 1)
			{
				system("cls");
				CondRetDES = DES_DesenharCorreto(pDesenho);
				printf("Opcao invalida!\n");
			}
		}
	}
	
	system("cls");
	CondRetDES = DES_DesenharCorreto(pDesenho);
	while(TestaFim != 1 && TestaFim != 2 && TestaFim != 3)
	{
		printf("Digite uma das opcoes a seguir:\n (1) - Salvar o projeto.\n (2) - Recomecar o projeto do zero. \n (3) - Sair.\n => ");
		scanf("%d", &TestaFim);
		if( TestaFim == 2)
		{
			system("cls");
			return Projeto();
		}
		else if(TestaFim == 1)
		{
			system("cls");
			CondRetDES = DES_DesenharCorreto(pDesenho);
			printf("Nome do arquivo para salvar o jogo (maximo de 64 caracteres, sem espacos)\n=> ");
			scanf(" %64[^\n]", NomeArq);
			if(NomeArq == NULL)
			{
				TestaFim = 0;
				system("cls");
				printf("O projeto nao foi salvo, pois nao foi digitado o nome do arquivo.\n");
			}
			else if(strstr(NomeArq, " "))
			{
				TestaFim = 0;
				system("cls");
				printf("O projeto nao foi salvo, pois o nome digitado continha espacos.\n");
			}
				TestaValidez = Salva(pDesenho,NomeArq,Altura,Largura, 0);
		}else if(TestaFim == 3)
			exit(1);
		else {
			system("cls");
			CondRetDES = DES_DesenharCorreto(pDesenho);
			printf("Opcao invalida!\n");
		}
	}
} /* Fim da função Projeto */

/***************************************************************************
*
*  Função: JOGO  Salva
*  ****/

int Salva(ptDesenho pDesenho, char * NomeArq, int Altura, int Largura, int NumHint){
	int IteradorLinha, IteradorColuna ;
	int Estado ;
	FILE* arq = fopen(strcat(NomeArq, ".txt"), "w") ;
	if(arq == NULL)
	{
		return 0;
	}
	fprintf(arq,"%d %d \n", Altura, Largura);

	for(IteradorLinha = 1; IteradorLinha <= Altura ; IteradorLinha++)
	{
		for(IteradorColuna = 1; IteradorColuna <= Largura; IteradorColuna++)
		{
			CondRetDES = DES_ObterEstadoCorreto(pDesenho,IteradorLinha,IteradorColuna, &Estado);
			if(Estado == 1)
				fprintf(arq,"1 ");
			else
				fprintf(arq,"0 ");
		}
		fprintf(arq,"\n");
	}

	for(IteradorLinha = 1; IteradorLinha <= Altura ; IteradorLinha++)
	{
		for(IteradorColuna = 1; IteradorColuna <= Largura; IteradorColuna++)
		{
			CondRetDES = DES_ObterEstadoAtual(pDesenho,IteradorLinha,IteradorColuna, &Estado);
			if(Estado == 1)
				fprintf(arq,"1 ");
			else
				fprintf(arq,"0 ");
		}
		fprintf(arq,"\n");
	}
	fprintf(arq, "%d", NumHint);
	fclose(arq);
	return 1;
}/* Fim função Salva */

/***************************************************************************
*
*  Função: JOGO  Load
*  ****/

ptDesenho Load(char * NomeArq , int * Altura, int * Largura, int * NumHint){
	int Estado = 0, IteradorAltura = 1, IteradorLargura = 1;
	FILE* arq = fopen(strcat(NomeArq, ".txt"), "r") ;
	if(arq == NULL)
	{
		return NULL;
	}
	fscanf(arq, "%d %d", Altura, Largura) ;
	DES_GerarMatrizes( &pDesenho, *Altura, *Largura ) ;

	while(IteradorAltura <= *Altura )
	{
		for(IteradorLargura =1 ; IteradorLargura <= *Largura ; IteradorLargura++)
		{
			
			fscanf(arq,"%d ", &Estado) ;
			if(Estado == 1)
			{
				DES_AlterarEstadoCorreto(pDesenho, IteradorAltura, IteradorLargura) ;
			}
		}
		
		IteradorAltura++ ;
	}
	IteradorAltura = 1 ;
	while(IteradorAltura <= *Altura )
	{
		for(IteradorLargura =1 ; IteradorLargura <= *Largura ; IteradorLargura++)
		{
			
			fscanf(arq,"%d ", &Estado) ;
			if(Estado == 1)
			{
				DES_AlterarEstadoAtual(pDesenho, IteradorAltura, IteradorLargura) ;
			}
		}
		
		IteradorAltura++ ;
	}

	fscanf(arq,"%d", NumHint);

	return pDesenho ;

}/* Fim função Load */

/***************************************************************************
*
*  Função: JOGO  TestaFimJogo
*  ****/

int TestaFimJogo(ptDesenho pDesenho , int Altura, int Largura){
	int IteradorAltura, IteradorLargura;
	int EstadoCorreto, EstadoAtual ;

	for(IteradorAltura = 1; IteradorAltura <= Altura; IteradorAltura++)
	{
		for(IteradorLargura = 1; IteradorLargura <=Largura ; IteradorLargura++)
		{
			CondRetDES = DES_ObterEstadoCorreto(pDesenho,IteradorAltura,IteradorLargura, &EstadoCorreto) ;
			CondRetDES = DES_ObterEstadoAtual(pDesenho,IteradorAltura,IteradorLargura,&EstadoAtual) ;
			if(EstadoCorreto != EstadoAtual)
				return 1;
		}
	}

	return 0;

}/* Fim função TestaFimJogo */

/***************************************************************************
*
*  Função: JOGO  Hint
*  ****/

ptDesenho Hint(ptDesenho Desenho, int Altura, int Largura){
	int IteradorLinha, IteradorColuna, idx = 0 ; 
	int EstadoAtual = -1 , EstadoCorreto = -1;

	for(IteradorLinha = 1 ; IteradorLinha <= Altura; IteradorLinha++)
	{
		for(IteradorColuna = 1 ; IteradorColuna <= Largura ; IteradorColuna++)
		{
			CondRetDES = DES_ObterEstadoAtual(pDesenho,IteradorLinha,IteradorColuna,&EstadoAtual); 
			CondRetDES = DES_ObterEstadoCorreto(pDesenho,IteradorLinha,IteradorColuna,&EstadoCorreto);
			if(EstadoAtual != EstadoCorreto)
			{
				CondRetDES = DES_AlterarEstadoAtual(pDesenho,IteradorLinha,IteradorColuna) ;
				return pDesenho ;
			}
		}
	}
	
} /* Fim função Hint */

/***************************************************************************
*
*  Função: JOGO  Desafio
*  ****/

void Desafio()
{
	int TestaFim = 0, TestaFinal = -1, Linha = -1, Coluna = -1, TestaValidez = -1, Opcao = -1 ;
	int NumHint, TestaHint = 0, SalvaJogo, OpcaoInvalida = 0, Opcoes = 0, Opcoes2 = 0;
	int Altura, Largura;
	char NomeArq[65], NomeArq2[65] ;

	system("cls");
	while(TestaValidez != 0)
	{
		TestaValidez = 0;
		printf("Digite o nome do arquivo que deseja abrir (sem o formato): \n=> ");
		scanf(" %64[^\n]", NomeArq);
		pDesenho = Load(NomeArq, &Altura, &Largura, &NumHint) ;
		if(pDesenho == NULL)
		{
			system("cls");
			printf("Arquivo invalido!\n");
			TestaValidez = -1;
		}
	}

	TestaValidez = -1;
	TestaFinal = TestaFimJogo(pDesenho,Altura,Largura) ;
	system("cls");
	CondRetDES = DES_DesenharAtual(pDesenho);
	if(TestaFinal == 0)
	{
		printf("Voce venceu!\nPressione qualquer tecla para fechar...");
		getch();
		exit(1);
	}

	while(TestaFim == 0)
	{
		system("cls");
		CondRetDES = DES_DesenharAtual(pDesenho);
		if(OpcaoInvalida == 1)
		{
			printf("Opcao Invalida!\n");
			OpcaoInvalida = 0;
		}
		printf("Digite uma das opcoes a seguir:\n (1) - Escolher um quadrado para ser modificado.\n (2) - Usar um hint. Voce possui ainda %d hints disponiveis\n (3) - Salvar o estado atual do jogo. \n => ", 10 - NumHint);
		scanf("%d", &Opcao);
		if(Opcao == 2)
		{
			if(NumHint <= 10)
			{
				pDesenho = Hint(pDesenho, Altura,Largura);
				NumHint++;
				system("cls");
				CondRetDES = DES_DesenharAtual(pDesenho);
				printf("Numero de Hints utilizados: %d de 10\n", NumHint);
				printf("\n");
				TestaFinal = TestaFimJogo(pDesenho,Altura,Largura) ;
				if(TestaFinal == 0)
				{
					printf("Voce venceu!\nPressione qualquer tecla para fechar...");
					getch();
					exit(1);
				}
			}else{
				printf("Numero maximo de hints (10) ja foi utilizado!\n");
			}
		}else if(Opcao == 3)
		{
			system("cls");
			CondRetDES = DES_DesenharAtual(pDesenho);
			printf("Digite o nome do arquivo: \n");
			scanf(" %64[^\n]",&NomeArq2);
			SalvaJogo = Salva(pDesenho,NomeArq2, Altura,Largura, NumHint);
			if(SalvaJogo == 0)
			{
				printf("Erro ao salvar o arquivo\n");
			}else
			{
				printf("Arquivo salvo corretamente\n");
			}
		}
		else if(Opcao == 1)
		{
			system("cls");
			CondRetDES = DES_DesenharAtual(pDesenho);
			printf("Digite as coordenadas do quadrado. \nLinha => ");
			scanf("%d", &Linha );
			printf("Coluna => ");
			scanf("%d", &Coluna);
			printf("\n");

			TestaValidez = PosicaoValida(Altura,Largura,Linha,Coluna);

			if(TestaValidez == 1 )
				printf("Coordenadas invalidas \n");
			else
			{
				CondRetDES = DES_AlterarEstadoAtual(pDesenho,Linha,Coluna);
				system("cls");
				CondRetDES = DES_DesenharAtual(pDesenho);
				TestaFinal = TestaFimJogo(pDesenho,Altura,Largura) ;
				if(TestaFinal == 0)
				{
					printf("Voce venceu!\nPressione qualquer tecla para fechar...");
					getch();
					exit(1);
				}
				TestaFinal = 0;
				system("cls");
				CondRetDES = DES_DesenharAtual(pDesenho);
				while(Opcoes == 0)
				{
					printf("Digite uma das opcoes a seguir:\n (0) - Modificar mais quadrados.\n (1) - Terminar o jogo. \n => ");
					scanf("%d", &TestaFim) ;
					if(TestaFim == 0)
						Opcoes = 1;
					else if(TestaFim == 1)
					{
						TestaFinal = TestaFimJogo(pDesenho,Altura,Largura) ;
						if(TestaFinal == 0)
						{
							printf("Voce venceu!\nPressione qualquer tecla para fechar...");
							Opcoes = 1;
							getch();
						}
						else
						{
							system("cls");
							while(Opcoes2 == 0)
							{
								printf("O nonograma nao foi completado corretamente. \nDigite uma das opcoes a seguir:\n (0) - Continuar tentando.\n (1) - Sair do jogo. \n => ");
								scanf("%d", &TestaFim) ;
								if(TestaFim == 0)
								{
									Opcoes = 1;
									Opcoes2 = 1;
								}
								else if(TestaFim == 1)
								{
									exit(1);
								}
								else
								{
									system("cls");
									printf("Opcao invalida!\n");
								}
							}
							Opcoes2 = 0;
						}
					}
					else
					{
						system("cls");
						printf("Opcao invalida!\n");
					}
				}
				Opcoes = 0;
			}
			printf("\n");
		}
		else
		{
			OpcaoInvalida = 1;
		}
	}
}/* Fim função Desafio */

/***************************************************************************
*
*  Função: JOGO  Main
*  ****/

int main(void)
{
	int Modo = -1 ;
	char NomeArq[65] ;
	
	while(Modo != 0 && Modo != 1 && Modo != 2)
	{
		system("cls");
		printf("Digite uma das opcoes a seguir:\n (1) - Criar um novo projeto.\n (2) - Abrir um arquivo no modo desafio.\n (0) - Sair. \n => ");
		scanf("%d", &Modo);
		if(Modo == 1)
		{
			Projeto();
		} else if(Modo == 2) {
			Desafio();
		} else if (Modo != 0) {
			printf("Opcao invalida!\n");
		} /* if */
	} /* for */

	return 1;

} /* Fim da função Main */
