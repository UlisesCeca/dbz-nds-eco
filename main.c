// Includes C
#include <stdio.h>

// Includes propietarios NDS
#include <nds.h>

// Includes librerias propias
#include <nf_lib.h>

// Timers
static int frame=0; //Timer para cambios de frames en sprites
static int atack=1; //Timer para que el bicho ataque cada cierto tiempo
static int superatack=1; //Timer para un ataque que quitará bastante vida
static int atackrate=15; //Cambiará segun el nivel para que el bicho ataque mas rapido
void timeout()
{
	
   static int num=0;
   num++;
   frame = num%2; //Tomará el valor 1 o 0 dependiendo de num, con cada uno cambiará de frame
   atack = num%atackrate; //Tomará el valor cada ciertos segundos
   superatack = num%20;	//Aumentará el contador cada 10 segundos para el super ataque

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

// Inicializa los fondos tileados
NF_InitTiledBgBuffers();	// Inicializa los buffers para almacenar fondos
NF_InitTiledBgSys(0);	// Inicializa los fondos Tileados para la pantalla superior
NF_InitTiledBgSys(1);	// Iniciliaza los fondos Tileados para la pantalla inferior

// Inicializa los Sprites
NF_InitSpriteBuffers();	// Inicializa los buffers para almacenar sprites y paletas
NF_InitSpriteSys(0);	// Inicializa los sprites para la pantalla superior
NF_InitSpriteSys(1);	// Inicializa los sprites para la pantalla inferior

// Inicializa el motor de texto
NF_InitTextSys(0);	// Inicializa el texto para la pantalla superior

// Inicializa los buffers de mapas de colisiones
NF_InitCmapBuffers();

// Carga la fuente por defecto para el texto
NF_LoadTextFont("fnt/default", "normal", 256, 256, 0);

// Crea una capa de texto
NF_CreateTextLayer(0, 2, 0, "normal");

// Carga los archivos de fondo desde la FAT / NitroFS a la RAM
NF_LoadTiledBg("bg/torneo", "torneo", 256, 256);	// Carga el fondo para la pantalla superior
NF_LoadTiledBg("bg/pabajo", "pabajo", 256, 256);	// Carga el fondo para la pantalla superior

// Crea los fondos de la pantalla superior
NF_CreateTiledBg(0, 3, "torneo");

// Carga los archivos de sprites desde la FAT / NitroFS a la RAM
NF_LoadSpriteGfx("sprite/goku", 0, 64, 64);	// Goku
NF_LoadSpritePal("sprite/goku", 0);
NF_LoadSpriteGfx("sprite/saibaman", 2, 64, 64);	// saibaman
NF_LoadSpritePal("sprite/saibaman", 2);
NF_LoadSpriteGfx("sprite/bola", 1, 64, 64);	// bola ataque final, hemos creado otro sprite porque no nos cabe en 64x64 junto a goku
NF_LoadSpritePal("sprite/bola", 1);
NF_LoadSpriteGfx("sprite/corazones", 3, 16, 16);	// Corazones
NF_LoadSpritePal("sprite/corazones", 3);
NF_LoadSpriteGfx("sprite/corazones", 4, 16, 16);	// Corazones
NF_LoadSpritePal("sprite/corazones", 4);
NF_LoadSpriteGfx("sprite/corazones", 5, 16, 16);	// Corazones
NF_LoadSpritePal("sprite/corazones", 5);

// Transfiere a la VRAM los sprites necesarios
NF_VramSpriteGfx(0, 0, 0, true);	// Goku
NF_VramSpritePal(0, 0, 0);
NF_VramSpriteGfx(0, 2, 2, true);	// saibaman
NF_VramSpritePal(0, 2, 2);
NF_VramSpriteGfx(0, 1, 1, true);	// bola ataque final
NF_VramSpritePal(0, 1, 1);

NF_VramSpriteGfx(1, 3, 3, true);	// corazones
NF_VramSpritePal(1, 3, 3);
NF_VramSpriteGfx(1, 1, 1, true);	// corazones
NF_VramSpritePal(1, 1, 1);
NF_VramSpriteGfx(1, 2, 2, true);	// corazones
NF_VramSpritePal(1, 2, 2);


// Crea el Sprite del goku y la bola final en la pantalla superior
s16 x = 4;
NF_CreateSprite(0, 0, 0, 0, x, 120);
NF_CreateSprite(0, 2, 2, 2, x, 120);

// Crea el Sprite del monstruo en la pantalla superior
s16 x2 = 169;
NF_CreateSprite(0, 1, 1, 1, x2, 120);

// Crea corazones de vidas en la pantalla inferior
NF_CreateSprite(1, 1, 3, 3, x, 120);


// Variable para la lectura del keypad
u16 keys = 0;

//Variable para el modo de juego: intro, niveles y perdedor
int mode = 0;

//Variables para la vida
int vidagoku = 6;	//a los 6 golpes muere goku 6*30
int vidabicho = 5;	//a los 2 golpes muere el bicho 2*30

// Buffer de texto
char mytext[32];

// Variables para hacia donde mirarán los sprites
int side = 0;	//lado al que mira goku
int side2 = 0;	//lado al que mire el bicho

//Contador para que los timers aumenten o resten de uno en uno, porque estos aumentan de 30 en 30
int contadorgoku=0;	//contador para la vida de goku
int contadorbola=0;	//contador para la carga de la bola

// Variable para el super ataque y ataques normales
int ataque = 0;	//controlador ataque, permite evitar que si se queda una tecla pulsada le baje la vida continuamente al monstruo, por lo que hay que repetir las pulsaciones
int bola = 0;	//cargador super ataque

// Variables para impedir hacer ataques infinitos mientras se corre
int correrAtaques = 0;	//evitar ataques infinitos al volar

// Bucle (repite para siempre)
while(1) {
// Lee el teclado
scanKeys();
keys = keysHeld();
// Si no se pulsan teclas, estamos vivos y no estamos en los limites: el personaje está quieto
if(keys==0 && vidagoku>0 || x== 4 || x ==195){
	NF_SpriteFrame(0,1,2);	//ponemos que el sprite de la bola no se vea
	if(side==0){	//para mirar hacia la derecha
	if (frame==0){
		NF_SpriteFrame(0,0,0);
	}
	else if (frame==1){
			NF_SpriteFrame(0,0,1);
		}
	}
	else if(side==1){	//para mirar a la izquierda
	if (frame==0){
		NF_SpriteFrame(0,0,16);
	}
	else if (frame==1){
			NF_SpriteFrame(0,0,17);
		}
	}
	ataque = 1;	//ponemos que sea necesario levantar la tecla para realizar ataques (para quitar vida al monstruo)
	correrAtaques = 0;	//Al levantar las teclas de ataque podremos correr libremente, evitando ataques infinitos
}
// Si se pulsa la tecla izquierda, estamos vivos, no se están haciendo ataques y no estamos en el limite izquierdo: nos movemos a la izquierda
if (keys & KEY_LEFT && vidagoku>0 && correrAtaques == 0 && x != 4) {

	if (frame==0){
		NF_SpriteFrame(0,0,4);
	}
	else if (frame==1){
			NF_SpriteFrame(0,0,5);
	}
	x -= 3;
	side = 1; //ponemos que mire hacia la izquierda cuando haga otro movimiento que no sea moverse
}
// // Si se pulsa la tecla derecha, estamos vivos, no se están haciendo ataques y no estamos en el limite derecho: nos movemos a la derecha
if (keys & KEY_RIGHT && vidagoku>0 && correrAtaques == 0 && x != 195){
	if (frame==0){
		NF_SpriteFrame(0,0,2);
	}
	else if (frame==1){
			NF_SpriteFrame(0,0,3);
		}
	x +=3;
	side = 0; //ponemos que mire hacia la derecha cuando haga otro movimiento que no sea moverse
}
// Si se pulsa la tecla B y el bicho y nosotros estamos vivos: Patada
if (keys & KEY_B && vidagoku>0 && vidabicho>0){
	if (side==0){
	NF_SpriteFrame(0,0,7); //patada hacia derecha
	if (x2 > x && x2 <= x+30 && vidabicho>0 && ataque == 1){
		vidabicho--;
		side2 = 1;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
		ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
		}
	}
	else if (side==1){
	NF_SpriteFrame(0,0,6); //patada hacia izquierda
		if (x2 < x && x2 >= x-30 && vidabicho>0 && ataque == 1){
			vidabicho--;
			side2 = 0;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
			ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
		}
	}
	correrAtaques = 1;
}
// Si se pulsa la tecla A y el bicho y nosotros estamos vivos: Puñetazo
if (keys & KEY_A && vidagoku>0 && vidabicho>0){
	if (side==0){
		NF_SpriteFrame(0,0,9); //puñetazzo hacia derecha
		if (x2 > x && x2 <= x+30 && vidabicho>0 && ataque == 1){
			vidabicho--;
			side2 = 1;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
			ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
		}
	}
	else if (side==1){
		NF_SpriteFrame(0,0,8); //puñetazzo hacia izquierda
		if (x2 < x && x2 >= x-30 && vidabicho>0 && ataque == 1){
			vidabicho--;
			side2 = 0;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
			ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
		}
	}
	correrAtaques = 1;
}
// Cada diez segundos se carga en un punto el super ataque si el bicho y nosotros estamos vivos
if (superatack == 0 && vidagoku>0 && vidabicho>0){
	contadorbola++;
	if (contadorbola%30==0){	//el contador aumenta en 30 debido al timer, por tanto cada vez que el resto sea 0 nos cargará en un punto el super ataque
		bola++;
		if (bola>=6){
			bola=6;
		}
	}
}
// Si se sopla y el ataque final está cargado (6 puntos): Ataque final
if (keys & KEY_X && bola>=6){
	if (side==0){
		NF_MoveSprite(0, 1, x+55, 114);	//calibramos la posicion del sprite de la bola para que encaje con el de goku y salga donde nosotros
		NF_SpriteFrame(0,0,11); //super ataque hacia derecha
		NF_SpriteFrame(0,1,0);	//frame bola hacia derecha
		if (x2 > x && x2 <= x+81 && vidabicho>0  && ataque == 1){	//aumentamos el rango al que le afectará el ataque a diferencia de una patada o puñetazo
			vidabicho-=20;
			side2 = 1;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
			ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
			bola = 0; // Ponemos el cargador a 0
		}
	}
	else if (side==1){
		NF_MoveSprite(0, 1, x-55, 115);	//calibramos la posicion del sprite de la bola para que encaje con el de goku y salga donde nosotros
		NF_SpriteFrame(0,0,13);	//super ataque hacia izquierda
		NF_SpriteFrame(0,1,1);	//frame bola hacia izquierda
		if (x2 < x && x2 >= x-81 && vidabicho>0  && ataque == 1){	//aumentamos el rango al que le afectará el ataque a diferencia de una patada o puñetazo
			vidabicho-=20;
			side2 = 0;	//ponemos que la muerte del bicho sea hacia el lado opuesto al nuestro por si muere
			ataque = 0;	//cambiamos esta variable a 0 para que sea necesario levantar la tecla para quitar vida al monstruo
			bola = 0; // Ponemos el cargador a 0
		}
	}
	correrAtaques = 1;

}

// Posicion y movimientos del Sprite bicho
if (x2 > x && vidabicho>0){	//el bicho está a nuestra derecha
	if (x2 <= x+30){	//a ciertos pixeles se detendrá para no juntar ambos sprites
		if (atack==0 && vidagoku>0){	//el personaje atacará dependiendo del timer cada ciertos segundos
			NF_SpriteFrame(0,2,9);
			contadorgoku++;
			if(contadorgoku%30==0){	//el contador aumenta en 30 debido al timer, por tanto cada vez que el resto sea 0 nos quitará un punto de vida
				vidagoku--;
			}
		} else if (frame==0){	//cuando no ataque estrá parado haciendo el movimiento de parado mirando hacia la izquierda (donde estamos)
			NF_SpriteFrame(0,2,0);
		} else if (frame==1){
			NF_SpriteFrame(0,2,1);
		}
		NF_MoveSprite(0, 2, x2, 120); //x2 (eje x del bicho) no hace nada para quedarse donde está
	}
	else {	//si no está a ciertos pixels, nos seguirá
		if (frame==0){	//como está en movimiento, hara el movimiento de andar hacia nosotros, la izquierda
			NF_SpriteFrame(0,2,6);
		} else if (frame==1){
			NF_SpriteFrame(0,2,7);
		}
		NF_MoveSprite(0, 2, x2--, 120); //x2 (eje x del bicho) se decrementa para ir hacia la izquierda
	}
} else if (x2 < x && vidabicho>0){	//el bicho está a nuestra izquierda
	if (x2 >= x-30){	//a ciertos pixeles se detendrá para no juntar ambos sprites
	if (atack==0 && vidagoku>0){	//el personaje atacará dependiendo del timer cada ciertos segundos
			NF_SpriteFrame(0,2,8);
			contadorgoku++;
			if(contadorgoku%30==0){	//el contador aumenta en 30 debido al timer, por tanto cada vez que el resto sea 0 nos quitará un punto de vida
				vidagoku--;
			}
		} else if (frame==0){	//cuando no ataque estrá parado haciendo  el movimiento de parado mirando hacia la derecha (donde estamos)
			NF_SpriteFrame(0,2,2);
		} else if (frame==1){
			NF_SpriteFrame(0,2,3);
	}
	NF_MoveSprite(0, 2, x2, 120); //x2 (eje x del bicho) no hace nada para quedarse donde está
	}
	else {	//si no está a ciertos pixels, nos seguirá
	if (frame==0){	//como está en movimiento, hara el movimiento de andar hacia nosotros, la derecha
		NF_SpriteFrame(0,2,4);
	} else if (frame==1){
		NF_SpriteFrame(0,2,5);
	}
	NF_MoveSprite(0, 2, x2++, 120);	//x2 (eje x del bicho) se incrementa para ir hacia la derecha
	}
}
//Muerte del personaje cuando su vida llega a 0
if(vidagoku<=0 && side==0){	//animacion muerte hacia la derecha
	NF_SpriteFrame(0,0,14);
} else if(vidagoku<=0 && side==1){	//animacion muerte hacia la izquierda
	NF_SpriteFrame(0,0,15);
}
//Muerte del bicho cuando su vida llega a 0
if(vidabicho<=0 && side2 == 0){	//animacion muerte hacia la derecha
	NF_SpriteFrame(0,2,11);
} else if(vidabicho<=0 && side2 == 1){	//animacion muerte hacia la izquierda
	NF_SpriteFrame(0,2,10);
}
//Nos aseguramos que la vida del bicho no sea negativa cuando este muerto
if(vidabicho<0){
	vidabicho=0;
}
// Posicion del Sprite goku
NF_MoveSprite(0, 0, x, 120);

// Limites del movimiento de nuestro personaje, para el bicho no necesitamos porque siempre nos seguira
if (x < 4) x = 4;
if (x > 195) x = 195;

// Imprime la posicion del cursor
sprintf(mytext,"VIDA GOKU: %d  VIDA BICHO: %d  CARGADOR: %d", vidagoku, vidabicho, bola);
NF_WriteText(0, 2, 1, 1, mytext);


NF_UpdateTextLayers();	// Actualiza las capas de texto
NF_SpriteOamSet(0);

oamUpdate(&oamMain);

oamUpdate(&oamSub);	// Actualiza a VRAM el OAM Secundario
swiWaitForVBlank();	// Espera al sincronismo vertical

}
return 0; 
}
