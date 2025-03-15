#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include "Sound.h"

using namespace std;

int i=0,j,pz=0,cv=0,reipreto=0,reibranco=0;
char nome1[100]="Branco", nome2[100] = "Preto"; 
const char nomeBot[100] = "UltraT";
char captB[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}; 
char captP[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
char ax,ay,sx,sy,joestar;
int vez=2, real, feique,rbot;
bool xadrezNormal=1,rock, bot=0;

void resetar();
bool selecionado(int x, int y);
bool movimento(int ix, int iy, int mx, int my);

char tabuleiro[8][8]= {  {'L','E','X','K','Q','X','E','L'},
	                     {'s','s','s','s','s','s','s','s'},
	  					 {'-','-','-','-','-','-','-','-'},
						 {'-','-','-','-','-','-','-','-'},
						 {'-','-','-','-','-','-','-','-'},
						 {'-','-','-','-','-','-','-','-'},
						 {'p','p','p','p','p','p','p','p'},
						 {'T','C','B','R','D','B','C','T'}};

int main() {

	std::locale::global(std::locale("pt_BR.UTF-8"));

	system("MODE con:cols=34 lines=30");
	FILE *positivo;
	positivo = fopen("historico.txt","a");
	void menu();
	void biomecanico();
	
	comeco:
	system("cls || clear");	
	menu();
	
	if(bot == 1){
	for(i=0;i<100;i++)
	nome2[i] = nomeBot[i];
	}
	
	do{
		positivo = fopen("historico.txt","a");
	inicio:
		system("cls || clear");
	reibranco=0;
	reipreto=0;	
	if(vez % 2 == 0){
	cout<< "Vez de " << nome1<<"\n\n";
	}else{
	cout<< "Vez de " << nome2<<"\n\n";		
	}
	for(i=0; i<16; i++)
	printf("%c-",captB[i]);			
   cout<<"\n\n   0 1 2 3 4 5 6 7\n\n";
//impress�o do tabuleiro
	for(i=0;i<8;i++){
		cout<<i<<"  ";
	for(j=0;j<8;j++)
	printf("%c ",tabuleiro[i][j]);
	printf("\n");					
	}
	printf("\n");
	//Pe�as capturadas pelos brancos
	for(i=0; i<16; i++)
		cout<<captP[i]<<"-";
		
	//Caso tenha o bot:	
	if(vez % 2 != 0 && bot == 1){
		biomecanico();
	}
	else{
	//Escolher a��o
	cout<<"\n\n1)Movimentar\n8)Sair\n9)Desistir\n10)Empate\n";
	scanf("%i,%i",& real,& feique);
	if((int)real==8){
	goto comeco;
	// Desistir:
	} else if(real==9){
		printf("Tem certeza?\n\n1) Sim\n2) Não\n");
		scanf("%i",&feique);
		if(feique == 1){
			printf("Não aguentou a pressão\n\n");
			Sound::GetInstance()->desistencia();
			if(vez % 2 == 0){
				fprintf(positivo,"-1 %s x %s 1\n",nome1,nome2);
				fclose(positivo);
			} else {
				fprintf(positivo,"1 %s x %s -1\n",nome1,nome2);
				fclose(positivo);
			}
			
			fclose(positivo);
			system("pause");
			resetar();
			goto comeco;
		} else{
			goto inicio;
		}
		
	} else if(real == 10){
		//Empate:
	cout<<"Os dois concordam com isso?\n\n1)Sim\n2)Sin\'t\n";
	cin>>feique;
	if(feique == 1){
		printf("Então é isso\n");
		Sound::GetInstance()->empate();
		fprintf(positivo,"0 %s x %s 0\n",nome1,nome2);
		fclose(positivo);
		resetar();
		system("pause");
		goto comeco;
	} else{
		printf("Esta partida está longe de acabar\n");
		Sound::GetInstance()->empateNegado();
		system("pause");
		goto inicio;
	}	
	} else {
	// Inserir e verificar pe�a selecionada
	cout<<"\nMovimento:\n\nDe:";
	scanf("%i,%i",& ax,& ay);
	if(selecionado((int)ax,(int)ay)){
		printf("Não há uma peça sua nessa posição\n\n");
		system("pause");
		system("cls || clear");
		goto inicio;
	}
	//Inserir e verificar movimento
	printf("\n%c irá para: ",tabuleiro[ax][ay]);
	scanf("%i,%i",& sx,& sy);
	if(movimento(ax, ay, sx, sy)){
		if(rock){
			joestar = tabuleiro[ax][ay];
			tabuleiro[ax][ay] = tabuleiro[sx][sy];
			tabuleiro[sx][sy] = joestar;
			printf("\nOs do rock eu sei quem são");
			rock=0;
			fflush(stdin);
			getchar();
		} else {
			if(tabuleiro[sx][sy] != '-'){
				if(vez%2 != 0){
					captP[pz] = tabuleiro[sx][sy];
					pz++;
				}else{
					captB[cv] = tabuleiro[sx][sy];
					cv++;
				}
			Sound::GetInstance()->assassinato(vez);
			}
		tabuleiro[sx][sy]=tabuleiro[ax][ay];
		tabuleiro[ax][ay]='-';
		 
		}
	} else {
		printf("\nMovimento inválido\n\n");
		system("pause");
		system("cls || clear");
		goto inicio;
	}
}
} //<--- Se for uma pessoa jogando
	//Verificar reis
	for(i=0;i<8;i++)
	for(j=0;j<8;j++){
		if(tabuleiro[i][j]=='R')
		reipreto++;
		if(tabuleiro[i][j]=='K')
		reibranco++;
	}
	++vez;
	system("cls");

} while (reipreto>=1 && reibranco>=1);
// Mostrar cheque-mate
cout<<"   0 1 2 3 4 5 6 7\n\n";
for(i=0;i<8;i++){
		cout<<i<<"  ";
	for(j=0;j<8;j++)
	printf("%c ",tabuleiro[i][j]);
	printf("\n");					
	}
	Sound::GetInstance()->the_final_countdown();
//Quem ganhou?
	cout<<"\n\nCheque-Mate\n\n";
	if((vez-1)%2==0){
	cout<<nome1<< " ganhou\n\n";
	fprintf(positivo,"1 %s x %s 0\n",nome1,nome2);
	fclose(positivo);
	resetar();
	system ("pause");
	
	}else{
	cout<<nome2<< " ganhou\n\n";
	fprintf(positivo,"0 %s x %s 1\n",nome1,nome2);
	fclose(positivo);
	resetar();
	system ("pause");
}
system("cls");
goto comeco;
return 0;	
}
void menu(){
	
	int t,r;
	static string titulo="           Xadrez em C+";
	do{
	 cout<<titulo<<"\n\n";
	printf("             1) Jogar\n");
	printf("       2) Escolher os nomes\n");
	printf("         3) Ver as regras\n");
	printf("        4) Selecionar jooj\n");
	printf("      5) Resetar o tabuleiro\n");
	printf("          6) Salvar jogo\n");
	printf("         7) Carregar save\n");
	printf("     8) Histórico de partidas\n");
	printf("           9) Sair-lhes\n");
	if(bot){
	printf("         0) Desligar bote\n");	
	} else {
	printf("        0) Ligar bot massa\n");	
	}
	
	cin>>t;
	if(t==2){
		system("clear || cls");
		printf("Insira os nomes (sem espaços):\nBranco: ");
	
	cin>>nome1;
	cout<<"Preto: ";
	cin>>nome2;
	system("clear || cls");

} else if(t==3){
	system("clear || cls");
	if(xadrezNormal){
	printf("1. Jogue quando for o seu turno\n\n2. Insira as cordenadas como: linha, virgula, coluna\n\n");
	printf("3. Insira primeiro as cordenadas de onde está a peça que vc quer mover\n\n");
	printf("4. Depois insira a cordenada da casa pra qual vc quer que a peça se desloque\n\n");
	printf("5. Se o movimento for válido, o movimento acontecerá\n\n");
	printf("6. Digite apenas numeros!\n\n");
	printf("7. Espere o \"bot\" pensar!\n\n");
	printf("8. Tente entender o jogo\n\n");
	printf("9. Se tu não seguir as regras e algo der errado, o problema não é meu\n\n");
	} else{
		cout<<"O cara acha que vai entender o Xadrez 2\n\n";
	}
	system("pause");
	system("clear || cls");
} else if(t==4){
	system ("clear || cls");
	
	cout<<"1)Xadrez normal\n\n2)Xadrez 2\n\n";
	scanf("%i",&r);
	if(r==2){
		xadrezNormal=0;
		titulo="             Xadrex 2";
		system("title Xadrez muito mais bolado");
	} else {
		xadrezNormal=1;
		titulo="          Xadrez Normal?"; 
		system("title Xadrez normal");
	}
	system("clear || cls");
} else if(t==5){
	resetar();
   
} else if (t == 6){
	//Salvar jogo
	FILE *tab;
	FILE *users;
	FILE *comrade;
	
	tab = fopen("tabuleiro.txt","w");
	
	for(i=0; i<8; i++)
	for(j=0; j<8; j++)
		fprintf(tab, "%c", tabuleiro[i][j]);
	fclose(tab);
	
	users = fopen("partida.txt","w");
	fprintf(users, "%s %s %i", nome1, nome2, vez);
	fclose(users);
	
	comrade = fopen("comidas.txt","w");
	for(i=0; i<16; i++)
	fprintf(comrade, "%c%c", captB[i], captP[i]);
	fclose(comrade);
	
} else if (t == 7){
	//Carregar jogo
	FILE *car;
	FILE *ryu;
	FILE *cavalo;
	cavalo = fopen("comidas.txt", "r");
	ryu = fopen("partida.txt", "r");
	car = fopen("tabuleiro.txt", "r");
	if(car == NULL || ryu == NULL || cavalo == NULL){
		printf("\nNão tem nenhum tabuleiro salvo aqui\n");
		system("pause");
	} else {
	for(i=0;i<8;i++)
	for(j=0;j<8;j++)
	fscanf(car, "%c", &tabuleiro[i][j]);
	fclose(car);
	
	fscanf(ryu, "%s %s %i", &nome1, &nome2, &vez);
	fclose(ryu);
	
	for(i=0; i<16; i++)
	fscanf(cavalo, "%c%c", &captB[i], &captP[i]);
	fclose(cavalo);
	}
} else if (t == 8){
	//Historico de atleta:
	system("cls || clear");
	char hit[1000];
	FILE *mega;
	mega = fopen("historico.txt", "r");
	
	if(mega == NULL){
		printf("Não há partidas registradas\n");
	} else {
		while(fgets(hit, 1000, mega) != NULL){
			printf("%s\n", hit);
		}
		cout<<"\n"; 
	}
	system("pause");
	
}
 else if (t == 9)
exit(1);
else if (t == 0){
	if(bot)
	bot=0;
	else
	bot=1;
}
	system ("clear || cls");
}while(t!=1);
}
bool selecionado(int x, int y){
	
if(xadrezNormal){
	if (tabuleiro[x][y]!='-'){
		if(vez % 2 == 0 && (tabuleiro[x][y]=='s' || tabuleiro[x][y]=='L' || tabuleiro[x][y]=='E' || tabuleiro[x][y]=='X' || tabuleiro[x][y]=='K' || tabuleiro[x][y]=='Q')){
		return 0;
	}else if(vez % 2 != 0 && (tabuleiro[x][y]!='s' && tabuleiro[x][y]!='L' && tabuleiro[x][y]!='E' && tabuleiro[x][y]!='X' && tabuleiro[x][y]!='K' && tabuleiro[x][y]!='Q')){
		return 0;
	}else{
		return 1;
	}
} else{
	return 1;
}
} else{
	return 0;
}
}
bool movimento(int ix, int iy, int mx, int my){
	int obst=0;
	i=1;
	j=1;
	
		if(tabuleiro[ix][iy]=='K' && tabuleiro[mx][my]=='L'){
			rock=1;
			return 1;
		}else if(tabuleiro[ix][iy]=='R' && tabuleiro[mx][my]=='T'){
			rock=1;
			return 1;
		}
	if(xadrezNormal){
	if(ix==mx && iy==my)
	return 0;
	if(vez%2!=0){
	if( tabuleiro[mx][my]=='p' || tabuleiro[mx][my]=='T' || tabuleiro[mx][my]=='C' || tabuleiro[mx][my]=='B' || tabuleiro[mx][my]=='R' || tabuleiro[mx][my]=='D')
    	return 0;
    } else{
    	if(tabuleiro[mx][my]=='s' || tabuleiro[mx][my]=='L' || tabuleiro[mx][my]=='E' || tabuleiro[mx][my]=='X' || tabuleiro[mx][my]=='K' || tabuleiro[mx][my]=='Q')
    	return 0;
	}
    }
// Movimento do pe�o s
	int requiem;
	if(tabuleiro[ix][iy]=='s'){
		if (((my==iy && mx==ix+1) && tabuleiro[mx][my]=='-') || (mx==ix+1 && (my==iy-1 || my==iy+1 ) && tabuleiro[mx][my]!='-' ) || (my==iy && ix==1 && mx==ix+2 && tabuleiro[ix+1][iy]=='-' && tabuleiro[mx][my]=='-')) {
	    if (mx==7){
	    	printf("\nPeão Requiem\n\n");
			Sound::GetInstance()->requi(); 
			printf("Pra qual peça o seu peão vai mega-evoluir?\n\n");
	    	printf("1)Liteira\n2)Elefante\n3)Xamã\n4)Queen\n");
	    	if(!xadrezNormal)
	    	cout<<"5)King Crimson\n";
	    	cin>>requiem;
	    	switch(requiem){
	    		case 1:
	    			tabuleiro[ix][iy]='L';
	    			break;
	    		case 2:
	    			tabuleiro[ix][iy]='E';
	    			break;
				case 3:
	    			tabuleiro[ix][iy]='X';
	    			break;
	    		case 4:
	    			tabuleiro[ix][iy]='Q';	
	    			break;		
	    		case 5:
					tabuleiro[ix][iy]='K';
					break;
				default:
					printf("\nAo ser abandonado pelo seu King, o peão decide mudar de lado\n");
				 	tabuleiro[ix][iy]='p';	
			}
			system("pause");
		}
	    return 1;
	} else {
		return 0;
	}
	}
// Movimento do pe�o p
if(tabuleiro[ix][iy]=='p'){
	if (((my==iy && mx==ix-1) && tabuleiro[mx][my]=='-') || (mx==ix-1 && (my==iy-1 || my==iy+1 ) && tabuleiro[mx][my]!='-' ) || (my==iy && ix==6 && mx==ix-2 && tabuleiro[ix-1][iy]=='-' && tabuleiro[mx][my]=='-')) {
	    if (mx==0){
	    	if(!bot){
	    	printf("\nPeão Requiem\n\n");
			Sound::GetInstance()->requi(); 
			printf("Pra qual peça o seu peão vai mega-evoluir?\n\n");
	    	printf("1)Torre\n2)Cavalo\n3)Bispo\n4)Rainha\n");
	    	if(!xadrezNormal)
	    	cout<<"5)Reinaldo";
	    	cin>>requiem;
	    	switch(requiem){
	    		case 1:
	    			tabuleiro[ix][iy]='T';
	    			break;
	    		case 2:
	    			tabuleiro[ix][iy]='C';
	    			break;
	    		case 3:
	    			tabuleiro[ix][iy]='B';
	    			break;
	    		case 4:
	    			tabuleiro[ix][iy]='D';
	    			break;	
	    		case 5:
					tabuleiro[ix][iy]='R';
					break;
				default:
				 	printf("\nAo ser abandonado pelo seu rei, o peão decide mudar de lado\n");
				 	tabuleiro[ix][iy]='s';
			}
			system ("pause");
			} else {
				switch(rbot){
	    		case 1:
	    			tabuleiro[ix][iy]='T';
	    			break;
	    		case 2:
	    			tabuleiro[ix][iy]='C';
	    			break;
	    		case 3:
	    			tabuleiro[ix][iy]='B';
	    			break;
	    		case 4:
	    			tabuleiro[ix][iy]='D';
	    			break;	
	    		case 5:
					tabuleiro[ix][iy]='R';
					break;
				default:
				 	printf("\nAo ser abandonado pelo bot, o peão decide ficar do seu lado\n");
				 	tabuleiro[ix][iy]='s';
				 	Sleep(2000);
			}
		}
		}
	    return 1;
	} else {
		return 0;
	}
}
// Movimento Torres
  if(tabuleiro[ix][iy]=='T' || tabuleiro[ix][iy]=='L'){
    	
    		if(mx==ix && my>iy){
    			i=iy+1;
    			while(i<my){
    				if(tabuleiro[ix][i]!='-')
    				obst++;
    				i++;
				}
				if(obst!=0){
					return 0;
				} else {
					return 1;
				}
			} else if(mx==ix && my<iy){
				i=iy-1;
    			while(i>my){
    				if(tabuleiro[ix][i]!='-')
    				obst++;
    				i--;	
			}
    			if(obst!=0){
					return 0;
				} else {
					return 1;
				}
			} else if(my==iy && mx<ix){
				i=ix-1;
    			while(i>mx){
    				if(tabuleiro[i][iy]!='-')
    				obst++;
    				i--;	
			}
    			if(obst!=0){
					return 0;
				} else {
					return 1;
				}
			} else if(my==iy && mx>ix){
				i=ix+1;
    			while(i<mx){
    				if(tabuleiro[i][iy]!='-')
    				obst++;
    				i++;
				}
				if(obst!=0){
					return 0;
				} else {
					return 1;
				}
			} else{
				return 0;
			}
}
//Movimento dos Reis	
	if(tabuleiro[ix][iy]=='K' || tabuleiro[ix][iy]=='R'){
		
		if( (mx==ix && (my==iy-1 || my==iy+1) ) || (my==iy && (mx==ix+1 || mx==ix-1)) || (mx==ix+1 && my==iy+1) || (mx==ix+1 && my==iy-1) || (mx==ix-1 && my==iy+1) || (mx==ix-1 && my==iy-1)){
		return 1;
		} else {
			return 0;
		}
	}
//Movimento dos Cavalos
	 if(tabuleiro[ix][iy]=='C' || tabuleiro[ix][iy]=='E'){
		if(((mx==ix+2 || mx==ix-2) && (my==iy+1 || my==iy-1)) || ((mx==ix+1 || mx==ix-1) && (my==iy+2 || my==iy-2)) ){
			return 1;
		} else {
			return 0;
		}
	}
//Movimento dos Bispos
	 if(tabuleiro[ix][iy]=='B' || tabuleiro[ix][iy]=='X'){
		if(mx>ix && my>iy){
			if(mx - ix == my - iy) {
				for(i=1;i<=mx-ix-1;i++)
					if(tabuleiro[ix+i][iy+i] != '-' && ix+i!=mx && iy+i!=my){
					return 0;
					break;
					}
			return 1;		
			} else {
				return 0;
			}
		} else if(mx<ix && my<iy){
			if(mx - ix == my - iy) {
				for(i=1;i<=ix-mx;i++)
					if(tabuleiro[ix-i][iy-i] != '-' && ix-i!=mx && iy-i!=my){
					return 0;
					break;
					}
			return 1;
		} else {
				return 0;
			}
			
		} else if(mx>ix && my<iy){
			if(mx - ix == iy - my) {
				for(i=1;i<=mx-ix;i++)
					if(tabuleiro[ix+i][iy-i] != '-' && ix+i!=mx && iy-i!=my){
					return 0;
					break;
					}
			return 1;
			} else {
				return 0;
			}
				
		} else if(mx<ix && my>iy){
			if(ix - mx == my - iy) {
				for(i=1;i<=my-iy;i++)
					if(tabuleiro[ix-i][iy+i] != '-' && ix-i!=mx && iy+i!=my){
					return 0;
					break;
					}
			return 1;
			} else {
			return 0;
			}
		} else {
			return 0;
		}
	}
// Movimento das Rainhas
	if(tabuleiro[ix][iy] == 'D' || tabuleiro[ix][iy] == 'Q'){
		// Movimento em X
		if(mx>ix && my>iy){
			if(mx - ix == my - iy) {
				for(i=1;i<=mx-ix-1;i++)
					if(tabuleiro[ix+i][iy+i] != '-' && ix+i!=mx && iy+i!=my){
					return 0;
					break;
					}
			return 1;		
			} else {
				return 0;
			}
		} else if(mx<ix && my<iy){
			if(mx - ix == my - iy) {
				for(i=1;i<=ix-mx;i++)
					if(tabuleiro[ix-i][iy-i] != '-' && ix-i!=mx && iy-i!=my){
					return 0;
					break;
					}
			return 1;
			} else {
			return 0;
			}
			
		} else if(mx>ix && my<iy){
			if(mx - ix == iy - my) {
				for(i=1;i<=mx-ix;i++)
					if(tabuleiro[ix+i][iy-i] != '-' && ix+i!=mx && iy-i!=my){
					return 0;
					break;
					}
			return 1;
			} else {
			return 0;
			}
				
		} else if(mx<ix && my>iy){
			if(ix - mx == my - iy) {
				for(i=1;i<=my-iy;i++)
					if(tabuleiro[ix-i][iy+i] != '-' && ix-i!=mx && iy+i!=my){
					return 0;
					break;
					}
			return 1;
			} else {
			return 0;
			}
		 } 
		 // Movimento em +
		 else if(mx==ix && my>iy){
    			i=iy+1;
    			while(i<my){
    				if(tabuleiro[ix][i]!='-')
    				obst++;
    				i++;
				}
				if(obst!=0){
					return 0;
				} else {
					return 1;
				}
				
			} else if(mx==ix && my<iy){
				i=iy-1;
    			while(i>my){
    				if(tabuleiro[ix][i]!='-')
    				obst++;
    				i--;	
			}
    			if(obst!=0){
					return 0;
				} else {
					return 1;
				}
			} else if(my==iy && mx<ix){
				i=ix-1;
    			while(i>mx){
    				if(tabuleiro[i][iy]!='-')
    				obst++;
    				i--;	
			}
    			if(obst!=0){
					return 0;
				} else {
					return 1;
				}
			} else if(my==iy && mx>ix){
				i=ix+1;
    			while(i<mx){
    				if(tabuleiro[i][iy]!='-')
    				obst++;
    				i++;
				}
				if(obst!=0){
					return 0;
				} else {
					return 1;
				}
			} else{
				return 0;
			}
		
	}	
}
void resetar(){
	tabuleiro[0][0]='L';
	tabuleiro[0][1]='E';
	tabuleiro[0][2]='X';
	tabuleiro[0][3]='K';
	tabuleiro[0][4]='Q';
	tabuleiro[0][5]='X';
	tabuleiro[0][6]='E';
	tabuleiro[0][7]='L';
	for(i=0;i<8;i++)
	tabuleiro[1][i]='s';
	for(i=2;i<6;i++)
	for(j=0;j<8;j++)
	tabuleiro[i][j]='-';
	for(i=0;i<8;i++)
	tabuleiro[6][i]='p';
	tabuleiro[7][0]='T';
	tabuleiro[7][1]='C';
	tabuleiro[7][2]='B';
	tabuleiro[7][3]='R';
	tabuleiro[7][4]='D';
	tabuleiro[7][5]='B';
	tabuleiro[7][6]='C';
	tabuleiro[7][7]='T';
   vez=2;
   
   for(i=0;i<16;i++){
   	captB[i] = ' ';
   	captP[i] = ' ';
   }
	
}
void biomecanico(){

 int uix, uiy, afx, afy;
 bool boina;
 srand(time(NULL));
 rbot = rand() % 5;
 int idk = 0;	
Sleep(2000);
while(1){
	idk = 0;
	
	uix = rand() % 8;
	uiy = rand() % 8;
	
	if(!selecionado(uix,uiy)){
		do{
			afx = rand() % 8;
			afy = rand() % 8;
			
		//	cout<<endl<<idk<<"---"<<uix<<","<<uiy<<" "<<afx<<","<<afy;
			boina = movimento(uix,uiy,afx,afy);
			
			if(boina){
				break;
			}
			idk++; 
		}while(idk != 500);
	}
	
	if(boina)
		break;
}
//cout<<endl<<idk<<"---"<<uix<<","<<uiy<<" "<<afx<<","<<afy<<endl;
//system("pause");
if(boina){
		if(rock){
			joestar = tabuleiro[uix][uiy];
			tabuleiro[uix][uiy] = tabuleiro[afx][afy];
			tabuleiro[afx][afy] = joestar;
			printf("\nO bot é do rock");
			rock=0;
			Sleep(1000);
		} else {
			if(tabuleiro[afx][afy] != '-'){
				if(vez%2 != 0){
					captP[pz] = tabuleiro[afx][afy];
					pz++;
				}else{
					captB[cv] = tabuleiro[afx][afy];
					cv++;
				}
				Sound::GetInstance()->assassinato(vez); 
			}
		tabuleiro[afx][afy]=tabuleiro[uix][uiy];
		tabuleiro[uix][uiy]='-';
		 
		}
}

}
