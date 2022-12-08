#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char output[12];

int den;
int mesic;
int rok;
int poradi;
int kontrolni;

int zena;
int konec;

int count=0;

void generovat(){

    output[0] = '0' + rok/10;
    output[1] = '0' + rok%10;

    if(zena){
        mesic += 50;

        output[2] = '0' + mesic/10;
        output[3] = '0' + mesic%10;

        mesic -= 50;

    } else{
        output[2] = '0' + mesic/10;
        output[3] = '0' + mesic%10;
    }

    output[4] = '0' + den/10;
    output[5] = '0' + den%10;
    
    output[7] = '0' + poradi/100;
    output[8] = '0' + (poradi/10)%10;
    output[9] = '0' + poradi%10;

    output[10] = '0' + kontrolni;


    if(kontrolni+1 == 10){
        kontrolni = 0;

        if(poradi+1 == 1000){
            poradi = 0;

            if((den+1 == 29 && mesic==2) || (den+1 == 32 && mesic%2 == 0) || (den+1 == 31 && mesic%2 == 1)){
                den = 1;

                if(mesic+1 == 13){
                    mesic = 1;

                    if(rok+1 == 100){
                        // př. 991231/9999
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

    output[6] = '/';
    output[11] = '\0';

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

        //printf("%s\n", output);
        fprintf(f, "%s\n", output);
        count++;
    }

    printf("Zacinam generovat zenska rodna cisla...\n");
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

        //printf("%s\n", output);
        fprintf(f, "%s\n", output);
        count++;
    }

    fclose(f);

    printf("\nGenerace dokoncena.\nDoba trvani: %dsec\n", time(0)-zacatek);
    printf("Pocet rodnych cisel: %d\n", count);

    system("pause");
    return 0;
}