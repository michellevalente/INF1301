#if ! defined( DESENHO_ )
#define DESENHO_
/***************************************************************************
*
*  $MCD Módulo de definição: DES  Módulo Desenho
*
*  Arquivo gerado:          	DESENHO.H
*  Letras identificadoras:  	DES
*
*  Nome da base de software:  Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: Trabalho 2 - Programação Modular
*  Autores: GB - Gustavo Bach
*       	JG - João Lucas Gardenberg
*       	MV - Michelle Valente
*
*  $HA Histórico de evolução:
*  	Versão   Autor  	Data      	Observações
*  	1.00 	GB,JG,MV   12/abr/2014   início desenvolvimento
*   2.00    GB,JG,MV   16/mai/2014   remoção da função de criar e preencher as matrizes de valores.
*   2.00    GB,JG,MV   16/mai/2014   modificação da função de criar a matriz principal. agora ela também cria as matrizes de valores
*   2.01    GB,JG,MV   16/mai/2014   modificação brusca da função de alterar estado correto.
*   2.02    GB,JG,MV   16/mai/2014   adição das funçãos de desenhar atual e correto. remoção da função anterior de desenhar
*
*  $ED Descrição do módulo
*  	Módulo que gera e gerencia o desenho utilizado no Jogo.
*
***************************************************************************/
 
#if defined( DESENHO_OWN )
	#define DESENHO_EXT
#else
	#define DESENHO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/


/* Tipo referência para um desenho */

	typedef struct tgDesenho * ptDesenho ;

/***********************************************************************
*
*  $TC Tipo de dados: DES Condições de retorno
*
*  $ED Descrição do tipo
*  	Condições de retorno das funções do valor
*
***********************************************************************/

	typedef enum {

		DES_CondRetOK,
           	/* Concluiu corretamente */

		DES_CondRetFaltouMemoria,
           	/* Faltou memória ao tentar alocar espaço */

		DES_CondRetDesenhoNaoExiste,
           	/* O Desenho não existe */

		DES_CondRetMatrizNaoExiste,
           	/* Alguma das matrizes não existe quando devia existir */

		DES_CondRetMatrizVazia,
           	/* Alguma das matrizes está vazia */

		DES_CondRetCelNaoExiste,
           	/* Alguma célula não existe quando devia existir */

		DES_CondRetEstadoCelInvalido,
			/* Alguma célula está com o estado inválido */

		DES_CondRetValorNaoExiste,
			/* Algum valor não existe quando devia existir */

		DES_CondRetFimColunas,
			/* Foi atingido o fim das colunas de alguma matriz */

		DES_CondRetFimLinhas
			/* Foi atingido o fim das linhas de alguma matriz */

	} DES_tpCondRet ;

/***********************************************************************
*
*  $FC Função: DES &Gerar Matrizes
*
*  $ED Descrição da função
*  	Gera as matrizes (a de células e as duas de valores) do jogo.
*
*  $EP Parâmetros
*  	pDesenho - Ponteiro para o campo desenho a ser criado.
*  	Altura - Altura da matriz a ser criada.
*  	Largura - Largura da matriz a ser criada.
*
*  $FV Valor retornado
*    	DES_CondRetOK
*    	DES_CondRetFaltouMemoria
*
*  Assertivas de entradas esperadas - pDesenho != NULL.
*                                 	Altura e largura são números inteiros
*                                 	maiores que zero.	 
*
*  Assertivas de saidas esperadas   - DES_CondRetOk => pDesenho terá sido criado com
*                                 	com uma matriz contendo valores do tipo Celula, e
*                                   duas matrizes contendo valores do tipo Valor.
*                                 	DES_CondRetFaltouMemoria => pDesenho == NULL.
*    
*
***********************************************************************/

	DES_tpCondRet DES_GerarMatrizes( ptDesenho * pDesenho, 
										int Altura, 
										int Largura ) ;

/***********************************************************************
*
*  $FC Função: DES &Alterar Estado Correto
*
*  $ED Descrição da função
*  	Altera o Estado Correto da célula cujas coordenadas são passadas e preenche a coluna e a linha
*   respectiva das matrizes de valores.
*
*  $EP Parâmetros
*  	pDesenho - Ponteiro para o campo desenho.
*  	Linha - Linha da célula.
*  	Coluna - Coluna da célula.
*
*  $FV Valor retornado
*  	DES_CondRetOK
*  	DES_CondRetDesenhoNaoExiste
*  	DES_CondRetMatrizNaoExiste
*  	DES_CondRetMatrizVazia
*  	DES_CondRetCelNaoExiste
*   DES_CondRetValorNaoExiste
*	DES_CondRetFimColunas
*   DES_CondRetFimLinhas
*
*  Assertivas de entradas esperadas - pDesenho != NULL.
*                                 	Linha e Coluna são números inteiros maiores que zero.
*
*  Assertivas de saidas esperadas   - DES_CondRetOk => Estado Correto da célula da matriz de pDesenho
*                                 	presente na linha e coluna passadas como parâmetro irá alterar. As
*                                   matrizes de valores também irão alterar nas respectivas linha e coluna.
*                                 	DES_CondRetDesenhoNaoExiste => pDesenho não altera.
*                                 	DES_CondRetMatrizNaoExiste => pDesenho não altera.
*                                 	DES_CondRetMatrizVazia => pDesenho não altera.
*                                 	DES_CondRetCelNaoExiste => pDesenho não altera.
*                                   DES_CondRetValorNaoExiste => pDesenho não altera.
*
***********************************************************************/

	DES_tpCondRet DES_AlterarEstadoCorreto( ptDesenho pDesenho, 
											int Linha, 
											int Coluna ) ;

/***********************************************************************
*
*  $FC Função: DES &Alterar Estado Atual
*
*  $ED Descrição da função
*  	Altera o Estado Atual da célula cujas coordenadas são passadas.
*
*  $EP Parâmetros
*  	pDesenho - Ponteiro para o campo desenho.
*  	Linha - Linha da célula.
*  	Coluna - Coluna da célula.
*
*  $FV Valor retornado
*  	DES_CondRetOk
*  	DES_CondRetDesenhoNaoExiste
*  	DES_CondRetMatrizNaoExiste
*  	DES_CondRetMatrizVazia
*  	DES_CondRetCelNaoExiste

*  Assertivas de entradas esperadas - pDesenho != NULL.
*                                 	Linha e Coluna são números inteiros
*                                 	maiores que zero.
*                                   Esta função é intencionada a ser executada APÓS todas as chamadas 
*                                   da função DES &Alterar Estado Correto (que preenche as matrizes).
*
*  Assertivas de saidas esperadas   - DES_CondRetOk => Estado Atual da célula da matriz de pDesenho
*                                 	presente na linha e coluna passadas como parâmetro irá alterar.
*                                 	DES_CondRetDesenhoNaoExiste => pDesenho não altera.
*                                 	DES_CondRetMatrizNaoExiste => pDesenho não altera.
*                                 	DES_CondRetMatrizVazia => pDesenho não altera.
*                                 	DES_CondRetCelNaoExiste => pDesenho não altera.
*    
*
***********************************************************************/

	DES_tpCondRet DES_AlterarEstadoAtual( ptDesenho pDesenho, 
											int Linha, 
											int Coluna ) ;


/***********************************************************************
*
*  $FC Função: DES &Obter Estado Correto
*
*  $ED Descrição da função
*  	Obtém o Estado Correto da célula cujas coordenadas são passadas.
*
*  $EP Parâmetros
*  	pDesenho - Ponteiro para o campo desenho.
*  	Linha - Linha da célula.
*  	Coluna - Coluna da célula.
*  	pValor - Ponteiro onde o estado será armazenado.
*
*  $FV Valor retornado
*  	DES_CondRetOk
*  	DES_CondRetDesenhoNaoExiste
*  	DES_CondRetMatrizNaoExiste
*  	DES_CondRetMatrizVazia
*  	DES_CondRetCelNaoExiste
*
*  Assertivas de entradas esperadas - pDesenho != NULL.
*                                 	Linha e Coluna são números inteiros
*                                 	maiores que zero.
*
*  Assertivas de saidas esperadas   - DES_CondRetOK => Estado Correto da célula da matriz de pDesenho
*                                 	presente na linha e coluna passadas como parâmetro será obtido
*                                 	via pValor.
*                                 	Com qualquer outro retorno, nenhum valor é obtido.
*
***********************************************************************/

	DES_tpCondRet DES_ObterEstadoCorreto( ptDesenho pDesenho, 
											int Linha, 
											int Coluna, 
											int * pValor ) ;


/***********************************************************************
*
*  $FC Função: DES &Obter Estado Atual
*
*  $ED Descrição da função
*  	Obtém o Estado Atual da célula cujas coordenadas são passadas.
*
*  $EP Parâmetros
*  	pDesenho - Ponteiro para o campo desenho.
*  	Linha - Linha da célula.
*  	Coluna - Coluna da célula.
*  	pValor - Ponteiro onde o estado será armazenado.
*
*  $FV Valor retornado
*  	DES_CondRetOk
*  	DES_CondRetDesenhoNaoExiste
*  	DES_CondRetMatrizNaoExiste
*  	DES_CondRetMatrizVazia
*  	DES_CondRetCelNaoExiste
*
*  Assertivas de entradas esperadas - pDesenho != NULL.
*                                 	Linha e Coluna são números inteiros
*                                 	maiores que zero.
*
*  Assertivas de saidas esperadas   - DES_CondRetOK => Estado Atual da célula da matriz de pDesenho
*                                 	presente na linha e coluna passadas como parâmetro será obtido
*                                 	via pValor.
*                                 	Com qualquer outro retorno, nenhum valor é obtido.
*
***********************************************************************/

	DES_tpCondRet DES_ObterEstadoAtual( ptDesenho pDesenho, 
										int Linha, 
										int Coluna, 
										int * pValor ) ;


/***********************************************************************
*
*  $FC Função: DES &Desenhar atual
*
*  $ED Descrição da função
*  	Desenha na tela a matriz de células com seus estados atuais, as 
*   matrizes de valores à esquerda e em cima, e se as linhas/colunas
*   estão corretas à direita e em baixo. "o" significa que a linha/coluna
*   está correta. "x" significa que a linha/coluna está errada.
*
*  $EP Parâmetros
*  	pDesenho - Ponteiro para o campo desenho.
*
*  $FV Valor retornado
* 	 DES_CondRetOK
* 	 DES_CondRetDesenhoNaoExiste
* 	 DES_CondRetMatrizNaoExiste
* 	 DES_CondRetMatrizVazia
* 	 DES_CondRetValorNaoExiste
* 	 DES_CondRetCelNaoExiste
* 	 DES_CondRetEstadoCelInvalido
*
*  Assertivas de entradas esperadas - pDesenho != NULL.  
*
*  Assertivas de saidas esperadas   - O desenho do estado atual do jogo na tela.
*
***********************************************************************/

	DES_tpCondRet DES_DesenharAtual( ptDesenho pDesenho ) ;


/***********************************************************************
*
*  $FC Função: DES &Desenhar correto
*
*  $ED Descrição da função
*  	Desenha na tela a matriz de células com seus estados corretosas 
*   matrizes de valores à esquerda e em cima, e obviamente (o)'s à
*   direita e em baixo, indicando como seria o desenho correto.
*
*  $EP Parâmetros
*  	pDesenho - Ponteiro para o campo desenho.
*
*  $FV Valor retornado
* 	 DES_CondRetOK
* 	 DES_CondRetDesenhoNaoExiste
* 	 DES_CondRetMatrizNaoExiste
* 	 DES_CondRetMatrizVazia
* 	 DES_CondRetCelNaoExiste
* 	 DES_CondRetEstadoCelInvalido
*
*  Assertivas de entradas esperadas - pDesenho != NULL.
*
*  Assertivas de saidas esperadas   - O desenho do estado correto do jogo na tela.
*
***********************************************************************/

	DES_tpCondRet DES_DesenharCorreto( ptDesenho pDesenho ) ;


#undef DES_EXT

/********** Fim do módulo de definição: DES  Módulo Desenho **********/

#else
#endif
