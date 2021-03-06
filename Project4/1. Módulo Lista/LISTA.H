#if ! defined( LISTA_ )
   #define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: Trabalho 2 - Programa��o Modular
*  Autores: avs - Arndt von Staa
*           GB - Gustavo Bach
*           JG - Jo�o Lucas Gardenberg
*           MV - Michelle Valente
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor      Data          Observa��es
*     5.01    GM,JG,MV   20/abr/2014   mudan�a no jeito como o par�metro � utilizado na fun��o de alterar valor
*     5.00    GM,JG,MV   12/abr/2014   todas as fun��es exportadas pelo m�dulo retornam
*                                      condi��es de retorno
*     5.00    GB,JG,MV   11/abr/2014   adicionar fun��o de alterar valor do elemento
*     4.00    avs        01/fev/2006   criar linguagem script simb�lica
*     3.00    avs        08/dez/2004   uniformiza��o dos exemplos
*     2.00    avs        07/jul/2003   unifica��o de todos os m�dulos em um s� projeto
*     1.00    avs        16/abr/2003   in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista.
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria ,
               /* Faltou mem�ria ao tentar criar um elemento de lista */

         LIS_CondRetListaNaoExiste
               /* A lista n�o existe */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     $P pLista        - ponteiro para a lista a ser criada.
*                        Este ponteiro ser� utilizado pelas fun��es
*                        que manipulem esta lista.
*     $P ExcluirValor  - ponteiro para a fun��o que processa a
*                        exclus�o do valor referenciado pelo elemento
*                        a ser exclu�do.
*                        Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     LIS_CondRetOK            - se executou corretamente.
*     LIS_CondRetFaltouMemoria - se faltou mem�ria para alocar o espa�o da lista.
*
*  Assertivas de entradas esperadas - pLista == NULL.
*
*  Assertivas de saidas esperadas   - CondRetOk => pLista != NULL.
*									  (*pLista)->pOrigemLista == NULL ;
*									  (*pLista)->pFimLista == NULL ;
*									  (*pLista)->pElemCorr == NULL ;
*									  (*pLista)->numElem == 0 ;
*									  (*pLista)->ExcluirValor == ExcluirValor ;
*                                     CondRetFaltouMemoria => pLista == NULL.
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista * pLista,
             void   ( * ExcluirValor ) ( void * pDado )
			 #ifdef _DEBUG
			,
			char tipoElemento
			#endif
			) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $EP Par�metros
*     $P pLista - ponteiro para a lista a ser destru�da.
*
*  $FV Valor retornado
*     LIS_CondRetOK             - se destruiu sem problemas.
*     LIS_CondRetListaNaoExiste - se a lista a ser destru�da n�o existir.
*
*  Assertivas de entradas esperadas - pLista != NULL.
*
*  Assertivas de saidas esperadas   - CondRetOk => pLista == NULL.
*									  CondRetListaNaoExiste => pLista == NULL.
*
***********************************************************************/

   LIS_tpCondRet LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada.
*
*  $FV Valor retornado
*     LIS_CondRetOK             - se esvaziou sem problemas.
*     LIS_CondRetListaNaoExiste - se a lista a ser esvaziada n�o existir.
*
*  Assertivas de entradas esperadas - pLista != NULL.
*
*  Assertivas de saidas esperadas   - CondRetOk => pLista != NULL.
*									  pLista->pOrigemLista == NULL ;
*                                     pLista->pFimLista == NULL ;
*                                     pLista->pElemCorr == NULL ;
*                                     pLista->numElem == 0 ;
*									  CondRetListaNaoExiste => pLista == NULL.
*
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento.
*     pValor - ponteiro para o valor do novo elemento.
*              Pode ser NULL.
*
*  $FV Valor retornado
*     LIS_CondRetOK            - se inseriu o elemento sem problemas.
*     LIS_CondRetFaltouMemoria - se faltou mem�ria para a aloca��o do
*                                elemento a ser inserido.
*
*  Assertivas de entradas esperadas - pLista != NULL.
*									  pValor != NULL.
*
*  Assertivas de saidas esperadas   - pValor ser� alocado no elemento antes.
*									  CondRetFaltouMemoria => pLista n�o altera.
*
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor         
										   #ifdef _DEBUG
											,
											char tipoElemento
											#endif
											) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento.
*        pValor - ponteiro para o valor do novo elemento.
*                 Pode ser NULL.
*           
*
*  $FV Valor retornado
*     LIS_CondRetOK            - se inseriu o elemento sem problemas.
*     LIS_CondRetFaltouMemoria - se faltou mem�ria para a aloca��o do
*                                elemento a ser inserido.
*
*  Assertivas de entradas esperadas - pLista != NULL.
*									  pValor != NULL.
*
*  Assertivas de saidas esperadas   - pValor ser� alocado no elemento ap�s.
*									  CondRetFaltouMemoria => pLista n�o altera.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor         
										  #ifdef _DEBUG
										  ,
										  char tipoElemento
										  #endif
										  ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento � esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se excluiu o elemento sem problemas.
*     LIS_CondRetListaVazia - se a lista cujo elemento deveria ser exclu�do
*                             estiver vazia.
*
*  Assertivas de entradas esperadas - pLista != NULL.									  
*
*  Assertivas de saidas esperadas   - Elemento corrente ter� sido excluido e ter�
*                                     um novo elemento corrente, pelas regras explicadas
*                                     na descri��o da fun��o.
*                                     CondRetListaVazia => pLista n�o altera.
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*     pValor - ponteiro que receber� a refer�ncia para o valor contido
*              no elemento.
*
*  $FV Valor retornado
*     LST_CondRetOK             - se o valor foi passado por referencia sem problemas.
*     LST_CondRetListaNaoExiste - se a lista passada para a fun��o n�o existir.
*     LST_CondRetListaVazia     - se a lista passada para a fun��o estiver vazia.
*
*  Assertivas de entradas esperadas - pLista != NULL.									  
*
*  Assertivas de saidas esperadas   - pLista n�o altera.
*                                     pValor ir� receber o valor do elemento corrente
*                                     CondRetListaNaoExiste => pLista == NULL.
*                                     CondRetListaVazia => pLista n�o ir� alterar.
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista,
	                             void ** pValor         ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular.
*
*  $FV Valor retornado
*     LST_CondRetOK             - se foi para o in�cio sem problemas.
*     LST_CondRetListaNaoExiste - se a lista passada para a fun��o n�o existir.
*	  LST_CondRetListaVazia     - se a lista passada para a fun��o estiver vazia.
*
*  Assertivas de entradas esperadas - pLista != NULL.									  
*
*  Assertivas de saidas esperadas   - CondRetOk => elemento corrente de pLista passar�
*                                     a ser o elemento de origem da lista.
*                                     CondRetListaNaoExiste => pLista == NULL.
*                                     CondRetListaVazia => pLista n�o ir� alterar.
*
***********************************************************************/

   LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*     LST_CondRetOK             - se foi para o final sem problemas.
*     LST_CondRetListaNaoExiste - se a lista passada para a fun��o n�o existir.
*	  LST_CondRetListaVazia     - se a lista passada para a fun��o estiver vazia.
*
*  Assertivas de entradas esperadas - pLista != NULL.									  
*
*  Assertivas de saidas esperadas   - CondRetOk => elemento corrente de pLista passar�
*                                     a ser o elemento de fim da lista.
*                                     CondRetListaNaoExiste => pLista == NULL.
*                                     CondRetListaVazia => pLista n�o ir� alterar.
*
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*     dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada.
*     numElem - o n�mero de elementos a andar.
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados.
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos.
*     CondRetListaVazia - se a lista passada para a fun��o estiver vazia.
*
*  Assertivas de entradas esperadas - pLista != NULL.	
*									  numElem � inteiro positivo.
*
*  Assertivas de saidas esperadas   - CondRetOk => elemento corrente de pLista passar�
*                                     a ser o elemento numElem a frente do corrente.
*                                     CondRetListaVazia => pLista n�o ir� alterar.
*                                     CondRetFimLista => elemento corrente de pLista passar�
*                                     a ser o elemento de fim da lista.
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem           ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK           - se encontrou.
*                               O elemento corrente � o primeiro elemento do
*                               elemento corrente inclusive para o fim da lista
*                               e que cont�m o ponteiro procurado
*     LIS_CondRetNaoEncontrou - se o ponteiro n�o foi encontrado
*                               O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista passada para a fun��o estiver vazia.
*
*  Assertivas de entradas esperadas - pLista != NULL.	
*									  pVoid != NULL.
*
*  Assertivas de saidas esperadas   - CondRetOk => elemento corrente de pLista passar�
*                                     a ser o o elemento procurado.
*                                     CondRetListaVazia => pLista n�o ir� alterar.
*                                     CondRetNaoAchou => pLista n�o ir� alterar.
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor         ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Alterar valor de um elemento
*
*  $ED Descri��o da fun��o
*     Altera o valor do elemento corrente.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista cujo elemento ser� alterado.
*     pValor  - ponteiro para o Valor a ser inserido no lugar do
*               valor anterior.
*
*  $FV Valor retornado
*     LIS_CondRetOK               - se o valor for alterado sem problemas.
*     LIS_CondRetListaNaoExiste   - se a lista passada para a fun��o n�o existir.
*     LIS_CondRetListaVazia       - se a lista passada para a fun��o estiver vazia.
*
*  Assertivas de saidas esperadas   - CondRetOk => elemento corrente de pLista passar�
*                                     a ser a ser pValor.
*                                     LIS_CondRetListaNaoExiste => pLista == NULL.
*                                     CondRetListaVazia => pLista n�o ir� alterar.
*
***********************************************************************/

      LIS_tpCondRet LIS_AlterarValor( LIS_tppLista pLista,
	                               void * pValor          
		#ifdef _DEBUG
				,char tipoElemento
		#endif
		);
#ifdef _DEBUG

/***********************************************************************
*
*  $FC Fun��o: LIS Liberar n� corrente.
*
*  $EP Par�metros
*     pLista - lista que deseja liberar o n�.
*
*  $ED Descri��o da fun��o
*     Libera o ponteiro para o n� corrente.
*     No modo DEBUG recebe um caracter para indicar o tipo de elemento.
*
*  $FV Valor retornado
*     LST_CondRetOK
*     LST_CondRetListaInexistente
*	  LST_CondRetListaVazia
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*   O ponteiro corrente aponta para o n� a ser excluido
*
*  $AS Assertivas de Sa�da
*	Caso a lista seja v�lida, o n� foi excluido e o ponteiro corrente aponta
*	para o pr�ximo n� ou NULL caso a lista tenha acado.
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
***********************************************************************/

	LIS_tpCondRet LIS_LiberarNoCorrente( LIS_tppLista pLista );

/***********************************************************************
*
*  $FC Fun��o: LIS Altera Ponteiro Sucessor.
*
*  $EP Par�metros
*     pLista - lista que deseja alterar.
*     ponteiro - ponteiro do tipo void que deseja alterar
*
*  $ED Descri��o da fun��o
*	  Percorre a lista alterando o ponteiro sucessor do elemento dado.
*
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*   Ponteiro pode ser NULL ou v�lido.
*
*  $AS Assertivas de Sa�da
*	Lista estar� depurtada de acordo com o escolhido.
*
***********************************************************************/

   void LIS_AlteraPonteiroSucessor ( LIS_tppLista pLista , void *ponteiro );

/***********************************************************************
*
*  $FC Fun��o: LIS Altera Ponteiro Predecessor.
*
*  $EP Par�metros
*     pLista - lista que deseja alterar.
*     ponteiro - ponteiro do tipo void que deseja alterar
*
*  $ED Descri��o da fun��o
*	  Percorre a lista alterando o ponteiro predecessor do elemento dado.
*
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*   Ponteiro pode ser NULL ou v�lido.
*
*  $AS Assertivas de Sa�da
*	Lista estar� depurtada de acordo com o escolhido.
*
***********************************************************************/

   void LIS_AlteraPonteiroPredecessor ( LIS_tppLista pLista , void *ponteiro );

/***********************************************************************
*
*  $FC Fun��o: LIS Corrente NULL .
*
*  $EP Par�metros
*     pLista - lista que deseja alterar.
*
*  $ED Descri��o da fun��o
*	  Acessa a Lista definindo como Nulo o ponteiro para o no corrente.
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Sa�da
*	Ponteiro para n� corrente da lista � NULL.
*
***********************************************************************/

   void LIS_CorrenteNull ( LIS_tppLista pLista );

/***********************************************************************
*
*  $FC Fun��o: LIS Origem NULL .
*
*  $EP Par�metros
*     pLista - lista que deseja alterar.
*
*  $ED Descri��o da fun��o
*	  Acessa a Lista definindo como Nulo o ponteiro para o no origem.
*
*  $AE Assertivas de Entrada
*   Valem as assertivas estrururais da Lista Duplamente Encadeada.
*
*  $AS Assertivas de Sa�da
*	Ponteiro para n� origem da lista � NULL.
*
***********************************************************************/

   void LIS_OrigemNull ( LIS_tppLista pLista );


    int LIS_VerificaProxElemento ( LIS_tppLista pLista );
	int LIS_VerificaAntElemento ( LIS_tppLista pLista );
	int LIS_VerificaListaVazia ( LIS_tppLista pLista);
	int LIS_VerificaListaElemUnico ( LIS_tppLista pLista );
	int LIS_VerificaListaPreenchida ( LIS_tppLista pLista );
	int LIS_VerificaTipoElemento ( LIS_tppLista pLista, char TipoElemento );
	void LIS_AlteraTipoElemento ( LIS_tppLista pLista, char TipoElemento );
	int LIS_VerificaTamanho ( LIS_tppLista pLista, int tamanho);
	int LIS_VerificaElementoNULL ( LIS_tppLista pLista );
	void LIS_LixoSucessor ( LIS_tppLista pLista, int lixo );
	int LIS_VerificaDuplamenteEncadeada ( LIS_tppLista pLista );

#endif
#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif


