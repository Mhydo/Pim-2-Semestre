#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

#define SIZE 10 

//Estrtura de dados de LOGIN
static struct {
	char usuario[15];
	char senha[4];
}login;
//Estrutura de dados para cadrastro de clientes
static struct {
	char cpf[12];
	char nome[30];
	char telefone[10];
}cliente;
//Estrutura de dados para cadastro de equipamentos
static struct {
	char cpf[12];
	char op[10];
	char nome[50];
	char descricao[100];
	char material_usado[100];
	float custo;
}equipamento[SIZE];

//DECLARAÇÃO DAS FUNÇOES
void menu_inicial(void);
void senha_admin(void);
void reseta_lista(void);
void cabecalho(void);
void entrada_usuario(void);
void entrada_cliente(void);
void entrada_equipamento(void);
void mostra_lista_clientes(void);
void pesquisa_cliente(void);
void pesquisa_equip(void);
void menu_funcionario(void);
void verifica_login(void);
void status_reparo(void);
void gera_relatorio(void);
void carrega_arquivos(void);


//Metodo principal
int main (void){
	setlocale(LC_ALL, "portuguese");
	
	menu_inicial();
	
	return 0;
}

//Cabeçalho do programa
void cabecalho(void){
	system("cls");
	printf("\t  _____________________________\n");
	printf("\t |         GAVITECH            |\n");
	printf("\t |  Assitência Especializada   |\n");
	printf("\t |_____________________________|\n\n");
}

//Função que cria arquivo, lê os dados de usuario e senha e grava no arquivo em seguida!
//Função para cadastro de novos usuarios no programa.
void entrada_usuario(void){
	system ("cls");
	system("mode con:cols=70 lines=30");
	cabecalho();
	printf("\n      -Acesso a criacao de usuario liberado-\n");
	
	FILE *arq;
	arq = fopen("logins.bin", "ab");
		
	if(arq == NULL){
		printf("Problema na criacao do arquivo!\n");
	}
	else{
		do{
			cabecalho();
			fflush(stdin);
			printf("\n      -Digite o nome de usuário (até 6 caracteres): ");
			fgets(login.usuario, 15, stdin);
			
			fflush(stdin);
			printf("      -Digite a Senha de seu login (4 numeros): ");
			fgets(login.senha,  5, stdin);
			
			fwrite(&login, sizeof(login), 1, arq);
			
			system("cls");
			printf("\t  _____________________________\n");
			printf("\t |                             |\n");
			printf("\t |  Login criado com sucesso!  |\n");
			printf("\t |_____________________________|\n\n");
			printf("      -DESEJA CADASTRAR OUTRO USUARIO? (s/n)\n");
			
			
			
		}while(getche() == 's' || getche() == 'S' );
		fclose(arq);
		menu_inicial();
	}
	
			
}
//Função que cria arquivo, lê os dados do cliente e grava no arquivo em seguida!
//Função para realização cadastro dos clientes.
void entrada_cliente(void){
	FILE *arq;
	arq = fopen("clientes.bin", "ab");
		
	if(arq == NULL){
		printf("Problema na criacao do arquivo!\n");
	}
	else{
		do{
			cabecalho();
			
			fflush(stdin);
			printf("\n\t  -Cpf: ");
			fgets(cliente.cpf, 12, stdin);
			
			fflush(stdin);
			printf("\n\t  -Nome: ");
			fgets(cliente.nome,  30, stdin);
			
			fflush(stdin);
			printf("\n\t  -Telefone: ");
			fgets(cliente.telefone,  10, stdin);
						
			fwrite(&cliente, sizeof(cliente), 1, arq);			
			printf("\n\t-DESEJA CADASTRAR OUTRO CLIENTE? (s/n)");
				
		}while(getche() == 's' || getche() == 'S');
		fclose(arq);
	}			
}
//Função que lê os dados do equipamento e grava no arquivo em seguida!
//Função para registrar novos equipamentos a serem consertados.
void entrada_equipamento(void){
	int i =0;
	FILE *arq;
	arq = fopen("dados_equipamentos.bin", "ab");
	
	if(arq == NULL){
		printf("Problema na criação do arquivo!\n");
	}
	else{
		do{
			system("mode con:cols=80 lines=30");
			cabecalho();
			
			fflush(stdin);
			printf("\n\t-Digite o número da ordem de pedido do equipamento: ");
			fgets(equipamento[i].op, 11, stdin);
			
			fflush(stdin);
			printf("\n\t-Digite o cpf do cliente dono do equipamento: ");
			fgets(equipamento[i].cpf, 12, stdin);
			
			fflush(stdin);
			printf("\n\t-Digite a marca e o nome/modelo do equipamento: ");
			fgets(equipamento[i].nome, 51, stdin);
			
			fflush(stdin);
			printf("\n\t-Descreva o problema: ");
			fgets(equipamento[i].descricao, 101, stdin);
			
			fflush(stdin);
			printf("\n\t-Descreva os materiais utilizados: ");
			fgets(equipamento[i].material_usado, 101, stdin);
			
			fflush(stdin);
			printf("\n\t-Digite o custo da manutenção: ");
			scanf("%f", &equipamento[i].custo);
			
			fwrite(&equipamento[i], sizeof(equipamento), 1 ,arq);
			printf("\n\n\t-Deseja cadastrar outro equipamento?(s/n)\n");
			i++;
			
		}while(getche()!= 'n' && i<SIZE);
		fclose(arq);		
	}
}

//Função para imprimir os dados do cliente gravados no arquivo!
//Função que mostra na tela uma lista de todos os dados de clientes ja registrados.
void mostra_lista_clientes(void){
	int c = 0;
	FILE *arq;
	arq = fopen("clientes.bin", "rb");
		
	if(arq == NULL){
		printf("Problema na leitura do arquivo!\n");
	}
	else{
		while(fread(&cliente, sizeof(cliente), 1, arq)){
			printf("CPF: %s", cliente.cpf);
			printf("\nNome: %s", cliente.nome);
			printf("Telefone: %s", cliente.telefone);			
			printf("\n--------------------------------\n");
			c++;
		}
	}
	printf("Numero total de clientes: %d\n", c);
	system("pause");
	fclose(arq);
}
//Função que realiza a leitura do arquivo e imprime dados na tela!
//Função para pesquisar clientes ja cadastrados a partir do CPF registrado.
void pesquisa_cliente(void){
	cabecalho();
	char cpf_cliente[12];
	
	FILE *arq;
	arq = fopen("clientes.bin", "rb");

	fflush((stdin));
	printf("\n  -Qual o cpf do cliente a ser consultado?: \n");
	fgets(cpf_cliente, 12, stdin);
			
	if(arq == NULL){
		printf("Problema na leitura do arquivo!\n");
	}
	else{
		while(fread(&cliente, sizeof(cliente), 1, arq) ==1){
			if(strcmp(cpf_cliente, cliente.cpf) == 0){
				printf("\n\t--------------------------------\n");
				printf("\t  -CPF: %s", cliente.cpf);
				printf("\n\t  -Nome: %s", cliente.nome);
				printf("\t  -Telefone: %s", cliente.telefone);
				printf("\n\t--------------------------------\n\n");
			}									
		}
	}
	fclose(arq);
	system("pause");
}

//Função para pesquisar equipamendo pelo número da ordem de pedido!
void pesquisa_equip(void){
	system("mode con:cols=70 lines=30");
	cabecalho();
	char op_procura[10];
	int i = 0;
	
	FILE *arq;
	arq = fopen("dados_equipamentos.bin", "rb");

	fflush((stdin));
	printf("\n\t-Qual o número da ordem de pedido?: ");
	fgets(op_procura, 11, stdin);
			
	if(arq == NULL){
		printf("Problema para ler o arquivo!\n");
	}else{
		while(fread(&equipamento[i], sizeof(equipamento), 1, arq) == 1){
			if(strcmp(op_procura, equipamento[i].op) == 0){
				printf("\n\t--------------------------------");
				printf("\n\t  -cliente: %s", equipamento[i].cpf);
				printf("\n\t  -Nome: %s", equipamento[i].nome);
				printf("\t  -Descricao do problema: %s", equipamento[i].descricao);
				printf("\t  -Materiais utilizados: %s", equipamento[i].material_usado);
				printf("\t  -Ordem de pedido: %s\n", equipamento[i].op);
				printf("\t  -Custo: %.2f", equipamento[i].custo);
				printf("\n\t--------------------------------\n\n");			
			}
			i++;									
		}
	}	
	fclose(arq);
	system("pause");
}

//Menu incial do programa.
void menu_inicial(void){
	
	int escolha;
	do{
		system("mode con:cols=50 lines=30");
		cabecalho();
		printf("\n\t-----------------------------\n");
		printf("\t      -MENU DE OPÇÕES-\n\n");
		printf("\t1 - Logar\n");
		printf("\t2 - Cadastrar usuario\n");  
		printf("\t3 - Sair do programa\n");
		printf("\n\t-----------------------------\n\n");
		
		printf("\t-Digite a opção desejada: ");
		fflush(stdin);
		scanf("%d", &escolha);
		cabecalho();
		
		switch(escolha){
			case 1: verifica_login();
				break;
			case 2: senha_admin();
				break;
			case 3: 
			 	exit(0);
		}		
	}while(escolha != 3);	
}
//Função que solicita senha de admin a partes do programa com acesso restrito.
void senha_admin(void){
	
	char adminkey[5] = "9999";
	char adminkey1[5];
	int cont;
	
	for(cont = 1; cont<=3; cont++ ){
		system("cls");
		system("mode con:cols=70 lines=30");
		cabecalho();
		printf("\n   -Senha do administrador solicitada,tentativa %d/3 :", cont);
		
		fflush(stdin);
		fgets(adminkey1, 5, stdin);
		
		
		if (strcmp(adminkey, adminkey1) == 0){
			entrada_usuario();	
			break;
		}
	}	
	
	printf("\t\nSenhas invalidas, retornando ao menu inicial!\n\n");
	system ("pause");
	menu_inicial();	
}

//Menu geral de opções.
void menu_funcionario(void){
	
	int escolha;
	do{
		system("mode con:cols=50 lines=30");
		cabecalho();
		printf("\n\t  -----------------------------\n");
		printf("\t        -MENU DE OPÇÕES\n");
		printf("\n\t  1 - Consultar cliente\n"); 
		printf("\t  2 - Cadastrar cliente\n"); 
		printf("\t  3 - Cadastrar equipamento\n");
		printf("\t  4 - Consultar equipamento\n");
		printf("\t  5 - Gerar relatório\n"); 
		printf("\t  6 - Sair do programa\n");
		printf("\n\t  -----------------------------\n");
		
		printf("\t   -Digite a opção desejada: ");
		fflush(stdin);
		scanf("%d", &escolha);
		cabecalho();
		
		switch(escolha){
			case 1: pesquisa_cliente(); 
				break;
			case 2: entrada_cliente();
				break;
			case 3: entrada_equipamento();
				break;
			case 4: pesquisa_equip();
				break;
			case 5: gera_relatorio();
				break;
			case 6:
			 	exit(0);
		}
	}while(escolha != 6);	
}
//Função que valida o login do usuario e libera o acesso caso validação OK. 
void verifica_login(void){	
	int logado =0;	
	char novo_login[10], nova_senha[5];
	system("mode con:cols=50 lines=30");
	cabecalho();
	
	FILE *arq;
	arq = fopen("logins.bin", "rb");

	if(arq == NULL){
		printf("Problema na leitura do arquivo!\n");
	}
	else{
		do{
			fflush((stdin));
			printf("\n\t  -Usuário: ");
			fgets(novo_login, 8, stdin);
			
			fflush((stdin));
			printf("\n\t  -Senha: ");
			fgets(nova_senha,  5, stdin);
			
			while(fread(&login, sizeof(login), 1, arq)){
				if(strcmp(novo_login, login.usuario) == 0 && strcmp(nova_senha, login.senha) == 0){
					cabecalho();
					menu_funcionario();
					logado = -1;
					break;
				} 
			}
			rewind(arq);
			if(!logado)
				printf("\n\t  -login inválido!Tente novamente\n");
		}while(!logado);
		}
	fclose(arq);
	getch();
}
//Função que gera relatório geral - mostra dados de equipamentos e total dos custos.
void gera_relatorio(void){
	FILE *arq1, *arq2;
	double total = 0;
	
	arq1 = fopen("relatorio.txt", "w");
	arq2 = fopen("dados_equipamentos.bin", "rb");
	
	if (arq2 == NULL || arq2 == NULL){
		printf("Problema em um dos arquivos!\n");
	}else{
		for(int i =0; i < SIZE; i++){
			fread(&equipamento[i], sizeof(equipamento), 1, arq2);
			if(strlen(equipamento[i].op) == 0) 
				break;
			else{
				fprintf(arq1,"Equipamento: %sDescricao: %sMateriais usados: %sOrdem de pedido: \n%sCliente: %sCusto: %.2f\n\n"
				, equipamento[i].nome, equipamento[i].descricao, equipamento[i].material_usado, equipamento[i].op, equipamento[i].cpf, equipamento[i].custo);
				total += equipamento[i].custo;
			}
		}	
		fprintf(arq1,"\nTotal: R$ %.2f", total);	
	}
	fclose(arq1);
	fclose(arq2);
	printf("\nRelatório gerado com sucesso!\n");
	system("pause");
}
