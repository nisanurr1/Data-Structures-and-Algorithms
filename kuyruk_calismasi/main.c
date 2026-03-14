#include <stdio.h>
#include <stdlib.h>

typedef struct kuyruk
{
    int bas; // ekleme yapilacak dizideki indeksleri yonetmek icin
    int son;
    int sayi; // bu bana bos mu dolu mu kontorlleri saglayacak.
    int eleman[5]; //ekleme yapacagim dizi
} kuyruk;

kuyruk* kuyrukOlustur()
{
    kuyruk *yeni_kuyruk = (kuyruk*)malloc(sizeof(kuyruk));

    yeni_kuyruk->bas = 0;
    yeni_kuyruk->son = 0;
    yeni_kuyruk->sayi = 0;

    return yeni_kuyruk;
}

void enqueu(kuyruk *yeniKuyruk, int eklenecek_sayi)
{
    //once kuyruk dolu mu diye bak!
    if(yeniKuyruk->sayi >= 5)
    {
        printf("\n kuyruk dolu oldugu icin ekleme yapilamadi!\n");
        return;
    }


    else // dolu degilse ekleme islemini yap.
    {
        //kuyruk dizi veri tipinde oldugundan dolayi bellekten yer ayirmiyoruz
        yeniKuyruk->eleman[yeniKuyruk->son] = eklenecek_sayi;

        //sonu da guncellemeyi unutma bir sonraki eklemeler icin.
        yeniKuyruk->son = (yeniKuyruk->son+1) % 5;
        yeniKuyruk->sayi++;

        printf("\nkuyruga eklenen sayi : %d", eklenecek_sayi);
    }
}

int dequeue(kuyruk *yeniKuyruk)
{
    // bos ise cikarilacak bir sey yoktur.
    if(yeniKuyruk->sayi <= 0)
    {
        printf("\n kuyruk bos oldugu icin cikarma yapilamadi!\n");
        return -1;
    }

    else
    {
        int cikanSayi;
        //bastan cikar
        cikanSayi = yeniKuyruk->eleman[yeniKuyruk->bas];
        yeniKuyruk->bas = (yeniKuyruk->bas + 1) % 5;
        yeniKuyruk->bas--;

        printf("\nkuyruktan cikan sayi : %d", cikanSayi);
        return cikanSayi;
    }

}

int main()
{
    kuyruk *yeni_kuyruk = kuyrukOlustur();

    //simdi kuyruga ekleme yapacagim.

    enqueu(yeni_kuyruk, 10);
    enqueu(yeni_kuyruk, 20);
    enqueu(yeni_kuyruk, 30);
    enqueu(yeni_kuyruk, 40);

    int cikan;

    //simdi ise kuyruktan cikarma islemini yapacagim.

    cikan = dequeue(yeni_kuyruk);
    cikan = dequeue(yeni_kuyruk);
    cikan = dequeue(yeni_kuyruk);


return 0;
}
