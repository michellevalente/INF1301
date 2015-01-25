#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: MAT  Matriz de listas
*
*  Arquivo gerado:          	MATRIZ.h
*  Letras identificadoras:  	MAT
*
*  Nome da base de software:	Arcabouço para a automação de testes de programas redigidos em C
*
*  Projeto: Trabalho 2 - Programação Modular
*  Autores: GB - Gustavo Bach
*       	JG - João Lucas Gardenberg
*       	MV - Michelle Valente
*
*  $HA Histórico de evolução:
*      Versão   Autor      Data          Observações
*      2.01     GB,JG,MV   20/abr/2013   mudança no jeito como o parâmetro é utilizado na função de inserir.
*      2.00     GB,JG,MV   11/abr/2013   reformulação de todas as funções
*      1.00     GB,JG,MV   28/mar/2013   início desenvolvimento
*
*  $ED Descrição do módulo
*      Módulo de Matriz Genérica.
*
***************************************************************************/



#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma matriz */

typedef struct tgMatriz * ptMatriz ;


/***********************************************************************
*
*  $TC Tipo de dados: MAT Condições de retorno
*
*  $ED Descrição do tipo
*   	Condições de retorno das funções da matriz
*
***********************************************************************/

   typedef enum {

   	MAT_CondRetOK,
      	/* Concluiu corretamente */

   	MAT_CondRetMatrizNaoExiste,
      	/* Não concluiu corretamente */

   	MAT_CondRetMatrizVazia,
      	/* A matriz não contém elementos */

   	MAT_CondRetFaltouMemoria,
      	/* Faltou memória ao tentar criar um elemento de lista */

   	MAT_CondRetFimColunas,
      	/* Foi atingido o fim das colunas da matriz */

   	MAT_CondRetFimLinhas
      	/* Foi atingido o fim das linhas da matriz */

	#ifdef _DEBUG
			,
			MAT_CondRetValorInalterado
	#endif

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT  Criar matriz
*
*  $ED Descrição da função
*      Cria uma matriz genérica.
*      Os possíveis tipos são desconhecidos a priori.
*      A tipagem é implícita.
*      Não existe identificador de tipo associado à matriz.
*
*  $EP Parâmetros
*      $P pMatriz - ponteiro para a matriz a ser criada.
*                   Este ponteiro será utilizado pelas funções
*                   que manipulem esta matriz.
*      $P Altura  - define qual vai ser a altura da matriz.
*      $P Largura - define qual vai ser a largura da matriz.
*
*  $FV Valor retornado
*      MAT_CondRetOK        	- se criou sem problemas.
*      MAT_CondRetFaltouMemoria - se faltou memória para alocar o espaço da matriz.
*
*  Assertivas de entradas esperadas - pMatriz == NULL.
*
*  Assertivas de saidas esperadas   - CondRetOK => pMatriz != NULL.
*                                     (*pMatriz)->Altura = Altura.
*                                     (*pMatriz)->Largura = Largura.
*                                     CondRetFaltouMemoria => pMatriz == NULL.
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( ptMatriz * pMatriz, int Altura, int Largura 
	   #ifdef _DEBUG
		,
		 char tipoElemento

		#endif

		)
		;


/***********************************************************************
*
*  $FC Função: MAT  Destruir matriz
*
*  $ED Descrição da função
*      Destrói a matriz fornecida.
*      O parâmetro ponteiro para a matriz não é modificado.
*      Se ocorrer algum erro durante a destruição, a matriz resultará
*      estruturalmente incorreta.
*      OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*      $P pMatriz - ponteiro para a matriz a ser destruída.
*
*  $FV Valor retornado
*      MAT_CondRetOK              - se destruiu sem problemas
*      MAT_CondRetMatrizNaoExiste - se a matriz a ser destruída não existir.
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
*  $FC Função: MAT  Inserir valor no elemento
*
*  $ED Descrição da função
* 	Insere novo elemento na posição especificada.
*
*  $EP Parâmetros
* 	$P pMatriz   - ponteiro para a matriz a ser alterada.
* 	$P pElemento - ponteiro para o elemento que será inserido.
* 	$P Linha     - linha onde o elemento será inserido.
*                  O número tem que ser maior que 0 e menor ou igual
*                  à altura da matriz.
* 	$P Coluna    - coluna onde o elemento será inserido.
*                  O número tem que ser maior que 0 e menor ou igual
*                  à coluna da matriz.
*
*  $FV Valor retornado
* 	MAT_CondRetOK              - se inseriu o elemento sem problemas.
* 	MAT_CondRetMatrizNaoExiste - se a matriz a ser alterada não existir.
* 	MAT_CondRetMatrizVazia     - se a matriz a ser alterada estiver vazia.
* 	MAT_CondRetFimLinhas       - se o parâmetro Linha passado for maior do que
*                                o número de linhas da matriz a ser alterada.
* 	MAT_CondRetFimColunas      - se o parâmetro Coluna passado for maior do que
*                                o número de colunas da matriz a ser alterada.
*
*  Assertivas de entradas esperadas - pMatriz != NULL.
*                                     pElemento != NULL.
*                                     0 < Linha <= pMatriz->Altura.
*                                     0 < Coluna <= pMatriz->Largura.
*
*  Assertivas de saidas esperadas   - pElemento será alocado na linha e coluna
*                                     especificadas.
*                                     CondRetMatrizNaoExiste => pMatriz == NULL.
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirValor( ptMatriz pMatriz, void * pElemento, int Linha , int Coluna 
	   #ifdef _DEBUG
		,
		 char tipoElemento
		#endif
		 ) ;


/***********************************************************************
*
*  $FC Função: MAT  Obter valor do elemento
*
*  $ED Descrição da função
* 	Obtém o valor do elemento que está na posição especificada.
*
*  $EP Parâmetros
* 	$P pMatriz - ponteiro para a matriz onde o elemento se encontra.
* 	$P Linha   - linha onde o elemento se encontra.
* 	$P Coluna  - coluna onde o elemento se encontra.
* 	$P pValor  - ponteiro que receberá a referência para o valor contido
*                no elemento.
*
*  $FV Valor retornado
* 	MAT_CondRetOK              - se obteve o valor do elemento sem problemas.
* 	MAT_CondRetMatrizNaoExiste - se a matriz a ser utilizada não existir.
* 	MAT_CondRetMatrizVazia     - se a matriz a ser utilizada estiver vazia.
* 	MAT_CondRetFimLinhas       - se o parâmetro Linha passado for maior do que
*                                o número de linhas da matriz utilizada.
* 	MAT_CondRetFimColunas      - se o parâmetro Coluna passado for maior do que
*                                o número de colunas da matriz utilizada.
*
*  Assertivas de entradas esperadas - pMatriz != NULL.
*                                     pMatriz->Matriz->pElemCorr != NULL.
*                                     0 < Linha <= pMatriz->Altura.
*                                     0 < Coluna <= pMatriz->Largura.
*
*  Assertivas de saidas esperadas   - pMatriz não altera.
*                                     pValor irá receber o valor do elemento cuja
*                                     linha e coluna foram especificados.
*                                     CondRetMatrizNaoExiste => pMatriz == NULL.
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValor( ptMatriz pMatriz, int Linha, int Coluna, void ** pValor ) ;


/***********************************************************************
*
*  $FC Função: MAT  Obter Altura e Largura da Matriz
*
*  $ED Descrição da função
*      Obtém a altura e a largura da matriz, por referência.
*
*  $EP Parâmetros
* 	$P pMatriz  - ponteiro para a matriz onde o elemento se encontra.
* 	$P Altura   - ponteiro que receberá a referência para a altura da matriz.
* 	$P Largura  - ponteiro que receberá a referência para a largura da matriz.
*
*  $FV Valor retornado
* 	MAT_CondRetOK              - se obteve o valor do elemento sem problemas.
* 	MAT_CondRetMatrizNaoExiste - se a matriz a ser utilizada não existir.
* 	MAT_CondRetMatrizVazia     - se a matriz a ser utilizada estiver vazia.
*
*  Assertivas de entradas esperadas - pMatriz != NULL.
*
*  Assertivas de saidas esperadas   - Altura receberá pMatriz->Altura.
*                                     Largura receberá pMatriz->Largura.
*                                     CondRetMatrizNaoExiste => pMatriz == NULL.
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterAlturaLargura ( ptMatriz pMatriz,
	                                      int * Altura,
										  int * Largura     ) ;

#ifdef _DEBUG

/***********************************************************************
*
*  $FC Função: MAT Liberar nó corrente.
*
*  $EP Parâmetros
*     pMatriz - matriz que deseja liberar o nó corrente.
*
*  $ED Descrição da função
*     Libera o ponteiro para o nó corrente.
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Matriz de Listas.
*
*  $AS Assertivas de Saída
*	Caso a matriz seja válida, o nó foi excluido e o ponteiro corrente aponta
*	para o próximo nó ou NULL caso a matriz tenha acado.
*   Valem as assertivas estrururais da Matriz de Listas.
*
***********************************************************************/

	void MAT_LiberaElementoCorrente( ptMatriz pMatriz, int linha, int coluna);


/***********************************************************************
 *
 *  $FC Função: MAT Altera Ponteiro Sucessor.
 *
 *  $EP Parâmetros
 *     matriz - Matriz que se deseja alterar.
 *     Linha - linha que deseja alterar.
 *     Coluna - Coluna que deseja alterar
 *     Elemento - Elemento que deseja que substitua o atual
 *
 *  $ED Descrição da função
 *     Altera o ponteiro sucessor do elemento informado pelas linhas e colunas
 *     para o elemento fornecido.
 *
 *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  - Para executar corretamente, a funcao deve receber 
 *    dois inteiros válidos e um ponteiro que pode ser NULL
 *  
 *  $AS Assertivas de saída
 *  - A matriz será deturpada como desejada
 *
 ***********************************************************************/

	  void MAT_AlteraPonteiroSucessor( ptMatriz pMatriz, int linha, int coluna, void* elem );

/***********************************************************************
 *
 *  $FC Função: MAT Altera Ponteiro Predecessor.
 *
 *  $EP Parâmetros
 *     matriz - Matriz que se deseja alterar.
 *     Linha - linha que deseja alterar.
 *     Coluna - Coluna que deseja alterar
 *     Elemento - Elemento que deseja que substitua o atual
 *
 *  $ED Descrição da função
 *     Altera o ponteiro predecessor do elemento informado pelas linhas e colunas
 *     para o elemento fornecido.
 *
 *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  - Para executar corretamente, a funcao deve receber 
 *    dois inteiros válidos e um ponteiro que pode ser NULL
 *  
 *  $AS Assertivas de saída
 *  - A matriz será deturpada como desejada
 *
 ***********************************************************************/

	  void MAT_AlteraPonteiroPredecessor( ptMatriz pMatriz, int linha, int coluna, void* elem ) ;

/***********************************************************************
 *
 *  $FC Função: MAT alterar a informação contida em uma posição da matriz.
 *
 *  $EP Parâmetros
 *     matriz- lista que deseja realizar a alteração
 *     elemento substituto - informação que deseja colocar na matriz.
 *     linha - linha do elemento a ser alterado
 *     coluna - coluna do elemento a ser alterado
 *     No modo DEBUG, caracter que representa o tipo de elemento da matriz
 *
 *  $ED Descrição da função
 *    Altera o valor que está na posição dada da matriz.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetValorInalterado
 *
 *	$AE Assertivas de entrada
 *   - Valem as assertivas estruturais de matriz.
 *   - A função deve receber endereços válidos de matriz e elemento, 
 *     para os tipos Matriz e Elemento, respectivamente, para executar
 *	   corretamente.
 *
 *  $AS Assertivas de saída
 *    - Se a funcao alterar o elemento da matriz corretamente, deve retornar
 *      condicao ok.
 *    - Devolve condicao nao ok, quando recebe um endereco invalido de matriz
 *      para o tipo Matriz
 *
 ***********************************************************************/

	  MAT_tpCondRet MAT_AlteraCelula(  ptMatriz pMatriz, void* elem, int linha, int coluna,char tipoElemento ) ;

/***********************************************************************
 *
 *  $FC Função: MAT Destaca Celula
 *
 *  $EP Parâmetros
 *     matriz - Matriz que se deseja alterar.
 *
 *  $ED Descrição da função
 *     Exclui um elemento da lista porem sem liberar seu espaco na memoria.
 *
 *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  
 *  $AS Assertivas de saída
 *  - A matriz será deturpada como desejada, será excluido o nó
 *    corrente sem liberar seu espaço na memória.
 *
 ***********************************************************************/

	  void MAT_DestacaCelula(  ptMatriz pMatriz, int linha, int coluna );

/***********************************************************************
 *
 *  $FC Função: MAT Ir Para Elemento
 *
 *  $EP Parâmetros
 *     matriz - Matriz que se deseja alterar.
 *
 *  $ED Descrição da função
 *     Avança as listas ate chegar no elemento que esta na linha e coluna.
 *
 *  $AE Assertivas de entrada
 *  - Valem as assertivas estruturais de matriz.
 *  
 *  $AS Assertivas de saída
 *  - Elemento corrente sera o da linha e coluna.
 *
 ***********************************************************************/

	  void MAT_IrParaElemento( ptMatriz pMatriz, int Linha, int Coluna);

/***********************************************************************
*
*  $FC Função: MAT corrente NULL .
*
*  $EP Parâmetros
*     pMatriz - matriz que deseja alterar.
*
*  $ED Descrição da função
*	  Acessa a matriz definindo como Nulo o ponteiro para o no corrente.
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Matriz.
*
*  $AS Assertivas de Saída
*	Ponteiro para nó corrente da matriz é NULL.
*
***********************************************************************/

	  void MAT_CorrenteNULL(  ptMatriz pMatriz, int linha, int coluna ) ;

/***********************************************************************
*
*  $FC Função: MAT origem NULL .
*
*  $EP Parâmetros
*     pMatriz - matriz que deseja alterar.
*
*  $ED Descrição da função
*	  Acessa a matriz definindo como Nulo o ponteiro para o no origem.
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Matriz.
*
*  $AS Assertivas de Saída
*	Ponteiro para nó origem da matriz é NULL.
*
***********************************************************************/

	void MAT_OrigemNULL(  ptMatriz pMatriz) ;

	int MAT_VerificaProxElemento ( ptMatriz pMatriz, char direcao, int posicao );
	int MAT_VerificaAntElemento ( ptMatriz pMatriz, char direcao, int posicao );
	int MAT_VerificaListaVazia ( ptMatriz pMatriz, char direcao, int posicao);
	int MAT_VerificaListaElemUnico ( ptMatriz pMatriz, char direcao, int posicao);
	int MAT_VerificaListaPreenchida ( ptMatriz pMatriz, char direcao, int posicao );
	int MAT_VerificaTipoCelula ( ptMatriz pMatriz, int linha, int coluna);
	int MAT_VerificaTamanhoListas ( ptMatriz pMatriz, int linha);
	int MAT_VerificaCelulaNULL ( ptMatriz pMatriz, int linha, int coluna);
	void MAT_DeturpaCelulaNULL ( ptMatriz pMatriz, int linha, int coluna);
	void MAT_LixoSucessor ( ptMatriz pMatriz, int linha, int coluna);
	int MAT_VerificaDuplamenteEncadeada ( ptMatriz pMatriz, int linha, int coluna);

#endif
#undef MATRIZ_EXT

#else
#endif
