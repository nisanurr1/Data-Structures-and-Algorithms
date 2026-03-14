#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//23100011052 - Nisanur Cakir

typedef struct kisi
{
    char ad[30];
    char soyad[30];
    char tel[15];
    struct kisi *next;
} Kisi_bilgisi;

Kisi_bilgisi *head = NULL;

Kisi_bilgisi* yeniKisiOlustur(char *ad, char *soyad, char *tel)
{
    Kisi_bilgisi *yeni = (Kisi_bilgisi*)malloc(sizeof(Kisi_bilgisi));
    strcpy(yeni->ad, ad);
    strcpy(yeni->soyad, soyad);
    strcpy(yeni->tel, tel);
    yeni->next = NULL;

    return yeni;
}

int VarMi(char *tel)
{
    if(head == NULL)
    {
        return 0;
    }
    Kisi_bilgisi *temp = head;

    while(temp->next != head)
    {
        if (strcmp(temp->tel, tel) == 0) //gelen tel no herhangi biri ile ayni mi diye kontrol ediyoruz. Ayni ise 0 gelecek.
        {
            return 1;
        }
        temp = temp->next;
    }
    if(strcmp(temp->tel, tel) == 0) //son dugumu atlamasin diye ekledim.
    {
        return 1;
    }
    return 0;
}

//dairesel liste olarak ekliyoruz.
void listeyeEkle(char *ad, char *soyad, char *tel)
{
    if(VarMi(tel)) // ayni numara zaten var ise ekleme
        return; //var ise cik.

    Kisi_bilgisi *yeni = yeniKisiOlustur(ad,soyad,tel);

    if(head == NULL) // bos ise yeni ile doldur.
    {
        head = yeni;
        head->next = head;
        return;
    }

    //bos degil ise de basi kontrol et.
    if(strcmp(yeni->ad, head->ad) < 0 || (strcmp(yeni->ad, head->ad) == 0 && strcmp(yeni->soyad, head->soyad) < 0))
    {
        Kisi_bilgisi* temp = head;

        while(temp->next != head)
        {
            temp = temp->next;
        }

        temp->next = yeni;
        yeni->next = head;
        head = yeni;

        return;
    }

    //orta ya da sona bak.
    Kisi_bilgisi* temp = head;

    while(temp->next != head && (strcmp(temp->next->ad, yeni->ad) < 0 || (strcmp(temp->next->ad, yeni->ad) == 0 && strcmp(temp->next->soyad, yeni->soyad) < 0)))
    {
        temp = temp->next;
    }
    yeni->next = temp->next;
    temp->next = yeni;

}

// Dosyadan tum verileri oku
void verileriAl()
{
    FILE *veri = fopen("Veri.txt", "r");
    if (veri == NULL)
    {
        printf("Veri.txt bulunamadi!\n");
        return;
    }

    char icerik[1000];

    fread(icerik, sizeof(char), 999, veri);
    fclose(veri);
    icerik[strcspn(icerik, "\n")] = '\0';

    char *bas = icerik;
    while ((bas = strchr(bas, '{')) != NULL)
    {
        char *son = strchr(bas, '}');
        if (son == NULL) break;

        char kayit[100];
        strncpy(kayit, bas + 1, son - bas - 1);
        kayit[son - bas - 1] = '\0';

        char ad[30], soyad[30], tel[20];
        sscanf(kayit, "%[^,],%[^,],%s", ad, soyad, tel);

        listeyeEkle(ad, soyad, tel);   //her ayiklanan ifadeyi listeye ekliyoruz.

        bas = son + 1;
    }
    printf("\nDosya okundu...\n");
}

void listeyiTersCevir()
{
    if(head == NULL || head->next == head)
    {
        return;
    }

    Kisi_bilgisi* onceki = NULL;
    Kisi_bilgisi* sonraki = NULL;
    Kisi_bilgisi* suanki = head;
    Kisi_bilgisi* ilk = head;   //dairesel listeyi kapatmak icin kullanacagim.

    while(1)
    {
        sonraki = suanki->next;
        suanki->next = onceki;
        onceki = suanki;
        suanki = sonraki;

        if(suanki == head)
        {
            break; //basa gelince duracak cunku cevrilmis olacak.
        }
    }
    ilk->next = onceki; //ilk artik son olacak, son dugum bastaki dugumu gosterecek boylece donguyu kuracagiz.
    head = onceki; //artik yeni head onceki olacak.

    return;
}

// Listeyi yazdir
void listeyiYazdir()
{
    if (head == NULL)
    {
        printf("Liste bos!\n");
        return;
    }

    Kisi_bilgisi *temp = head;
    printf("\n--- Kayitli Kisiler ---\n");

    while(temp->next != head)
    {
        printf("%s %s - %s\n", temp->ad, temp->soyad, temp->tel);
        temp = temp->next;
    }
    printf("%s %s - %s\n", temp->ad, temp->soyad, temp->tel);
}

void adresYazdir()
{
    if(head == NULL)
    {
        return;
    }
    Kisi_bilgisi* temp = head;
    printf("\n\n--- Adresler ---\n");

    while(temp->next != head)
    {
        printf("%p -> ",(void*)temp);
        temp = temp->next;
    }
    printf("%p \n",(void*)temp);
}

int main()
{
    int secim;
    while(1)
    {
        printf("\n--- MENU ---\n");
        printf("1- Verileri Al ve Listeye Ekle\n");
        printf("2- Listeyi Ters Cevir\n");
        printf("0- Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        switch (secim)
        {
            case 1:
            {
                verileriAl();
                listeyiYazdir();
                adresYazdir();
                break;
            }

            case 2:
            {
                listeyiTersCevir();
                listeyiYazdir();
                adresYazdir();
                break;
            }

            case 0:
            {
                printf("Program sonlandirildi.\n");
                return 0;
            }
        }
    }

    return 0;
}
