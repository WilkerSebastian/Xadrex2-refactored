#include "Sound.h"

#include <windows.h>

Sound *Sound::instance_ = nullptr;

Sound *Sound::GetInstance() {

    if (instance_ == nullptr)
        instance_ = new Sound();
    
    return instance_;

}

void Sound::the_final_countdown() {
	
	Beep(554,110);
	Beep(493,120);
	Beep(554,500);
	Beep(369,400); 
	
	Sleep(800);
	
	Beep(587,100);
	Beep(554,100);
	Beep(587,200);
	Beep(554,200); 
	Beep(493,500);
	
	Sleep(900);
	
	Beep(587,100);
	Beep(554,100);
	Beep(587,500);
	Beep(369,500);
	
	Sleep(700);
	
	Beep(493,100);
	Beep(440,100);
	Beep(493,200);
	Beep(440,200);
	Beep(415,200);
	Beep(493,200);
	Beep(440,700);
	
}

void Sound::desistencia() {

    int c3=261,c_sus3=277,d3=293,d_sus3=311,e3=329,f3=349,f_sus3=369,g3=392,g_sus3=415,a3=440,a_sus3=466,b3=494,c4=523,c_sus4=554,d4=587;

    Beep(c_sus4 , 300);
    Beep(g_sus3 , 300);
    Beep(c_sus4 , 300);

    Beep(c_sus4 , 300);
    Beep(g_sus3 , 300);
    Beep(c_sus4 , 300);
    Beep(g_sus3 , 300);


    Beep(a_sus3 , 300);
    Beep(f_sus3 , 300);
    Beep(c_sus3 , 300);

}

void Sound::empateNegado() {
	
    int F5 = 1396, G5 = 1567, Ab5 = 1661, C6 = 2093, Cb5 = 1975, Bb5 = 1864, C5 = 1046, Fb5 = 1318, Eb5 = 1244;
	
	Beep(F5,300);
	Beep(G5,300);
	Beep(Ab5,280);
	Beep(C6,280);
	Beep(Ab5,200);
	Beep(Cb5,280);
	Beep(Bb5,280);
	Beep(Ab5,500);
	
	Sleep(200);
	
	Beep(C5,300);
	Beep(Eb5,200);
	Beep(Fb5,200);
	Beep(F5,1000);
	
}

void Sound::empate() {
	
    int F5 = 1396, G5 = 1567, Ab5 = 1661, C6 = 2093, Cb5 = 1975, Bb5 = 1864, C5 = 1046, Fb5 = 1318, Eb5 = 1244, Db6 = 2217, A5 = 1760, F = 1479, E5 = 1318 ;

    Beep(Db6,1000);
    Beep(Db6,100);
    Beep(Db6,100);
    Beep(Db6,210);
    Beep(C6,130);
    Beep(Bb5,130);
    Beep(Db6,180);
    Beep(C6,130);
    Beep(Bb5,130);
    Beep(A5,1050);
    Beep(A5,130);
    Beep(A5,130);
    Beep(A5,210);
    Beep(Ab5,100);

    Beep(F,100);
    Beep(A5,210);
    Beep(Ab5,100);
    Beep(F,100);
    Sleep(200);
    Beep(F5,1000);
    Beep(E5,1000);
    Beep(Eb5,1000);
	
}

void Sound::assassinato(int round) {

	if (round % 2 == 0) {

		Beep(1300,200);
		Beep(900,200);
		return;

	}

	Beep(900,200);
    Beep(1300,200);

}

void Sound::requi() {

	int Fs4 = 739, D4 = 587, E4 = 659, F4 = 698, Cs4 = 554, B4 = 987, Cs5 = 1108, D5 = 1174, G5 = 1567, As4 = 932, G4 = 783;
	
	Beep(Fs4,240);
	Beep(D4,400);
	
	Sleep(400);
	
	Beep(D4,180);
	Beep(E4,180);
	Beep(F4,350);
	Beep(E4,350);
	Beep(D4,300);
	
	Beep(Cs4,350);
	Beep(D4,350);
	Beep(E4,300);
	Beep(Fs4,550);
	Beep(Fs4,250);
	Beep(B4,800);
	Beep(B4,290);
	
	Beep(Cs5,290);
	Beep(D5,350);
	Beep(G4,350);
	Beep(Fs4,200);
	Beep(F4,350);
	Beep(D5,350);
	Beep(As4,180);
	Beep(1000,800);

}