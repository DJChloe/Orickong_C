#include <lib.h>
#define plot(X,Y,C) poke(0xBBA8+(X)+(Y)*40,C)
#define scrn(X,Y) peek(0xBBA8+(X)+(Y)*40)

//temporisation animations tableaux
#define TEMPO1 50
#define TEMPO2 50
#define TEMPO3 50
#define TEMPO4 50
#define TEMPOFEU 10;
#define TEMPO_OK 1
#define INITTIMER 65535

//temporisation bonus
#define TEMPOB  200


#define PERDU 1

#define TONNEAU1 		91
#define TONNEAU2 		92
#define TONNEAU3 		93
#define TONNEAU4 		94
#define TAPIS1          123
#define TAPIS2          124
#define ADDR1TAPIS1     47064
#define ADDR2TAPIS1     47071
#define ADDR1TAPIS2     47072
#define ADDR2TAPIS2     47079
#define ADDRTAPIS0      47032
#define SAFE           0
#define OUCH           1
#define ENDLEVEL       2

#define BONHOMMESAUT   'a'
#define BONHOMMEGAUCHE 'e'
#define BONHOMMEDROITE 'd'
#define STRUCTLIFT     'c'
#define SOL            'b'
#define SOL2           'w' 
#define ECHELLE        'h'
#define PARAPLUIE      'i'
#define CHAPEAU		   'p'
#define GATEAU		   'r'
#define FEU		       't'
#define SAC            'q'	
#define PRINCESSE 	   'v'
#define RIVET          'g'
#define TAPISGAUCHE    95
#define TAPISDROITE    96
#define POUTRE          'y'
#define CABLE 		   'x'
#define PORTE 		   '&'
#define VIDE           ' ' 

#define MAXTONNEAUX     5

#define NBREASCENCEURS  3
#define NBREFEUX  4

//Language setting for compilation (comment this line for english)
//#define __FRENCH__

//Locales
#ifdef __FRENCH__
//FR
	#define MSG1FR "Pr!sente"
	#define MSG01  "Pr!sente"
	#define MSG02  "Touches :"
	#define MSG03  "Haut : [A]       Gauche : [K]"
	#define MSG04  " Bas : [Z]       Droite : [L]"
	#define MSG05  "Saut : [SPACE]    Pause : [P]"
	#define MSG06  "PRESSEZ UNE TOUCHE..."
	#define MSG07  "Cr!dit : Bertrand RAVEL,Tilt #11,1984"
	
	#define MSG11  "J'OUVRE    "
    #define MSG12  "LA GRILLE"
	
	#define MSGS1  "\n\nVOUS VENEZ DE REALISER L'UN"  
	#define MSGS2  "\nDES 7 MEILLEURS SCORES."
	#define MSGS3  "\nVOTRE NOM S.V.P :\n"
	
	#define MSGHH  "JUSQU'OU IREZ-VOUS ?"
#else
//EN
	#define MSG01  "Presents"
	#define MSG02  "Keys :"
	#define MSG03  "  Up : [A]         Left : [K]"
	#define MSG04  "Down : [Z]        Right : [L]"
	#define MSG05  "Jump : [SPACE]    Pause : [P]"
	#define MSG06  "PRESS A KEY..."
	#define MSG07  "Credit : Bertrand RAVEL,Tilt #11,1984"
	
	#define MSG11  "I OPEN     "
    #define MSG12  "THE GATE"
	
	#define MSGS1  "\n\nYOU JUST ACHIEVED ONE OF"
	#define MSGS2  "\nTHE BEST SCORES."  
	#define MSGS3  "\nWHAT'S YOUR NAME, PLEASE :\n" 
	
	#define MSGHH  "HOW HIGH CAN YOU GET ?"
#endif 
unsigned int temps;
void plots(char x,char y,const char *msg);

char rnd(char max);
void son1();
void goal();
void saut();
char fin_saut();
void saut_3eme();
char fin_saut_3eme();
char enleve_rivet();
char touche_action();
void how_high();
void affichage_data();
void animation_feu();
void tonneau_descend();
char affichage_bonus();
void chap_par_sac();
void wait(unsigned int wait_cs);

char x=0,y=0,level=0;
char a=0,b=0;
char a1=0; //dir saut
char vies=0; //vies
char ht=0,hauteur=0,t=0,tableaunum=0,otb; //t=0
unsigned int i=0,j=0,k=0,kk,score=0,saute=0,saut_special=0;
char tempo_tonneaux,nbre_tonneaux,co;
int bonus=0;
unsigned int timer1,timer2,timerbonus=0,timerg,timer_feu;
char anim_event,bonus_event;
int ch=0,ha=0;
int st=0,cp=0,l=0;
int c=0,dp=0,yp=0,yb=0,xb=0;
int iy=0,cb=0,y_poutre=0, x_poutre,an_poutre, xr,what_below=0;what_above=0;
int sb=0, sd=0, in=0,zx=0;
char rr=0,np=0,s=0,co=0;
int opendoor; //cl=0, 


//tonneaux
char xt[MAXTONNEAUX];
char yt[MAXTONNEAUX];
char at[MAXTONNEAUX]; //direction x
char bt[MAXTONNEAUX]; //direction y
char ot[MAXTONNEAUX]; //ancien caractere
char animt[MAXTONNEAUX]; //animation tonneau
char *xxt,*yyt,*aat,*oot,*ant;
char noot=0;
char tonneau_fincourse=0;
char animtapis=1,animfeu=0;
char xa[NBREASCENCEURS];
char ya[NBREASCENCEURS];
char *xxa,*yya;
char xa2[NBREFEUX];
char ya2[NBREFEUX];

char APS;
char bonhomme=BONHOMMEDROITE;
unsigned char touche;
char NS[20],affs[8];
char ABS,ARS,ASS;
char PLS[]="bbb";
char B2S[]="bb";
char BAS[]="ccx";
char ABSS[NBREFEUX]="    ";
char PLATFORM[]="ccccccccccc";
char PLATFORMDELETE[]="           ";
char ORICKONG[]="ORIC KONG";
char DKTOP[]="jkl";
char DKBOT[]="mno";



char redefchar[208]=   //208 +24
{
 12,45,45,63,12,12,18,33,	//(a) bonhomme tombe/saute
 63,63,4,10,17,32,63,63,	//(b) sol
 63,63,49,32,32,49,63,63,	//(c) 
 12,12,8,29,46,12,10,17,	//(d) bonhomme vers droite
 12,12,4,46,29,12,20,34,	//(e) bonhomme vers gauche
 0,0,0,28,58,54,46,28,		//(f) tonneau
 63,63,45,45,45,45,63,63,	//(g)
 63,33,63,33,63,33,63,33,	//(h) échelle
 4,14,31,21,4,4,20,28,		//(i) parapluie
 0,0,1,7,15,31,31,28,		//(j) DK haut
 0,63,45,63,51,45,63,51,	//(k) DK haut
 0,0,32,56,60,62,62,14,		//(l) DK haut
 12,7,7,3,7,7,7,15,			//(m) DK bas
 33,33,51,63,51,33,0,0,		//(n) DK bas
 12,56,56,48,56,56,56,60,	//(o) DK bas
 0,2,5,2,4,12,30,63,		//(p) CHAPEAU
 0,12,18,18,30,51,51,63,	//(q) SAC
 0,0,0,4,12,18,63,30,		//(r) gateau 
 12,30,31,31,15,7,3,1,		//(s) coeur gauche
 8,16,48,56,30,55,51,30,    //(t) Feu
 12,18,35,37,41,49,18,12,	//(u) engrenage tapis (animation ?)
 14,8,28,46,12,28,62,20,	//(v) princesse
 63,63,24,24,24,24,63,63,	//(w) tapis roulant
 32,32,32,32,32,32,32,32,	//(x)
 63,12,18,33,33,18,12,63,	//(y) Poids (sac ?)
 12,30,62,62,60,56,48,32	//(z) coeur droite
 };
 
 char redefchar2[48]=
{
0,0,0,28,58,54,46,28,  //91 tonneau 1      
0,0,0,28,62,0,62,28,   //92 tonneau 2
0,0,0,28,46,54,58,28,  //93 tonneau 3
0,0,0,20,54,54,54,20,   //94 tonneau 4
15,19,33,45,45,33,19,15, //tapis gauche (95)
60,50,33,45,45,33,50,60 //tapis droite (96)
};
 
char spritetapis[3]={56,15,51};
//'t'=116  -->‭47008‬
char spritefeu47008[6]={ 8,16, 8, 4, 2, 4};
char spritefeu47009[6]={16, 8, 4, 2, 4, 8};
char spritefeu47010[6]={24,12, 6, 6,12,24};
char spritefeu47011[6]={28,14,14,14,28,28};
char spritefeu47013[6]={55,59,55,59,55,59};


unsigned char screen1[246]=
{
	0x4c,0x5a,0x37,0x37,0x60,0x04,0xee,0x00,0xff,0x10,0x10,0x42,0x4f,0x4e,0x55,0x53,
	0x3a,0x7d,0x10,0x00,0x80,0x53,0x43,0x4f,0x52,0x45,0x11,0xa0,0x7e,0x1d,0x00,0x07,
	0x32,0x30,0x30,0x30,0x20,0x00,0xa0,0x6e,0x0e,0xa0,0x4c,0x3d,0x31,0x1d,0x10,0x10,
	0x07,0x23,0x90,0xb1,0x76,0x30,0xb0,0x3e,0x80,0x27,0x60,0x01,0x62,0x00,0x60,0x68,
	0x14,0x26,0xf0,0x4f,0x00,0x02,0x74,0x40,0x68,0x01,0x00,0x09,0x50,0x87,0x80,0xd7,
	0x64,0x20,0x33,0x77,0x30,0x03,0x9c,0x00,0x6a,0x6b,0xe3,0x6c,0x02,0x27,0xf0,0x77,
	0xb0,0x27,0x10,0x6d,0x6e,0x6f,0xc4,0x27,0xf0,0x9f,0xc0,0x01,0xec,0x00,0x9b,0x70,
	0x05,0x90,0x68,0x62,0x01,0x62,0x9f,0xf0,0x00,0xf0,0xa7,0xa0,0x27,0xf0,0x27,0xf0,
	0x27,0xf0,0x27,0xf0,0x00,0x9f,0xd0,0x8b,0x00,0x91,0x30,0xa6,0xb0,0x4f,0xe0,0xe3,
	0x30,0xe9,0xf0,0x27,0xf0,0x70,0x27,0xf0,0x27,0xf0,0x27,0xf0,0x19,0x62,0x00,0x0a,
	0x31,0x27,0x12,0x00,0x3f,0xf1,0xa6,0x70,0x3f,0x21,0x27,0x60,0xef,0xf0,0x98,0x51,
	0x17,0xf1,0x27,0xf0,0x00,0x27,0xf0,0x27,0xf0,0x27,0xf0,0x3f,0xd1,0x43,0xe1,0xef,
	0xf0,0x85,0xf1,0x17,0xf1,0x80,0x27,0xf0,0x27,0xf0,0x27,0xf0,0x24,0xf0,0x7f,0xf2,
	0x7f,0xf2,0x1f,0xe3,0x01,0xff,0x26,0x02,0x41,0x54,0x54,0x45,0x4e,0x44,0x1f,0x45,
	0x5a,0x2e,0x2e,0x2e,0xef,0xf0,0x27,0x80,0x1e,0xf1,0x02,0x27,0xf0,0x64,0x27,0xf0,
	0x3f,0xf1,0x9b,0xf0,0x3f,0xd1
};

unsigned char screen2[257]=
{
	0x4c,0x5a,0x37,0x37,0x60,0x04,0xf9,0x00,0xff,0x10,0x10,0x42,0x4f,0x4e,0x55,0x53,
	0x3a,0x7d,0x10,0x00,0x80,0x53,0x43,0x4f,0x52,0x45,0x11,0xa0,0x7e,0x1d,0x00,0x07,
	0x33,0x30,0x30,0x30,0x20,0x00,0xa0,0x6e,0x0e,0xa0,0x4c,0x3d,0x31,0x1d,0x10,0x10,
	0x07,0x23,0xb0,0xc0,0x00,0xf0,0x43,0x30,0x27,0xf0,0x00,0xf0,0x27,0xf0,0x00,0xf0,
	0x20,0x64,0xa3,0x20,0x33,0x27,0xf0,0x00,0xf0,0x4f,0x60,0x01,0xc3,0x70,0x62,0x68,
	0x01,0x00,0x00,0xf0,0x77,0xf0,0x68,0x01,0x00,0x20,0x76,0x23,0xf0,0x8e,0x27,0xe0,
	0x01,0x68,0x62,0x00,0x20,0x26,0xf0,0x77,0x60,0x6a,0x87,0x6b,0x6c,0x07,0x4f,0x20,
	0x57,0x20,0x00,0xf0,0x9f,0x50,0x6d,0x53,0x6e,0x6f,0x27,0xf0,0x77,0x90,0x03,0x8b,
	0x11,0x77,0x00,0xf0,0x00,0x0c,0x20,0x9f,0xe0,0x42,0xf0,0x14,0xc0,0x27,0xf0,0x27,
	0xf0,0x67,0xf1,0x0f,0x02,0x3b,0x74,0x74,0x14,0xb2,0x00,0x0a,0x35,0x27,0x12,0x9f,
	0x20,0xdf,0x5f,0x7b,0x7b,0x68,0x7b,0x00,0x10,0x68,0x7b,0x6f,0x60,0x3d,0x3d,0x5f,
	0x0c,0x60,0x7b,0x60,0x27,0x70,0x40,0xb7,0x41,0xe9,0xa0,0xf6,0xf0,0x27,0xf0,0x27,
	0xf0,0x27,0xe0,0x70,0x27,0xd0,0x21,0x69,0x67,0xd1,0xad,0x31,0xb5,0x41,0xbb,0x01,
	0x68,0x11,0x30,0xc0,0x81,0x00,0x07,0xb2,0x09,0xf0,0x27,0xf0,0x27,0xf0,0x27,0xf0,
	0x00,0xf0,0xdf,0xf1,0x3f,0xb1,0x00,0x06,0x80,0x3f,0x31,0xef,0xf0,0x17,0xf1,0x77,
	0xf0,0x27,0xf0,0x27,0xf0,0x1a,0xb0,0x01,0x71,0x27,0xf0,0x3f,0xc1,0x00,0xf0,0x00,
	0x83
};

unsigned char screen3[302]=
{
	0x4c,0x5a,0x37,0x37,0x60,0x04,0x26,0x01,0xff,0x10,0x10,0x42,0x4f,0x4e,0x55,0x53,
	0x3a,0x7d,0x10,0x00,0x80,0x53,0x43,0x4f,0x52,0x45,0x11,0xa0,0x7e,0x1d,0x00,0x07,
	0x32,0x30,0x30,0x30,0x20,0x00,0xa0,0x6e,0x0e,0xa0,0x4c,0x3d,0x31,0x1d,0x10,0x10,
	0x03,0x23,0xb0,0xc8,0x00,0xf0,0x43,0x30,0x27,0xd0,0x76,0x22,0xf0,0x27,0xd0,0x68,
	0x01,0xeb,0x68,0x62,0x00,0x10,0x68,0x85,0xa0,0x64,0x20,0x33,0x0e,0x4f,0x70,0x6a,
	0x6b,0x6c,0x27,0x00,0x01,0x00,0x2f,0x20,0x4d,0xf0,0xce,0x77,0x50,0x6d,0x6e,0x6f,
	0x27,0xf0,0x27,0xb0,0x01,0x20,0xe1,0x20,0x6d,0x20,0x03,0xb0,0x2b,0xe0,0xef,0x50,
	0x63,0x63,0x78,0x74,0x06,0x80,0x59,0x40,0x71,0x27,0xe0,0x01,0x20,0x78,0x20,0x11,
	0x84,0x06,0x00,0x4a,0x21,0x03,0xcb,0x20,0xd7,0x00,0x27,0xf0,0x27,0xd0,0x01,0x03,
	0x62,0x62,0x2d,0x30,0x27,0xf0,0x4f,0x70,0x24,0x00,0x55,0x60,0xc7,0x70,0x01,0x69,
	0x4f,0xb0,0xc8,0x00,0xc7,0x31,0x27,0xd0,0x5a,0x01,0x77,0x00,0x65,0x01,0x00,0x06,
	0x10,0x9c,0x00,0x79,0x71,0xef,0xd0,0x27,0x10,0xbb,0x00,0x27,0x60,0x2c,0x01,0x1c,
	0x9f,0x00,0x58,0x20,0x00,0x0a,0x35,0x27,0x12,0x27,0xf0,0x9c,0x50,0x00,0x43,0x42,
	0x27,0xf0,0x4f,0x50,0xc7,0x30,0x47,0xc2,0x27,0xf0,0x8b,0x42,0xf2,0x30,0x30,0x27,
	0xf0,0x27,0xd0,0x67,0xd1,0xdf,0x11,0x68,0x62,0x27,0xf0,0xbf,0x12,0x48,0x67,0xd1,
	0x7d,0x01,0xef,0x10,0x70,0x27,0xf0,0x27,0xf0,0x78,0x08,0x11,0x40,0x77,0xb0,0x70,
	0x61,0x4f,0xb0,0x07,0x82,0xc6,0xe0,0x47,0x23,0x64,0x27,0xd0,0x00,0x24,0xd0,0xa7,
	0x72,0x2f,0x82,0x6d,0x90,0x2f,0xf2,0x77,0xd0,0x27,0xf0,0xcf,0xf2,0xf0,0x00,0xf0,
	0x1f,0x33,0x21,0xf3,0x06,0x80,0x20,0x20,0x20,0x20,0x07,0x20,0x20,0x20
};

unsigned char screen4[262]=
{
	0x4c,0x5a,0x37,0x37,0x60,0x04,0xfe,0x00,0xff,0x10,0x10,0x42,0x4f,0x4e,0x55,0x53,
	0x3a,0x7d,0x10,0x00,0x80,0x53,0x43,0x4f,0x52,0x45,0x11,0xa0,0x7e,0x1d,0x00,0x07,
	0x33,0x30,0x30,0x30,0x20,0x00,0xa0,0x6e,0x0e,0xa0,0x4c,0x3d,0x31,0x1d,0x10,0x10,
	0x03,0x23,0xb0,0xc0,0x00,0xf0,0x43,0x30,0x27,0xf0,0x00,0xf0,0x27,0xf0,0x00,0xf0,
	0x20,0x64,0xa3,0x20,0x33,0x27,0xf0,0x00,0xf0,0x4f,0x60,0x05,0x13,0xc0,0x76,0x54,
	0x23,0xf0,0x4f,0x20,0x04,0xeb,0x70,0x63,0x00,0x90,0x78,0x9f,0xc0,0xe1,0x01,0x13,
	0x91,0x1c,0x60,0x25,0xc0,0x27,0xf0,0x20,0x6a,0x6b,0xe9,0x6c,0x27,0xf0,0x27,0x80,
	0x69,0x4f,0x40,0x6d,0x6e,0x6f,0x3c,0x27,0xf0,0x9f,0x80,0x68,0x63,0x63,0x67,0x03,
	0x00,0xa3,0x40,0x03,0x68,0x67,0x03,0x00,0x3f,0xf1,0x27,0x10,0x03,0x40,0x0d,0xf0,
	0x27,0xf0,0x70,0x27,0xf0,0x27,0xf0,0x27,0xf0,0x27,0x30,0x00,0x0a,0x35,0x27,0x12,
	0x00,0x3f,0x51,0x9a,0x10,0x93,0x00,0x9a,0x10,0x46,0x21,0x0b,0x10,0x50,0x20,0x27,
	0x50,0x00,0xb7,0x41,0x4a,0xb0,0x09,0xd0,0x27,0xf0,0x09,0xf0,0x27,0xf0,0x09,0xf0,
	0x3f,0xe1,0x02,0x39,0x21,0x67,0x9b,0x40,0xa3,0x10,0xab,0x20,0xf1,0x80,0x57,0x42,
	0x03,0x41,0x40,0x0a,0x51,0x0e,0xc0,0x27,0xf0,0x27,0xf0,0x27,0xf0,0x27,0xd0,0x70,
	0x27,0xa0,0x00,0x7f,0x22,0x33,0x71,0x3f,0x91,0xe2,0x91,0xf7,0x32,0xa2,0x91,0x0b,
	0xf0,0x27,0xf0,0x08,0x0b,0xf0,0x27,0xf0,0xda,0x91,0x71,0x27,0xf0,0x1f,0x13,0x18,
	0xa3,0x03,0xb0,0x00,0x26,0x53
};

unsigned int hs[7]={60,50,30,20,21,10,1};
char HSS[7][16]=
{
	"LADYWASKY",
	"MAXIMUS",
	"KENNETH",
	"DBUG",
	"ISS",
	"SYMOON",
	"TILT"
};

void main()
{	
	x=9;
	y=25;
	vies=3;
	level=1; 	
	
	
	
	//presentation
L_Presentation:
	text(); cls(); paper(0); ink(7); zap();
	setflags(SCREEN+NOKEYCLICK);
	poke(0x020C,0xff); //Caps Lock
	play(7,0,0,0);

#ifdef __FRENCH__	
	//é (!)
	memcpy((unsigned char*)46344,(unsigned char*)46888,8);
	poke(46344,4);
	poke(46345,8);
#endif
	
	memcpy((unsigned char*)46560,redefchar+144,8);
	memcpy((unsigned char*)46576,redefchar+200,8);
    // TITRE
	
	
	memset((unsigned char*)48000, A_BGBLUE, 40);
	plots(10,-1,"<> CHLOE AVRILLON <>");
	plot(9,-1,A_FWRED); plot(12,-1,A_FWWHITE);
	plot(27,-1,A_FWRED); plot(30,-1,A_FWWHITE);
	plot(0,0,A_BGBLUE);
	plots(16,0,MSG01);
	plot(1,7,A_FWYELLOW); //1,11
	plot(2,7,A_STD2HFL); //2,11
	plots(14,7,ORICKONG);
	plot(1,8,A_FWYELLOW);//1,12
	plot(2,8,A_STD2HFL);
	plots(14,8,ORICKONG);
	for (i=48441;i<=48681;i+=40) poke(i,A_FWGREEN);
	plots(2,12,MSG02);
	plots(7,14,MSG03);
	plots(7,15,MSG04);
	plots(7,16,MSG05);
	plots(2,23,MSG06);
	plot(0,26,A_BGBLUE);plot(1,26,A_FWWHITE);
	plots(2,26,MSG07);
	
	get();
	for (i=48000;i<=48039;i++) poke(i,A_BGBLACK);
	
	memcpy((unsigned char*)46856,redefchar,208);
	memcpy((unsigned char*)46808,redefchar2,48);
	
	for (i=46384;i<=46390;i+=2){
		poke(i,62); poke(i+1,42);
	}
	
	memcpy((unsigned char*)ADDR1TAPIS1,(unsigned char*)ADDRTAPIS0,8);
	memcpy((unsigned char*)ADDR1TAPIS2,(unsigned char*)ADDRTAPIS0,8);
	
	poke(ADDR1TAPIS1,spritetapis[0]);
	poke(ADDR2TAPIS1,spritetapis[2]);
	poke(ADDR1TAPIS2,spritetapis[2]);
	poke(ADDR2TAPIS2,spritetapis[0]);
	score=0;

 // *** TABLEAU 1 ***
 tableau1:
    doke(0x0276,INITTIMER);
	tableaunum=1;
	how_high();
	timer1=INITTIMER; timer2=TEMPO1/3;	
	co=0;
	anim_event=1;
	
	bonus_event=1;
	opendoor=1;
	bonhomme=BONHOMMEDROITE;
    saute=0;
	if (level>2) {ht=0;} else ht=4;
	if (level==1) bonus=20; else bonus=30;
	
	x=9;y=25;APS=VIDE; nbre_tonneaux=0; a1=1;
    /* affichage_data();
	plot(x,y,bonhomme);
	
	plot(12,25,A_FWGREEN);
	plot(12,24,A_FWGREEN);
	plot(12,23,A_FWGREEN);
	plot(11,25,PORTE);
	plot(11,24,PORTE);
	plot(11,23,PORTE);
	plot(10,25,A_FWRED);
	plot(10,24,A_FWRED);
	plot(10,23,A_FWRED);
	plots(13,23,"ATTENDEZ...");
	
	//for (i=26,j=1040;i>=6;i-=4, j-=160)
	for (i=1040;i>=240;i-=160)
	{
		poke(48042+i,A_FWRED); poke(48002+i,A_FWGREEN); 
		poke(47962+i,A_FWGREEN); poke(47922+i,A_FWGREEN);		
		memset((unsigned char*)48046+i, 'b', 25);
	}
	
	
	plot(2,4,A_FWYELLOW); plot(2,5,A_FWYELLOW); 
	plots(6,4,DKTOP); plots(6,5,DKBOT);
	plot(9,4,A_FWGREEN); plot(9,5,A_FWGREEN);
	for (i=22;i<=25;i++) plot(28,i,ECHELLE);
	for (i=18;i<=21;i++){ plot(8,i,ECHELLE); plot(18,i,ECHELLE);}
	for (i=14;i<=17;i++){ plot(21,i,ECHELLE); plot(28,i,ECHELLE);}
	for (i=10;i<=13;i++){ plot(8,i,ECHELLE); plot(14,i,ECHELLE);}
	for (i=6;i<=9;i++) 	plot(28,i,ECHELLE);
	for (i=3;i<=5;i++){ plot(10,i,ECHELLE); plot(12,i,ECHELLE); plot(20,i,ECHELLE);}

	plot(9,2,A_FWRED); 
	//plots(10,2,"bbbbbbbbbbh");
	memset((unsigned char*)48130, SOL, 10); plot(20,2,ECHELLE);
	plot(33,3,BONHOMMEDROITE); 
	plot(14,1,PRINCESSE);
	
	plot(34,13,A_STD2H); plots(35,13,"100");
	plot(34,14,A_STD2H); plots(35,14,"100"); */
	file_unpack((unsigned char*)48000,screen1);
#ifndef __FRENCH__
	plots(13,23,"WAIT...    ");
#endif
	plots(35,3,itoa(vies));
	//init tonneaux
	co=0;
	tempo_tonneaux=rnd(8)+6;
	for(i=0;i<MAXTONNEAUX;i++){
		xt[i]=9;yt[i]=5;at[i]=1; ot[i]=2;
		animt[i]=TONNEAU1;
	}
	cp=0;
	nbre_tonneaux=1;
	
	// == ACTION ==
 L250:
 
    timerg=deek(0x0276);
	if (timer1>=timerg) 
	{		
		anim_event=1;
		timer1=timerg-timer2;		
	} else anim_event=0;
	
	
	if ((timerbonus>=timerg) && (bonus_event==1))
	{
		//hide bonus
		plot(33,13,0);
		plot(33,14,0);
		bonus_event=0;
	} 
	if (saute!=1) plot(x,y,bonhomme);
    if (score==0) plots(20,0,"0        ");	
	else {gotoxy(20,1); printf("%d00 ",score);}
	
	if (opendoor==1) {
		switch(nbre_tonneaux)
		{
			case MAXTONNEAUX :
				opendoor=0;
				plots(13,24,"GO  ");
				wait(30);
				for (i=23;i<=25;i++){
					plots(10,i,"   ");
					wait(30);
				}
				plots(13,24,"    ");
				timer2=TEMPO1/level;
				break;
			case MAXTONNEAUX-1 :
				//plots(10,24,"   ");
				plots(13,24,"1...");
				break;
			case MAXTONNEAUX-2 :
			    //plots(10,23,"   ");
				plots(13,24,"2...");
				break;
			case MAXTONNEAUX-3 :
			    plots(13,23,"           ");
			    plots(13,24,"3...     ");
				break;
			case MAXTONNEAUX-4 :			    
				plots(13,23,MSG11);
				plots(13,24,MSG12);
				break;
		}
	}
		
	if (nbre_tonneaux<MAXTONNEAUX) goto L_tonneaux;
	if (saute==1){
	   if(anim_event==1) {
		   rr=fin_saut();
		   if (rr==OUCH) goto L_perte;
		   if (rr==ENDLEVEL) goto L_fin;
	   }
	   goto L250;
	}
	a=0; b=0;
	touche_action();
	
	if ((APS>=TONNEAU1)&&(APS<=TONNEAU4)) goto L_perte;
	if ((y==5) && (x<16)) goto L_Presentation;
	if (scrn(x,y+1)==VIDE) goto L_Chute;
	if (y==1) { 	  
	  goal(); goto tableau2;};
	if (a!=0) a1=a;
	a=0;b=0;
	//co=co+1;
	//if (co==5) { co=0; timer2=TEMPO1; goto L250; };
    
	// ==  TONNEAUX  ==
 L_tonneaux: 
    if(anim_event==1) 
	{
		for(t=0;t<nbre_tonneaux;t++) 
		{   
			tonneau_fincourse=0;
			xxt=&xt[t];
			yyt=&yt[t];
			aat=&at[t];
			oot=&ot[t];
			ant=&animt[t];
			plot(x,y,bonhomme);
			plot(*xxt,*yyt,*oot);
			noot=scrn(*xxt+*aat,*yyt);
			if (!((noot>=TONNEAU1)&&(noot<=TONNEAU4)))
			{
				*xxt=*xxt+*aat;
				*ant+=*aat;
				if (*ant>TONNEAU4) *ant=TONNEAU1;
				if (*ant<TONNEAU1) *ant=TONNEAU4;
			}
			*oot=scrn(*xxt,*yyt);			
			plot(*xxt,*yyt,*ant);
			if ((*xxt==x) && (*yyt==y)) goto L_perte;
			if ((*yyt==25) && (*xxt<6)) tonneau_fincourse=1;
			if (*xxt<6){
				*aat=1;
				tonneau_descend();
				if (affichage_bonus()==PERDU) goto L_perte;
			}
			if (*xxt>30){
				*aat=-1;
				tonneau_descend();
				if (affichage_bonus()==PERDU) goto L_perte;
			}
			if (*yyt>(y+ht)) tonneau_fincourse=1;
			if (scrn(*xxt,(*yyt+1))==ECHELLE){
				s=rnd(3);
				if (s==2){ 
					*aat=-*aat;
					tonneau_descend();
				}
			};	
			
			if (tonneau_fincourse==1)
			{
				plot(*xxt,*yyt,*oot);	
				*xxt=9; *yyt=5;
				*oot=2;
				*ant=TONNEAU1;
				*aat=1;
			}
		}
		
		if (nbre_tonneaux<MAXTONNEAUX){
			cp+=1;
			if (cp>tempo_tonneaux) {cp=0; tempo_tonneaux=rnd(8)+6; nbre_tonneaux+=1;};
		}
	};	
	goto L250;
	
 L_perte:
	// *** PERTE ***
	otb=scrn(x,y);
	for(i=0;i<5;i++){
		plot(x,y,BONHOMMESAUT);
		wait(20);
		plot(x,y,otb);
		wait(20);
	}
	play(7,0,0,0);
	for (i=11;i>=1;i--)
	{
		music(1,4,i,7);
		wait(10);
		if (j==1) 
		{
			wait(20); j=0;
		}
		else j=1;
	}
	wait(20);
	shoot();
	wait(100);
	a=0;b=0;t=0;bonhomme=BONHOMMEDROITE;
	vies-=1;
	if (vies==0){
		plots(14,11,"           ");
		plots(14,12," GAME OVER ");
		plots(14,13,"           ");
		goto maj_scores;
	}
	switch(tableaunum)
     {
      case 1:   
      goto tableau1;
      break;
      
      case 2:   
      goto tableau2;
      break;
      
      case 3:   
      goto tableau3;
      break;
	  
	  case 4:   
      goto tableau4;
      break;
     }
maj_scores:
	wait(100);
	t=0;
	while ((score<=hs[t]) && (t<7)) t++;
	if (t!=7) 
	{
		cls(); ink(2);	
		for (l=5;l>=t;l--) 
		{
			strcpy(HSS[l+1],HSS[l]);
			hs[l+1]=hs[l];
		}
		hs[t]=score;
		printf(MSGS1);
		printf(MSGS2);
		printf(MSGS3);
		gets(NS);
		NS[15]=0;
		strcpy(HSS[t],NS);
	}

	cls(); ink(2);
	printf("\n%c%cN%cQ          --- ORIC KONG ---\n",4,27,27);
	printf("%c\n\n",A_FWBLUE);
	for (i=0;i<7;i++){
		for (j=0;j<5-strlen(itoa(hs[i]));j++) affs[j]=' ';
		affs[j]=0;
		strcat(affs,itoa(hs[i]));		
		printf("-%d- %s00    %s\n\n",i,affs,HSS[i]);
	}
	
	for (i=0;i<4;i++){
		plot(1,2*i+4,i);
	}
	wait(200);
	plots(2,23,MSG06);
	get();
	vies=3; level=1; score=0; t=score; goto tableau1;

// *** TABLEAU 2 ***
tableau2:
	doke(0x0276,INITTIMER);
	tableaunum=2; dp=6; yp=21; 
	how_high(); 
	timer1=INITTIMER; timer2=TEMPO2/level;
	anim_event=1;
	bonus_event=1;	
	timer_feu=INITTIMER;
    saute=0;	
	yb=17;xb=17;ABS=VIDE;bonus=30;
	bonhomme=BONHOMMEDROITE; 
	x=10; y=25; APS=VIDE; a1=1;
	animtapis=0;
	
	/* affichage_data();
	plot(x,y,bonhomme);
	plot(33,3,BONHOMMEDROITE);
	ink(7);
	plot(1,26,A_FWRED); plot(1,18,A_FWRED);
	
	memset((unsigned char*)49086, SOL, 24);
	memset((unsigned char*)48766, SOL, 24);
	plot(1,10,A_FWYELLOW); plot(1,14,A_FWYELLOW); plot(1,22,A_FWYELLOW); 
		
	memset((unsigned char*)48446, SOL2, 24);
	
	memset((unsigned char*)48926, TAPIS1, 24);
	memset((unsigned char*)48606, TAPIS1, 10);
	memset((unsigned char*)48620, TAPIS1, 10);
	plot(11,18,VIDE); plot(23,18,VIDE); 
	for (i=14;i<=17;i++){
		plot(14,i,ECHELLE); plot(21,i,ECHELLE); 
		plot(8,i,ECHELLE); plot(27,i,ECHELLE);
	}
	for (i=22;i<=25;i++){
		plot(14,i,ECHELLE); plot(21,i,ECHELLE); 
		plot(8,i,ECHELLE); plot(27,i,ECHELLE);
	}
	plots(17,14,"=="); plot(5,14,TAPISGAUCHE); 
	plot (16,14,TAPISDROITE); plot (19,14,TAPISGAUCHE);
	plot(30,14,TAPISDROITE); plot(5,22,TAPISGAUCHE); plot(30,22,TAPISDROITE); 
	for (i=18;i<=20;i++){
		plot(12,i,ECHELLE); plot(22,i,ECHELLE);
	}
	plot(17,25,SAC); plot(12,17,CHAPEAU); plot(29,17,PARAPLUIE); 
	for (i=11;i<=12;i++){
		plot(7,i,ECHELLE); plot(28,i,ECHELLE);
	}
	plot(1,8,A_FWRED); plot(1,9,A_FWRED); plots(8,8,DKTOP);
	plots(8,9,DKBOT); plot(11,8,A_FWWHITE); plot(11,9,A_FWWHITE); 
	for (i=6;i<=9;i++){
		plot(12,i,ECHELLE); plot(14,i,ECHELLE);
	}
	plot(1,5,A_FWRED); plots(12,5,"b b"); 
	for (i=8;i<=9;i++){
		plot(20,i,ECHELLE);
	}
	plot(13,7,A_FWRED); plots(15,7,"bbbbbb"); 
	plot(17,6,PRINCESSE);plots(17,13,"tt"); 
	
	plot(34,13,A_STD2H); plots(35,13,"500");
	plot(34,14,A_STD2H); plots(35,14,"500"); */
	file_unpack((unsigned char*)48000,screen2);
	plots(35,3,itoa(vies));
L3200:
	timerg=deek(0x0276);
	
	if (timer1>=timerg) 
	{		
		anim_event=1;
		timer1=timerg-timer2;		
	} else anim_event=0;
	
	if (timer_feu>=timerg) 
	{
		animation_feu();
		timer_feu=timerg-TEMPOFEU;		
	};
	
	if ((timerbonus>=timerg) && (bonus_event==1))
	{
		//hide bonus
		plot(33,13,0);
		plot(33,14,0);
		bonus_event=0;
	} 
	
	if (saute!=1) plot(x,y,bonhomme);
	if (saute==1){
	   if(anim_event==1) {
		   rr=fin_saut();
		   if (rr==OUCH) goto L_perte;
		   if (rr==ENDLEVEL) goto L_fin;
	   }
	   goto L3200;
	}
	if (score==0) plots(20,0,"0        ");	
	else {gotoxy(20,1); printf("%d00 ",score);}
	
	touche_action();	
	if(anim_event==1) 
	{
		//bonhomme sur le tapis
		if ((y==21) && (iy==1)) {
			plot(x,y,VIDE); x+=1; iy=0 ; goto L3220;
		}
		if ((y==13) && (x>18)){
			plot(x,y,VIDE); x-=1; iy=0 ; goto L3220;
		}
		if ((y==13) && (x<17)){
			plot(x,y,VIDE); x+=1;
		}
		iy=1;
	}
L3220:

	//collisions joueur
	s=scrn(x,y);
	if ((s==PARAPLUIE)||(s==CHAPEAU)||(s==SAC)) chap_par_sac();
	if (y==5){
		y=6;
		goal();
		goto tableau3;
	}	
	
	
	//nouvelle version
	if (scrn(x,y+1)==VIDE) goto L_Chute;
	//fin
	if (s==FEU) goto L_perte;
	
	if(anim_event==1) 
	{
		
		//deplacement gateau (ou crotte ???)
		if (dp>29) {
			dp=6; yp=21 ; plot(30,21,VIDE);
		}
		plot(dp,yp,VIDE);
		dp+=1;
		if (scrn(dp,yp)!=VIDE) goto L_perte;
		plot(dp,yp,GATEAU);
		
		//deplacement FEU
		s=rnd(2); if (s==0) s=-1;
		plot(xb,yb,ABS);
		xb=xb+s;
		if ((xb<12) || (xb>22))xb=xb-s;
		sb=scrn(xb,yb);
		if ((sb!=VIDE) && (sb!=ECHELLE) && (sb!=CHAPEAU)) goto L_perte;
		ABS=scrn(xb,yb);
		plot(xb,yb,FEU);
		cb+=1;
		if (cb==5) {
			cb=0;
			if (affichage_bonus()==PERDU) goto L_perte;
		}
	
	
		poke(ADDR1TAPIS1,spritetapis[animtapis]);
		poke(ADDR2TAPIS1,spritetapis[2-animtapis]);
		poke(ADDR1TAPIS2,spritetapis[2-animtapis]);
		poke(ADDR2TAPIS2,spritetapis[animtapis]); 
		animtapis+=1;
		if(animtapis>2) animtapis=0;
		
		plot(x,y,bonhomme);
	}
	goto L3200;

// *** TABLEAU 3 ***
//Il faut ramasser la CHAPEAU pour afficher les echelles
//Mais oublié dans jeu original	(celà dit, mal placé)

tableau3:	
	doke(0x0276,INITTIMER);
	tableaunum=3; x=4; y=22; how_high();
	saut_special=0;
	timer1=INITTIMER; timer2=TEMPO3;
	if (level>1) timer2=TEMPO3/2;
	timer_feu=INITTIMER;
	anim_event=1;
	bonus_event=1;
    saute=0;	
	bonus=20; xb=16; yb=5;
	bonhomme=BONHOMMEDROITE; APS=VIDE; a1=1;
	an_poutre=0; x_poutre=23; y_poutre=4;
	ARS=VIDE; ABS=VIDE; 
	for (i=0;i<NBREASCENCEURS;i++) xa[i]=15;
	ya[0]=14; ya[1]=18; ya[2]=22;
	
	/* affichage_data();
	
	plot(x,y,bonhomme);
	plot(33,3,BONHOMMEDROITE); 
	ink(3); plot(1,0,A_FWWHITE);
	for (i=8;i<=24;i++){
		plot(7,i,A_FWRED); plot(10,i,A_FWYELLOW); plot(14,i,A_FWRED);
	}
	plot(1,26,A_FWRED);
	memset((unsigned char*)49086, SOL, 27);
	plot(1,23,A_FWRED);
	plots(4,23,PLS); plots(18,23,PLS);
	plot(1,12,A_FWRED); plot(1,18,A_FWRED);
	plots(4,12,PLS); plots(4,18,PLS);
	memset((unsigned char*)48284, SOL, 19);
	plot(1,6,A_FWRED);
	for (i=6;i<=9;i++) plot(23,i,ECHELLE);
	plots(11,12,"hbh"); plots(11,20,PLS); plot(10,20,A_FWRED);
	for (i=13;i<=19;i++) plots(11,i,"h h");
	
	plot(1,11,A_FWRED); plots(19,11,PLS); plots(28,20,PLS);
	
	plots(22,22,B2S); plots(25,21,B2S); 
	plots(23,15,B2S); plots(20,14,B2S);
	plots(23,10,B2S);
	plots(26,9,B2S); plots(29,8,B2S); 
	plots(26,16,B2S); plots(29,17,B2S);
	for (i=8;i<=12;i++) plot(29,i,ECHELLE);
	plots(26,13,"bbbbb");	
	for (i=18;i<=22;i++) plot(5,i,ECHELLE);
	for (i=12;i<=17;i++) plot(6,i,ECHELLE);
	for (i=17;i<=19;i++) plot(29,i,ECHELLE);
	plot(28,8,A_FWRED); plot(25,9,A_FWRED); plot(22,10,A_FWRED);
	plot(25,13,A_FWRED); plot(25,16,A_FWRED); plot(28,17,A_FWRED);
	plot(21,22,A_FWRED); plot(24,21,A_FWRED); 
	plot(22,15,A_FWRED); plot(19,14,A_FWRED);
	for (i=9;i<=11;i++) plot(28,i,A_FWYELLOW);
	plot(19,12,A_FWYELLOW);
	plot(25,15,A_FWYELLOW); plot(25,14,A_FWYELLOW);
	
	plots(8,7,BAS); plots(15,7,BAS);
	plots(8,25,BAS); plots(15,25,BAS);
	plots(6,4,DKTOP); plots(6,5,DKBOT);
	for (i=3;i<=5;i++) plots(11,i,"h h");
	plot(19,4,ECHELLE); plot(19,5,ECHELLE);
	plots(14,3,"bbbbbh");
	plot(12,3,A_FWRED);
	plot(29,7,SAC); plot(4,11,PARAPLUIE); plot(12,19,CHAPEAU);
	plot(16,2,PRINCESSE); plot(x,y,bonhomme);
	for (i=8;i<=24;i++){
		plot(9,i,CABLE); plot(16,i,CABLE);
	}
	plot(22,8,A_FWYELLOW); plot(22,9,A_FWYELLOW);
	plot(25,18,A_FWYELLOW); plot(25,19,A_FWYELLOW);
	plot(19,13,A_FWYELLOW); plot(22,13,A_FWRED);
	plot(10,12,A_FWRED);
	plot(34,13,A_STD2H); plots(35,13,"500");
	plot(34,14,A_STD2H); plots(35,14,"500"); */
	
	file_unpack((unsigned char*)48000,screen3);
	plots(35,3,itoa(vies));
	// *** ASCENSEURS ***
L_ascenseurs:
	timerg=deek(0x0276);
	if (timer1>=timerg) 
	{		
		anim_event=1;
		timer1=timerg-timer2;		
	} else anim_event=0;
	
	if (timer_feu>=timerg) 
	{
		animation_feu();
		timer_feu=timerg-TEMPOFEU;		
	};
	
	if ((timerbonus>=timerg) && (bonus_event==1))
	{
		//hide bonus
		plot(33,13,0);
		plot(33,14,0);
		bonus_event=0;
	} 
	
	if (saute!=1) plot(x,y,bonhomme);
	if (saute==1){
	   if(anim_event==1) {
		   rr=fin_saut_3eme();
		   if (rr==PERDU) goto L_Chute;
	   }
	   goto L_ascenseurs;
	}
	
	if(anim_event==1) 
	{		
		//deplacement ascenceur
		for (i=0;i<NBREASCENCEURS;i++)
		{
			xxa=&xa[i];
			yya=&ya[i];
			plots(*xxa,*yya," x"); //cable ascenceur
			if (*xxa==8) *yya-=1; else *yya+=1;
			if (*yya==8) *xxa=15;
			if ((*yya==24) && (*xxa==15)) *xxa=8;
			plots(*xxa,*yya,B2S);
		}
		
		//deplacement bonhomme sur l'ascenceur
		if (((x==15) || (x==16)) && (y>7)) {
			plot(x,y,APS); y+=1;
		}
		if ((x==8) || (x==9)) y-=1;
		if (y>24) goto L_perte;
	    
		
		//deplacement poutre
		plot(x_poutre,y_poutre,ARS);
		an_poutre+=1;
		if (an_poutre==29) {
			an_poutre=0; 
			if (affichage_bonus()==PERDU) goto L_perte;
		}
		
		if (an_poutre==0) {x_poutre=23; y_poutre=4;}
		else 
		{
			if ((an_poutre==2)||(an_poutre==7)
				||(an_poutre==14)||(an_poutre==15)||(an_poutre==16)) {
				if ((x==x_poutre) &&((y+1)==y_poutre)){
					plot(x,y,APS); x+=1;
					APS=scrn(x,y);plot(x,y,bonhomme);
				}				
				x_poutre+=1;
			}
			else if ((an_poutre==21)||(an_poutre==23)
				     ||(an_poutre==24)||(an_poutre==25)){
						if ((x==x_poutre)&&((y+1)==y_poutre)) {
							plot(x,y,APS);  x-=1;
							APS=scrn(x,y);plot(x,y,bonhomme);
							}
						x_poutre-=1;
					}					
					else {
						if ((x==x_poutre)&&((y+1)==y_poutre)){
							plot(x,y,APS);  y+=1;
							APS=scrn(x,y);plot(x,y,bonhomme);
						}
						y_poutre+=1;
					}						
		}
		sb=scrn(x_poutre,y_poutre);
		if ((sb==BONHOMMEDROITE) || (sb==BONHOMMEGAUCHE)) goto L_perte;
		ARS=scrn(x_poutre,y_poutre);
		plot(x_poutre,y_poutre,POUTRE);
		
		
				
		//deplacement FEU
		s=rnd(2);
		if (s==0) s=-1;
		plot(xb,yb,ABS);
		xb+=s;
		if ((xb<15) || (xb>22)) xb-=s;
		sb=scrn(xb,yb);
		if ((sb!=VIDE) && (sb!=ECHELLE)) goto L_perte;
		ABS=scrn(xb,yb);
		plot(xb,yb,FEU);
		
		if ((ARS==BONHOMMESAUT) || (ARS==BONHOMMEDROITE) || (ARS==BONHOMMEGAUCHE)) 
			goto L_perte;
	}	
	
	
	//actions joueur
	
	if (score==0) plots(20,0,"0        ");	
	else {gotoxy(20,1); printf("%d00 ",score);}
	
	switch(touche_action())
	{
		case 0:
			goto L5900;
			break;
		case ' ':
			if (bonhomme!=BONHOMMESAUT) {
				saut_3eme();
				goto L_ascenseurs;
			}
			break;
	}
		
	/*
	
	touche=key();
	if (touche==0) goto L5900;
	what_below=scrn(x,y+1);what_above=scrn(x,y-1);
	if ((touche=='L') && ((what_below!=ECHELLE) || (APS!=ECHELLE)))
	{
		if ((bonhomme==BONHOMMEGAUCHE)||(bonhomme==BONHOMMESAUT)) 
			{
				bonhomme=BONHOMMEDROITE;
				a=0; a1=1;
			}
		else a=1;
	}
	if ((touche=='K') && ((what_below!=ECHELLE) || (APS!=ECHELLE))) 
	{
		if ((bonhomme==BONHOMMEDROITE)||(bonhomme==BONHOMMESAUT)) 
			{
				bonhomme=BONHOMMEGAUCHE;
				a=0; a1=-1;
			}
			else a=-1; 
	}
	if ((touche=='A') && ((what_above==ECHELLE) || (APS==ECHELLE))) 
	{
		b=-1; bonhomme=BONHOMMESAUT; a=0;
	}
	if ((touche=='Z') && (what_below==ECHELLE)) 
	{
		b=1; bonhomme=BONHOMMESAUT; a=0;
	}
	if ((touche==' ')&&(bonhomme!=BONHOMMESAUT)) {
		saut_3eme();
		goto L_ascenseurs;
	}
	if (touche=='P') get();	
    
	plot(x,y,APS);
	x+=a; y+=b; 	
	if ((y==5) && (x<15)) {x=15;}
	else {if ((a+b)!=0) APS=scrn(x,y);}
	if (a!=0) a1=a;
	a=0; b=0;
	
	*/
	st=scrn(x,y);
	if ((st==PARAPLUIE) || (st==CHAPEAU) || (st==SAC)) chap_par_sac();
	if ((st==FEU) || (st==POUTRE)) 
		goto L_perte;
L5900:
	plot(x,y,bonhomme);
	st=scrn(x,y+1);
	//bonhomme ecrase entre ascenceur et "plafond"
	if (scrn(x,y-1)==STRUCTLIFT) goto L_perte; 
	if ((st==VIDE) || (st<7)) goto L_Chute;
	
	if (y==2){
		goal();
		goto tableau4;
	}
		
	goto L_ascenseurs;

// *** TABLEAU 4 ***
tableau4:
	doke(0x0276,INITTIMER);
	tableaunum=4;
	how_high();
	cls();
	timer1=INITTIMER; timer2=TEMPO4/level;
	
	timer_feu=INITTIMER;
	
	saute=0;
	anim_event=1;
	bonus_event=1;	
	bonus=30;
	np=0;
	
	
	/* affichage_data();
	
	ink(3);
	plot(1,0,A_FWWHITE);
	plot(33,3,BONHOMMEDROITE);
	
	plots(12,6,"cccccccccccccx");
	plots(9,10,"cccgcccccccccccgccc");
	plots(8,14,"ccccgcccccccccccgcccc");
	plots(7,18,"cccccgcccccccccccgccccc");
	plots(6,22,"ccccccgcccccccccccgcccccc");
	
	memset((unsigned char*)49085, 'c', 27);
	plot(32,26,CABLE);
	for (i=6;i<=26;i+=4) plot(1,i,A_FWBLUE);
	plot(1,5,A_FWMAGENTA);
	plot(17,5,PRINCESSE);
	for (i=7;i<=9;i++){
		plot(1,i,A_FWRED);
		plot(14,i,CABLE); 
		plot(23,i,CABLE);
	}
	plots(17,9,DKBOT);
	plots(17,8,DKTOP);
	for (i=10;i<=13;i++){
		plot(9,i,ECHELLE);
		plot(13,i,ECHELLE);
		plot(23,i,ECHELLE);
		plot(27,i,ECHELLE);
	}
	for (i=14;i<=17;i++){
		plot(8,i,ECHELLE);
		plot(18,i,ECHELLE);
		plot(28,i,ECHELLE);
	}
	for (i=18;i<=21;i++){
		plot(7,i,ECHELLE);
		plot(14,i,ECHELLE);
		plot(22,i,ECHELLE);
		plot(29,i,ECHELLE);
	}
	for (i=22;i<=25;i++){
		plot(6,i,ECHELLE);
		plot(18,i,ECHELLE);
		plot(30,i,ECHELLE);
	}
	plot(9,9,PARAPLUIE);
	plot(22,25,SAC);
	plot(27,21,CHAPEAU);
	
	plot(34,13,A_STD2H); plots(35,13,"500");
	plot(34,14,A_STD2H); plots(35,14,"500"); */
	
	file_unpack((unsigned char*)48000,screen4);
    plots(35,3,itoa(vies));
	x=12; y=25;	APS=VIDE; a1=1;
	for (i=0;i<4;i++) ABSS[i]=VIDE;
	ya2[0]=9; ya2[1]=13; ya2[2]=17; ya2[3]=21;
	bonhomme=BONHOMMEDROITE;
	plot(x,y,bonhomme);
	for (i=0;i<NBREFEUX;i++) xa2[i]=21;
LDebut4:
	//*** ACTION ***
	timerg=deek(0x0276);
	if (timer1>=timerg) 
	{		
		anim_event=1;
		timer1=timerg-timer2;		
	} else anim_event=0;
	
	if (timer_feu>=timerg) 
	{
		animation_feu();
		timer_feu=timerg-TEMPOFEU;		
	};
	
	if ((timerbonus>=timerg) && (bonus_event==1))
	{
		//hide bonus
		plot(33,13,0);
		plot(33,14,0);
		bonus_event=0;
	} 
	
	if (saute!=1) plot(x,y,bonhomme);
	if (saute==1){
	   if(anim_event==1) {
		   rr=fin_saut();
		   if (rr==OUCH) goto L_perte;
		   if (rr==ENDLEVEL) goto L_fin;
	   }
	   goto Laction4;
	}
	if (score==0) plots(22,0,"0     ");	
	else {gotoxy(22,1); printf("%d00 ",score);}
	touche_action();
Laction4:
	if(anim_event==1) 
	{
		c+=1;
		if (c==8) {
			c=0;
			if (affichage_bonus()==PERDU) goto L_perte;
		}
	}
	//collisions joueur
	s=scrn(x,y);
	if ((s==PARAPLUIE) || (s==CHAPEAU) || (s==SAC)) chap_par_sac();
	sd=scrn(x,y+1);
	if (sd==VIDE) goto L_Chute;
	if (sd==RIVET) {
		if(enleve_rivet()==ENDLEVEL) goto L_fin;
	}
	if ((s==FEU)||(s=='m')||(s=='o'))  goto L_perte;
	plot(x,y,bonhomme);
	// *** B.FEUX ***
	if(anim_event==1) 
	{
		for (i=0;i<NBREFEUX;i++){
			xxa=&xa2[i];
			yya=&ya2[i];
			s=rnd(2);
			if (s==0) s=-1;
			plot(*xxa,*yya,ABSS[i]);
			*xxa=*xxa+s;
			if (scrn(*xxa,*yya+1)==VIDE){
				*xxa=*xxa-s;
				goto L11260;
			}
			ABSS[i]=scrn(*xxa,*yya);
			if ((ABSS[i]==BONHOMMEDROITE) || (ABSS[i]==BONHOMMEGAUCHE)) goto L_perte;
			
			L11260:
			plot(*xxa,*yya,FEU);
		}
	}
	goto LDebut4; 
// *** fin ***
L_fin:
	play(7,0,0,0);
	//animation
	for (i=10;i<=22;i+=4) {
		plot(12,i,A_FWRED);
		plot(24,i,A_FWBLUE);
		wait(30);
	}
	wait(50);
	
	for(j=0;j<4;j++)
	{		   
		for (i=0;i<3;i++) {
			 k=j*3+i+10; 
            if (APS=='c') y+=1; 			 
			plots(13,k,PLATFORMDELETE);			
			plots(13,k+j+1,PLATFORM);
			if (scrn(x,y)=='c') {
				APS='c'; 
			}
			plot(x,y,bonhomme);
			plot(12,k+j+1,A_FWRED);
			plot(24,k+j+1,scrn(1,k+j+1));
			        
			wait(20);		
		}
		
		plots(13,j*4+14,PLATFORM);
		wait(50);
	}		
	
	
	for (i=8;i<20;i++) {
		plots(17,i,"   ");
		music(1,0,1,10);
		plots(17,i+1,DKTOP);
		plots(17,i+2,DKBOT);
		wait(20);
	}
	explode();
	//bonhomme ecrase
	if (APS=='c') goto L_perte;
	
	plot(20,5,BONHOMMEGAUCHE);
	plot(16,3,A_FWRED); plot(17,3,A_STD2HFL); plots(18,3,"sz");plot(21,3,A_STD);
	plot(16,4,A_FWRED); plot(17,4,A_STD2HFL); plots(18,4,"sz");
	
	play(7,0,0,0);
	music(1,4,8,9); wait(64);
	music(1,4,7,9); wait(42);
	music(1,4,2,9); wait(20);
	music(1,4,5,9); wait(42);
	music(1,4,3,9); wait(42);
	music(1,4,1,9); wait(42);
	music(1,3,10,9); wait(42);
	music(1,3,8,9); wait(42); 
	music(1,3,12,9); wait(20);
	music(1,3,10,9); wait(12);
	music(1,3,12,9); wait(18);
	music(1,3,10,9); wait(50);
	music(1,3,8,9); wait(100);
	ping(); 
	wait(100);
	level+=1;
	t=0;
	goto tableau1;

 
L_Chute:
	// *** CHUTE ***
	play(7,0,0,0);
	for (i=y;i<=25;i++){
		music(1,0,1,10);
		st=scrn(x,i+1);
		if ((st!=VIDE) && (st>7)){
			explode();
			goto L30020;
		}
		plot(x,i,BONHOMMESAUT);
		wait(20);
		plot(x,i,VIDE);
	}
	explode();
L30020:
	plot(x,i,BONHOMMESAUT);
	y=i;
	wait(100);
	goto L_perte;
} 


void tonneau_descend()
{
	plot(*xxt,*yyt,*oot);
	noot=scrn(*xxt,*yyt+4);
	if (!((noot>=TONNEAU1)&&(noot<=TONNEAU4)))
	{
		*yyt+=4;
		*ant+=*aat;
		if (*ant>TONNEAU4) *ant=TONNEAU1;
		if (*ant<TONNEAU1) *ant=TONNEAU4;
	}	
	*oot=scrn(*xxt,*yyt);
}

char affichage_bonus()
{
	bonus-=1;
	if (bonus<10) ping();
	plots(3,1,"     ");
	if (bonus!=0) {
		gotoxy(2,1); printf("%d00 ",bonus);
	}
	if (bonus==0){
		plot(1,0,A_FWRED); plots(2,0,"0        "); plot(3,0,A_FWWHITE);
		return PERDU;
	}
	return SAFE;
}

void how_high()
{
	cls(); ink(1);
	i=15;
	play(7,0,0,0);
	ch=4;
	if (tableaunum==4) { ink(4); ch=3; };
	for (j=1;j<=tableaunum;j++)
	{
		ha=j*25;
		plots(16,i,DKBOT);
		plots(16,i-1,DKTOP);
		plots(20,i,itoa(ha));
		plots(24,i,"M");
		i-=2;
	}
	plot(1,22,ch);
#ifdef __FRENCH__
	plots(9,22,MSGHH);
#else	
	plots(8,22,MSGHH);
#endif 
	wait(30);
	music(1,4,2,7); wait(50);
	music(1,4,7,7); wait(25);
	music(1,4,6,7); wait(50);
	music(1,4,9,7); wait(25);
	music(1,4,7,7); wait(25);
	music(1,4,11,7); wait(30);
	music(1,5,2,7); wait(55);
	play(0,0,0,0);
	wait(300);
	ping();
}

void goal()
{
	plot(x,y,bonhomme);  
    plot(33,13,A_FWRED); plot(34,13,A_STD2H);
	plots(35,13,"sz"); plot(37,13,A_BGBLACK);
    plot(33,14,A_FWRED); plot(34,14,A_STD2H);
	plots(35,14,"sz"); plot(37,14,A_BGBLACK);	
	wait(200);
	score+=bonus;
	play(7,0,0,0); 
	music(1,3,1,7); wait(50);
	music(1,3,5,8); wait(50);
	music(1,3,8,9); wait(50);
	music(1,5,1,7); wait(25);
	music(1,5,5,8); wait(25);
	music(1,5,8,9); wait(25);
	play(0,0,0,0);
	music(1,1,1,0);
	play(7,0,0,0);
	wait(150);
}
 
void son1()
{
	play(7,0,0,0);
	for (i=40;i<=60;i++) sound(1,i,8);
	play(0,0,0,0);
}
 
 void affichage_data()
{ 
	cls(); ink(7);
	plots(2,-1,"BONUS:");
	plots(20,-1,"SCORE:");
	plots(33,0,"L=");
	plots(35,0,itoa(level));
	if (bonus==0) plots(2,0,"0        ");	
	else {gotoxy(2,1); printf("%d00 ",bonus);}
	if (score==0) plots(20,0,"0        ");	
	else {gotoxy(20,1); printf("%d00 ",score);}
	plot(33,13,0); 
	plot(33,14,0);
}

void chap_par_sac()
{
	play(7,0,0,0);
	for (i=20;i<=50;i++) sound(1,i,9);
	play(0,0,0,0);
	plot(33,13,A_FWCYAN);
	plot(33,14,A_FWCYAN);
	score+=5;
	timerbonus=timerg-TEMPOB;
	bonus_event=1;
	APS=VIDE;
	if ((tableaunum==3) && (st==CHAPEAU)){
		for (i=11;i<=13;i++) {
			plot(20,i,ECHELLE);
			wait(20);
		}
	    for (i=13;i<=15;i++) {
			if (scrn(26,i)==POUTRE) ARS=ECHELLE;
			plot(26,i,ECHELLE);
			wait(20);
		}
	}
}

void animation_feu()
{
animfeu+=1;
if (animfeu==6) animfeu=0;
poke(47008,spritefeu47008[animfeu]);
poke(47009,spritefeu47009[animfeu]);
poke(47010,spritefeu47010[animfeu]);
poke(47011,spritefeu47011[animfeu]);
poke(47013,spritefeu47013[animfeu]);
}

char touche_action()
 { 
    //touche=key();
	touche=peek(0x208);
	switch(touche)
	{
		case 56://0:
			return 0;
			break;
		case 132://' ':
		    if (bonhomme!=BONHOMMESAUT) {
				if (tableaunum!=3) saut();
			}
			return ' ';
			break;
		case 157://'P':
			get();
			return 'P';
			break;
	}
	what_below=scrn(x,y+1);what_above=scrn(x,y-1);
	plot(x,y,APS);
	switch(touche)
	{
		case 143://'L':
		    if ((what_below!=ECHELLE) || (APS!=ECHELLE))
			{
		    if ((bonhomme==BONHOMMEGAUCHE)||(bonhomme==BONHOMMESAUT))
				{				
					bonhomme=BONHOMMEDROITE;
					a1=1; a=0;
				}
				else a=1; 
			}
			break;
		case 131://'K':
		    if ((what_below!=ECHELLE) || (APS!=ECHELLE))
			{
		    if ((bonhomme==BONHOMMEDROITE)||(bonhomme==BONHOMMESAUT)) 
				{
					bonhomme=BONHOMMEGAUCHE;
					a1=-1; a=0;
				}	
				else a=-1;
			}
			break;
		case 174: //'A':
			if ((what_above==ECHELLE) || (APS==ECHELLE))
			{
				b=-1; bonhomme=BONHOMMESAUT; a=0;
			}
			//b=-4; 
			break;
		case 170:  //'Z':
			if (what_below==ECHELLE)
			{
				b=1; bonhomme=BONHOMMESAUT; a=0;
			}
			//b=4;
			break;
	}
	x=x+a; y=y+b; 
	if ((tableaunum==3) && (y==5) && (x<15)) x=15;
	else if ((a+b)!=0) APS=scrn(x,y);
	if (a!=0) a1=a;
	a=0; b=0;
	return touche;
 }
 
void saut_3eme()
{
	saute=1;
	saut_special=0;
	if ((x==16) && (y==13)) {
		x=20;
		APS=ECHELLE;
		saut_special=1;
		return;
	}
	plot(x,y,APS); ASS=scrn(x+a1,y-1);
	
	if ((x==24) && (y==14)) {
		APS=ECHELLE;
		x=26;
		y=15;
		saut_special=1;
		return;
	}
	plot(x+a1,y-1,bonhomme);
	son1();	
}

char fin_saut_3eme()
{
	if (saut_special==0)
	{
		plot(x+a1,y-1,ASS);
		x=x+2*a1;
		y-=1;
		APS=scrn(x,y);
	}
	saute=0;
	//L7030:
	plot(x,y,bonhomme); 
	s=scrn(x,y+1);
	if ((s==SOL)||(s==ECHELLE)) return SAFE;
	for (i=0;i<=1;i++) {
		plot(x,y,APS);
		APS=scrn(x,y+1);
		y+=1;
		plot(x,y,bonhomme);
		s=scrn(x,y+1);
		if ((s==SOL)||(s==ECHELLE)) return SAFE;
	}	
	return PERDU;
}

void saut(){
	a=a1;
	ASS=scrn(x+a1,y-1);
	plot(x,y,APS);
	if (tableaunum==2) {
		zx=x+2*a1;
		if ((zx<6) || (zx>29)) return;
	}
	plot(x+a1,y-1,bonhomme); 
	son1();
	saute=1;
}
char fin_saut()
{
	saute=0;
	plot(x+a1,y-1,ASS); 
	x=x+2*a1;
	s=scrn(x,y);
	//************
	//APS=scrn(x,y);
	//plot(x,y,bonhomme);
	//************
	if ((s==GATEAU) || (s==FEU) || ((s>=TONNEAU1)&&(s<=TONNEAU4))) return OUCH;
 	
	if ((s==PARAPLUIE) || (s==CHAPEAU) || (s==SAC)) 
	{
		chap_par_sac();
		return SAFE;
	}
	
	APS=scrn(x,y);
	plot(x,y,bonhomme);
	sd=scrn(x-a1,y);
	if ((sd>=TONNEAU1) && (sd<=TONNEAU4)) {
		plot(33,13,A_FWCYAN);
		plot(33,14,A_FWCYAN);
		score+=1;
		timerbonus=timerg-TEMPOB;
		bonus_event=1;
	};
	if ((sd==GATEAU) || (sd==FEU)) chap_par_sac();
	if (scrn(x-a1,y+1)==RIVET) {
		x-=a1;
		in=1;
		return enleve_rivet();
	}
 return SAFE;
}

char enleve_rivet()
{
	plot(x,y+1,VIDE);
	play(7,0,0,0);
	for (i=20;i<=50;i++) sound(1,i,9);
	play(0,0,0,0);
	if (in==1) {
		x=x+a1;
		in=0;
	}
	plot(x,y,APS); 
	x=x+a1;
	APS=scrn(x,y);
	score=score+1;
	np=np+1;
	if (np==8) {
		goal();
		return ENDLEVEL;
	}
 return SAFE;
 }
 
void wait(unsigned int wait_cs)
 {
	unsigned int start=deek(0x0276);
	unsigned int tw=start-wait_cs;
	while (tw<start) {start=deek(0x0276);};
}
 
 void plots(char x_pos,char y_pos, const char *msg)
{
    memcpy((unsigned char*)(0xBBA8+x_pos+y_pos*40),msg,strlen(msg));	
}

char rnd(char max)
 {
 return (char) (rand()/(32768/max));
 }