/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo �rvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*       3.00   avs   28/02/2003 Uniformiza��o da interface das fun��es e
*                               de todas as condi��es de retorno.
*       2.00   avs   03/08/2002 Elimina��o de c�digo duplicado, reestrutura��o
*       1.00   avs   15/08/2001 In�cio do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do n� da �rvore
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   � NULL sse o n� � raiz
               *   Se n�o for raiz, um de pNoEsq ou pNoDir de pNoPai do n�
               *   corrente apontam para o n� corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho � esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do n� X != NULL ent�o pNoPai de pNoEsq aponta para o n� X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho � direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do n� X != NULL ent�o pNoPai de pNoDir aponta para o n� X */
		 
		 struct tgNoArvore * pNoFolhaDir ;
		       /* Ponteiro para a folha � direita
			   *
			   *$EED Assertivas estruturais
			   *   � NULL se o n� n�o for folha, ou for a �ltima folha (� direita)
			   *   Se o n� corrente for folha (tirando a �ltima folha � direita),
			   *   pNoFolhaDir aponta para a pr�xima folha */
			   
		 char Valor ;
               /* Valor do n� */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabe�a de uma �rvore
*
*
*  $ED Descri��o do tipo
*     A cabe�a da �rvore � o ponto de acesso para uma determinada �rvore.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a �rvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a �rvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da �rvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o n� corrente da �rvore */

   } tpArvore ;

/*****  Dados encapsulados no m�dulo  *****/

	  static tpNoArvore * pFolhaAnt = NULL ;
	        /* Ponteiro para o n� cujo atributo pNoFolhaDir ser� apontado para
			a pr�xima folha  */
			
	  static tpNoArvore * pFolhaAtt = NULL ;
	        /* Ponteiro para o n� atual, para onde pNoFolhaDir de pFolhaAnt apontar� */
			
	  static tpNoArvore * pFolhaFim = NULL ;
	        /* Ponteiro para a �ltima folha da �rvore (a mais � direita) */

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static tpNoArvore * CriarNo( char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( ptArvore * pArvore, char ValorParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

   static void CosturarNosFolha( tpNoArvore * pNo ) ;

   static void RemoverCostura( tpNoArvore * pNo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: ARV Criar �rvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( ptArvore * pArvore )
   {

      if ( *pArvore != NULL )
      {
		  ARV_DestruirArvore( pArvore ) ;
      } /* if */

      (*pArvore) = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
	  
      if ( *pArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      (*pArvore)->pNoRaiz = NULL ;
      (*pArvore)->pNoCorr = NULL ;

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Criar �rvore */

/***************************************************************************
*
*  Fun��o: ARV Destruir �rvore
*  ****/

   void ARV_DestruirArvore( ptArvore * pArvore )
   {

      if ( *pArvore != NULL )
      {
         if ( (*pArvore)->pNoRaiz != NULL )
         {
            DestroiArvore( (*pArvore)->pNoRaiz ) ;
         } /* if */
		 
         free( *pArvore ) ;
         *pArvore = NULL ;
      } /* if */

   } /* Fim fun��o: ARV Destruir �rvore */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho � esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( ptArvore * pArvore, char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, esquerda */

         CondRet = CriarNoRaiz( pArvore, ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar n� � esquerda de folha */

         pCorr = (*pArvore)->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */
               
         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
			
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
			
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            (*pArvore)->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar n�o folha � esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV Adicionar filho � esquerda */

/***************************************************************************
*
*  Fun��o: ARV Adicionar filho � direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( ptArvore * pArvore, char ValorParm )
   {

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      /* Tratar vazio, direita */

         CondRet = CriarNoRaiz( pArvore, ValorParm ) ;
		 
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar n� � direita de folha */

         pCorr = (*pArvore)->pNoCorr ;
		 
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
			
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            (*pArvore)->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      /* Tratar n�o folha � direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV Adicionar filho � direita */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� pai
*  ****/

   ARV_tpCondRet ARV_IrPai( ptArvore * pArvore )
   {

      if ( *pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
	  
      if ( (*pArvore)->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( (*pArvore)->pNoCorr->pNoPai != NULL )
      {
         (*pArvore)->pNoCorr = (*pArvore)->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } else {
         return ARV_CondRetNohEhRaiz ;
      } /* if */

   } /* Fim fun��o: ARV Ir para n� pai */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� � esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( ptArvore * pArvore )
   {

      if ( *pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( (*pArvore)->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( (*pArvore)->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      (*pArvore)->pNoCorr = (*pArvore)->pNoCorr->pNoEsq ;
	  
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Ir para n� � esquerda */

/***************************************************************************
*
*  Fun��o: ARV Ir para n� � direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( ptArvore * pArvore )
   {

      if ( *pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      if ( (*pArvore)->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( (*pArvore)->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      (*pArvore)->pNoCorr = (*pArvore)->pNoCorr->pNoDir ;
	  
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Ir para n� � direita */

/***************************************************************************
*
*  Fun��o: ARV Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( ptArvore * pArvore, char * ValorParm )
   {

      if ( *pArvore == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */
	  
      if ( (*pArvore)->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */
	  
      * ValorParm = (*pArvore)->pNoCorr->Valor ;

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Obter valor corrente */

/***************************************************************************
*
*  Fun��o: ARV Costurar n�s folha
*  ****/

   ARV_tpCondRet ARV_CosturarNosFolha( ptArvore * pArvore )
   {

	  if ( *pArvore == NULL )
	  {
         return ARV_CondRetArvoreNaoExiste ;
	  } /* if */
	  
	  if ( (*pArvore)->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

	  /* Remover costura existente (se houver) */

	     RemoverCostura( (*pArvore)->pNoRaiz ) ;

	  /* Chamar a fun��o recursiva que costura os n�s (encapsulada no m�dulo) */

	     CosturarNosFolha( (*pArvore)->pNoRaiz ) ;

	  /* Voltar as vari�veis encapsuladas no m�dulo para os seus estados iniciais */

		 pFolhaAnt = NULL ;
		 pFolhaAtt = NULL ;

	  /* Retornar dizendo que executou corretamente */

		 return ARV_CondRetOK ;

   } /* Fim fun��o: ARV Costurar n�s folha */

/***************************************************************************
*
*  Fun��o: ARV Imprimir n�s folha
*  ****/

   ARV_tpCondRet ARV_ImprimirNosFolha( ptArvore * pArvore )
   {
      
	  tpNoArvore * pCorr ;
	        /* Ponteiro para o n� corrente da �rvore */

	  if ( *pArvore == NULL )
	  {
         return ARV_CondRetArvoreNaoExiste ;
	  } /* if */
	  
	  if ( (*pArvore)->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

	  /* Fazer com que o n� corrente seja a raiz da �rvore */

	     pCorr = (*pArvore)->pNoRaiz ;

	  /* Ir para a folha mais � esquerda */

		while( ( pCorr->pNoEsq != NULL ) || ( pCorr->pNoDir != NULL ) )
		{
			if( pCorr->pNoEsq == NULL )
			{
				pCorr = pCorr->pNoDir ;
			} else {
				pCorr = pCorr->pNoEsq ;
			} /* if */
		} /* while */

	  /* Imprimir as folhas da esquerda para a direita */

		printf(" -> ");
		
		while( pCorr->pNoFolhaDir != NULL )
		{
			printf("%c ", pCorr->Valor) ;
			pCorr = pCorr->pNoFolhaDir ;
		} /* while */

		printf("%c ", pCorr->Valor) ;
		pCorr = pCorr->pNoFolhaDir ;

	  /* Retornar dizendo que executou corretamente */

		return ARV_CondRetOK ;
	  
   } /* Fim fun��o: ARV Imprimir n�s folha */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� da �rvore
*
*  $FV Valor retornado
*     Ponteiro para o n� criado.
*     Ser� NULL caso a mem�ria tenha se esgotado.
*     Os ponteiros do n� criado estar�o nulos e o valor � igual ao do
*     par�metro.
*
***********************************************************************/

   tpNoArvore * CriarNo( char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
	  
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      pNo->pNoPai = NULL ;
      pNo->pNoEsq = NULL ;
      pNo->pNoDir = NULL ;
	  pNo->pNoFolhaDir = NULL ;
      pNo->Valor  = ValorParm ;
      return pNo ;

   } /* Fim fun��o: ARV Criar n� da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Criar n� raiz da �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( ptArvore * pArvore, char ValorParm )
   {

      ARV_tpCondRet CondRet ;
      tpNoArvore * pNo ;

      if ( *pArvore == NULL )
      {
         CondRet = ARV_CriarArvore( pArvore ) ;

         if ( CondRet != ARV_CondRetOK )
         {
            return CondRet ;
         } /* if */
      } /* if */

      if ( (*pArvore)->pNoRaiz == NULL )
      {
         pNo = CriarNo( ValorParm ) ;
		 
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
		 
         (*pArvore)->pNoRaiz = pNo ;
         (*pArvore)->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim fun��o: ARV Criar n� raiz da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV Destruir a estrutura da �rvore
*
*  $EAE Assertivas de entradas esperadas
*     pNo != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim fun��o: ARV Destruir a estrutura da �rvore */

/***********************************************************************
*
*  $FC Fun��o: ARV Costurar n�s folha recursivamente
*
*  $EAE Assertivas de entradas esperadas
*     pNo != NULL  
*
***********************************************************************/

   void CosturarNosFolha( tpNoArvore * pNo )
   {

	   if(pNo != NULL)
	   {
		   /* M�todo P�s-Ordem de percorrer a �rvore bin�ria recursivamente */
		      
			  CosturarNosFolha( pNo->pNoEsq ) ;
		      CosturarNosFolha( pNo->pNoDir ) ;

		      if( ( pNo->pNoEsq == NULL ) && ( pNo->pNoDir == NULL ) )
		      {
				  pFolhaAtt = pNo ;

			      if( pFolhaAnt != NULL )
			      {
				      pFolhaAnt->pNoFolhaDir = pFolhaAtt ;
			      } /* if */

			      pFolhaAnt = pNo ;
		      } /* if */
	   } /* if */

   } /* Fim fun��o: ARV Costurar n�s folha recursivamente */

/***********************************************************************
*
*  $FC Fun��o: ARV Remover costura existente recursivamente
*
*  $EAE Assertivas de entradas esperadas
*      
*
***********************************************************************/

   void RemoverCostura( tpNoArvore * pNo )
   {

      if(pNo != NULL)
	  {
         /* M�todo P�s-Ordem de percorrer a �rvore bin�ria recursivamente */
            
			RemoverCostura( pNo->pNoDir ) ;
            RemoverCostura( pNo->pNoEsq ) ;

			if(pNo->pNoFolhaDir != NULL)
			{
				pNo->pNoFolhaDir = NULL ;
			} /* if */
	  }

   } /* Fim fun��o: ARV Remover costura existente recursivamente */

/********** Fim do m�dulo de implementa��o: M�dulo �rvore **********/