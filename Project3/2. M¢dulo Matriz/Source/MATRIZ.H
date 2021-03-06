#if ! defined( MATRIZ_ )
   #define MATRIZ_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: MAT  Matriz de listas
*
*  Arquivo gerado:          	MATRIZ.h
*  Letras identificadoras:  	MAT
*
*  Nome da base de software:	Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: Trabalho 2 - Programa��o Modular
*  Autores: GB - Gustavo Bach
*       	JG - Jo�o Lucas Gardenberg
*       	MV - Michelle Valente
*
*  $HA Hist�rico de evolu��o:
*      Vers�o   Autor      Data          Observa��es
*      2.01     GB,JG,MV   20/abr/2013   mudan�a no jeito como o par�metro � utilizado na fun��o de inserir.
*      2.00     GB,JG,MV   11/abr/2013   reformula��o de todas as fun��es
*      1.00     GB,JG,MV   28/mar/2013   in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*      M�dulo de Matriz Gen�rica.
*
***************************************************************************/


#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma matriz */

typedef struct tgMatriz * ptMatriz ;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Condi��es de retorno
*
*  $ED Descri��o do tipo
*   	Condi��es de retorno das fun��es da matriz
*
***********************************************************************/

   typedef enum {

   	MAT_CondRetOK,
      	/* Concluiu corretamente */

   	MAT_CondRetMatrizNaoExiste,
      	/* N�o concluiu corretamente */

   	MAT_CondRetMatrizVazia,
      	/* A matriz n�o cont�m elementos */

   	MAT_CondRetFaltouMemoria,
      	/* Faltou mem�ria ao tentar criar um elemento de lista */

   	MAT_CondRetFimColunas,
      	/* Foi atingido o fim das colunas da matriz */

   	MAT_CondRetFimLinhas
      	/* Foi atingido o fim das linhas da matriz */

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: MAT  Criar matriz
*
*  $ED Descri��o da fun��o
*      Cria uma matriz gen�rica.
*      Os poss�veis tipos s�o desconhecidos a priori.
*      A tipagem � impl�cita.
*      N�o existe identificador de tipo associado � matriz.
*
*  $EP Par�metros
*      $P pMatriz - ponteiro para a matriz a ser criada.
*                   Este ponteiro ser� utilizado pelas fun��es
*                   que manipulem esta matriz.
*      $P Altura  - define qual vai ser a altura da matriz.
*      $P Largura - define qual vai ser a largura da matriz.
*
*  $FV Valor retornado
*      MAT_CondRetOK        	- se criou sem problemas.
*      MAT_CondRetFaltouMemoria - se faltou mem�ria para alocar o espa�o da matriz.
*
*  Assertivas de entradas esperadas - pMatriz == NULL.
*
*  Assertivas de saidas esperadas   - CondRetOK => pMatriz != NULL.
*                                     (*pMatriz)->Altura = Altura.
*                                     (*pMatriz)->Largura = Largura.
*                                     CondRetFaltouMemoria => pMatriz == NULL.
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( ptMatriz * pMatriz, int Altura, int Largura );


/***********************************************************************
*
*  $FC Fun��o: MAT  Destruir matriz
*
*  $ED Descri��o da fun��o
*      Destr�i a matriz fornecida.
*      O par�metro ponteiro para a matriz n�o � modificado.
*      Se ocorrer algum erro durante a destrui��o, a matriz resultar�
*      estruturalmente incorreta.
*      OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $EP Par�metros
*      $P pMatriz - ponteiro para a matriz a ser destru�da.
*
*  $FV Valor retornado
*      MAT_CondRetOK              - se destruiu sem problemas
*      MAT_CondRetMatrizNaoExiste - se a matriz a ser destru�da n�o existir.
*
*  Assertivas de entradas esperadas - pMatriz != NULL.
*
*  Assertivas de saidas esperadas   - CondRetOK => pMatriz == NULL.
*                                     CondRetMatrizNaoExiste => pMatriz == NULL.
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz( ptMatriz pMatriz ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT  Inserir valor no elemento
*
*  $ED Descri��o da fun��o
* 	Insere novo elemento na posi��o especificada.
*
*  $EP Par�metros
* 	$P pMatriz   - ponteiro para a matriz a ser alterada.
* 	$P pElemento - ponteiro para o elemento que ser� inserido.
* 	$P Linha     - linha onde o elemento ser� inserido.
*                  O n�mero tem que ser maior que 0 e menor ou igual
*                  � altura da matriz.
* 	$P Coluna    - coluna onde o elemento ser� inserido.
*                  O n�mero tem que ser maior que 0 e menor ou igual
*                  � coluna da matriz.
*
*  $FV Valor retornado
* 	MAT_CondRetOK              - se inseriu o elemento sem problemas.
* 	MAT_CondRetMatrizNaoExiste - se a matriz a ser alterada n�o existir.
* 	MAT_CondRetMatrizVazia     - se a matriz a ser alterada estiver vazia.
* 	MAT_CondRetFimLinhas       - se o par�metro Linha passado for maior do que
*                                o n�mero de linhas da matriz a ser alterada.
* 	MAT_CondRetFimColunas      - se o par�metro Coluna passado for maior do que
*                                o n�mero de colunas da matriz a ser alterada.
*
*  Assertivas de entradas esperadas - pMatriz != NULL.
*                                     pElemento != NULL.
*                                     0 < Linha <= pMatriz->Altura.
*                                     0 < Coluna <= pMatriz->Largura.
*
*  Assertivas de saidas esperadas   - pElemento ser� alocado na linha e coluna
*                                     especificadas.
*                                     CondRetMatrizNaoExiste => pMatriz == NULL.
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirValor( ptMatriz pMatriz, void * pElemento, int Linha , int Coluna ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT  Obter valor do elemento
*
*  $ED Descri��o da fun��o
* 	Obt�m o valor do elemento que est� na posi��o especificada.
*
*  $EP Par�metros
* 	$P pMatriz - ponteiro para a matriz onde o elemento se encontra.
* 	$P Linha   - linha onde o elemento se encontra.
* 	$P Coluna  - coluna onde o elemento se encontra.
* 	$P pValor  - ponteiro que receber� a refer�ncia para o valor contido
*                no elemento.
*
*  $FV Valor retornado
* 	MAT_CondRetOK              - se obteve o valor do elemento sem problemas.
* 	MAT_CondRetMatrizNaoExiste - se a matriz a ser utilizada n�o existir.
* 	MAT_CondRetMatrizVazia     - se a matriz a ser utilizada estiver vazia.
* 	MAT_CondRetFimLinhas       - se o par�metro Linha passado for maior do que
*                                o n�mero de linhas da matriz utilizada.
* 	MAT_CondRetFimColunas      - se o par�metro Coluna passado for maior do que
*                                o n�mero de colunas da matriz utilizada.
*
*  Assertivas de entradas esperadas - pMatriz != NULL.
*                                     pMatriz->Matriz->pElemCorr != NULL.
*                                     0 < Linha <= pMatriz->Altura.
*                                     0 < Coluna <= pMatriz->Largura.
*
*  Assertivas de saidas esperadas   - pMatriz n�o altera.
*                                     pValor ir� receber o valor do elemento cuja
*                                     linha e coluna foram especificados.
*                                     CondRetMatrizNaoExiste => pMatriz == NULL.
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValor( ptMatriz pMatriz, int Linha, int Coluna, void ** pValor ) ;


/***********************************************************************
*
*  $FC Fun��o: MAT  Obter Altura e Largura da Matriz
*
*  $ED Descri��o da fun��o
*      Obt�m a altura e a largura da matriz, por refer�ncia.
*
*  $EP Par�metros
* 	$P pMatriz  - ponteiro para a matriz onde o elemento se encontra.
* 	$P Altura   - ponteiro que receber� a refer�ncia para a altura da matriz.
* 	$P Largura  - ponteiro que receber� a refer�ncia para a largura da matriz.
*
*  $FV Valor retornado
* 	MAT_CondRetOK              - se obteve o valor do elemento sem problemas.
* 	MAT_CondRetMatrizNaoExiste - se a matriz a ser utilizada n�o existir.
* 	MAT_CondRetMatrizVazia     - se a matriz a ser utilizada estiver vazia.
*
*  Assertivas de entradas esperadas - pMatriz != NULL.
*
*  Assertivas de saidas esperadas   - Altura receber� pMatriz->Altura.
*                                     Largura receber� pMatriz->Largura.
*                                     CondRetMatrizNaoExiste => pMatriz == NULL.
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterAlturaLargura ( ptMatriz pMatriz,
	                                      int * Altura,
										  int * Largura     ) ;


#undef MAT_EXT

/********** Fim do m�dulo de defini��o: MAT  Matriz de listas **********/

#else
#endif
