#include <stdio.h>
#include <stdlib.h>

//oncelikle agacin koku ve sag sol cocuklari olur, bunun yapisini kur.

typedef struct Agac
{
    int eleman;
    struct Agac *sag, *sol;
} Agaclar;

Agaclar *kok = NULL;


void recursive_ekle(Agaclar *agac_kok, Agaclar *yeni)
{
    if(agac_kok == NULL)
    {
        agac_kok = yeni;
        kok = yeni;
    }
    else //kok doluysa 2 durum var ya kokten buyuk ya da kucuk
    {
        if(yeni->eleman < agac_kok->eleman)
        {
            if(agac_kok->sol == NULL)
            {
                agac_kok->sol =yeni;
            }
            else //sol kok bos degilse artik recursive sekilde ekleme yapilacak
            {
                recursive_ekle(agac_kok->sol, yeni);
            }
        }
        if(yeni->eleman > agac_kok->eleman)
        {
            //yine 2 durum var sag kok dolu mu bos mu kontrol et
            if(agac_kok->sag == NULL)
            {
                agac_kok->sag = yeni;
            }
            else
            {
                recursive_ekle(agac_kok->sag, yeni); //alt agaci kontrol ede ede ilerleyecek koymasi gereken yere koyacak.
            }
        }
    }
}


void inorder_listele(Agaclar *agackok)
{
    if(agackok != NULL)
    {
        inorder_listele(agackok->sol);
        printf("%d      ",agackok->eleman);
        inorder_listele(agackok->sag);
    }
}

int sayac = 0; //bize dugum sayisini dondurecek.
int recursive_dugumSayisi_Bul(Agaclar *kok)// parametre olarak gelen kok surekli kendine gelen kokun devamindakileri dolasacak.
{
    if(kok != NULL)
    {
        recursive_dugumSayisi_Bul(kok->sol);
        sayac++;
        recursive_dugumSayisi_Bul(kok->sag);
    }
}

int main()
{
    //eklenecek dugumun bilgisini al

    int sayi,secim;

    while(1)
    {
        printf("\n1-Ekle");
        printf("\n2-Listele");
        printf("\n3-Dugum Sayisini Bul");
        printf("\n4-Cikis\nBirini seciniz: ");
        scanf("%d",&secim);

        switch(secim)
        {
            case 1:
            {
                printf("\nEklenecek sayiyi giriniz: ");
                scanf("%d",&sayi);

                Agaclar *yeni = (Agaclar*)malloc(sizeof(Agaclar));
                yeni->eleman = sayi;
                yeni->sag = NULL;
                yeni->sol = NULL;

                recursive_ekle(kok, yeni);
                break;
            }
            case 2:
            {
                //listelenecek.
                inorder_listele(kok);
                break;

            }
            case 3: //recursive sekilde binary treedeki node sayisini bulacak.
            {
                recursive_dugumSayisi_Bul(kok);
                printf("\nToplam anlik dugum sayisi: %d",sayac);
                break;

            }
            case 4:
            {
                //sirayla ahaci gezip nodelarý free etmen gerekir.
                return 0;
            }
        }

    }

    return 0;
}
