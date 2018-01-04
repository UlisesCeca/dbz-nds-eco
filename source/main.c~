// Includes C
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Para saber si un sprite ha sido pulsado
#include "touch.h"

// Timers
static int frame=0; //Timer para cambios de frames en sprites
static int atack=1; //Timer para que el bicho ataque cada cierto tiempo
static int superatack=1; //Timer para un ataque que quitará bastante vida
static int atackrate=15; //Cambiará segun el nivel para que el bicho ataque mas rapido
static int contador=1;	//Variable para que el contador baje hacia atrás
void timeout()
{

   static int num=0;

   num++;
   frame = num%2; //Tomará el valor 1 o 0 dependiendo de num, con ellos cambiará de frame
   atack = num%atackrate; //Valor para que el bicho ataque, en cada nivel será mas rapido
   superatack = num%16;	//Valor para cargar el super ataque
   contador = num%3;	//Valor para disminuir el contador

}


// Inicializamos un timer
void enableTimer(){
  
  NF_SPRITEOAM[1][1].hide = true;	

}

int main(int argc, char **argv) {

// Pantalla de espera inicializando NitroFS
NF_Set2D(0, 0);
NF_Set2D(1, 0);

//Inicializamos un timer
irqSet(IRQ_TIMER0, &timeout);
irqEnable(IRQ_TIMER0);	
consoleDemoInit();
TIMER_DATA(0) = 0;
TIMER_CR(0) = TIMER_DIV_256 | TIMER_ENABLE | TIMER_IRQ_REQ;

iprintf("\n NitroFS init. Please wait.\n\n");
iprintf(" Iniciando NitroFS,\n por favor, espere.\n\n");
swiWaitForVBlank();

// Define el ROOT e inicializa el sistema de archivos
NF_SetRootFolder("NITROFS");	// Define la carpeta ROOT para usar NITROFS

// Inicializa el motor 2D
NF_Set2D(0, 0);	// Modo 2D_0 en ambas pantallas
NF_Set2D(1, 0);

// Inicializa el engine de audio de la DS
soundEnable();

// Inicializa los buffers de sonido
NF_InitRawSoundBuffers();

// Inicializa los fondos tileados
NF_InitTiledBgBuffers();	// Inicializa los buffers para almacenar fondos
NF_InitTiledBgSys(0);	// Inicializa los fondos Tileados para la pantalla superior
NF_InitTiledBgSys(1);	// Iniciliaza los fondos Tileados para la pantalla inferior

// Inicializa los Sprites
NF_InitSpriteBuffers();	// Inicializa los buffers para almacenar sprites y paletas
NF_InitSpriteSys(0);	// Inicializa los sprites para la pantalla superior
NF_InitSpriteSys(1);	// Inicializa los sprites para la pantalla inferior

// Carga los sonidos
NF_LoadRawSound("musica/bg", 0, 8000, 0);	//Musica de fondo
NF_LoadRawSound("musica/punetazo", 1, 11025, 0);	//Sonido puñetazo
NF_LoadRawSound("musica/patada", 2, 11025, 0);	//Sonido patada
NF_LoadRawSound("musica/kamehameha", 6, 11025, 0);	//Sonido super ataque
NF_LoadRawSound("musica/muerte", 4, 11025, 0);	//Sonido muerte goku
NF_LoadRawSound("musica/golpe", 5, 11025, 0);	//Sonido golpe
NF_LoadRawSound("musica/muertebicho", 3, 11025, 0);	//Sonido muerte del bicho

// Ejecuta la musica
NF_PlayRawSound(0, 127, 64, true, 0);	//Musica de fondo

// Carga los archivos de fondo desde la FAT / NitroFS a la RAM
NF_LoadTiledBg("bg/torneo", "torneo", 256, 256);	// Carga el fondo para la pantalla superior
NF_LoadTiledBg("bg/pabajo", "pabajo", 256, 256);	// Carga el fondo para la pantalla inferior
NF_LoadTiledBg("bg/intro1", "intro1", 256, 256);	// Imagen superior para la intro
NF_LoadTiledBg("bg/intro2", "intro2", 256, 256);	// Imagen inferior para la intro
NF_LoadTiledBg("bg/instrucciones1", "instrucciones1", 256, 256);	// Imagen superior para las instrucciones
NF_LoadTiledBg("bg/instrucciones2", "instrucciones2", 256, 256);	// Imagen inferior para las instrucciones
NF_LoadTiledBg("bg/muerto1", "muerto1", 256, 256);	// Imagen superior para cuando perdemos	
NF_LoadTiledBg("bg/ganador", "ganador", 256, 256);	// Imagen superior para cuando ganamos
NF_LoadTiledBg("bg/ganador2", "ganador2", 256, 256);	// Imagen inferior para cuando ganamos

// Carga los archivos de sprites desde la FAT / NitroFS a la RAM
NF_LoadSpriteGfx("sprite/goku", 0, 64, 64);	// Goku
NF_LoadSpritePal("sprite/goku", 0);

NF_LoadSpriteGfx("sprite/saibaman", 2, 64, 64);	// saibaman
NF_LoadSpritePal("sprite/saibaman", 2);

NF_LoadSpriteGfx("sprite/bola", 1, 64, 64);	// bola ataque final, hemos creado otro sprite porque no nos cabe en 64x64 junto a goku
NF_LoadSpritePal("sprite/bola", 1);

NF_LoadSpriteGfx("sprite/corazones", 3, 16, 16);	// Corazones goku
NF_LoadSpritePal("sprite/corazones", 3);
NF_LoadSpriteGfx("sprite/corazones", 4, 16, 16);	
NF_LoadSpriteGfx("sprite/corazones", 5, 16, 16);	

NF_LoadSpriteGfx("sprite/corazones", 6, 16, 16);	// Corazones bicho
NF_LoadSpriteGfx("sprite/corazones", 7, 16, 16);	
NF_LoadSpriteGfx("sprite/corazones", 8, 16, 16);	

NF_LoadSpriteGfx("sprite/botones", 9, 64, 32);	// botones
NF_LoadSpritePal("sprite/botones", 4);

NF_LoadSpriteGfx("sprite/estrella", 10, 16, 16);	// estrella para la bola
NF_LoadSpritePal("sprite/estrella", 5);
NF_LoadSpriteGfx("sprite/estrella", 11, 16, 16);	
NF_LoadSpriteGfx("sprite/estrella", 12, 16, 16);	

NF_LoadSpriteGfx("sprite/cargador", 13, 64, 64);	// cargador super ataque
NF_LoadSpritePal("sprite/cargador", 6);
NF_LoadSpriteGfx("sprite/cargador", 14, 64, 64);	
NF_LoadSpriteGfx("sprite/cargador", 15, 64, 64);	

NF_LoadSpriteGfx("sprite/numeros", 16, 32, 32);	// numeros level unidades
NF_LoadSpriteGfx("sprite/numeros", 17, 32, 32);	// numeros level decenass
NF_LoadSpriteGfx("sprite/numeros", 18, 32, 32);	// numeros contador unidades
NF_LoadSpriteGfx("sprite/numeros", 19, 32, 32);	// numeros contador decenass
NF_LoadSpritePal("sprite/numeros", 7);

NF_LoadSpriteGfx("sprite/level", 20, 64, 32);	// level
NF_LoadSpritePal("sprite/level", 8);

NF_LoadSpriteGfx("sprite/gokuface", 21, 32, 32);	// goku face
NF_LoadSpritePal("sprite/gokuface", 9);

NF_LoadSpriteGfx("sprite/bichoface", 22, 32, 32);	// bicho face
NF_LoadSpritePal("sprite/bichoface", 10);

// Transfiere a la VRAM los sprites necesarios
NF_VramSpriteGfx(0, 0, 0, true);	// Goku
NF_VramSpritePal(0, 0, 0);

NF_VramSpriteGfx(0, 2, 2, true);	// saibaman
NF_VramSpritePal(0, 2, 2);

NF_VramSpriteGfx(0, 1, 1, true);	// bola ataque final
NF_VramSpritePal(0, 1, 1);

NF_VramSpriteGfx(0, 3, 3, true);	// corazones goku
NF_VramSpritePal(0, 3, 3);
NF_VramSpriteGfx(0, 4, 4, true);	
NF_VramSpriteGfx(0, 5, 5, true);	

NF_VramSpriteGfx(0, 6, 6, true);	// corazones bicho
NF_VramSpriteGfx(0, 7, 7, true);	
NF_VramSpriteGfx(0, 8, 8, true);	

NF_VramSpriteGfx(1, 9, 9, true);	// botones
NF_VramSpritePal(1, 4, 4);

NF_VramSpriteGfx(1, 10, 10, true);	// estrella
NF_VramSpritePal(1, 5, 5);
NF_VramSpriteGfx(1, 11, 11, true);	
NF_VramSpriteGfx(1, 12, 12, true);	

NF_VramSpriteGfx(1, 13, 13, true);	// cargador superataque
NF_VramSpritePal(1, 6, 6);
NF_VramSpriteGfx(1, 14, 14, true);	
NF_VramSpriteGfx(1, 15, 15, true);	

NF_VramSpriteGfx(1, 16, 16, true);	// numeros level unidades
NF_VramSpriteGfx(1, 17, 17, true);	// numeros level decenas
NF_VramSpriteGfx(0, 18, 18, true);	// numeros level decenas
NF_VramSpriteGfx(0, 19, 19, true);	// numeros level decenas
NF_VramSpritePal(1, 7, 7);
NF_VramSpritePal(0, 7, 7);

NF_VramSpriteGfx(1, 20, 20, true);	// sprite level
NF_VramSpritePal(1, 8, 8);

NF_VramSpriteGfx(0, 21, 21, true);	// goku face
NF_VramSpritePal(0, 9, 9);

NF_VramSpriteGfx(0, 22, 22, true);	// bicho face
NF_VramSpritePal(0, 10, 10);

// Variables para posicion de goku
s16 x = 4;
s16 y = 120;

// Variables para posicion del bicho
s16 x2 = 169;
s16 y2 = 120;

// Variable para la lectura del keypad
u16 keys = 0;

//Variable para el modo de juego: intro, niveles e instrucciones
int mode = 0;

//Variables para la vida
int vidagoku = 6;	//Vida goku
int subirvidabicho = 0;	//Variable que subirá la vida al bicho al pasar de nivel
int vidabicho = 5;	//Vida inicial del bicho
int vidabichocorazon = vidabicho;	//Variable para cambiar los corazones de vida del bicho, puesto que estos cambian con divisiones respecto al valor inicial (que aumenta con los niveles)

// Variables para hacia donde mirarán los sprites
int side = 0;	//Lado al que mira goku
int side2 = 0;	//Lado al que mire el bicho

//Contador para que los timers aumenten o resten de uno en uno, porque estos aumentan de 30 en 30
int contadorgoku=0;	//Contador para la vida de goku
int contadorbola=0;	//Contador para la carga de la bola
int contadoratras=0;	//Contador para el timer

// Variable para el super ataque y ataques normales
int ataque = 0;	//Controlador ataque, permite evitar que si se queda una tecla pulsada le baje la vida continuamente al monstruo, por lo que hay que repetir las pulsaciones
int bola = 0;	//Cargador super ataque

// Variables para impedir hacer ataques infinitos mientras se corre
int correrAtaques = 0;	//Evitar ataques infinitos al volar

//Variable para cargar sprites y fondos solo una vez
int sprites=0;
int fondos= 0;

// Variable para poder revivir cuando hayamos muerto, aumentará por nivel ganado y lo marcarán las estrellas de las bolas
int revivir=0;

// Variable para nivel
int level = 1;	//nivel en el que estamos

// Variable para el contador
int timeup=30;  //Contador hacia atrás, 30 segundos

//Variables para actualizar el sprite del contador en las unidades
int unidades=10;

// Variable para evitar que los sonidos se repitan por estar ejecutandose todo el rato
int sonidos = 0;	//Para ataques goku
int sonidos2=0;		//Para ataques bicho
int sonidosmuerte=0;	//Para cuando se muere el bicho

// Bucle (repite para siempre)
while(1) {

// Lee el teclado
scanKeys();
keys = keysHeld();

if (mode==0){	//Pantalla de intro
	if(fondos==0){	//Comprobamos que los fondos no estén creados
		NF_CreateTiledBg(0, 3, "intro1"); //Creamos ambos fondos
		NF_CreateTiledBg(1, 3, "intro2");
		fondos=1;	//Evitamos que se vuelvan a cargar infinitamente los fondos
	}
	oamDisable (&oamSub);	//Quitamos la renderizaciones de sprites de la pantalla inferior para que se vayan los sprites de abajo

	//Reinicio de variables del juego para cuando nos maten y volvamos aqui
	vidagoku=6;	//Las vidas se reinician
	vidabicho=5;
	x = 4;	//Se reinician las posiciones de los jugadoress
	y = 120;
	x2 = 169;
	y2 = 120;
	level = 1;	//Reseteamos el nivel en el que estamos
	revivir = 0;	//Las estrellas para revivir se ponen a 0
	bola = 0;	//El cargador para el super ataque se pone a 0
	subirvidabicho = 0;	//El incrementador de la vida del bicho se pone a 0
	vidabichocorazon = vidabicho;	//Igualamos la variable para la vida de los corazones del bicho
	atackrate = 15;	//Reiniciamos la velocidad de ataque del bicho
	timeup = 30;	//Reiniciamos el contador
	unidades = 10;	//Reiniciamos las unidades para los sprites del contador
	NF_SpriteFrame(0,3,0);	// Los corazones de goku se ponen enteros
	NF_SpriteFrame(0,4,0);
	NF_SpriteFrame(0,5,0);
	NF_SpriteFrame(1,13,0);	//Se vacia el cargador del super ataque
	NF_SpriteFrame(1,14,0);
	NF_SpriteFrame(1,15,0);

	if (keys & KEY_START) {	//Al pulsar start empieza el juego
		mode = 3;	//El modo 3 es el de jugar
		sprites = 0;	//Activamos que se carguen los sprites
	}
	if (keys & KEY_SELECT) {	//Al darle a select nos vamos a las instrucciones
		fondos = 0;
		mode = 1;
	}
}

if (mode==1){	//Pantalla de instrucciones
	if (fondos==0){
		NF_CreateTiledBg(0, 3, "instrucciones1"); //Creamos ambos fondoss
		NF_CreateTiledBg(1, 3, "instrucciones2");
		fondos = 1;
	}
	if (keys & KEY_B) {	//Al darle a B volvemos al menu de intro
		fondos = 0;	//Habilitamos la carga de fondos
		mode = 0;
	}
}

if (mode==3){	//Modo de juego
	if(sprites==0){	//Comprobamos que no se hayan creado ya los sprites para no volver a crearlos
		NF_CreateSprite(1, 9, 9, 4, 94, 155);  //Creamos sprites botones
		NF_CreateSprite(1, 10, 10, 5, 15, 67);  //Creamos sprites estrellas
		NF_CreateSprite(1, 11, 11, 5, 8, 83);
		NF_CreateSprite(1, 12, 12, 5, 22, 83); 
		NF_CreateSprite(1, 13, 13, 6, 94, 100);  //Creamos sprites cargador super ataque
		NF_CreateSprite(1, 14, 14, 6, 94, 60);
		NF_CreateSprite(1, 15, 15, 6, 94, 20); 
		NF_CreateTiledBg(0, 3, "torneo"); //Creamos ambos fondos
		NF_CreateTiledBg(1, 3, "pabajo");
		NF_CreateSprite(1, 16, 16, 7, 145, 0);  //Creamos Numeros level unidades
		NF_CreateSprite(1, 17, 17, 7, 130, 0);  //Creamos Numeros level decenas
		NF_CreateSprite(0, 18, 18, 7, 102, 0);  //Creamos Numeros contador unidades
		NF_CreateSprite(0, 19, 19, 7, 117, 0);  //Creamos Numeros contador decenas
		NF_CreateSprite(1, 20, 20, 8, 80, 2);  //Creamos Numeros contador decenas
		NF_CreateSprite(0, 21, 21, 9, 4, 2);  //Sprite cara goku
		NF_CreateSprite(0, 22, 22, 10, 220, 2);  //Sprite cara bicho
		NF_SpriteFrame(0,18,3); //Ponemos las decenas del contador del sprite a 30
		oamEnable (&oamMain);	//Ponemos que se puedan renderizar los sprites
		oamEnable (&oamSub);	
		// Crea el Sprite del goku y la bola final en la pantalla superior
		NF_CreateSprite(0, 0, 0, 0, x, y);
		NF_CreateSprite(0, 2, 2, 2, x, y);

		// Crea el Sprite del monstruo en la pantalla superior
		NF_CreateSprite(0, 1, 1, 1, x2, y2);

		// Crea corazones de vidas de goku en la pantalla superior
		NF_CreateSprite(0, 3, 3, 3, 80, 5);
		NF_CreateSprite(0, 4, 4, 3, 60, 5);
		NF_CreateSprite(0, 5, 5, 3, 40, 5);

		// Crea corazones de vidas del bicho en la pantalla superior
		NF_CreateSprite(0, 6, 6, 3, 160, 5);
		NF_CreateSprite(0, 7, 7, 3, 180, 5);
		NF_CreateSprite(0, 8, 8, 3, 200, 5);
		sprites=1;	//Ponemos que los sprites no se carguen mas
	}
	
	// Si no se pulsan teclas, estamos vivos y no estamos en los limites: el personaje está quieto
	if(keys==0 && vidagoku>0){
		NF_SpriteFrame(0,1,0);	//Ponemos que el sprite de la bola no se veaa
		if(side==0){	//Si el personaje está mirando a la derecha
		if (frame==0){
			NF_SpriteFrame(0,0,0);	//Cambio de Frame
		}
		else if (frame==1){
			NF_SpriteFrame(0,0,1);	//Cambio de Frame
			}
		}
		else if(side==1){	//Si el personaje está mirando a la izquierda
		if (frame==0){
			NF_SpriteFrame(0,0,16);	//Cambio de Frame
		}
		else if (frame==1){
			NF_SpriteFrame(0,0,17);	//Cambio de Frame
			}
		}
		ataque = 1;	//Ponemos que sea necesario levantar la tecla para realizar ataques (para quitar vida al monstruo)
		correrAtaques = 0;	//Al levantar las teclas de ataque podremos correr libremente, evitando ataques infinitos
		sonidos = 0;	//Ponemos que se oiga el sonido de ataques de goku al levantar la tecla
	}


	// Si se pulsa la tecla izquierda, estamos vivos, no se están haciendo ataques y no estamos en el limite izquierdo: nos movemos a la izquierda
	if (keys & KEY_LEFT && vidagoku>0 && correrAtaques == 0) {
		if(x==4){	//Si estamos en el limite hacemos la animacion de estar quietos
			NF_SpriteFrame(0,1,0);	//Ponemos que el sprite de la bola no se vea
			if(side==0){	//Si el personaje está mirando a la derecha
				if (frame==0){
					NF_SpriteFrame(0,0,0);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,1);	//Cambio de Frame
				}
			}
			else if(side==1){	//Si el personaje está mirando a la izquierda
				if (frame==0){
					NF_SpriteFrame(0,0,16);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,17);	//Cambio de Frame
				}
			}
		} else {	//Si no estamos en el limite hacemos la animacion de moverse
			if (frame==0){
				NF_SpriteFrame(0,0,4);	//Cambio de Frame
			}
			else if (frame==1){
				NF_SpriteFrame(0,0,5);	//Cambio de Frame
			}
		x -= 3;	//Nos deplazamos en el eje X
		side = 1; //ponemos que mire hacia la izquierda cuando haga otro movimiento que no sea moverse
		}
	}

	// Si se pulsa la tecla derecha, estamos vivos, no se están haciendo ataques y no estamos en el limite derecho: nos movemos a la derecha
	if (keys & KEY_RIGHT && vidagoku>0 && correrAtaques == 0){
		if(x==195){	//Si estamos en el limite hacemos la animacion de estar quietos
			NF_SpriteFrame(0,1,0);	//ponemos que el sprite de la bola no se vea
			if(side==0){	////Si el personaje está mirando a la derecha
				if (frame==0){
					NF_SpriteFrame(0,0,0);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,1);	//Cambio de Frame
				}
			}
			else if(side==1){	//Si el personaje está mirando a la izquierda
				if (frame==0){
					NF_SpriteFrame(0,0,16);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,17);	//Cambio de Frame
				}
			}
		} else {	//Si no estamos en el limite hacemos la animacion de moverse
			if (frame==0){
				NF_SpriteFrame(0,0,2);	//Cambio de Frame
			}
			else if (frame==1){
				NF_SpriteFrame(0,0,3);	//Cambio de Frame
			}
		x +=3;	//Nos deplazamos en el eje X
		side = 0; //ponemos que mire hacia la derecha cuando haga otro movimiento que no sea moverse
		}
	}

	// Si se pulsa la tecla abajo, estamos vivos, no se están haciendo ataques y no estamos en el limite derecho: nos movemos a la derecha
	if (keys & KEY_DOWN && vidagoku>0 && correrAtaques == 0) {
		if (keys & KEY_LEFT && y==120) {	//Si estamos al limite de y, y se pulsa la tecla izquierda y abajo a la vez, hara la animacion hacia la izquierda
			if(x==4){	//Si estamos en el limite de x hacemos la animacion de estar quietos
				if(side==0){	//Si el personaje está mirando a  la derecha
					if (frame==0){
						NF_SpriteFrame(0,0,0);	//Cambio de Frame
					}
					else if (frame==1){
						NF_SpriteFrame(0,0,1);	//Cambio de Frame
					}
				}
				else if(side==1){	//Si el personaje está mirando a la izquierda
					if (frame==0){
						NF_SpriteFrame(0,0,16);	//Cambio de Frame
					}
					else if (frame==1){
						NF_SpriteFrame(0,0,17);	//Cambio de Frame
					}
				}
			} else {	//Si no estamos en el limite de x pero si en el de y, hacemos la animacion de ir hacia la izquierda
				if (frame==0){
					NF_SpriteFrame(0,0,4);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,5);	//Cambio de Frame
				} 
			}
		} else if (keys & KEY_RIGHT && y==120){	//Si estamos al limite de y, y se pulsa la tecla derecha y abajo a la vez, hara la animacion hacia la derecha
			if(x==195){	//Si estamos en el limite de x hacemos la animacion de estar quietos
				NF_SpriteFrame(0,1,0);	//ponemos que el sprite de la bola no se vea
				if(side==0){	//Si el personaje está mirando a la derecha
					if (frame==0){
						NF_SpriteFrame(0,0,0);	//Cambio de Frame
					}
					else if (frame==1){
						NF_SpriteFrame(0,0,1);	//Cambio de Frame
					}
				}
				else if(side==1){	//Si el personaje está mirando a la izquierda
					if (frame==0){
						NF_SpriteFrame(0,0,16);	//Cambio de Frame
					}
					else if (frame==1){
						NF_SpriteFrame(0,0,17);	//Cambio de Frame
					}
				}
			} else {	//Si no estamos en el limite de x pero si en el de y, hacemos la animacion de ir hacia la derecha
				if (frame==0){
					NF_SpriteFrame(0,0,2);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,3);	//Cambio de Frame
				}
			} 
		} else if (y==120){	//Si estamos en el limite de y solo hacemos la animacion de estar quietos
			NF_SpriteFrame(0,1,0);	//ponemos que el sprite de la bola no se vea
			if(side==0){	//Si el personaje está mirando a la derecha
				if (frame==0){
					NF_SpriteFrame(0,0,0);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,1);	//Cambio de Frame
					}
			}
			else if(side==1){	//Si el personaje está mirando a la izquierda
				if (frame==0){
					NF_SpriteFrame(0,0,16);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,17);	//Cambio de Frame
				}
			}
		} else {	//Si no estamos en el limite de y, hacemos la animacion de moverse
			if(side==1){	//Si el personaje está mirando a la izquierda
				if (frame==0){
					NF_SpriteFrame(0,0,22);	//Cambio de Frame
			}
				if (frame==1){
					NF_SpriteFrame(0,0,23);	//Cambio de Frame
				}
			} else if(side==0){	//Si el personaje está mirando a la derecha
				if (frame==0){
					NF_SpriteFrame(0,0,24);	//Cambio de Frame
				}
				if (frame==1){
					NF_SpriteFrame(0,0,25);	//Cambio de Frame
				}
			}
		y = y+3;	//Nos desplazamos en el eje Y
		}
	}

	// Si se pulsa la tecla arriba, estamos vivos, no se están haciendo ataques y no estamos en el limite derecho: nos movemos a la arriba
	if (keys & KEY_UP && vidagoku>0 && correrAtaques == 0) {
		if (keys & KEY_LEFT && y==30) {	//Si estamos al limite de y, y se pulsa la tecla izquierda y abajo a la vez, hara la animacion hacia la izquierda
			if(x==4){	//Si estamos en el limite de x hacemos la animacion de estar quietos
				if(side==0){	//Si el personaje está mirando a la derecha
					if (frame==0){
						NF_SpriteFrame(0,0,0);	//Cambio de Frame
					}
					else if (frame==1){
						NF_SpriteFrame(0,0,1);	//Cambio de Frame
					}
				}
				else if(side==1){	//Si el personaje está mirando a la izquierda
					if (frame==0){
						NF_SpriteFrame(0,0,16);	//Cambio de Frame	
					}
					else if (frame==1){
						NF_SpriteFrame(0,0,17);	//Cambio de Frame
					}
				}
			} else {	//Si no estamos en el limite de x pero si en el de y, hacemos la animacion de ir hacia la izquierda
				if (frame==0){
					NF_SpriteFrame(0,0,4);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,5);	//Cambio de Frame
				} 
			}
		} else if (keys & KEY_RIGHT && y==30){	//Si estamos al limite de y, y se pulsa la tecla derecha y abajo a la vez, hara la animacion hacia la derecha
			if(x==195){	//Si estamos en el limite de x hacemos la animacion de estar quietos
				NF_SpriteFrame(0,1,0);	//ponemos que el sprite de la bola no se vea
				if(side==0){	//Si el personaje está mirando a la derecha
					if (frame==0){
						NF_SpriteFrame(0,0,0);	//Cambio de Frame
					}
					else if (frame==1){
						NF_SpriteFrame(0,0,1);	//Cambio de Frame
					}
				}
				else if(side==1){	//Si el personaje está mirando a la izquierda
					if (frame==0){
						NF_SpriteFrame(0,0,16);	//Cambio de Frame
					}
					else if (frame==1){
						NF_SpriteFrame(0,0,17);	//Cambio de Frame
					}
				}
			} else {	//Si no estamos en el limite de x pero si en el de y, hacemos la animacion de ir hacia la derecha
				if (frame==0){
					NF_SpriteFrame(0,0,2);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,3);	//Cambio de Frame
				}
			} 
		} else if (y==30){	//Si estamos en el limite de y solo hacemos la animacion de estar quietos
			NF_SpriteFrame(0,1,0);	//ponemos que el sprite de la bola no se vea
			if(side==0){	//Si el personaje está mirando a la derecha
				if (frame==0){
					NF_SpriteFrame(0,0,0);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,1);	//Cambio de Frame
				}
			}
			else if(side==1){	//Si el personaje está mirando a la izquierda
				if (frame==0){
					NF_SpriteFrame(0,0,16);	//Cambio de Frame
				}
				else if (frame==1){
					NF_SpriteFrame(0,0,17);	//Cambio de Frame
				}
			}
		} else {	//Si no estamos en el limite hacemos la animacion de moverse
			if(side==0){	//Si el personaje está mirando a la derecha
				if (frame==0){
					NF_SpriteFrame(0,0,18);	//Cambio de Frame
				}
				if (frame==1){
					NF_SpriteFrame(0,0,19);	//Cambio de Frame
				}
			} else if(side==1){	//Si el personaje está mirando a la izquierda
				if (frame==0){
					NF_SpriteFrame(0,0,20);	//Cambio de Frame
				}
				if (frame==1){
					NF_SpriteFrame(0,0,21);	//Cambio de Frame
				}
			}
		y = y-3;	//Nos desplazamos en el eje Y
		}
	}

	// Si se pulsa la tecla B y el bicho y nosotros estamos vivos: Patada
	if (keys & KEY_B && vidagoku>0 && vidabicho>0){
		if (sonidos==0){	//Si este sonido está habilitado
			NF_PlayRawSound(2, 100, 64, false, 0);	//Sonido patada
			sonidos=1;	//Lo desabilitamos para que no se repita
		}
		if (side==0){	//Si el personaje está mirando a la derecha
		NF_SpriteFrame(0,0,7); //patada hacia derecha
		if (x2 > x && x2 <= x+30 && y==y2 && vidabicho>0 && ataque == 1){	//Le quitamos vida al bicho si está lo bastante cerca
			vidabicho--;
			side2 = 1;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
			ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
			}
		}
		else if (side==1){	//Si el personaje está mirando a la izquierda
		NF_SpriteFrame(0,0,6); //patada hacia izquierda
			if (x2 < x && x2 >= x-30 && y==y2 && vidabicho>0 && ataque == 1){	//Le quitamos vida al bicho si está lo bastante cerca
				vidabicho--;
				side2 = 0;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
				ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
			}
		}
		correrAtaques = 1;	//Anulamos que se pueda correr mientras estamos atacando
	}

	// Si se pulsa la tecla A y el bicho y nosotros estamos vivos: Puñetazo
	if (keys & KEY_A && vidagoku>0 && vidabicho>0){
		if (sonidos==0){	//Si este sonido está habilitado
			NF_PlayRawSound(1, 100, 64, false, 0);	//Sonido puñetazo
			sonidos=1;	//Lo desabilitamos para que no se repita
		}
		if (side==0){	//Si el personaje está mirando a la derecha
			NF_SpriteFrame(0,0,9); //puñetazzo hacia derecha
			if (x2 > x && x2 <= x+30 && y==y2 && vidabicho>0 && ataque == 1){	//Le quitamos vida al bicho si está lo bastante cerca
				vidabicho--;
				side2 = 1;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
				ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
			}
		}
		else if (side==1){	//Si el personaje está mirando a la izquierda
			NF_SpriteFrame(0,0,8); //puñetazzo hacia izquierda
			if (x2 < x && x2 >= x-30 && y==y2 && vidabicho>0 && ataque == 1){	//Le quitamos vida al bicho si está lo bastante cerca
				vidabicho--;
				side2 = 0;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
				ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
			}
		}
		correrAtaques = 1;	//Anulamos que se pueda correr mientras estamos atacando
	}

	// Cada ciertos segundos se carga en un punto el super ataque si el bicho y nosotros estamos vivos
	if (superatack == 0 && vidagoku>0 && vidabicho>0){
		contadorbola++;	//Aumentamos el contador de la bola
		if (contadorbola%30==0){	//El contador aumenta en 30 debido al timer, por tanto cada vez que el resto sea 0 nos cargará en un punto el super ataque
			bola++;
			if (bola>=6){	//Evitamos que el cargador sea mas de 6
				bola=6;
			}
		}
	}

	// Si se pulsa X y el ataque final está cargado (6 puntos): Ataque final
	if (keys & KEY_X && bola>=6 && vidagoku>0 && vidabicho>0){
		NF_PlayRawSound(6, 100, 64, false, 0);	//Hacemos el sonido de ataque final
		if (side==0){	//Si el personaje está mirando a la derecha
			NF_MoveSprite(0, 1, x+55, y-6);	//Calibramos la posicion del sprite de la bola para que encaje con el de goku y salga donde nosotros
			NF_SpriteFrame(0,0,11); //Super ataque hacia derecha
			NF_SpriteFrame(0,1,1);	//Frame bola hacia derecha
			if (x2 > x && x2 <= x+81 && y==y2 && vidabicho>0  && ataque == 1){	//Aumentamos el rango al que le afectará el ataque a diferencia de una patada o puñetazo
				vidabicho-=20;	//lE quita 20 puntos de vida al monstruo
				side2 = 1;	//Ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
				ataque = 0;	//Cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
			}
		}
		else if (side==1){	//Si el personaje está mirando a la izquierda
			NF_MoveSprite(0, 1, x-55, y-6);	//Calibramos la posicion del sprite de la bola para que encaje con el de goku y salga donde nosotros
			NF_SpriteFrame(0,0,13);	//Super ataque hacia izquierda
			NF_SpriteFrame(0,1,2);	//Frame bola hacia izquierda
			if (x2 < x && x2 >= x-81 && y==y2 && vidabicho>0  && ataque == 1){	//Aumentamos el rango al que le afectará el ataque a diferencia de una patada o puñetazo
				vidabicho-=20;	//lE quita 20 puntos de vida al monstruo
				side2 = 0;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
				ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
			}
		}
		bola = 0; //Reseteamos el cargador del ataque
		correrAtaques = 1;	//Anulamos que se pueda correr mientras estamos atacando
	}

	//Movimientos horizontales para que nos siga y ataques bicho en el eje x
	if (x2 > x && vidabicho>0 && vidagoku>0){	//Si el bicho está a nuestra derecha
		if (x2 <= x+30){	//A ciertos pixeles se detendrá para no juntar ambos sprites
			if (atack==0 && vidagoku>0 && y2==y){	//El personaje atacará dependiendo del timer cada ciertos segundos
				NF_SpriteFrame(0,2,9);	//Frame ataque
				if (sonidos2==0){	//Sonido de ataque si está habilitado
					NF_PlayRawSound(5, 100, 64, false, 0);
					sonidos2=1;	//Deshabilitamos el sonido para que no se repita
				}
				contadorgoku++;	//Aumentamos el contador para que nos quite vida
				if(contadorgoku%30==0){	//el contador aumenta en 30 debido al timer, por tanto cada vez que el resto sea 0 nos quitará un punto de vida
					vidagoku--;
					sonidos2=0;	//Habilitamos sonido ataque bicho	
				}
			} else if (frame==0){	//Cuando no ataque estrá parado haciendo el movimiento de parado mirando hacia la izquierda (donde estamos)
				NF_SpriteFrame(0,2,0);	//Cambio de frame
			} else if (frame==1){
				NF_SpriteFrame(0,2,1);	//Cambio de frame
			}
			side2=1;	//Se pondrá mirando a la izquierda para otros movimientos
		}
		else {	//si no está a ciertos pixels, nos seguirá
			if (frame==0){	//Como está en movimiento, hara el movimiento de andar hacia nosotros, la izquierda
				NF_SpriteFrame(0,2,6);	//Cambio de frame
			} else if (frame==1){
				NF_SpriteFrame(0,2,7);	//Cambio de frame
			}
			NF_MoveSprite(0, 2, x2--, y2); //x2 (eje x del bicho) se decrementa para ir hacia la izquierda
			side2=1;	//Se pondrá mirando a la izquierda para otros movimientos
		}
	} else if (x2 < x && vidabicho>0 && vidagoku>0){	//el bicho está a nuestra izquierda
		if (x2 >= x-30){	//a ciertos pixeles se detendrá para no juntar ambos sprites
		if (atack==0 && vidagoku>0  && y2==y){	//El personaje atacará dependiendo del timer cada ciertos segundos
				NF_SpriteFrame(0,2,8);	//Frame ataque
				if (sonidos2==0){	//Sonido de ataque si está habilitado
					NF_PlayRawSound(5, 100, 64, false, 0);
					sonidos2=1;	//Deshabilitamos el sonido para que no se repita
				}
				contadorgoku++;	//Aumentamos el contador para que nos quite vida
				if(contadorgoku%30==0){	//el contador aumenta en 30 debido al timer, por tanto cada vez que el resto sea 0 nos quitará un punto de vida
					vidagoku--;
					sonidos2=0;	//Habilitamos sonido ataque bicho	
				}
			} else if (frame==0){	//cuando no ataque estrá parado haciendo  el movimiento de parado mirando hacia la derecha (donde estamos)
				NF_SpriteFrame(0,2,2);	//Cambio de frame
			} else if (frame==1){
				NF_SpriteFrame(0,2,3);	//Cambio de frame
		}
		side2=0;	//Se pondrá mirando a la derecha para otros movimientos
		}
		else {	//si no está a ciertos pixels, nos seguirá
		if (frame==0){	//como está en movimiento, hara el movimiento de andar hacia nosotros, la derecha
			NF_SpriteFrame(0,2,4);	//Cambio de frame
		} else if (frame==1){
			NF_SpriteFrame(0,2,5);	//Cambio de frame
		}
		NF_MoveSprite(0, 2, x2++, y2);	//x2 (eje x del bicho) se incrementa para ir hacia la derecha
		side2=0;	//Se pondrá mirando a la derecha para otros movimientos
		}
	}

	//Movimientos verticales para que nos siga el bicho en el eje y
	if (y2!=120 && y2<y &&  vidagoku>0 && vidabicho>0){	//Si el bicho no está a nuestra altura, nos seguirá
		if(side2==0){	//El bicho está mirando hacia la derecha
			if (frame==0){
				NF_SpriteFrame(0,2,16);	//Cambio de frame
			}
			if (frame==1){
				NF_SpriteFrame(0,2,17);	//Cambio de frame
			}
		} else if(side2==1){	//El bicho está mirando hacia la izquierda
			if (frame==0){
				NF_SpriteFrame(0,2,14);	//Cambio de frame
			}
			if (frame==1){
				NF_SpriteFrame(0,2,15);	//Cambio de frame
			}
		}
		NF_MoveSprite(0, 2, x2, y2++);	//El bicho se moverá hacia abajo
	}
	if (y2!=30 && y2>y &&  vidagoku>0 && vidabicho>0){	//Si el bicho no está a nuestra altura, nos seguirá
		if(side2==1){	//El bicho está mirando hacia la izquierda
			if (frame==0){
				NF_SpriteFrame(0,2,1);	//Cambio de frame
			}
			if (frame==1){
				NF_SpriteFrame(0,2,12);	//Cambio de frame
			}
		} else if(side2==0){	//El bicho está mirando hacia la derecha
			if (frame==0){
				NF_SpriteFrame(0,2,3);	//Cambio de frame
			}
			if (frame==1){
				NF_SpriteFrame(0,2,13);	//Cambio de frame
			}
		}
		NF_MoveSprite(0, 2, x2, y2--);	//El bicho se moverá hacia arriba
	}

	//Cambio de los frames de los niveles segun en el que estemos
	switch(level){
		case 1:
			NF_SpriteFrame(1,16,1);	//Cambiamos la unidad a 1
			break;
		case 2:
			NF_SpriteFrame(1,16,2);	//Cambiamos la unidad a 2
			break;
		case 3:
			NF_SpriteFrame(1,16,3);	//Cambiamos la unidad a 3
			break;
		case 4:
			NF_SpriteFrame(1,16,4);	//Cambiamos la unidad a 4
			break;
		case 5:
			NF_SpriteFrame(1,16,5);	//Cambiamos la unidad a 5
			break;
		case 6:
			NF_SpriteFrame(1,16,6);	//Cambiamos la unidad a 6
			break;
		case 7:
			NF_SpriteFrame(1,16,7);	//Cambiamos la unidad a 7
			break;
		case 8:
			NF_SpriteFrame(1,16,8);	//Cambiamos la unidad a 8
			break;
		case 9:
			NF_SpriteFrame(1,16,9);	//Cambiamos la unidad a 9
			break;
		case 10:
			NF_SpriteFrame(1,16,0);	//Cambiamos la unidad a 0
			NF_SpriteFrame(1,17,1);	//Cambiamos la decena a 1
			break;
		case 11:
			NF_SpriteFrame(1,16,1);	//Cambiamos la unidad a 1
			break;
		case 12:
			NF_SpriteFrame(1,16,2);	//Cambiamos la unidad a 2
			break;
		case 13:
			NF_SpriteFrame(1,16,3);	//Cambiamos la unidad a 3
			break;
		case 14:
			NF_SpriteFrame(1,16,4);	//Cambiamos la unidad a 4
			break;
		case 15:
			NF_SpriteFrame(1,16,5);	//Cambiamos la unidad a 5
			break;
}


	//Cambio del cargador segun los puntos acumulados para el super ataque
	switch(bola){
		case 0:
			NF_SpriteFrame(1,13,0);	//Se vacian las bolas del cargador
			NF_SpriteFrame(1,14,0);
			NF_SpriteFrame(1,15,0);
			break;
		case 2:
			NF_SpriteFrame(1,13,1);	//Se llena una bola del cargador
			break;
		case 4:
			NF_SpriteFrame(1,14,1);	//Se llena otra bola del cargador
			break;
		case 6:
			NF_SpriteFrame(1,15,1);	//Se llena otra bola del cargador
			break;
	}

	//Cambio de los corazones de goku segun su vida, al recibir un golpe se le quitará medio corazon, al recibir el siguiente se le quitará un corazon entero
	switch(vidagoku){

		case 0:
			NF_SpriteFrame(0,5,2);	//Todos sus corazones están a 0
			break;
		case 1:
			NF_SpriteFrame(0,5,1);	//Se le quita medio corazon
			break;
		case 2:
			NF_SpriteFrame(0,4,2);	//Se le quita un corazon
			break;
		case 3:
			NF_SpriteFrame(0,4,1);	//Se le quita medio corazon
			break;
		case 4:
			NF_SpriteFrame(0,3,2);	//Se le quita un corazon
			break;
		case 5:
			NF_SpriteFrame(0,3,1);	//Se le quita medio corazon
			break;
		case 6:
			NF_SpriteFrame(0,3,0);	// Los corazones de goku se ponen enteros
			NF_SpriteFrame(0,4,0);
			NF_SpriteFrame(0,5,0);
			break;
		
	}

	//Cambio de los corazones del bicho segun su vida con divisiones, puesto que su vida aumentará con los niveles
	if (vidabicho <= vidabichocorazon/2) {	//Cuando le falte la mitad de vida se le resta un corazon
		NF_SpriteFrame(0,6,2);
	} 
	if (vidabicho <= vidabichocorazon/3){	//Cuando le falte un tercio de vida se le resta otro corazon
		NF_SpriteFrame(0,7,2);
	} 
	if (vidabicho<=0){	//Al morir se le quitan todos los corazones (estan todos por si muere debido a un superataque)
		NF_SpriteFrame(0,6,2);
		NF_SpriteFrame(0,7,2);
		NF_SpriteFrame(0,8,2);
	} 

	// Cambio de las estrellas en la bola segun tengamos para revivir o no
	switch(revivir){
		case 0:
			NF_SpriteFrame(1,10,2);	//Se nos quitan todas las estrellas
			NF_SpriteFrame(1,11,2);
			NF_SpriteFrame(1,12,2);	
			break;
		case 1:
			NF_SpriteFrame(1,10,1);	//Conseguimos una estrella
			break;

		case 2:
			NF_SpriteFrame(1,11,1);	//Conseguimos la segunda estrella
			break;

		case 3:
			NF_SpriteFrame(1,12,1);	//Conseguimos la tercera estrella
			break;
	} 

	//Muerte del personaje cuando su vida llega a 0
	if (vidagoku<=0){
		if(sonidosmuerte==0){	//Si su sonido de muerte está habilitado lo ejecutamos
			NF_PlayRawSound(4, 100, 64, false, 0);
			sonidosmuerte=1;	//Deshabilitamos el sonido de muerte para que no se repita
		}
		if(vidagoku<=0 && side==0 ){	//Si el personaje está mirando a la derecha	
			if(y!=120){	//Si el personaje no está en el suelo
				NF_MoveSprite(0, 0, x, y+=2);	//Funcion para que caiga el personaje al suelo cuando muere si está en el aire
			}
			NF_SpriteFrame(0,0,14);	//Frame de muerto hacia la derecha
		} else if(vidagoku<=0 && side==1){	//Si el personaje está mirando a la izquierda
			if(y!=120){	//Si el personaje no está en el suelo
				NF_MoveSprite(0, 0, x, y+=2);	//Funcion para que caiga el personaje al suelo cuando muere si está en el aire
			}
			NF_SpriteFrame(0,0,15);	//Frame de muerto hacia la izquierda
		}
		sprites = 1;	//Ponemos para que no se ejecute el bloque de los sprites puesto que estamos muertos
		if (revivir < 3){	//Si no podemos revivir
			NF_CreateTiledBg(0, 3, "muerto1");	//Creamos el fondo de game over
			oamDisable (&oamMain);	//Quitamos los sprites de arriba
			if (frame==0){	//Cambiamos al boton a RETRY
				NF_SpriteFrame(1,9,5);
			} else if (frame==1){
				NF_SpriteFrame(1,9,6);
			}
			if(_SpriteTouched(9)){	//Al tocar el boton vamos al intro y se resetean los valores iniciales
				fondos=0;	//Habilitamos la carga de fondos para que se carguen los de intro
				NF_SpriteFrame(0,6,0);	// Los corazones del bicho se ponen enteros
				NF_SpriteFrame(0,7,0);
				NF_SpriteFrame(0,8,0);
				NF_SpriteFrame(1,17,0);	// Reseteamos las decenas del nivel
				NF_SpriteFrame(0,18,3);	//Reiniciamos las unidades y decenas en el sprite del contador
				NF_SpriteFrame(0,19,0);
				sonidosmuerte=0;	//Ponemos que se habiliten los sonidos de muerte
				mode=0;	//Vamos a la pantalla de intro
			}
			} else if (revivir >=3){	//Si podemos revivir
				if (frame==0){	//Cambiamos al boton a revivir
					NF_SpriteFrame(1,9,7);
				} else if (frame==1){
					NF_SpriteFrame(1,9,8);
				}
				if(_SpriteTouched(9)){	//Al pulsar el boton
					vidagoku = 6;	//Se resetea la vida de goku
					revivir = 0;	//Se resetea la cantidad de puntos necesarios para revivir
					sonidosmuerte=0;	//Ponemos que se habiliten los sonidos de muerte
			}
		}
	}
	//Muerte del bicho cuando su vida llega a 0
	if(vidabicho<=0){
		if (sonidosmuerte==0){	//Ejecutamos su sonido de muerte si está habilitado
			NF_PlayRawSound(3, 100, 64, false, 0);
			sonidosmuerte=1;	//Deshabilitamos el sonido de muerte para que no se repita
		}	
		if(y!=120){		//Si el bicho no está en el suelo	
			NF_MoveSprite(0, 2, x2, y2+=2);	//Funcion para que caiga el bicho al suelo cuando muere si está en el aire
		}
		if(side2==0){	//Animacion muerte hacia la derecha
			NF_SpriteFrame(0,2,11);
		} else if(side2==1){	//Animacion muerte hacia la izquierda
			NF_SpriteFrame(0,2,10);
		}
		if (frame==0){	//Aparece el boton next
			NF_SpriteFrame(1,9,3);
		} else if (frame==1){
			NF_SpriteFrame(1,9,4);
		}
		if(_SpriteTouched(9)){	//Al tocar el boton NEXT se resetean y cambian ALGUNOS los valores iniciales
			subirvidabicho+=5;	//Le subimos la vida al bicho en 5
			vidagoku=6;	//Las vida de goku se reinician
			atackrate-=1;	//La velocidad de ataque del bicho aumenta
			vidabicho=5 + subirvidabicho;	//Le aumentamos la vida inicial al bicho
			vidabichocorazon = vidabicho; //Actualizamos la vida del bicho para los sprites de sus corazones
			x = 4;	//Se reinician las posiciones de los jugadores
			y = 120;
			x2 = 169;
			y2 = 120;
			NF_SpriteFrame(0,6,0);	// Los corazones del bicho se ponen enteros
			NF_SpriteFrame(0,7,0);
			NF_SpriteFrame(0,8,0);
			timeup = 30;	//Reiniciamos el contador
			unidades = 10;	//Reiniciamos las unidades para el sprite del contador
			NF_SpriteFrame(0,18,3);//Reiniciamos las unidades y decenas en el sprite del contador
			NF_SpriteFrame(0,19,0);
			revivir++;	//Conseguimos una estrella para revivir
			level++;	//Pasamos al siguiente nivel
			sonidosmuerte=0;	//Habilitamos los sonidos de muerte
			if (atackrate==0){	//We allow to create backgrounds for when we winner
				fondos = 0;
			}
		}
	}

	//Nos aseguramos que la vida del bicho no sea negativa cuando este muerto
	if(vidabicho<0){
		vidabicho=0;
	}

	// Posicion del Sprite goku
	NF_MoveSprite(0, 0, x, y);

	// Limites del movimiento de nuestro personaje, para el bicho solo necesitamos para cuando le matemos para que no caiga inifinitamente, para el resto no porque siempre nos seguirá
	if (x < 4) x = 4;
	if (x > 195) x = 195;
	if (y > 120) y = 120;
	if (y < 30) y = 30;
	if (y2 > 120) y2 = 120;

	
	if (atackrate==0){	//Cuando hayamos vencido al monstruo teniendo 1 de ataque ya habremos ganado el juego
		if (fondos == 0){
			NF_CreateTiledBg(0, 3, "ganador");	//Creamos el fondo de ganador arriba
			NF_CreateTiledBg(1, 3, "ganador2");	//Creamos el fondo de ganador abajo
			oamDisable (&oamSub);	//Quitamos la renderizaciones de sprites
			oamDisable (&oamMain);
			fondos = 1;
		}
		if (frame==0){	//Cambiamos al boton de RETRY
			NF_SpriteFrame(1,9,5);
		} else if (frame==1){
			NF_SpriteFrame(1,9,6);
		}
		if(keys & KEY_Y){	//Al tocar el boton vamos al principio y se resetean los valores iniciales
			fondos=0;	//Habilitamos que se carguen los fondos
			mode=0;	//Vamos a la pantalla de intro
			NF_SpriteFrame(0,6,0);	// Los corazones del bicho se ponen enteros
			NF_SpriteFrame(0,7,0);
			NF_SpriteFrame(0,8,0);
			NF_SpriteFrame(1,17,0);	// Reseteamos las decenas del nivel del sprite del contadorr

		}
	}


	// Botones que se mostraran en pantalla inferior segun el estado del juego y lo controlará
	if(vidagoku>0 && vidabicho>0){	//Si se está peleando solo se muestra un icono de fight
			NF_SpriteFrame(1,9,0);	
	}
	if (vidagoku>0 && vidabicho >0 && bola==6){	//Si nuestro cargador esta lleno para el super ataque y aun estamos luchando, aparecera un boton indicandolo para soplar y realizarlo
		if (frame==0){
			NF_SpriteFrame(1,9,1);
		} else if (frame==1){
			NF_SpriteFrame(1,9,2);
		}
	}

	// Funcion para que disminuya el contador de tiempo (sprites)
	if(contador==0 && timeup > 0 && vidagoku>0 && vidabicho >0){	//Si pasa un segundo, el tiempo es mayor a 0, y ambos personajes estan vivos
		contadoratras++;	//Aumentamos el contador hacia atras
		if(contadoratras%30==0){	//Puesto que aumenta de 30 en 30 debido al timer, cuando se divisible entre 0 haremos nuestras instrucciones
			timeup--;	//Reducimos el contador
			unidades--;	//Reducimos las unidades para el sprite
			if (unidades<0){	//Nos aseguramos que las unidades no sean menor a 0 y las reiniciamos
				unidades=9;
			}
			NF_SpriteFrame(0,19,unidades);	//Actualizamos las unidades del sprite segun estas vayan disminuyendo
			switch (timeup){	//Actualizamos las decenas del sprite
				case 29:
					NF_SpriteFrame(0,18,2);	//Cuando sea menor a 30 se pone 2X
					break;
				case 19:
					NF_SpriteFrame(0,18,1);	//Cuando sea menor a 20 se pone 1X
					break;
				case 9:
					NF_SpriteFrame(0,18,0);	//Cuando sea menor a 10 se pone 0X
					break;
			}
		}
	}

	if (timeup <= 0){	//Si se acaba el tiempo morimos, aunque podamos revivir
		NF_CreateTiledBg(0, 3, "muerto1");	//Creamos el fondo de game over
		oamDisable (&oamMain);	//Quitamos los sprites de arriba
		if (frame==0){	//Cambiamos al boton de RETRY
			NF_SpriteFrame(1,9,5);
		} else if (frame==1){
			NF_SpriteFrame(1,9,6);
		}
		if(_SpriteTouched(9)){	//Al tocar el boton vamos al intro y se resetean los valores iniciales
			fondos=0;	//Habilitamos la carga de fondos
			sonidosmuerte=0;	//Reiniciamos los sonidos de muerte
			mode=0;	//Vamos a la pantalla de intro
			NF_SpriteFrame(0,6,0);	// Los corazones del bicho se ponen enteros
			NF_SpriteFrame(0,7,0);
			NF_SpriteFrame(0,8,0);
			NF_SpriteFrame(1,17,0);	// Reseteamos las decenas del nivel
			NF_SpriteFrame(0,18,3);	//Reiniciamos las unidades y decenas en el sprite del contador
			NF_SpriteFrame(0,19,0);
		}
	}
}
NF_SpriteOamSet(0);
NF_SpriteOamSet(1);

oamUpdate(&oamMain);

oamUpdate(&oamSub);	// Actualiza a VRAM el OAM Secundario
swiWaitForVBlank();	// Espera al sincronismo vertical

}
return 0; 
}
