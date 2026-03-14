#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//23100011052 - Nisanur Cakir

// Urunler icin yapi
typedef struct
{
    char urunAdi[50];
    int satisMiktari;
    int stokMiktari;
} Urun;

//dugumler icin yapi
typedef struct Node
{
    struct Node* prev;
    struct Node* next;
    Urun urun;
}Node;

Node* head = NULL;
int listeolustu = 0;
int verilerOkundu = 0;

void verileriOku(const char *dosyaAdi)
{
    FILE *dosya = fopen(dosyaAdi, "r");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi!\n");
        return;
    }

    char urunAdi[50];
    int satisMiktari, stokMiktari;

    while (fscanf(dosya, "%[^,], %d, %d\n", urunAdi, &satisMiktari, &stokMiktari) == 3)
    {
        bagliListeyiOlustur(urunAdi, satisMiktari, stokMiktari);
    }
    verilerOkundu = 1;

    fclose(dosya);
}

void bagliListeyiOlustur(char urunAdi[], int satisMiktari, int stokMiktari)
{
    listeolustu = 1;
    Node* yeni = (Node*)malloc(sizeof(Node));

    strcpy(yeni->urun.urunAdi, urunAdi); //char tipinde oldugu icin
    yeni->urun.satisMiktari = satisMiktari;
    yeni->urun.stokMiktari = stokMiktari;

    //dugumler bos ise basa ekle.
    if(head == NULL)
    {
        head = (Node*)malloc(sizeof(Node));
        head = yeni;
        head->next = head;
        head->prev = head;
        return;
    }

    //yeni gelen bastakinden buyukse bastakiyle yer degistir.
    if(satisMiktari > head->urun.satisMiktari)
    {
        yeni->next = head;
        yeni->prev = head->prev;
        head->prev->next = yeni;
        head->prev = yeni;
        head = yeni;
        return;
    }

    //ortaya ya da sona hangisinden buyuk kaliyorsa oraya ekle
    else
    {
        Node* temp = head;

        while(temp->next != head && temp->next->urun.satisMiktari > satisMiktari)
        {
            temp = temp->next;
        }
        yeni->next = temp->next;
        yeni->prev = temp;
        temp->next->prev = yeni;
        temp->next = yeni;
        return;
    }
}

void ekranaYazdir()
{
    Node* temp = head;
    if(head == NULL) return;

    printf("\n-----------------------------------------\n");
    while(1)
    {
        printf("Ad: %s, \tSatis: %d, \tStok: %d\n", temp->urun.urunAdi, temp->urun.satisMiktari, temp->urun.stokMiktari);
        temp = temp->next;
        if(temp == head) break;
    }
    printf("\n-----------------------------------------\n");
}

void satisGir()
{
    char urun_Ad[50];
    int satis_Mik;
    int bul = 0;

    printf("-----------------------------------------");
    printf("\nUrun adi giriniz: ");
    scanf("%s",&urun_Ad);

    Node* temp = head;

    while(temp->next != head && strcmp(temp->urun.urunAdi, urun_Ad) != 0) //urunu bulana kadar git.
    {
        temp = temp->next;
    }

    if(strcmp(temp->urun.urunAdi, urun_Ad) == 0)
    {
        bul = 1;
    }

    if(bul == 0)
    {
        printf("\n***Urun bulunamadi!***\n");
        return;
    }

    printf("\nSatis miktari giriniz: "); //burada satilmak istenen kadar
    scanf("%d",&satis_Mik);
    printf("\n-----------------------------------------\n\n");

    //girilen urunden var mi yok mu ona bak.


    if(temp->urun.stokMiktari >= satis_Mik && temp->urun.stokMiktari > 0) //sifir bile olsa satis yapilir yoksa.
    {
        //urun bulunmustur ve stok yeterlidir(sifirdan da farklidir).

        temp->urun.stokMiktari -= satis_Mik; //satis kadar dusus yasandi.
        temp->urun.satisMiktari += satis_Mik; //satilan miktar artmis oldu.
    }
    else
    {
        printf("\nYeteri kadar stok yoktur!\n\n");
        return;
    }

    //buraya kadar o urunun satis islemi gerceklestirildi.
    //Simdi yeri dogru mu diye bakacagiz.

    //dogru ise cikarma
    if ((temp->prev->urun.satisMiktari >= temp->urun.satisMiktari) && (temp->next->urun.satisMiktari <= temp->urun.satisMiktari))
    {
        return;
    }

    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    //head ise headi cikardik.
    if(temp == head)
    {
        head = head->next;
    }

    //headden buyuk ise headin onune ekleyecegiz.
    if (temp->urun.satisMiktari > head->urun.satisMiktari)
    {
        Node* son = head->prev;
        temp->next = head;
        temp->prev = son;
        son->next = temp;
        head->prev = temp;

        head = temp;
        return;
    }
    //simdi dogru yere ekleyecegiz.
    Node* temp2 = head;

    while(temp2->next != head && temp2->next->urun.satisMiktari > temp->urun.satisMiktari)
    {
         temp2 = temp2->next;
    }
    temp->next = temp2->next;
    temp->prev = temp2;
    temp2->next->prev = temp;
    temp2->next = temp;

    return;
}

void stokGir()
{
    char urun_Ad[50];
    int stok_Mik;

    printf("------------------------------");
    printf("\nUrun adini giriniz: ");
    scanf("%s",&urun_Ad);
    printf("\nUrun stok miktarini giriniz: ");
    scanf("%d",&stok_Mik);
    printf("\n------------------------------\n\n");

    if(stok_Mik < 0)
    {
        printf("Negatif stok miktari giremezsiniz!");
        return;
    }

    Node* temp = head;

    while(temp->next != head && strcmp(temp->urun.urunAdi, urun_Ad) != 0)
    {
        temp = temp->next;
    }

    temp->urun.stokMiktari = stok_Mik;
}

int main()
{
    int secim;

    while(1)
    {
        printf("\n1-Bagli Listeyi Olustur\n");
        printf("2-Satis Gir\n");
        printf("3-Stok Gir\n");
        printf("4-Cikis\n");
        printf("\nBir secim yapiniz: ");
        scanf("%d",&secim);

        switch(secim)
        {
            case 1:
            {
                if(listeolustu != 0)
                {
                    printf("\nZaten olusturulmus listeniz var!\n");
                    ekranaYazdir();
                    break;
                }
                verileriOku("veri.txt"); // okuduktan sonra ebagli liste olusturmak icin parametre olarak verecek.
                ekranaYazdir();
                break;
            }
            case 2:
            {
                if(verilerOkundu != 1)
                {
                    printf("\nHenuz veriler okunmadi!\n");
                    break;
                }
                satisGir();
                ekranaYazdir();
                break;
            }
            case 3:
            {
                if(verilerOkundu != 1)
                {
                    printf("\nHenuz veriler okunmadi!\n");
                    break;
                }
                stokGir();
                ekranaYazdir();
                break;
            }
            case 4:
            {
                return 0;
            }
        }
    }

    return 0;
}










