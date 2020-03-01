#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <conio2.h> // include "conio2.h"

#define N 64
#define M 100

// prot. functions
void cad_conta(); // menu >> cadastro
void log_conta(); // menu >> cadastro
void menu_conta(); // menu >> cadastro
void dep_conta(); // conta >> deposito
void saq_conta(); // conta >> saque
void ext_conta(); // conta >> extrato
void balance(int color); //

// structs
struct account{
	char nome[N];
	int cod; // cod. gerado automaticamente
	float deposito[M];
	float saque[M];	
	float soma;	
} acc;

/* 
	01 de março de 2020	
    Departamento de T.I., UniProjeção (Taguatinga, Campus I)
    
    Sistemas de Informação (3º semestre)
    Autor: Yan Almeida Garcia - 2019 199 05
    
	Criar uma conta bancária (utilizando structs):
		- deposito
		- saque
		- extrato
		- dados da conta
*/

// global vars.
	int x = 19, y = 4; // coordenadas
	int d, D, s, S; // controle de dados
	int i, j, k;
	char op;		

int main(){
	system("mode 76");
		
	cad_conta();
	
	return 0;
}

// functions
	// menu >> cadastro
void cad_conta(){
	system("title Bank Account - sign up");
	system("cls");
	
	bordas(20, 70, 2, 1);
	
	bordas(4, 36, x, y);
	
	movexy(x + 2, y + 2, " Name: ");
	gets(acc.nome);		
	fflush(stdin);
		// gerando senha para o cadastro
	srand(time(NULL));
	acc.cod = 1001 + (rand() % 4000);	
	Sleep(350);
	movexy(x + 2, y + 3, " Password: ");
	printf("%d", acc.cod);
	fflush(stdin);
	
	Sleep(900);
	textbackground(GREEN);
	textcolor(WHITE);
	movexy(x + 4, y + 5,  " Account has been registered! ");
	textbackground(NULL);
	textcolor(LIGHT_GRAY);
	
	getch();
	Sleep(350);
	log_conta();
}
	// menu >> login
void log_conta(){
	char name[N];
	int pass;
	
	system("title Bank Account - sign in");
	
	textcolor(LIGHT_GRAY);
	do{
		bordas(20, 70, 2, 1);
	
		system("cls");
	
		bordas(4, 36, x, y);
		
		movexy(x + 2, y + 2, " Name: ");
		gets(name);
		fflush(stdin);
		
		movexy(x + 2, y + 3, " Pass: ");
		scanf(" %d", &pass);
		fflush(stdin);
		
		if((strcmp(acc.nome, name) == 0) && (pass == acc.cod)){
			Sleep(450);
			menu_conta();
				
		}else{
			Sleep(900);
			textbackground(RED);
			textcolor(WHITE);
			movexy(x + 5, y + 5,  " ERROR: login or password! ");
			textbackground(NULL);
			textcolor(LIGHT_GRAY);
		} 
		
		getch();
	}while(1);		
}
	// menu >> menu geral 
void menu_conta(){
	int x = 26, y = 4;
	int posX = x + 3, posY = y + 2;
	
	system("cls");
	system("title Bank Account - menu");
	
	textcolor(LIGHT_GRAY);
	bordas(20, 70, 2, 1);
	bordas(5, 19, x , y);

	movexy(posX, posY + 0, " DEPOSIT CASH   ");
	movexy(posX, posY + 1, " LOOT CASH      ");
	movexy(posX, posY + 2, " BANK STATEMENT ");
	movexy(posX - 1 , posY, "O");
		
	do{
		op = getch();
		
		if(op == 72 && posY > 6){ // LIM 6
			movexy(posX - 1, posY, " ");  
			posY--;
			movexy(posX - 1, posY, "O");
			_beep(400, 100);
						
		}if(op == 80 && posY < 8){ // LIM 8
			movexy(posX - 1, posY, " ");
			posY++;
			movexy(posX - 1, posY, "O");
			_beep(420, 100);
		}
			// 'CASH DEPOSIT'	
		if(op == 13 && posY == 6) dep_conta();
			// 'LOOT CASH'	
		if(op == 13 && posY == 7) saq_conta();		
			// 'BANK STATEMENT'	
		if(op == 13 && posY == 8) ext_conta();
				
	}while(1);
}
	// conta >> deposito
void dep_conta(){	
	int x = 48, xx = 25;
	
	Sleep(350);
	system("title Bank Account - deposit");
	
	do{
		system("cls");
		textcolor(LIGHT_GRAY);
		bordas(20, 70, 2, 1);
		
		balance(GREEN);
		
		movexy(xx, 5, "New Deposit: ");
		scanf(" %f", &acc.deposito[d]);
		fflush(stdin);
	
		acc.soma += acc.deposito[d];
		
		balance(GREEN);
		
		if(acc.deposito[d] > 0){
			d++; // indice
			D++; // max
		}
			
		movexy(xx, 7, "BACK [1]: ");
		scanf(" %d", &k);
		fflush(stdin);
		
		if(k == 1) menu_conta();
	}while(1);
}
	// conta >> saque
void saq_conta(){
	int x = 48, xx = 25;
	
	Sleep(350);
	system("title Bank Account - loot");
	
	do{				
		if(acc.soma > 0){
			system("cls");
			textcolor(LIGHT_GRAY);
			bordas(20, 70, 2, 1);
			
			balance(GREEN);
			
			movexy(xx, 5, "New Loot: ");
			scanf(" %f", &acc.saque[s]);
			fflush(stdin);
			
			if(acc.saque[s] > acc.soma){
				system("title Bank Account - insufficient balance");
				
				textcolor(WHITE);
				textbackground(BLUE);
				movexy(xx - 4, 9, " Insufficient balance. ");
				movexy(xx - 4, 10, "  Try another amount!  ");
				textbackground(NULL);
			}else{
				system("title Bank Account - successful loot");
				system("cls");
				
				acc.soma -= acc.saque[s];
				
				textcolor(LIGHT_GRAY);
				bordas(20, 70, 2, 1);
							
				textbackground(NULL);
				textcolor(WHITE);
				movexy(xx, 5, "New Loot: ");
				printf("%.f", acc.saque[s]);
			
				balance(RED);	
				
				s++; // indice
				S++; // max
			}									
		}else{
			system("title Bank Account - do an deposit");
			system("cls");
			
			textcolor(LIGHT_GRAY);
			bordas(20, 70, 2, 1);
		
			textcolor(WHITE);
			textbackground(BLUE);
			movexy(28, 5, " Insufficient balance. ");
			movexy(28, 6, "    Do an deposit!     ");
			textbackground(NULL);
	
			getch();
			menu_conta();
		} 
		
		movexy(xx, 7, "BACK [1]: ");
		scanf(" %d", &k);
		fflush(stdin);
		if(k == 1) menu_conta();
	}while(1);
}
	// conta >> extrato
void ext_conta(){
	int x = 8;
	
	Sleep(350);
	system("title Bank Account - balance");
	
	system("cls");
	textcolor(LIGHT_GRAY);
	
	bordas(20, 70, 2, 1);
	
	textcolor(BLACK);
	textbackground(WHITE);
	movexy(42, 22, " Balance: $ ");
	printf("%.2f ", acc.soma);
	
	textcolor(WHITE);
	textbackground(GREEN);
	movexy(x, 3, " DEPOSIT CASH ");
		
	textcolor(BLACK);
	textbackground(WHITE);	
	for(d = 0; d < D; d++){
		gotoxy(x, 5 + d);
		printf(" Deposit [%d]: $ %.2f ", d + 1, acc.deposito[d]);	
	} 
	
	textcolor(WHITE);
	textbackground(RED);
	movexy(45, 3, " LOOT CASH");
	
	textcolor(BLACK);
	textbackground(WHITE);
	for(s = 0; s < S; s++){
		gotoxy(45, 5 + s);
		printf(" Loot [%d]: $ %.2f ", s + 1, acc.saque[s]);	
	} 
	textbackground(NULL);
	
	getch();
	Sleep(650);
	
	menu_conta();	
}
	//
void balance(int color){
	int x = 48;
	
	textcolor(WHITE);
	textbackground(color);
	movexy(x, 3, " Balance: $ ");
	printf("%.2f ", acc.soma);
	textbackground(NULL);
}
