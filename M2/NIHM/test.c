#include <gpio.h> 
#include <time.h>


pin_t ledJ1 = MAKE_PIN(GPIO_PORT_A, 5);
pin_t ledJ2 = MAKE_PIN(GPIO_PORT_B, 4);

pin_t ledStart = MAKE_PIN(GPIO_PORT_G,13);
pin_t BoutonJ1 = MAKE_PIN(GPIO_PORT_B, 7);
pin_t BoutonJ2 = MAKE_PIN(GPIO_PORT_C, 3);

int main(){
	uint16_t i,ledAllume;
	uint16_t fin=0;
	ledAllume = 1;
	/* Connexion des leds des deux joueurs */
	gpio_config(ledJ1, pin_dir_write); 
	gpio_config(ledJ2, pin_dir_write); 

	/* Connexion de la led centrale */
	gpio_config(ledStart, pin_dir_write);
	gpio_set(ledStart,0);

	/* Connexion des boutons des deux joueurs */
	gpio_config(BoutonJ1, pin_dir_write);
	gpio_config(BoutonJ2, pin_dir_write);

	/* Boucle permettant d'attendre avant d'allumer la led*/	
	for(i=0;i<100000;i++){ 
		/* Si le joueur 1 appuie sur son bouton alors il a perdu */
		if(gpio_get(J1)==1){
			gpio_set(ledJ2,1);
			ledAllume = 2;
			fin=1;
		}
		/* Si le joueur 2 appuie sur son bouton alors il a perdu */
		if(!fin && gpio_get(J2)==1){
			gpio_set(ledJ1,1);
			ledAllume = 1;
			fin=1;
		}
	}
	
	/* Si un des deux joueurs a déja appuyé alors on allume la led de l'autre joueur qui est vainqueur*/
	if(fin){
		if(ledAllume==1)
			gpio_set(ledJ1, 1);
		else
			gpio_set(ledJ2, 1);			
	}
	
	/* On allume la led centrale et on attend qu'un joueur appuie sur son bouton */
	else{
		gpio_set(ledStart, 1);

		while(!fin){
			if(gpio_get(J1)==1){
				gpio_set(ledJ1,1);
				fin=0;
			}
			if(!fin && gpio_get(J2)==1){
				gpio_set(ledJ2,1);
				fin=0;
			}
		}
	}

	return 0;

}
