/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:          	DESTMAT.C
*  Letras identificadoras:  	TDES
*
*  Nome da base de software:	Exemplo de teste automatizado
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
*  	Este módulo contém as funções específicas para o teste do
*  	módulo desenho. Ilustra como redigir um interpretador de comandos
*  	de teste específicos utilizando o arcabouço de teste para C.
*	 
*  $EIU Interface com o usuário pessoa
*  	Comandos de teste específicos para testar o módulo desenho:
*
* 	"=gerarmatriz" <Int> <Int> <Int>
*                	- chama a função DES_GerarMatriz( ).
*                  	Obs. notação: O 1o <Int> é a altura da matriz.
*                  	Obs. notação: O 2o <Int> é a largura da matriz.
*                  	Obs. notação: O 3o <Int> é a condição de retorno esperada.
* 	"=altestadocorreto" <Int> <Int> <Int>
*                	- chama a função DES_AlterarEstadoCorreto( ).
*                  	Obs. notação: O 1o <Int> é a linha onde o estado correto será alterado.
*                  	Obs. notação: O 2o <Int> é a coluna onde o estado correto será alterado.
*                  	Obs. notação: O 3o <Int> é a condição de retorno esperada.
* 	"=altestadoatual" <Int> <Int> <Int>
*                	- chama a função DES_AlterarEstadoAtual( ).
*                  	Obs. notação: O 1o <Int> é a linha onde o estado atual será alterado.
*                  	Obs. notação: O 2o <Int> é a coluna onde o estado atual será alterado.
*                  	Obs. notação: O 3o <Int> é a condição de retorno esperada.
* 	"=obterestadocorreto" <Int> <Int> <Int> <Int>
*                	- chama a função DES_ObterEstadoCorreto( ).
*                  	Obs. notação: O 1o <Int> é o estado correto esperado.
*                  	Obs. notação: O 2o <Int> é a linha onde o estado correto será obtido.
*                  	Obs. notação: O 3o <Int> é a coluna onde o estado correto será obtido.
*                  	Obs. notação: O 4o <Int> é a condição de retorno esperada.
* 	"=obterestadoatual" <Int> <Int> <Int> <Int>
*                	- chama a função DES_ObterEstadoAtual( ).
*                  	Obs. notação: O 1o <Int> é o estado atual esperado.
*                  	Obs. notação: O 2o <Int> é a linha onde o estado atual será obtido.
*                  	Obs. notação: O 3o <Int> é a coluna onde o estado atual será obtido.
*                  	Obs. notação: O 4o <Int> é a condição de retorno esperada.
* 	"=desenharatual" <Int>
*                	- chama a função DES_DesenharAtual( ).
*                  	Obs. notação: O <Int> é a condição de retorno esperada.
* 	"=desenharcorreto" <Int>
*                	- chama a função DES_DesenharCorreto( ).
*                  	Obs. notação: O <Int> é a condição de retorno esperada.
*
***************************************************************************/

#include	<string.h>
#include	<stdio.h>

#include	"TST_ESPC.H"

#include	"generico.h"
#include	"lerparm.h"

#include	"DESENHO.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define  	GERAR_MATRIZ_CMD        	"=gerarmatriz"
#define  	ALT_ESTADO_CORRETO_CMD  	"=altestadocorreto"
#define  	ALT_ESTADO_ATUAL_CMD    	"=altestadoatual"
#define  	OBT_ESTADO_CORRETO_CMD  	"=obterestadocorreto"
#define  	OBT_ESTADO_ATUAL_CMD    	"=obterestadoatual"
#define		DESENHAR_ATUAL_CMD			"=desenharatual"
#define		DESENHAR_CORRETO_CMD		"=desenharcorreto"


ptDesenho pDesenho;
int LinhaMatrizValores, ColunaMatrizValores ;


/***********************************************************************
*
*  $FC Função: TDES  Efetuar operações de teste específicas para desenho
*
*  $ED Descrição da função
*  	Efetua os diversos comandos de teste específicos para o módulo
*  	desenho sendo testado.
*
*  $EP Parâmetros
*  	$P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*  	Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

	TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
	{
    
    	DES_tpCondRet CondRetObtido   = DES_CondRetOK ;
    	DES_tpCondRet CondRetEsperada = DES_CondRetFaltouMemoria ;

    	int  NumLidos = -1 ;

   	 TST_tpCondRet Ret ;

    	/* Testar Gera Matriz */

        	if ( strcmp( ComandoTeste , GERAR_MATRIZ_CMD ) == 0 )
        	{
             	int Altura = -1, Largura = -1 ;
             	NumLidos = LER_LerParametros( "iii" ,
                                   	&Altura, &Largura, &CondRetEsperada ) ;

             	if ( NumLidos != 3 )
             	{
                	return TST_CondRetParm ;
             	} /* if */

             	CondRetObtido = DES_GerarMatrizes( &pDesenho, Altura, Largura ) ;

             	return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                        	"Retorno errado ao gerar matrizes." ) ;
        	} /* Fim Ativa: Testar Gera Matriz */
    
    	/* Testar Alterar Estado Correto */

        	else if ( strcmp( ComandoTeste , ALT_ESTADO_CORRETO_CMD ) == 0 )
        	{
             	int Linha = -1, Coluna = -1 ;
             	NumLidos = LER_LerParametros( "iii" ,
                                   	&Linha, &Coluna, &CondRetEsperada ) ;

             	if ( NumLidos != 3 )
             	{
                	return TST_CondRetParm ;
             	} /* if */

             	CondRetObtido = DES_AlterarEstadoCorreto( pDesenho, Linha, Coluna ) ;

             	return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                        	"Retorno errado ao alterar estado correto." ) ;
        	} /* Fim Ativa: Testar Alterar Estado Correto */

    	/* Testar Alterar Estado Atual */

        	else if ( strcmp( ComandoTeste , ALT_ESTADO_ATUAL_CMD ) == 0 )
        	{
             	int Linha = -1, Coluna = -1 ;
             	NumLidos = LER_LerParametros( "iii" ,
                                   	&Linha, &Coluna, &CondRetEsperada ) ;

             	if ( NumLidos != 3 )
             	{
                	return TST_CondRetParm ;
             	} /* if */

             	CondRetObtido = DES_AlterarEstadoAtual( pDesenho, Linha, Coluna ) ;

             	return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                        	"Retorno errado ao alterar estado atual." ) ;
        	} /* Fim Ativa: Testar Alterar Estado Atual */

    	/* Testar Obter Estado Correto */

        	else if ( strcmp( ComandoTeste , OBT_ESTADO_CORRETO_CMD ) == 0 )
        	{
   			 int Linha = -1, Coluna = -1, EstadoEsperado, EstadoObtido ;
   			 NumLidos = LER_LerParametros( "iiii", &EstadoEsperado,
   				               	&Linha, &Coluna, &CondRetEsperada ) ;

   			 if( NumLidos != 4 )
   			 {
   				 return TST_CondRetParm ;
   			 } /* if */

   			 CondRetObtido = DES_ObterEstadoCorreto( pDesenho, Linha, Coluna, &EstadoObtido ) ;

   			 Ret = TST_CompararInt( CondRetEsperada, CondRetObtido,
   				                	"Retorno errado ao obter estado correto." ) ;

   			 if( Ret != TST_CondRetOK || CondRetObtido != DES_CondRetOK )
   			 {
   				 return Ret ;
   			 } /* if */

   			 return TST_CompararInt( EstadoEsperado, EstadoObtido,
   				                      	"Valor errado do estado ao obter estado correto." ) ;
   		 } /* Fim Ativa: Testar Obter Estado Correto */

    	/* Testar Obter Estado Atual */

        	else if ( strcmp( ComandoTeste , OBT_ESTADO_ATUAL_CMD ) == 0 )
        	{
   			 int Linha = -1, Coluna = -1, EstadoEsperado, EstadoObtido ;
   			 NumLidos = LER_LerParametros( "iiii", &EstadoEsperado,
   				               	&Linha, &Coluna, &CondRetEsperada ) ;

   			 if( NumLidos != 4 )
   			 {
   				 return TST_CondRetParm ;
   			 } /* if */

   			 CondRetObtido = DES_ObterEstadoAtual( pDesenho, Linha, Coluna, &EstadoObtido ) ;

   			 Ret = TST_CompararInt( CondRetEsperada, CondRetObtido,
   				                	"Retorno errado ao obter estado atual." ) ;

   			 if( Ret != TST_CondRetOK || CondRetObtido != DES_CondRetOK )
   			 {
   				 return Ret ;
   			 } /* if */

   			 return TST_CompararInt( EstadoEsperado, EstadoObtido,
   				                      	"Valor errado do estado ao obter estado atual." ) ;
   		 } /* Fim Ativa: Testar Obter Estado Atual */

    	/* Testar Desenhar Atual */

        	else if ( strcmp( ComandoTeste , DESENHAR_ATUAL_CMD ) == 0 )
        	{
             	NumLidos = LER_LerParametros( "i" ,
                                   	&CondRetEsperada ) ;

             	if ( NumLidos != 1 )
             	{
                	return TST_CondRetParm ;
             	} /* if */

				printf("\n\n");
             	CondRetObtido = DES_DesenharAtual( pDesenho ) ;

             	return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                        	"Retorno errado ao fazer o desenho atual." ) ;
        	} /* Fim Ativa: Testar Desenhar Atual */

		/* Testar Desenhar Correto */

        	else if ( strcmp( ComandoTeste , DESENHAR_CORRETO_CMD ) == 0 )
        	{
             	NumLidos = LER_LerParametros( "i" ,
                                   	&CondRetEsperada ) ;

             	if ( NumLidos != 1 )
             	{
                	return TST_CondRetParm ;
             	} /* if */

				printf("\n\n");
             	CondRetObtido = DES_DesenharCorreto( pDesenho ) ;

             	return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                        	"Retorno errado ao fazer o desenho correto." ) ;
        	} /* Fim Ativa: Testar Desenhar Correto */

    	return TST_CondRetNaoConhec ;
   	 
	} /* Fim função: TMAT  Efetuar operações de teste específicas para matriz */

/********** Fim do módulo de implementação: Módulo de teste específico **********/
