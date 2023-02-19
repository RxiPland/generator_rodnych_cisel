#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// *PROMENNE*

char rodneCislo[12]; // "RRMMDD/PPPK\0"
// D = 1-(28/30/31)
// M = 1-12
// R = 00-99
// P = 000-999
// K = 0-9

int den, mesic, rok, poradi, kontrolni;
int pocet=0;



// *NASTAVENI* (1=povolit, 0=zakazat):

int nabidnoutNastaveni = 1; // po zakazani nebude moci uzivatel zadat nastaveni a budou pouzite hodnoty nize

int ulozitDoSouboru = 1;  // ulozit rodna cisla do souboru
char nazevSouboru[256] = "rodna_cisla.txt"; // nazev souboru

int muz = 1;  // generovat muzska rodna cisla
int zena = 1; // generovat zenska rodna cisla


int generovat(){
    // funkce pro zapsani hodnot do pole rodneCislo, pokud je
    // rodne cislo validni (rozdil sudych a lichych cisel je delitelny bezezbytku 11)

    int sude=0, liche=0;

    liche += rok/10;
    sude += rok%10;

    if(zena && !muz){
        liche += (mesic+50)/10;
        sude += (mesic+50)%10;

    } else{
        liche += mesic/10;
        sude += mesic%10;
    }

    liche += den/10;
    sude += den%10;
    liche += poradi/100;
    sude += (poradi/10)%10;
    liche += (poradi%10)%10;
    sude += kontrolni;

    // negace cisla pokud bude zaporne
    int vysledek = sude-liche;
    if(vysledek<0){
        vysledek = -vysledek;
    }

    if((vysledek)%11==0){

        rodneCislo[0] = 48+(rok/10);
        rodneCislo[1] = 48+(rok%10);

        if(zena && !muz){
            rodneCislo[2] = 48+((mesic+50)/10);
            rodneCislo[3] = 48+((mesic+50)%10);
        
        } else{
            rodneCislo[2] = 48+(mesic/10);
            rodneCislo[3] = 48+(mesic%10);
        }
        
        rodneCislo[4] = 48+(den/10);
        rodneCislo[5] = 48+(den%10);
        //rodneCislo[6] = '/';
        rodneCislo[7] = 48+(poradi/100);
        rodneCislo[8] = 48+((poradi/10)%10);
        rodneCislo[9] = 48+((poradi%10)%10);
        rodneCislo[10] = 48+(kontrolni);

        pocet++;

        return 1;
    
    } else{
        return 0;
    }
}

int main(){

    FILE *f;
    int validni;
    char vstup[256];

    printf("*** Generator rodnych cisel ***\n\n");

    if(nabidnoutNastaveni){

        printf("Nastaveni (1=ano | 0=ne):\n\n");
        
        printf("Chcete generovat muzska rodna cisla? ");
        fgets(vstup, 256, stdin);

        if(vstup[0] == '0'){
            muz = 0;

        } else if(vstup[0] == '1'){
            muz = 1;
        
        } else{
            printf("Spatna hodnota! Nastavuji na 1\n");
            muz = 1;
        }

        printf("Chcete generovat zenska rodna cisla? ");
        fgets(vstup, 256, stdin);

        if(vstup[0] == '0'){
            zena = 0;

        } else if(vstup[0] == '1'){
            zena = 1;
        
        } else{
            printf("Spatna hodnota! Nastavuji na 1\n");
            zena = 1;
        }

        printf("\nChcete vystup ulozit do souboru? ");
        fgets(vstup, 256, stdin);

        if(vstup[0] == '0'){
            ulozitDoSouboru = 0;

        } else if(vstup[0] == '1'){
            ulozitDoSouboru = 1;
        
        } else{
            printf("Spatna hodnota! Nastavuji na 0\n");
            ulozitDoSouboru = 0;
        }

        if (ulozitDoSouboru){
            printf("Zadejte nazev souboru (max 255 znaku): ");
            fgets(vstup, 300, stdin);

            // spocitat delku nazvu
            int delka=0, i=0;
            while(vstup[delka] != '\0' && vstup[delka] != '\n' && delka<=254){
                delka++;
            }
            
            if(delka==0){
            	printf("Nazev nemuze byt prazdny! Nastavuji na rodna_cisla.txt\n");
        		// promenna nazevSouboru s defaultnim nazvem nebude prepsana
            	
			} else{
				
                // prepsat do noveho pole
				for(i=0; i<delka; i++){
					nazevSouboru[i] = vstup[i];
				}
				nazevSouboru[i] = '\0';
			}
        }
    }

    // otevrit soubor
    if (ulozitDoSouboru){
        f = fopen(nazevSouboru, "w");

        if (f == NULL){
            return 1;
        }
    }


    rodneCislo[6] = '/';
    int zacatek = time(0); // cas zacatku

    printf("\n\n");

    if(muz || zena){

        A:

        if(muz){
            printf("Zacinam generovat muzska rodna cisla...\n");

        } else if (zena){
            printf("Zacinam generovat zenska rodna cisla...\n");
        }

        if(!ulozitDoSouboru){
            sleep(2);
        }

        // postupne inkrementovani hodnot
        for(rok=00; rok<=99; rok++){

            for(mesic=01; mesic<=12; mesic++){

                for(den=01; (den<=31 && mesic%2==0 && mesic!=02) || (den<=30 && mesic%2!=0 && mesic!=02) || (den<=28 && mesic==02); den++){
                    
                    for(poradi=000; poradi<=999; poradi++){

                        for(kontrolni=0; kontrolni<=9; kontrolni++){

                            validni = generovat();

                            if(validni && ulozitDoSouboru){
                                // zapsat do souboru
                                fprintf(f, "%s\n", rodneCislo);

                            } else if (validni){
                                // vypsat do konzole
                                printf("%s\n", rodneCislo);
                            }
                        }
                    }
                }
            }
        }
    }

    // zopakovat proces pro zenu
    if(muz){
        if(zena){
            muz = 0;
            goto A;
        }
    }

    // zavrit soubor pokud se do nej zapisovalo
    if(ulozitDoSouboru){
        fclose(f);
    }

    printf("\n--------------------------------------------\n");
    printf("\nGenerace dokoncena.\nDoba trvani: %dsec\n", time(0)-zacatek);
    printf("Pocet rodnych cisel: %d\n\n", pocet);

    system("pause");

    return 0;
}
