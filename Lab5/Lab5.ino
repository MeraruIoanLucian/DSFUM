#define do  131
#define do_diez 139
#define re  147
#define re 156
#define mi  165
#define fa  175
#define fa_diez 185
#define sol  196
#define sol_diez 208
#define la  220
#define la_diez 233
#define si  247
 
// aici incepe cheia Sol (octava lui C4):
#define Do  262 
#define Do_diez 277
#define Re  294
#define Re_diez 311
#define Mi  330
#define Fa  349
#define Fa_diez 370
#define Sol  392 
#define Sol_diez 415
#define La  440
#define La_diez 466
#define Si  494
 
// aici incepe cheia sol cu o octava mai sus (octava lui C5)
#define DO  523
#define DO_diez 554
#define RE  587
#define RE_diez 622
#define MI  659
#define FA  698
#define FA_diez 740
#define SOL  784
#define SOL_diez 831
#define LA  880
#define LA_diez 932
#define SI  988

//TREI CULORI

/*int note[] = {
    Do,6,   Do,2,  Fa,12,  Fa,4, 
    Sol,6,  Do,2,  La,8,   Fa,8,
    Fa,6,   Mi,2,  Re,8,   Sol, 8,
    Fa,6,   Mi,2,  Fa,16,

    Do,6,   Do,2,  Fa,12,  Fa,4,
    Sol,6,  Do,2,  La,8,   Fa,8,
    Fa,6,   Mi,2,  Re,8,   La, 8,
    La,6,   Sol,2,La,16,

    La,6,   Si,2,  DO,12,  La,4,
    Si,6,   DO,2,  RE,8,   Si,4,  Sol,4,
    Fa,6,   Re,2,  Do,8,   Fa,8,
    La,6,   Sol,2, Fa,18                         
};
*/

//DESTEAPTA TE ROMANE

int note[] = {
    // Linia 1
    Do, 6,   Do, 2,   Fa, 12,  Fa, 4, 
    Sol, 6,  Do, 2,   La, 8,   Fa, 8,
    Fa, 6,   Mi, 2,   Re, 8,   Sol, 8,
    Fa, 6,   Mi, 2,   Fa, 16,
    
    // Linia 2
    Do, 6,   Do, 2,   Fa, 12,  Fa, 4,
    Sol, 6,  Do, 2,   La, 8,   Fa, 8,
    Fa, 6,   Mi, 2,   Re, 8,   La, 8,
    La, 6,   Sol, 2,  La, 16,
    
    // Linia 3
    La, 6,   Si, 2,   DO, 12,  DO, 4,
    Si, 6,   DO, 2,   RE, 8,   Si, 8,
    Sol, 8,  Mi, 8,   Do, 8,   Fa, 8,
    La, 6,   Sol, 2,  Fa, 16,
    
    // Linia 4
    La, 6,   Si, 2,   DO, 12,  DO, 4,
    Si, 6,   DO, 2,   RE, 8,   Si, 8,
    Sol, 8,  Mi, 8,   Do, 8,   Fa, 8,
    La, 6,   Sol, 2,  Fa, 16,
    
    // Linia 5
    Do, 6,   Do, 2,   Fa, 12,  Fa, 4,
    Sol, 6,  Do, 2,   La, 8,   Fa, 8,
    Fa, 6,   Mi, 2,   Re, 8,   La, 8,
    La, 6,   Sol, 2,  La, 16,
    
    // Linia 6
    La, 6,   Si, 2,   DO, 12,  DO, 4,
    Si, 6,   DO, 2,   RE, 8,   Si, 8,
    Sol, 8,  Mi, 8,   Do, 8,   Fa, 8,
    La, 6,   Sol, 2,  Fa, 16,
    
    // Linia 7
    La, 6,   Si, 2,   DO, 12,  DO, 4,
    Si, 6,   DO, 2,   RE, 8,   Si, 8,
    Sol, 8,  Mi, 8,   Do, 8,   Fa, 8,
    La, 6,   Sol, 2,  Fa, 16,
    
    // Linia 8 (identică cu linia 5)
    Do, 6,   Do, 2,   Fa, 12,  Fa, 4,
    Sol, 6,  Do, 2,   La, 8,   Fa, 8,
    Fa, 6,   Mi, 2,   Re, 8,   La, 8,
    La, 6,   Sol, 2,  La, 16
};
void setup() {
   for(int i=4; i<=7; i++)
   {
      pinMode(i,OUTPUT);
      digitalWrite(i,LOW);
    }
    int octava=1; // puteti schimba cu 2,4,8 pentru a incerca alta octava - uneori se aude mai bine
    for (int nota_curenta = 0; nota_curenta < 120; nota_curenta++) 
    {
      tone(3, note[nota_curenta*2] * octava, 100*note[nota_curenta*2+1]); // 3 = pinul cu buzzer-ul, nota, delay
      delay(100*note[nota_curenta*2+1] + 100);
      noTone(3);
    }  
}

void loop(){}