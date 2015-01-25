/***************************************************************************
*  $MCI Módulo de implementação: MAT  Matriz
*
*  Arquivo gerado:          	MATRIZ.c
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
           	/* Número de linhas da matriz */

    	int Largura ;
           	/* Número de colunas da matriz */

    	LIS_tppLista Matriz ;
           	/* Ponteiro para a lista de listas */

		#ifdef _DEBUG
		 char tipoElemento;
		#endif

	} tpMatriz ;

/***** Protótipos das funções encapsuladas no módulo *****/

	static void InicializarMatriz( ptMatriz pMatriz ) ;

	static void DestruirElemento ( void * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT  Criar matriz
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

	} /* Fim função: MAT  Criar matriz */

/***************************************************************************
*
*  Função: MAT  Destruir matriz
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

	} /* Fim função: MAT  Destruir matriz */

/***************************************************************************
*
*  Função: MAT  Inserir valor no elemento
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

	} /* Fim função: MAT  Inserir valor no elemento */

/***************************************************************************
*
*  Função: MAT  Obter valor do elemento
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

	} /* Fim função: MAT  Obter valor do elemento  */

/***************************************************************************
*
*  Função: MAT  Obter Altura e Largura da Matriz
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

	} /* Fim função: MAT  Obter Altura e Largura da Matriz */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: MAT  Inicializar Matriz
*
*  $ED Descrição da função
* 	Inicializa a estrutura da matriz.
*
***********************************************************************/

	void InicializarMatriz( ptMatriz pMatriz )
	{

    	pMatriz->Altura = 0 ;

    	pMatriz->Altura = 0 ;

    	pMatriz->Matriz = NULL ;

	} /* Fim função: MAT  Inicializar matriz */

/***********************************************************************
*
*  $FC Função: MAT  Destruir elemento
*
*  $ED Descrição da função
* 	Função de destruir elemento apontada pelo ponteiro para função
* 	utilizado na função LIS_CriarLista do módulo Lista.
*
***********************************************************************/

	void DestruirElemento ( void * pValor )
	{

    	if( pValor != NULL )
    	{
        	pValor = NULL ;
        	free(pValor) ;
    	} /* if */

	} /* Fim função: MAT  Destruir elemento */

#ifdef _DEBUG
/***********************************************************************
*
*  $FC Função: MAT Ir Para Inicio
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
*  $FC Função: MAT Ir Para Elemento
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
*  $FC Função: MAT Altera Ponteiro Sucessor
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
} /* Fim função: MAT Altera Ponteiro Sucessor */

/***********************************************************************
*
*  $FC Função: MAT Libera Nó Corrente
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
} /* Fim função: MAT  Libera Nó Corrente */

/***********************************************************************
*
*  $FC Função: MAT Altera Ponteiro Predecessor
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
} /* Fim função: MAT Altera Ponteiro Predecessor */

/***********************************************************************
*
*  $FC Função: MAT Altera Celula
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
} /* Fim função: MAT Altera Celula */

/***********************************************************************
*
*  $FC Função: MAT Destaca Celula
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
} /* Fim função: MAT Destaca Celula */

/***********************************************************************
*
*  $FC Função: MAT Corrente NULL
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
} /* Fim função: MAT Corrente NULL */

/***********************************************************************
*
*  $FC Função: MAT Origem NULL
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
} /* Fim função: MAT Origem NULL */

/***********************************************************************
*
*  $FC Função: MAT Verifica Prox Elemento
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

   }/* Fim função: MAT Verifica Prox Elemento  */

/***********************************************************************
*
*  $FC Função: MAT Verifica Ant Elemento
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
   }/* Fim função: MAT  Verifica Ant Elemento  */

   /***********************************************************************
*
*  $FC Função: MAT Verifica Lista Vazia
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
   }/* Fim função: MAT  Verifica Lista Vazia  */

/***********************************************************************
*
*  $FC Função: MAT Verifica Lista Elemento Unico
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
   }/* Fim função: MAT  Verifica Lista Elemento Unico  */

/***********************************************************************
*
*  $FC Função: MAT Verifica Lista Preenchida
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
   }/* Fim função: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Função: MAT Verifica Lista Preenchida
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
   }/* Fim função: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Função: MAT Verifica Tamanho Linhas
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
   }/* Fim função: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Função: MAT Verifica Tamanho Linhas
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
   }/* Fim função: LIS  Verifica Lista Preenchida  */

/***********************************************************************
*
*  $FC Função: MAT Deturpa Celular NULL
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
   }/* Fim função: MAT  Deturpa Celula NULL  */

/***********************************************************************
*
*  $FC Função: MAT Lixo Sucessor
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
   }/* Fim função: MAT  Deturpa Celula NULL  */

/***********************************************************************
*
*  $FC Função: MAT Verifica Lista Duplamente Encadeada
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
   }/* Fim função: LIS  Verifica Lista Preenchida  */

#endif
/********** Fim do módulo de implementação: MAT  Matriz **********/
