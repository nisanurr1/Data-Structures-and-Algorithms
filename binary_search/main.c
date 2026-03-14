#include <stdio.h>
#include <stdlib.h>


int binary_search(int dizi[], int bas, int son, int aranan)
{
    int orta, orta_deger;

    if(bas > son) // gezme islemi bitmistir.
    {
        printf("\nAradiginiz eleman bulunamadi!\n");
        return -1;
    }
    else
    {
        //gezme islemi devam ediyor.
        orta = (bas + son) / 2; //ortadaki indis
        orta_deger = dizi[orta];

        if(orta_deger == aranan)
        {
            printf("%d elemaninin sirasi: %d \n", aranan, orta+1);
            return 0;
        }
        if(aranan > orta_deger) // sag taraftaki daha buyuk degerlere bakilacak
        {
            //tekrar binary searche devam etmesi lazim.
            //ayni fonksiyonu kaldigimiz yerden itibaren olan degerlerle kullanacagiz.
            binary_search(dizi, orta + 1,son,aranan);
        }
        if(aranan < orta_deger)
        {
            binary_search(dizi, bas, orta - 1, aranan);
        }
    }
}

int main()
{
    int dizi[10] = {9,8,16,17,25,52,20,78,96,5}; // 10 elemanli bir dizi olusturdum simdi istedigim elemani binary search ile bulacagim.
    //dizinin sirali olmasi gerekiyor!

    int boyut = sizeof(dizi) / sizeof(dizi[0]);

    //printf("boyut: %d", boyut);
    int i,j;
    for(j = 0; j < boyut; j++)
    {
        for(i = 0; i < boyut - 1; i++ )
        {
            int temp;
            if(dizi[i] > dizi[i+1])
            {
                temp = dizi[i+1];
                dizi[i+1] = dizi[i];
                dizi[i] = temp;
            }
        }

    }
    //diziyi siraladik ki binary search yapabilelim
    for(i = 0; i < boyut ; i++)
    {
        printf("%d -> ", dizi[i]);
    }

    int aranan;

    printf("\n\nHangi elemanin indisini ogrenmek istiyorsunuz: ");
    scanf("%d",&aranan);

    binary_search(dizi,0, boyut-1, aranan);

    return 0;
}
