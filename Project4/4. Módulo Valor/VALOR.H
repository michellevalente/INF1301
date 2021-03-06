#if ! defined( VALOR_ )
#define VALOR_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: VAL  M�dulo Valor
*
*  Arquivo gerado:          	VALOR.H
*  Letras identificadoras:  	VAL
*
*  Nome da base de software:	Arcabou�o para a automa��o de testes de programas redigidos em C
*
*  Projeto: Trabalho 2 - Programa��o Modular
*  Autores: GB - Gustavo Bach
*       	JG - Jo�o Lucas Gardenberg
*       	MV - Michelle Valente
*
*  $HA Hist�rico de evolu��o:
*      Vers�o  Autor      Data          Observa��es
*      1.00    GB,JG,MV   28/mar/2014   in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*      Esse m�dulo implementa fun��es para criar e explorar a
*      estrutura Valor.
*      O Valor cont�m um inteiro com o n�mero de celulas que est�o
*      preenchidas e outro inteiro informando qual o estado
*      daquele valor, resolvido ou n�o.
*
***************************************************************************/
 
#if defined( VALOR_OWN )
   #define VALOR_EXT
#else
   #define VALOR_EXT extern
#endif

/* Tipo refer�ncia para um valor */

   typedef struct tgValor * ptValor ;

/***********************************************************************
*
*  $TC Tipo de dados: VAL Condi��es de retorno
*
*  $ED Descri��o do tipo
* 	Condi��es de retorno das fun��es do valor
*
***********************************************************************/

   typedef enum {

     	VAL_CondRetOK = 0,
           	/* Concluiu corretamente */

     	VAL_CondRetNaoAchou,
           	/* N�o encontrou o valor procurado */

     	VAL_CondRetFaltouMemoria,
           	/* Faltou mem�ria ao tentar criar um elemento de valor */

     	VAL_CondRetValorNaoExiste
           	/* Valor n�o existe */

   } VAL_tpCondRet ;

/***********************************************************************
*
*  $FC Fun��o: VAL  &Criar Valor
*
*  $ED Descri��o da fun��o
*      Cria um novo valor, com o n�mero de c�lulas enviado por par�metro
*      e o Estado inicializado como 0.
*
*  $EP Par�metros
*      pValor - ponteiro para o campo valor a ser criado
*      NumCel - n�mero de celulas.
*
*  $FV Valor retornado
*      VAL_CondRetOK        	- se criou sem problemas.
*      VAL_CondRetFaltouMemoria - se faltou mem�ria para alocar o espa�o do valor.
*
*  Assertivas de entradas esperadas - NumCel � um inteiro.
*
*  Assertivas de saidas esperadas   - CondRetOk => pValor != NULL.
*                                 	  pValor->Numcel ter� recebido valor de NumCel.
*                                 	  pValor->Estado ir� ter sido setado como 0.
*                                     CondRetFaltouMemoria => pValor == NULL.
*
***********************************************************************/

   VAL_tpCondRet VAL_CriarValor( ptValor * pValor, int NumCel ) ;

/***********************************************************************
*
*  $FC Fun��o: VAL  &Destruir Valor
*
*  $ED Descri��o da fun��o
*      Destroi o campo valor apontado pelo ponteiro.
*
*  $EP Par�metros
*      pValor - ponteiro para o campo valor a ser criado
*
*  $FV Valor retornado
*      VAL_CondRetOK - se destruiu sem problemas.
*
*  Assertivas de entradas esperadas - pValor != NULL.
*
*  Assertivas de saidas esperadas   - pValor == NULL.
*
***********************************************************************/

  VAL_tpCondRet VAL_DestruirValor( ptValor pValor ) ;

/***********************************************************************
*
*  $FC Fun��o: VAL  &Alterar NumCel
*
*  $ED Descri��o da fun��o
*      Altera o n�mero de celulas contido no valor.
*
*  $EP Par�metros
*      pValor - ponteiro para o campo valor a ser alterado
*      NumCel - n�mero de c�lulas novo.
*
*  $FV Valor retornado
*      VAL_CondRetOK         	 - se alterou sem problemas.
*      VAL_CondRetValorNaoExiste - se o valor a ser alterado n�o existir.
*
*  Assertivas de entradas esperadas - NumCel � um inteiro.
*                                 	  pValor != NULL.
*
*  Assertivas de saidas esperadas   - CondRetOk => pValor != NULL.
*                                 	  pValor->Numcel ter� recebido valor de NumCel.
*                                 	  pValor->Estado n�o � alterado.
*                                     VAL_CondRetValorNaoExiste => pValor == NULL.
*
***********************************************************************/

   VAL_tpCondRet VAL_AlterarNumCel( ptValor pValor, int NumCel ) ;

/***********************************************************************
*
*  $FC Fun��o: VAL  &Alterar Estado
*
*  $ED Descri��o da fun��o
*      Altera o estado corrente do valor.
*
*  $EP Par�metros
*      pValor - ponteiro para o campo valor a ser alterado
*      Estado - int contendo 0 ou 1, sendo 1 para valor resolvido e 0 para valor n�o resolvido.
*
*  $FV Valor retornado
*      VAL_CondRetOK             - se alterou sem problemas.
*      VAL_CondRetValorNaoExiste - se o valor a ser alterado n�o existir.
*
*  Assertivas de entradas esperadas - Estado � um inteiro.
*                                 	  pValor != NULL.
*
*  Assertivas de saidas esperadas   - CondRetOk => pValor != NULL.
*                                 	  pValor->Numcel n�o � alterado.
*                                 	  pValor->Estado ter� recebido valor de Estado.
*                                 	  VAL_CondRetValorNaoExiste => pValor == NULL.
*
***********************************************************************/

   VAL_tpCondRet VAL_AlterarEstado( ptValor pValor, int Estado ) ;

/***********************************************************************
*
*  $FC Fun��o: VAL  &Obter Estado
*
*  $ED Descri��o da fun��o
*      Obter o estado atual daquele valor, sendo 1 para resolvido e 0 para n�o resolvido.
*
*  $EP Par�metros
*      pValor - ponteiro para o campo valor
*      Estado - par�metro que receber� o estado contido no valor.
*           	Este par�metro � passado por refer�ncia.
*
*  $FV Valor retornado
*      VAL_CondRetOK         	- se obteve sem problemas.
*      VAL_CondRetValorNaoExiste - se o valor a ser utilizado n�o existir.
*
*  Assertivas de entradas esperadas - pValor != NULL.
*
*  Assertivas de saidas esperadas   - CondRetOk => pValor n�o � alterado.
*                                 	  Estado == pValor->Estado.
*                                 	  VAL_CondRetValorNaoExiste => pValor == NULL.
*
***********************************************************************/

   VAL_tpCondRet VAL_ObterEstado( ptValor pValor, int * Estado ) ;

/***********************************************************************
*
*  $FC Fun��o: VAL  &Obter NumCel
*
*  $ED Descri��o da fun��o
*      Obter o n�mero de c�lulas.
*
*  $EP Par�metros
*      pValor - ponteiro para o campo valor
*      NumCel - par�metro que receber� o n�mero de celulas contido no valor.
*           	Este par�metro � passado por refer�ncia.
*
*  $FV Valor retornado
*      VAL_CondRetOK             - se obteve sem problemas.
*      VAL_CondRetValorNaoExiste - se o valor a ser utilizado n�o existir.
*
*  Assertivas de entradas esperadas - pValor != NULL.
*
*  Assertivas de saidas esperadas   - CondRetOk => pValor n�o � alterado.    	
*                                 	  NumCel == pValor->NumCel.
*                                 	  VAL_CondRetValorNaoExiste => pValor == NULL.
*
***********************************************************************/

   VAL_tpCondRet VAL_ObterNumCel( ptValor pValor, int * NumCel ) ;

#undef VAL_EXT

/********** Fim do m�dulo de defini��o: VAL  M�dulo Valor **********/

#else
#endif
