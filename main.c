#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char rodneCislo[12]; // "xxxxxx/xxxx\0"

int den;
int mesic;
int rok;
int poradi;
int kontrolni;

int zena;
int konec;
int vyhovuje=0;

int count=0;


// kontrolni cislo => (devet cislic u sebe) % 11

void generovat(){

    int celeCislo = 000000000;

    celeCislo += (rok/10)*1000000000;
    celeCislo += (rok%10)*100000000;

    if(zena){
        mesic += 50;

        celeCislo += (mesic/10)*10000000;
        celeCislo += (mesic%10)*1000000;

        mesic -= 50;

    } else{
        celeCislo += (mesic/10)*10000000;
        celeCislo += (mesic%10)*1000000;
    }

    celeCislo += (den/10)*100000;
    celeCislo += (den%10)*10000;

    celeCislo += (poradi/100)*1000;
    celeCislo += ((poradi/10)%10)*100;
    celeCislo += (poradi%10)*10;


    while(!vyhovuje){
        // zkouseni nahodnych kombinaci kontrolniho cisla (dokud nebude cele rodne cislo delitelne 11 beze zbytku)

        celeCislo += kontrolni;


        if(celeCislo%11 == 0){

            vyhovuje = 1;
            break;
        
        } else{

            if(kontrolni+1 == 10){
                break;

            } else{
                celeCislo -= kontrolni;

                kontrolni++;
            }
        }
    }

    if(vyhovuje){
        // zapsat do pole, pokud vyhovuje

        rodneCislo[0] = '0' + rok/10;
        rodneCislo[1] = '0' + rok%10;

        if(zena){
            mesic += 50;

            rodneCislo[2] = '0' + mesic/10;
            rodneCislo[3] = '0' + mesic%10;

            mesic -= 50;

        } else{
            rodneCislo[2] = '0' + mesic/10;
            rodneCislo[3] = '0' + mesic%10;
        }

        rodneCislo[4] = '0' + den/10;
        rodneCislo[5] = '0' + den%10;
        
        rodneCislo[7] = '0' + poradi/100;
        rodneCislo[8] = '0' + (poradi/10)%10;
        rodneCislo[9] = '0' + poradi%10;

        rodneCislo[10] = '0' + kontrolni;
    }

    // pokud nevyhovuje (else), pouze se inkrementují hodnoty - bez zápisu

    if (kontrolni+1 == 10){
        kontrolni = 0;
    
        if (poradi+1 == 1000){
            poradi = 0;

            if((den+1 == 29 && mesic==2) || (den+1 == 32 && mesic%2 == 0) || (den+1 == 31 && mesic%2 == 1)){
                den = 1;

                if(mesic+1 == 13){
                    mesic = 1;

                    if(rok+1 == 100){

                        // ukončit while
                        konec = 1;

                    } else{
                        rok++;
                    }

                } else{
                    mesic++;
                }

            } else{
                den++;
            }

        } else{
            poradi++;
        }

    } else{
        kontrolni++;
    }
}

int main(){

    int zacatek = time(0);

    rodneCislo[6] = '/';
    rodneCislo[11] = '\0';

    FILE *f;
    f = fopen("rodna_cisla.txt", "w");

    if (f == NULL){
        return 1;
    }

    printf("Zacinam generovat muzska rodna cisla...\n");
    // reset hodnot

    den = 01;
    mesic = 01;
    rok = 00;
    poradi = 000;
    kontrolni = 0;

    zena = 0;
    konec = 0;

    while(!konec){
        generovat();

        if(vyhovuje){

            //printf("%s\n", rodneCislo);
            fprintf(f, "%s\n", rodneCislo);

            vyhovuje = 0;
            count++;
        }
    }

    printf("Zacinam generovat zenska rodna cisla...");
    // reset hodnot
    den = 01;
    mesic = 01;
    rok = 00;
    poradi = 000;
    kontrolni = 0;

    zena = 1;
    konec = 0;

    while(!konec){
        generovat();

        if(vyhovuje){

            //printf("%s\n", rodneCislo);
            fprintf(f, "%s\n", rodneCislo);

            vyhovuje = 0;
            count++;
        }
    }

    fclose(f);

    printf("\n--------------------------------------------\n");
    printf("\nGenerace dokoncena.\nDoba trvani: %dsec\n", time(0)-zacatek);
    printf("Pocet rodnych cisel: %d\n", count);

    system("pause");
    return 0;
}