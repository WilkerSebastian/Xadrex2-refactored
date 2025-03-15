#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <locale>
#include "Sound.h"
#include "Chessboard.h"

using namespace std;

int i=0,j,pz=0,cv=0,reipreto=0,reibranco=0;
char nome1[100]="Branco", nome2[100] = "Preto"; 
const char nomeBot[100] = "UltraT";
char captB[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}; 
char captP[16] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
char ax,ay,sx,sy,joestar;
int vez=2, real, feique,rbot;
bool xadrezNormal=1,rock, bot=0;

void resetar(Chessboard *board);
bool selecionado(Chessboard *board, int x, int y);
bool movimento(Chessboard *board, int ix, int iy, int mx, int my);

int main() {

	std::locale::global(std::locale("pt_BR.UTF-8"));

	Chessboard chessboard;

	system("MODE con:cols=34 lines=30");
	FILE *positivo;
	positivo = fopen("historico.txt","a");
	void menu(Chessboard *board);
	void biomecanico(Chessboard *board);
	
	comeco:
	system("cls || clear");	
	menu(&chessboard);
	
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
	chessboard.render();
	printf("\n");
	//Pe�as capturadas pelos brancos
	for(i=0; i<16; i++)
		cout<<captP[i]<<"-";
		
	//Caso tenha o bot:	
	if(vez % 2 != 0 && bot == 1){
		biomecanico(&chessboard);
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
			resetar(&chessboard);
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
		resetar(&chessboard);
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
	if(selecionado(&chessboard, (int)ax,(int)ay)){
		printf("Não há uma peça sua nessa posição\n\n");
		system("pause");
		system("cls || clear");
		goto inicio;
	}
	//Inserir e verificar movimento
	printf("\n%c irá para: ", chessboard.getHouse(ax, ay));
	scanf("%i,%i",& sx,& sy);
	if(movimento(&chessboard, ax, ay, sx, sy)){
		if(rock){
			chessboard.swap(ax, ay, sx, sy);
			printf("\nOs do rock eu sei quem são");
			rock=0;
			fflush(stdin);
			getchar();
		} else {
			if(!chessboard.houseIsEmpty(sx, sy)){
				if(vez%2 != 0){
					captP[pz] = chessboard.getHouse(sx, sy);
					pz++;
				}else{
					captB[cv] = chessboard.getHouse(sx, sy);
					cv++;
				}
			Sound::GetInstance()->assassinato(vez);
			}
		chessboard.copyHouseTo(ax, ay, sx, sy);
		chessboard.clearHouse(ax, ay);
		 
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
		if(chessboard.houseIs('R', i, j))
		reipreto++;
		if(chessboard.houseIs('K', i, j))
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
	printf("%c ", chessboard.getHouse(i, j));
	printf("\n");					
	}
	Sound::GetInstance()->the_final_countdown();
//Quem ganhou?
	cout<<"\n\nCheque-Mate\n\n";
	if((vez-1)%2==0){
	cout<<nome1<< " ganhou\n\n";
	fprintf(positivo,"1 %s x %s 0\n",nome1,nome2);
	fclose(positivo);
	resetar(&chessboard);
	system ("pause");
	
	}else{
	cout<<nome2<< " ganhou\n\n";
	fprintf(positivo,"0 %s x %s 1\n",nome1,nome2);
	fclose(positivo);
	resetar(&chessboard);
	system ("pause");
}
system("cls");
goto comeco;
return 0;	
}
void menu(Chessboard *board){
	
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
	resetar(board);
   
} else if (t == 6){
	//Salvar jogo
	FILE *tab;
	FILE *users;
	FILE *comrade;
	
	tab = fopen("tabuleiro.txt","w");
	
	for(i=0; i<8; i++)
	for(j=0; j<8; j++)
		fprintf(tab, "%c", board->getHouse(i, j));	
		
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
	char dist;
	cavalo = fopen("comidas.txt", "r");
	ryu = fopen("partida.txt", "r");
	car = fopen("tabuleiro.txt", "r");
	if(car == NULL || ryu == NULL || cavalo == NULL){
		printf("\nNão tem nenhum tabuleiro salvo aqui\n");
		system("pause");
	} else {
	for(i=0;i<8;i++)
	for(j=0;j<8;j++) {
		fscanf(car, "%c", &dist);
		board->setHouse(dist, i, j);
	}
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
bool selecionado(Chessboard *board, int x, int y){
	
if(xadrezNormal){
	if (board){
		if(vez % 2 == 0 && (
			board->houseIs('s', x, y) || 
			board->houseIs('L', x, y) || 
			board->houseIs('E', x, y) || 
			board->houseIs('X', x, y) || 
			board->houseIs('K', x, y) || 
			board->houseIs('Q', x, y)
		)){
		return 0;
	}else if(vez % 2 != 0 && (
		!board->houseIs('s', x, y) &&
		!board->houseIs('L', x, y) &&
		!board->houseIs('E', x, y) &&
		!board->houseIs('X', x, y) &&
		!board->houseIs('K', x, y) &&
		!board->houseIs('Q', x, y)
	)){
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
bool movimento(Chessboard *board, int ix, int iy, int mx, int my){
	int obst=0;
	i=1;
	j=1;
	
		if(board->houseIs('K', ix, iy) && board->houseIs('L', mx, my)){
			rock=1;
			return 1;
		}else if(board->houseIs('R', ix, iy) && board->houseIs('T', mx, my)){
			rock=1;
			return 1;
		}
	if(xadrezNormal){
	if(ix==mx && iy==my)
	return 0;
	if(vez%2!=0){
	if(
		board->houseIs('p', mx, my) || 
		board->houseIs('T', mx, my) || 
		board->houseIs('C', mx, my) || 
		board->houseIs('B', mx, my) || 
		board->houseIs('R', mx, my) || 
		board->houseIs('D', mx, my)
	)
    	return 0;
    } else{
    	if(
			board->houseIs('s', mx, my) || 
			board->houseIs('L', mx, my) || 
			board->houseIs('E', mx, my) || 
			board->houseIs('X', mx, my) || 
			board->houseIs('K', mx, my) || 
			board->houseIs('Q', mx, my)
		)
    	return 0;
	}
    }
// Movimento do pe�o s
	int requiem;
	if(board->houseIs('s', ix, iy)){
		if (((my==iy && mx==ix+1) && 
			board->houseIsEmpty(mx, my)) || (mx==ix+1 && (my==iy-1 || my==iy+1 ) && 
			!board->houseIsEmpty(mx, my) ) || (my==iy && ix==1 && mx==ix+2 && 
			board->houseIsEmpty(ix + 1, iy) && 
			board->houseIsEmpty(mx, my))) {
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
	    			board->setHouse('L', ix, iy);
	    			break;
	    		case 2:
					board->setHouse('E', ix, iy);
	    			break;
				case 3:
					board->setHouse('X', ix, iy);
	    			break;
	    		case 4:
					board->setHouse('Q', ix, iy);
	    			break;		
	    		case 5:
					board->setHouse('K', ix, iy);
					break;
				default:
					printf("\nAo ser abandonado pelo seu King, o peão decide mudar de lado\n");
					board->setHouse('p', ix, iy);
			}
			system("pause");
		}
	    return 1;
	} else {
		return 0;
	}
	}
// Movimento do pe�o p
if(board->houseIs('p', ix, iy)){
	if (((my==iy && mx==ix-1) && board->houseIsEmpty(mx, my)) || (mx==ix-1 && (my==iy-1 || my==iy+1 ) && 
		!board->houseIsEmpty(mx, my) ) || (my==iy && ix==6 && mx==ix-2 && 
		board->houseIsEmpty(ix - 1, iy) && 
		board->houseIsEmpty(mx, my))) {
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
	    			board->setHouse('T', ix, iy);
	    			break;
	    		case 2:
	    			board->setHouse('C', ix, iy);
	    			break;
	    		case 3:
	    			board->setHouse('B', ix, iy);
	    			break;
	    		case 4:
	    			board->setHouse('D', ix, iy);
	    			break;	
	    		case 5:
					board->setHouse('R', ix, iy);
					break;
				default:
				 	printf("\nAo ser abandonado pelo seu rei, o peão decide mudar de lado\n");
				 	board->setHouse('s', ix, iy);
			}
			system ("pause");
			} else {
				switch(rbot){
	    		case 1:
	    			board->setHouse('T', ix, iy);
	    			break;
	    		case 2:
	    			board->setHouse('C', ix, iy);
	    			break;
	    		case 3:
	    			board->setHouse('B', ix, iy);
	    			break;
	    		case 4:
	    			board->setHouse('D', ix, iy);
	    			break;	
	    		case 5:
					board->setHouse('R', ix, iy);
					break;
				default:
				 	printf("\nAo ser abandonado pelo bot, o peão decide ficar do seu lado\n");
				 	board->setHouse('s', ix, iy);
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
  if(board->houseIs('T', ix, iy) || board->houseIs('L', ix, iy)){
    	
    		if(mx==ix && my>iy){
    			i=iy+1;
    			while(i<my){
    				if(!board->houseIsEmpty(ix, i))
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
    				if(!board->houseIsEmpty(ix, i))
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
    				if(!board->houseIsEmpty(i, iy))
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
    				if(!board->houseIsEmpty(i, iy))
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
	if(board->houseIs('K', ix, iy) || board->houseIs('R', ix, iy)){
		
		if( (mx==ix && (my==iy-1 || my==iy+1) ) || (my==iy && (mx==ix+1 || mx==ix-1)) || (mx==ix+1 && my==iy+1) || (mx==ix+1 && my==iy-1) || (mx==ix-1 && my==iy+1) || (mx==ix-1 && my==iy-1)){
		return 1;
		} else {
			return 0;
		}
	}
//Movimento dos Cavalos
	 if(board->houseIs('C', ix, iy) || board->houseIs('E', ix, iy)){
		if(((mx==ix+2 || mx==ix-2) && (my==iy+1 || my==iy-1)) || ((mx==ix+1 || mx==ix-1) && (my==iy+2 || my==iy-2)) ){
			return 1;
		} else {
			return 0;
		}
	}
//Movimento dos Bispos
	 if(board->houseIs('B', ix, iy) || board->houseIs('X', ix, iy)){
		if(mx>ix && my>iy){
			if(mx - ix == my - iy) {
				for(i=1;i<=mx-ix-1;i++)
					if(!board->houseIsEmpty(ix + i, iy + i) && ix+i!=mx && iy+i!=my){
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
					if(!board->houseIsEmpty(ix - i, iy - i) && ix-i!=mx && iy-i!=my){
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
					if(!board->houseIsEmpty(ix + i, iy - i) && ix+i!=mx && iy-i!=my){
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
					if(!board->houseIsEmpty(ix - i, iy + i) && ix-i!=mx && iy+i!=my){
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
	if(board->houseIs('D', ix, iy) || board->houseIs('Q', ix, iy)){
		// Movimento em X
		if(mx>ix && my>iy){
			if(mx - ix == my - iy) {
				for(i=1;i<=mx-ix-1;i++)
					if(!board->houseIsEmpty(ix + i, iy + i) && ix+i!=mx && iy+i!=my){
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
					if(!board->houseIsEmpty(ix - i, iy - i) && ix-i!=mx && iy-i!=my){
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
					if(!board->houseIsEmpty(ix + i, iy - i) && ix+i!=mx && iy-i!=my){
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
					if(!board->houseIsEmpty(ix - i, iy + i) && ix-i!=mx && iy+i!=my){
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
    				if(!board->houseIsEmpty(ix, i))
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
    				if(!board->houseIsEmpty(ix, i))
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
    				if(!board->houseIsEmpty(i, iy))
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
    				if(!board->houseIsEmpty(i, iy))
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

void resetar(Chessboard *board) {

	board->reset();

	vez = 2;
   
	for(uint8_t i = 0; i < BOARD_LEN * 2; i++) {

		captB[i] = ' ';
		captP[i] = ' ';
   
	}
	
}

void biomecanico(Chessboard *board){

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
	
	if(!selecionado(board, uix,uiy)){
		do{
			afx = rand() % 8;
			afy = rand() % 8;
			
		//	cout<<endl<<idk<<"---"<<uix<<","<<uiy<<" "<<afx<<","<<afy;
			boina = movimento(board, uix,uiy,afx,afy);
			
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
			board->swap(uix, uiy, afx, afy);
			printf("\nO bot é do rock");
			rock=0;
			Sleep(1000);
		} else {
			if(board->houseIsEmpty(afx, afy)){
				if(vez%2 != 0){
					captP[pz] = board->getHouse(afx, afy);
					pz++;
				}else{
					captB[cv] = board->getHouse(afx, afy);
					cv++;
				}
				Sound::GetInstance()->assassinato(vez); 
			}
			board->copyHouseTo(uix, uiy, afx, afy);
			board->clearHouse(uix, uiy);
		 
		}
}

}
