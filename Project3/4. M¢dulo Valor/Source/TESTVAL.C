/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTVAL.C
*  Letras identificadoras:      TVAL
*
*  Nome da base de software:    Exemplo de teste automatizado
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
*      Este m�dulo cont�m as fun��es espec�ficas para o teste do
*      m�dulo valor.
*
*  $EIU Interface com o usu�rio pessoa
*      Comandos de teste espec�ficos para testar o m�dulo valor:
*
*     "=criar" <Int> <Int>
*                    - chama a fun��o VAL_CriarValor( ).
*                      Obs. nota��o: O 1o <Int> � o n�mero de c�lulas.
*                      Obs. nota��o: O 2o <Int> � a condi��o de retorno esperada.
*     "=altestado" <Int> <Int>
*                    - chama a fun��o VAL_AlterarEstado( ).
*                      Obs. nota��o: O 1o <Int> � o estado a ser alterado para.
*                      Obs. nota��o: O 2o <Int> � a condi��o de retorno esperada.
*     "=altnumcel" <Int> <Int>
*                    - chama a fun��o VAL_AlterarNumCel( ).
*                      Obs. nota��o: O 1o <Int> � o n�mero de c�lulas a ser alterado para.
*                      Obs. nota��o: O 2o <Int> � a condi��o de retorno esperada.
*     "=obterestado" <int> <Int>
*                    - chama a fun��o VAL_ObterEstado( ) e compara
*                      o valor retornado com o valor <int>.
*                      Obs. nota��o: O 1o <Int> � o estado esperado.
*                      Obs. nota��o: O 1o <Int> � a condi��o de retorno esperada.
*     "=obternumcel" <Int> <Int>
*                    - chama a fun��o VAL_ObterNumCel( ) e compara
*                      o valor retornado com o valor <int>.
*                      Obs. nota��o: O 1o <Int> � o n�mero de c�lulas esperado.
*                      Obs. nota��o: O 2o <Int> � a condi��o de retorno esperada.
*     "=destruir" <Int>
*                    - chama a fun��o VAL_DestruirValor( ).
*                      Obs. nota��o: O <Int> � a condi��o de retorno esperada.
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "VALOR.H"


/* Tabela dos nomes dos comandos de teste espec�ficos */

#define     CRIAR_VAL_CMD       "=criar"
#define     ALT_EST_CMD         "=altestado"
#define     ALT_NUMCEL_CMD      "=altnumcel"
#define     OBTER_EST_CMD       "=obterestado"
#define     OBTER_NUMCEL_CMD    "=obternumcel"
#define     DESTROI_VAL_CMD     "=destruir"

ptValor Valor ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TVAL Efetuar opera��es de teste espec�ficas para valor
*
*  $ED Descri��o da fun��o
*      Efetua os diversos comandos de teste espec�ficos para o m�dulo
*      valor sendo testado.
*
*  $EP Par�metros
*      $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*      Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      VAL_tpCondRet CondRetObtido   = VAL_CondRetOK ;
      VAL_tpCondRet CondRetEsperada = VAL_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */
      int ValorEsperado = -1  ;
      int ValorObtido   = 0 ;
      int ValorDado     = -1 ;
	  int NumCel = -1 ;
	  int Estado = -1 ;

      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

      /* Testar VAL Criar valor */

         if ( strcmp( ComandoTeste , CRIAR_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
							   &NumCel, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VAL_CriarValor( &Valor, NumCel ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar �rvore." ) ;

         } /* fim ativa: Testar ARV Criar �rvore */

      /* Testar VAL Destruir Valor */

         else if ( strcmp( ComandoTeste , DESTROI_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "i" ,
                              &CondRetEsperada ) ;

            if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VAL_DestruirValor( Valor ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir � direita." ) ;

         } /* fim ativa: Testar VAL Destruir Valor */

      /* Testar VAL Alterar Estado */

         else if ( strcmp( ComandoTeste , ALT_EST_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                              &Estado, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VAL_AlterarEstado( Valor, Estado ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir � direita." ) ;

         } /* fim ativa: Testar VAL Alterar Estado */

      /* Testar VAL Alterar N�mero de C�lulas */

         else if ( strcmp( ComandoTeste , ALT_NUMCEL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                              &NumCel, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VAL_AlterarNumCel( Valor, NumCel ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir � direita." ) ;

         } /* fim ativa: Testar VAL Alterar N�mero de C�lulas */

      /* Testar VAL Obter Estado */

         else if ( strcmp( ComandoTeste , OBTER_EST_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &ValorEsperado , &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VAL_ObterEstado( Valor , &ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." ) ;

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "Conte�do do n�mero de c�lulas est� errado." ) ;

         } /* fim ativa: Testar VAL Obter Estado */

      /* Testar VAL Obter N�mero de C�lulas */

         else if ( strcmp( ComandoTeste , OBTER_NUMCEL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &ValorEsperado , &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = VAL_ObterNumCel( Valor , &ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." ) ;

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararChar( ValorEsperado , ValorObtido ,
                                     "Conte�do do n�mero de c�lulas est� errado." ) ;

         } /* fim ativa: Testar VAL Obter N�mero de C�lulas */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TVAL Efetuar opera��es de teste espec�ficas para Valor */

/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

