#include "Sound.h"

#include <Utils.h>

using namespace Utils;

Sound *Sound::instance_ = nullptr;

Sound *Sound::GetInstance() {

    if (instance_ == nullptr)
        instance_ = new Sound();
    
    return instance_;

}

void Sound::the_final_countdown() {
	
	beep(554,110);
	beep(493,120);
	beep(554,500);
	beep(369,400); 
	
	sleep(800);
	
	beep(587,100);
	beep(554,100);
	beep(587,200);
	beep(554,200); 
	beep(493,500);
	
	sleep(900);
	
	beep(587,100);
	beep(554,100);
	beep(587,500);
	beep(369,500);
	
	sleep(700);
	
	beep(493,100);
	beep(440,100);
	beep(493,200);
	beep(440,200);
	beep(415,200);
	beep(493,200);
	beep(440,700);
	
}

void Sound::desistencia() {

    int c3=261,c_sus3=277,d3=293,d_sus3=311,e3=329,f3=349,f_sus3=369,g3=392,g_sus3=415,a3=440,a_sus3=466,b3=494,c4=523,c_sus4=554,d4=587;

    beep(c_sus4 , 300);
    beep(g_sus3 , 300);
    beep(c_sus4 , 300);

    beep(c_sus4 , 300);
    beep(g_sus3 , 300);
    beep(c_sus4 , 300);
    beep(g_sus3 , 300);


    beep(a_sus3 , 300);
    beep(f_sus3 , 300);
    beep(c_sus3 , 300);

}

void Sound::empateNegado() {
	
    int F5 = 1396, G5 = 1567, Ab5 = 1661, C6 = 2093, Cb5 = 1975, Bb5 = 1864, C5 = 1046, Fb5 = 1318, Eb5 = 1244;
	
	beep(F5,300);
	beep(G5,300);
	beep(Ab5,280);
	beep(C6,280);
	beep(Ab5,200);
	beep(Cb5,280);
	beep(Bb5,280);
	beep(Ab5,500);
	
	sleep(200);
	
	beep(C5,300);
	beep(Eb5,200);
	beep(Fb5,200);
	beep(F5,1000);
	
}

void Sound::empate() {
	
    int F5 = 1396, G5 = 1567, Ab5 = 1661, C6 = 2093, Cb5 = 1975, Bb5 = 1864, C5 = 1046, Fb5 = 1318, Eb5 = 1244, Db6 = 2217, A5 = 1760, F = 1479, E5 = 1318 ;

    beep(Db6,1000);
    beep(Db6,100);
    beep(Db6,100);
    beep(Db6,210);
    beep(C6,130);
    beep(Bb5,130);
    beep(Db6,180);
    beep(C6,130);
    beep(Bb5,130);
    beep(A5,1050);
    beep(A5,130);
    beep(A5,130);
    beep(A5,210);
    beep(Ab5,100);

    beep(F,100);
    beep(A5,210);
    beep(Ab5,100);
    beep(F,100);
    sleep(200);
    beep(F5,1000);
    beep(E5,1000);
    beep(Eb5,1000);
	
}

void Sound::assassinato(int round) {

	if (round % 2 == 0) {

		beep(1300,200);
		beep(900,200);
		return;

	}

	beep(900,200);
    beep(1300,200);

}

void Sound::requi() {

	int Fs4 = 739, D4 = 587, E4 = 659, F4 = 698, Cs4 = 554, B4 = 987, Cs5 = 1108, D5 = 1174, G5 = 1567, As4 = 932, G4 = 783;
	
	beep(Fs4,240);
	beep(D4,400);
	
	sleep(400);
	
	beep(D4,180);
	beep(E4,180);
	beep(F4,350);
	beep(E4,350);
	beep(D4,300);
	
	beep(Cs4,350);
	beep(D4,350);
	beep(E4,300);
	beep(Fs4,550);
	beep(Fs4,250);
	beep(B4,800);
	beep(B4,290);
	
	beep(Cs5,290);
	beep(D5,350);
	beep(G4,350);
	beep(Fs4,200);
	beep(F4,350);
	beep(D5,350);
	beep(As4,180);
	beep(1000,800);

}