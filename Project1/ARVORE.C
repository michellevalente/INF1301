/***************************************************************************
*  $MCI Módulo de implementação: Módulo árvore
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
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do nó da árvore
*
*
*  $ED Descrição do tipo
*     Descreve a organização do nó
*
***********************************************************************/

   typedef struct tgNoArvore {

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   É NULL sse o nó é raiz
               *   Se não for raiz, um de pNoEsq ou pNoDir de pNoPai do nó
               *   corrente apontam para o nó corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho à esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do nó X != NULL então pNoPai de pNoEsq aponta para o nó X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho à direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do nó X != NULL então pNoPai de pNoDir aponta para o nó X */
		 
		 struct tgNoArvore * pNoFolhaDir ;
		       /* Ponteiro para a folha à direita
			   *
			   *$EED Assertivas estruturais
			   *   É NULL se o nó não for folha, ou for a última folha (à direita)
			   *   Se o nó corrente for folha (tirando a última folha à direita),
			   *   pNoFolhaDir aponta para a próxima folha */
			   
		 char Valor ;
               /* Valor do nó */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabeça de uma árvore
*
*
*  $ED Descrição do tipo
*     A cabe‡a da árvore é o ponto de acesso para uma determinada árvore.
*     Por intermédio da referência para o nó corrente e do ponteiro
*     pai pode-se navegar a árvore sem necessitar de uma pilha.
*     Pode-se, inclusive, operar com a árvore em forma de co-rotina.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da árvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o nó corrente da árvore */

   } tpArvore ;

/*****  Dados encapsulados no módulo  *****/

	  static tpNoArvore * pFolhaAnt = NULL ;
	        /* Ponteiro para o nó cujo atributo pNoFolhaDir será apontado para
			a próxima folha  */
			
	  static tpNoArvore * pFolhaAtt = NULL ;
	        /* Ponteiro para o nó atual, para onde pNoFolhaDir de pFolhaAnt apontará */
			
	  static tpNoArvore * pFolhaFim = NULL ;
	        /* Ponteiro para a última folha da árvore (a mais à direita) */

/***** Protótipos das funções encapuladas no módulo *****/

   static tpNoArvore * CriarNo( char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( ptArvore * pArvore, char ValorParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

   static void CosturarNosFolha( tpNoArvore * pNo ) ;

   static void RemoverCostura( tpNoArvore * pNo ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: ARV Criar árvore
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

   } /* Fim função: ARV Criar árvore */

/***************************************************************************
*
*  Função: ARV Destruir árvore
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

   } /* Fim função: ARV Destruir árvore */

/***************************************************************************
*
*  Função: ARV Adicionar filho à esquerda
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

      /* Criar nó à esquerda de folha */

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

      /* Tratar não folha à esquerda */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à esquerda */

/***************************************************************************
*
*  Função: ARV Adicionar filho à direita
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

      /* Criar nó à direita de folha */

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

      /* Tratar não folha à direita */

         return ARV_CondRetNaoEhFolha ;

   } /* Fim função: ARV Adicionar filho à direita */

/***************************************************************************
*
*  Função: ARV Ir para nó pai
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

   } /* Fim função: ARV Ir para nó pai */

/***************************************************************************
*
*  Função: ARV Ir para nó à esquerda
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

   } /* Fim função: ARV Ir para nó à esquerda */

/***************************************************************************
*
*  Função: ARV Ir para nó à direita
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

   } /* Fim função: ARV Ir para nó à direita */

/***************************************************************************
*
*  Função: ARV Obter valor corrente
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

   } /* Fim função: ARV Obter valor corrente */

/***************************************************************************
*
*  Função: ARV Costurar nós folha
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

	  /* Chamar a função recursiva que costura os nós (encapsulada no módulo) */

	     CosturarNosFolha( (*pArvore)->pNoRaiz ) ;

	  /* Voltar as variáveis encapsuladas no módulo para os seus estados iniciais */

		 pFolhaAnt = NULL ;
		 pFolhaAtt = NULL ;

	  /* Retornar dizendo que executou corretamente */

		 return ARV_CondRetOK ;

   } /* Fim função: ARV Costurar nós folha */

/***************************************************************************
*
*  Função: ARV Imprimir nós folha
*  ****/

   ARV_tpCondRet ARV_ImprimirNosFolha( ptArvore * pArvore )
   {
      
	  tpNoArvore * pCorr ;
	        /* Ponteiro para o nó corrente da árvore */

	  if ( *pArvore == NULL )
	  {
         return ARV_CondRetArvoreNaoExiste ;
	  } /* if */
	  
	  if ( (*pArvore)->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

	  /* Fazer com que o nó corrente seja a raiz da árvore */

	     pCorr = (*pArvore)->pNoRaiz ;

	  /* Ir para a folha mais à esquerda */

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
	  
   } /* Fim função: ARV Imprimir nós folha */

/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: ARV Criar nó da árvore
*
*  $FV Valor retornado
*     Ponteiro para o nó criado.
*     Será NULL caso a memória tenha se esgotado.
*     Os ponteiros do nó criado estarão nulos e o valor é igual ao do
*     parâmetro.
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

   } /* Fim função: ARV Criar nó da árvore */


/***********************************************************************
*
*  $FC Função: ARV Criar nó raiz da árvore
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

   } /* Fim função: ARV Criar nó raiz da árvore */


/***********************************************************************
*
*  $FC Função: ARV Destruir a estrutura da árvore
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

   } /* Fim função: ARV Destruir a estrutura da árvore */

/***********************************************************************
*
*  $FC Função: ARV Costurar nós folha recursivamente
*
*  $EAE Assertivas de entradas esperadas
*     pNo != NULL  
*
***********************************************************************/

   void CosturarNosFolha( tpNoArvore * pNo )
   {

	   if(pNo != NULL)
	   {
		   /* Método Pós-Ordem de percorrer a árvore binária recursivamente */
		      
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

   } /* Fim função: ARV Costurar nós folha recursivamente */

/***********************************************************************
*
*  $FC Função: ARV Remover costura existente recursivamente
*
*  $EAE Assertivas de entradas esperadas
*      
*
***********************************************************************/

   void RemoverCostura( tpNoArvore * pNo )
   {

      if(pNo != NULL)
	  {
         /* Método Pós-Ordem de percorrer a árvore binária recursivamente */
            
			RemoverCostura( pNo->pNoDir ) ;
            RemoverCostura( pNo->pNoEsq ) ;

			if(pNo->pNoFolhaDir != NULL)
			{
				pNo->pNoFolhaDir = NULL ;
			} /* if */
	  }

   } /* Fim função: ARV Remover costura existente recursivamente */

/********** Fim do módulo de implementação: Módulo árvore **********/