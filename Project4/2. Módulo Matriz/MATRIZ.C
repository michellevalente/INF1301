/***************************************************************************
*  $MCI M�dulo de implementa��o: MAT  Matriz
*
*  Arquivo gerado:          	MATRIZ.c
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
***************************************************************************/

#include   <stdio.h>
#include   <string.h>
#include   <memory.h>
#include   <malloc.h>
#include   <assert.h>

#include "LISTA.H"

#define MATRIZ_OWN
#include "MATRIZ.H"
#undef MATRIZ_OWN

#ifdef _DEBUG
	#include "CESPDIN.H"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: MAT Matriz
*
*
***********************************************************************/

	typedef struct tgMatriz
	{

    	int Altura ;
           	/* N�mero de linhas da matriz */

    	int Largura ;
           	/* N�mero de colunas da matriz */

    	LIS_tppLista Matriz ;
           	/* Ponteiro para a lista de listas */

		#ifdef _DEBUG
		 char tipoElemento;
		#endif

	} tpMatriz ;

/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/

	static void InicializarMatriz( ptMatriz pMatriz ) ;

	static void DestruirElemento ( void * pValor ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: MAT  Criar matriz
*  ****/

	MAT_tpCondRet MAT_CriarMatriz( ptMatriz * pMatriz, int Altura, int Largura 

		#ifdef _DEBUG
		,
		 char tipoElemento
		#endif
	
		 )
	{
    	int IteradorAltura, IteradorLargura ;
    	LIS_tpCondRet CondRetLis ;

    	*pMatriz = ( tpMatriz * ) malloc( sizeof( tpMatriz ) ) ;
		if( *pMatriz == NULL )
    	{
        	return MAT_CondRetFaltouMemoria ;
    	} /* if */

    	InicializarMatriz( *pMatriz ) ;
	
    	CondRetLis = LIS_CriarLista ( &(*pMatriz)->Matriz, DestruirElemento 
															#ifdef _DEBUG
															,
															tipoElemento
															#endif
															) ;
    	if( CondRetLis == LIS_CondRetFaltouMemoria )
    	{
        	return MAT_CondRetFaltouMemoria ;
    	} /* if */

    	(*pMatriz)->Altura = Altura ;
    	(*pMatriz)->Largura = Largura ;
		(*pMatriz)->tipoElemento= tipoElemento;

    	for( IteradorAltura = 0 ; IteradorAltura < Altura ; IteradorAltura++ )
    	{
        	LIS_tppLista pLista = NULL ;

        	CondRetLis = LIS_CriarLista ( &pLista, DestruirElemento 
										#ifdef _DEBUG
										,
										 tipoElemento
										#endif
										 ) ;
        	if( CondRetLis == LIS_CondRetFaltouMemoria )
        	{
            	return MAT_CondRetFaltouMemoria ;
        	} /* if */

        	for( IteradorLargura = 0 ; IteradorLargura < Largura ; IteradorLargura++ )
        	{
            	CondRetLis = LIS_InserirElementoApos( pLista, NULL
													#ifdef _DEBUG
														,
													tipoElemento
													#endif
													) ;
            	if( CondRetLis == LIS_CondRetFaltouMemoria )
            	{
                	return MAT_CondRetFaltouMemoria ;
            	} /* if */
        	} /* for */

        	CondRetLis = LIS_InserirElementoApos( (*pMatriz)->Matriz, pLista
													#ifdef _DEBUG
														,
													tipoElemento
													#endif
													) ;
        	if( CondRetLis == LIS_CondRetFaltouMemoria )
        	{
            	return MAT_CondRetFaltouMemoria ;
        	} /* if */

        	LIS_IrInicioLista( pLista ) ;
    	} /* for */

    	LIS_IrInicioLista( (*pMatriz)->Matriz ) ;

#ifdef _DEBUG
		CED_MarcarEspacoAtivo(pMatriz);
#endif
    	return MAT_CondRetOK ;

	} /* Fim fun��o: MAT  Criar matriz */

/***************************************************************************
*
*  Fun��o: MAT  Destruir matriz
*  ****/

	MAT_tpCondRet MAT_DestruirMatriz( ptMatriz pMatriz )
	{

    	int IteradorAltura ;
    	LIS_tpCondRet CondRetLis ;

		if( pMatriz == NULL )
		{
			return MAT_CondRetMatrizNaoExiste ;
		} /* if */

		if( pMatriz->Matriz == NULL )
		{
			return MAT_CondRetMatrizVazia ;
		} /* if */

    	for( IteradorAltura = 0 ; IteradorAltura < pMatriz->Altura ; IteradorAltura++ )
    	{
        	void * pLista;

        	CondRetLis = LIS_IrFinalLista( pMatriz->Matriz ) ;
        	if( CondRetLis == LIS_CondRetListaNaoExiste )
        	{
            	return MAT_CondRetMatrizNaoExiste ;
        	} /* if */

        	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pLista ) ;
        	if( CondRetLis == LIS_CondRetListaNaoExiste )
        	{
            	return MAT_CondRetMatrizNaoExiste ;
        	} /* if */

        	CondRetLis = LIS_DestruirLista( ( LIS_tppLista ) pLista ) ;
        	if( CondRetLis == LIS_CondRetListaNaoExiste )
        	{
            	return MAT_CondRetMatrizNaoExiste ;
        	} /* if */

        	LIS_ExcluirElemento( pMatriz->Matriz ) ;
    	} /* for */

    	CondRetLis = LIS_DestruirLista( pMatriz->Matriz ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} /* if */

#ifdef _DEBUG
		CED_MarcarEspacoNaoAtivo(pMatriz);
#endif
    	return MAT_CondRetOK ;

	} /* Fim fun��o: MAT  Destruir matriz */

/***************************************************************************
*
*  Fun��o: MAT  Inserir valor no elemento
*  ****/

	MAT_tpCondRet MAT_InserirValor( ptMatriz pMatriz, void * pElemento, int Linha , int Coluna
									#ifdef _DEBUG
									 ,
									char tipoElemento
									#endif
									) 
	{


    	void * pValor ;
    	LIS_tppLista pLista ;
    	LIS_tpCondRet CondRetLis ;

		if( pMatriz == NULL )
		{
			return MAT_CondRetMatrizNaoExiste ;
		} /* if */

		if( pMatriz->Matriz == NULL )
		{
			return MAT_CondRetMatrizVazia ;
		} /* if */

    	CondRetLis = LIS_IrInicioLista( pMatriz->Matriz ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	CondRetLis = LIS_AvancarElementoCorrente( pMatriz->Matriz, Linha-1 ) ;
    	if ( CondRetLis == LIS_CondRetListaVazia )
    	{
        	return MAT_CondRetMatrizVazia ;
    	} else if ( CondRetLis == LIS_CondRetFimLista ) {
        	return MAT_CondRetFimLinhas ;
    	} /* if */

    	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	pLista = (LIS_tppLista) pValor ;

    	CondRetLis = LIS_IrInicioLista( pLista ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	CondRetLis = LIS_AvancarElementoCorrente( pLista, Coluna-1 ) ;
    	if ( CondRetLis == LIS_CondRetListaVazia )
    	{
        	return MAT_CondRetMatrizVazia ;
    	} else if ( CondRetLis == LIS_CondRetFimLista ) {
        	return MAT_CondRetFimColunas ;
    	} /* if */

    	CondRetLis = LIS_AlterarValor( pLista, pElemento
										#ifdef _DEBUG
										 ,
										tipoElemento
										#endif
										) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	CondRetLis = LIS_IrInicioLista( pLista ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	CondRetLis = LIS_IrInicioLista( pMatriz->Matriz ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	return MAT_CondRetOK ;

	} /* Fim fun��o: MAT  Inserir valor no elemento */

/***************************************************************************
*
*  Fun��o: MAT  Obter valor do elemento
*  ****/

	MAT_tpCondRet MAT_ObterValor( ptMatriz pMatriz, int Linha, int Coluna, void ** pValor )
	{

    	void * pValorObtido ;
    	LIS_tppLista pLista ;
    	LIS_tpCondRet CondRetLis ;

		if( pMatriz == NULL )
		{
			return MAT_CondRetMatrizNaoExiste ;
		} /* if */

		if( pMatriz->Matriz == NULL )
		{
			return MAT_CondRetMatrizVazia ;
		} /* if */

    	CondRetLis = LIS_IrInicioLista( pMatriz->Matriz ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	CondRetLis = LIS_AvancarElementoCorrente( pMatriz->Matriz, Linha-1 ) ;
    	if ( CondRetLis == LIS_CondRetListaVazia )
    	{
        	return MAT_CondRetMatrizVazia ;
    	} else if ( CondRetLis == LIS_CondRetFimLista ) {
        	return MAT_CondRetFimLinhas ;
    	} /* if */

    	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	pLista = ( LIS_tppLista ) pValorObtido ;

    	CondRetLis = LIS_IrInicioLista( pLista ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	CondRetLis = LIS_AvancarElementoCorrente( pLista, Coluna-1 ) ;
    	if ( CondRetLis == LIS_CondRetListaVazia )
    	{
        	return MAT_CondRetMatrizVazia ;
    	} else if ( CondRetLis == LIS_CondRetFimLista ) {
        	return MAT_CondRetFimColunas ;
    	} /* if */

    	CondRetLis = LIS_ObterValor( pLista, pValor ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	CondRetLis = LIS_IrInicioLista( pLista ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	CondRetLis = LIS_IrInicioLista( pMatriz->Matriz ) ;
    	if( CondRetLis == LIS_CondRetListaNaoExiste )
    	{
        	return MAT_CondRetMatrizNaoExiste ;
    	} else if ( CondRetLis == LIS_CondRetListaVazia ) {
        	return MAT_CondRetMatrizVazia ;
    	} /* if */

    	return MAT_CondRetOK ;

	} /* Fim fun��o: MAT  Obter valor do elemento  */

/***************************************************************************
*
*  Fun��o: MAT  Obter Altura e Largura da Matriz
*  ****/

	MAT_tpCondRet MAT_ObterAlturaLargura ( ptMatriz pMatriz,
	                                      int * Altura,
										  int * Largura     )
	{

		if( pMatriz == NULL )
		{
			return MAT_CondRetMatrizNaoExiste ;
		} /* if */

		if( pMatriz->Matriz == NULL )
		{
			return MAT_CondRetMatrizVazia ;
		} /* if */

		*Altura = pMatriz->Altura ;
		*Largura = pMatriz->Largura ;

		return MAT_CondRetOK ;

	} /* Fim fun��o: MAT  Obter Altura e Largura da Matriz */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: MAT  Inicializar Matriz
*
*  $ED Descri��o da fun��o
* 	Inicializa a estrutura da matriz.
*
***********************************************************************/

	void InicializarMatriz( ptMatriz pMatriz )
	{

    	pMatriz->Altura = 0 ;

    	pMatriz->Altura = 0 ;

    	pMatriz->Matriz = NULL ;

	} /* Fim fun��o: MAT  Inicializar matriz */

/***********************************************************************
*
*  $FC Fun��o: MAT  Destruir elemento
*
*  $ED Descri��o da fun��o
* 	Fun��o de destruir elemento apontada pelo ponteiro para fun��o
* 	utilizado na fun��o LIS_CriarLista do m�dulo Lista.
*
***********************************************************************/

	void DestruirElemento ( void * pValor )
	{

    	if( pValor != NULL )
    	{
        	pValor = NULL ;
        	free(pValor) ;
    	} /* if */

	} /* Fim fun��o: MAT  Destruir elemento */

#ifdef _DEBUG
/***********************************************************************
*
*  $FC Fun��o: MAT Ir Para Inicio
*
***********************************************************************/

	void MAT_IrParaInicio( ptMatriz pMatriz)
{
	void * pValor ;
    LIS_tppLista pLista ;
    LIS_tpCondRet CondRetLis ;

	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	pLista = (LIS_tppLista) pValor ;
	CondRetLis = LIS_IrInicioLista( pLista ) ;
	CondRetLis = LIS_IrInicioLista( pMatriz->Matriz ) ;
}

/***********************************************************************
*
*  $FC Fun��o: MAT Ir Para Elemento
*
***********************************************************************/

	void MAT_IrParaElemento( ptMatriz pMatriz, int Linha, int Coluna)
{
	void * pValor ;
    LIS_tppLista pLista ;
    LIS_tpCondRet CondRetLis ;

	CondRetLis = LIS_IrInicioLista( pMatriz->Matriz ) ;
	CondRetLis = LIS_AvancarElementoCorrente( pMatriz->Matriz, Linha-1 ) ;
	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	pLista = (LIS_tppLista) pValor ;
	CondRetLis = LIS_IrInicioLista( pLista ) ;
	CondRetLis = LIS_AvancarElementoCorrente( pLista, Coluna-1 ) ;

}

/***********************************************************************
*
*  $FC Fun��o: MAT Altera Ponteiro Sucessor
*
***********************************************************************/

	void MAT_AlteraPonteiroSucessor( ptMatriz pMatriz, int linha, int coluna, void* elem )
{
	void * pValorObtido ;
	LIS_tppLista pLista = NULL;
    LIS_tpCondRet CondRetLis ;
	CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	pLista = ( LIS_tppLista ) pValorObtido ;
	CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);

	LIS_AlteraPonteiroSucessor( pLista, elem );

	MAT_IrParaInicio( pMatriz);
} /* Fim fun��o: MAT Altera Ponteiro Sucessor */

/***********************************************************************
*
*  $FC Fun��o: MAT Libera N� Corrente
*
***********************************************************************/

	void MAT_LiberaElementoCorrente( ptMatriz pMatriz, int linha, int coluna)
{
	void * pValorObtido ;
	LIS_tppLista pLista = NULL;
    LIS_tpCondRet CondRetLis ;
	CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	pLista = ( LIS_tppLista ) pValorObtido ;
	CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);

	LIS_LiberarNoCorrente( pLista);
	MAT_IrParaInicio( pMatriz);
} /* Fim fun��o: MAT  Libera N� Corrente */

/***********************************************************************
*
*  $FC Fun��o: MAT Altera Ponteiro Predecessor
*
***********************************************************************/

	void MAT_AlteraPonteiroPredecessor( ptMatriz pMatriz, int linha, int coluna, void* elem )
{
	void * pValorObtido ;
	LIS_tppLista pLista = NULL;
    LIS_tpCondRet CondRetLis ;
	CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	pLista = ( LIS_tppLista ) pValorObtido ;
	CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);
	LIS_AlteraPonteiroPredecessor( pLista, elem );
	MAT_IrParaInicio( pMatriz);
} /* Fim fun��o: MAT Altera Ponteiro Predecessor */

/***********************************************************************
*
*  $FC Fun��o: MAT Altera Celula
*
***********************************************************************/

	MAT_tpCondRet MAT_AlteraCelula(  ptMatriz pMatriz, void* elem, int linha, int coluna,char tipoElemento )
{
	void * pValorObtido ;
	LIS_tppLista pLista = NULL;
    LIS_tpCondRet CondRetLis ;
	CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	pLista = ( LIS_tppLista ) pValorObtido ;
	CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);
	LIS_AlteraTipoElemento(pLista,tipoElemento);
	MAT_IrParaInicio( pMatriz);
} /* Fim fun��o: MAT Altera Celula */

/***********************************************************************
*
*  $FC Fun��o: MAT Destaca Celula
*
***********************************************************************/

	void MAT_DestacaCelula(  ptMatriz pMatriz, int linha, int coluna )
{
	void * pValorObtido ;
	LIS_tppLista pLista = NULL;
    LIS_tpCondRet CondRetLis ;
	CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	pLista = ( LIS_tppLista ) pValorObtido ;
	CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);
	LIS_LiberarNoCorrente( pLista);
	MAT_IrParaInicio( pMatriz);
} /* Fim fun��o: MAT Destaca Celula */

/***********************************************************************
*
*  $FC Fun��o: MAT Corrente NULL
*
***********************************************************************/

	void MAT_CorrenteNULL(  ptMatriz pMatriz, int linha, int coluna )
{
	void * pValor ;
    LIS_tppLista pLista ;
    LIS_tpCondRet CondRetLis ;
	void * pValorObtido ;

	CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	pLista = ( LIS_tppLista ) pValorObtido ;
	CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);
	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	pLista = (LIS_tppLista) pValor ;
	LIS_CorrenteNull ( pLista );
	MAT_IrParaInicio( pMatriz);
} /* Fim fun��o: MAT Corrente NULL */

/***********************************************************************
*
*  $FC Fun��o: MAT Origem NULL
*
***********************************************************************/

	void MAT_OrigemNULL(  ptMatriz pMatriz )
{
	void * pValor ;
    LIS_tppLista pLista ;
    LIS_tpCondRet CondRetLis ;
	CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	pLista = (LIS_tppLista) pValor ;
	LIS_OrigemNull ( pLista );
	MAT_IrParaInicio( pMatriz);
} /* Fim fun��o: MAT Origem NULL */

/***********************************************************************
*
*  $FC Fun��o: MAT Verifica Prox Elemento
*
***********************************************************************/

   int MAT_VerificaProxElemento ( ptMatriz pMatriz, int Linha, int Coluna )
   {
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;

	   void * pValorObtido ;

		CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,Linha-1);
		CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
		pLista = ( LIS_tppLista ) pValorObtido ;
		CondRetLis = LIS_AvancarElementoCorrente(pLista,Coluna-1);

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;
	
	   aux = LIS_VerificaProxElemento( pLista) ;
	   MAT_IrParaInicio( pMatriz);
	   return aux;

   }/* Fim fun��o: MAT Verifica Prox Elemento  */

/***********************************************************************
*
*  $FC Fun��o: MAT Verifica Ant Elemento
*
***********************************************************************/

   int MAT_VerificaAntElemento ( ptMatriz pMatriz, int Linha, int Coluna)
   {
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;

	  void * pValorObtido ;

	   CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,Linha-1);
	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	   pLista = ( LIS_tppLista ) pValorObtido ;
	   CondRetLis = LIS_AvancarElementoCorrente(pLista,Coluna-1);

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;
	   
	   aux = LIS_VerificaAntElemento( pLista) ;
	   MAT_IrParaInicio( pMatriz);

		return aux;
   }/* Fim fun��o: MAT  Verifica Ant Elemento  */

   /***********************************************************************
*
*  $FC Fun��o: MAT Verifica Lista Vazia
*
***********************************************************************/

   int MAT_VerificaListaVazia ( ptMatriz pMatriz, int linha, int coluna)
   {
	   
	   
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;

	   void * pValorObtido ;

	   CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	   pLista = ( LIS_tppLista ) pValorObtido ;
	   CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;
	
	   aux = LIS_VerificaListaVazia(pLista);
	   MAT_IrParaInicio( pMatriz);
	   return aux;
   }/* Fim fun��o: MAT  Verifica Lista Vazia  */

/***********************************************************************
*
*  $FC Fun��o: MAT Verifica Lista Elemento Unico
*
***********************************************************************/

   int MAT_VerificaListaElemUnico ( ptMatriz pMatriz, int linha, int coluna )
   {  
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;

	   void * pValorObtido ;

	   CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	   pLista = ( LIS_tppLista ) pValorObtido ;
	   CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;
	
	   aux = LIS_VerificaListaElemUnico( pLista);
	   MAT_IrParaInicio( pMatriz);
	   return aux;
   }/* Fim fun��o: MAT  Verifica Lista Elemento Unico  */

/***********************************************************************
*
*  $FC Fun��o: MAT Verifica Lista Preenchida
*
***********************************************************************/

   int MAT_VerificaListaPreenchida ( ptMatriz pMatriz, int linha, int coluna)
   {
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;

	   void * pValorObtido ;

	   CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	   pLista = ( LIS_tppLista ) pValorObtido ;
	   CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;
	
	   aux = LIS_VerificaListaPreenchida( pLista);
	   MAT_IrParaInicio( pMatriz);
	   return aux;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Fun��o: MAT Verifica Lista Preenchida
*
***********************************************************************/

   int MAT_VerificaTipoCelula ( ptMatriz pMatriz, int linha, int coluna)
   {
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;

	   void * pValorObtido ;

	   CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	   pLista = ( LIS_tppLista ) pValorObtido ;
	   CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;
	
	   aux = LIS_VerificaTipoElemento(pLista, pMatriz->tipoElemento);
	   MAT_IrParaInicio( pMatriz);
	   return aux;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Fun��o: MAT Verifica Tamanho Linhas
*
***********************************************************************/

   int MAT_VerificaTamanhoListas ( ptMatriz pMatriz, int linha)
   {
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;

	   void * pValorObtido ;

	   CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	   pLista = ( LIS_tppLista ) pValorObtido ;

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;
	   aux = LIS_VerificaTamanho(pLista,pMatriz->Largura);
	   MAT_IrParaInicio( pMatriz);
	   return aux;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Fun��o: MAT Verifica Tamanho Linhas
*
***********************************************************************/

   int MAT_VerificaCelulaNULL ( ptMatriz pMatriz, int linha, int coluna)
   {
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;

	   void * pValorObtido ;

	   CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	   pLista = ( LIS_tppLista ) pValorObtido ;
	   CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;
	
	   aux = LIS_VerificaElementoNULL(pLista);
	   MAT_IrParaInicio( pMatriz);
	   return aux;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Fun��o: MAT Deturpa Celular NULL
*
***********************************************************************/

   void MAT_DeturpaCelulaNULL ( ptMatriz pMatriz, int linha, int coluna)
   {
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;

	   void * pValorObtido ;

	   CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	   pLista = ( LIS_tppLista ) pValorObtido ;
	   CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;

	 LIS_CorrenteNull(pLista);
	   MAT_IrParaInicio( pMatriz);
   }/* Fim fun��o: MAT  Deturpa Celula NULL  */

/***********************************************************************
*
*  $FC Fun��o: MAT Lixo Sucessor
*
***********************************************************************/

   void MAT_LixoSucessor ( ptMatriz pMatriz, int linha, int coluna)
   {
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;
	   int lixo = 1;

	   void * pValorObtido ;

	   CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	   pLista = ( LIS_tppLista ) pValorObtido ;
	   CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;

	   LIS_LixoSucessor(pLista, lixo);
	   MAT_IrParaInicio( pMatriz);
   }/* Fim fun��o: MAT  Deturpa Celula NULL  */

/***********************************************************************
*
*  $FC Fun��o: MAT Verifica Lista Duplamente Encadeada
*
***********************************************************************/

   int MAT_VerificaDuplamenteEncadeada ( ptMatriz pMatriz, int linha, int coluna)
   {
	   void * pValor ;
	   LIS_tppLista pLista ;
	   LIS_tpCondRet CondRetLis ;
	   int aux;

	   void * pValorObtido ;

	   CondRetLis = LIS_AvancarElementoCorrente(pMatriz->Matriz,linha-1);
	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValorObtido ) ;
	   pLista = ( LIS_tppLista ) pValorObtido ;
	   CondRetLis = LIS_AvancarElementoCorrente(pLista,coluna-1);

	   CondRetLis = LIS_ObterValor( pMatriz->Matriz, &pValor ) ;
	   pLista = (LIS_tppLista) pValor ;
	
	   aux = LIS_VerificaDuplamenteEncadeada(pLista);
	   MAT_IrParaInicio( pMatriz);
	   return aux;
   }/* Fim fun��o: LIS  Verifica Lista Preenchida  */

#endif
/********** Fim do m�dulo de implementa��o: MAT  Matriz **********/
