#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

void sona_ekle(struct node *head, int veri)
{
    struct node *yeni;
    yeni = (struct node*)malloc(sizeof(struct node));

    yeni->data= veri;
    yeni->next=NULL;

    struct node *temp = head; //baslangictan itibaren kontrol edilecek.

    while(temp->next!= NULL)
    {
        temp = temp->next; //temp artýk son dugumu tutuyor demektir.

    }//boyle oldugu an sona gelmis demektir.
    //dolayisiyla gelinen son dugume yeninin adresini aktar.
    temp->next = yeni;
}

struct node* basa_ekle(struct node *head, int veri)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));

    temp->data = veri;
    temp->next = head;

    head = temp;
    return head;
}


void listele(struct node *head)
{
    struct node *temp; //bellekten yer ayýrmana gerek yok.
    temp = head;

    while(temp != NULL)    //temp->next != NULL dedigimde neden hata aliyorum?????
    {
        printf("\n%d",temp->data);
        temp = temp->next; //tempi guncellemeyi unutma
    }
}

void recursive_listele(struct node *head)
{
    if(head == NULL) //son dugume geldiginde cikis yap demek.
        return;      //bu olmazsa nerede duracagini bilemez ve fonksiyon sonsuz donguye girer.

    printf("\n%d",head->data);
    recursive_listele(head->next);
}
/*
void eleman_sayisi(struct node *head)
{
    struct node *temp;
    int sayac=0;

    temp = head;

    while(temp != NULL)
    {
        sayac++;
        temp=temp->next;
    }
    printf("\ntoplam eleman sayisi: %d",sayac);
}
*/
int eleman_sayisi(struct node *head)
{
    if(head == NULL)
    {
        return 0;
    }
    return eleman_sayisi(head->next) +1; //headden gectigi her bir sonraki icin returnu arttir.
}

int aranan_eleman(struct node *head, int aranan) //elemani ara, bul ve bastan kacinci sirada oldugunu yazdir.
{
    struct node *temp;
    temp = head;
    int sayac = 1; //ilk node'a 1 ile baslamasi gerekiyor.

    while(temp != NULL)
    {
        if(temp->data == aranan) //bulundu.
        {
            return sayac;
        }
        temp = temp->next;
        sayac++;
    }
}

struct node* bastan_sil(struct node *head)
{
    if(head == NULL)
    {
        printf("\n\nBastan silinecek eleman kalmadi!");
        return head;
    }

    struct node *temp;
    temp = head;

    head = head->next; //headin adresini temp ile silmeden once bir sonraki dugumu head ediyoruz, sonra tempteki headin adresini free ediyoruz
    /*struct node *temp;
      temp = head;
      head=head->next;
      free(temp); boylece ilk node silinmis oluyor.
    */

    free(temp);
    printf("\n\nSilme islemi tamamlandi!");
    return head;  //head return edilerek guncellenmis oluyor.
}

struct node *ortadan_sil(struct node *head, int silinecek_sayi)
{
    struct node *temp;
    temp = head;      //Burada tempe atama yapmayi unutmusum, dikkat etmelisin.

    while(temp != NULL && temp->next->data != silinecek_sayi)
    {
        if(temp->next->next == NULL)
        {
            printf("istediginiz veri bulunmamaktadir!");
            return head; //ayni headi geri donduruyor.
        }
        temp = temp->next; //tempi bir sonraki asamayi kontrol etmesi icin guncelle.
    }
    struct node *temp2;
    temp2 = temp->next;
    temp->next = temp2->next; //burayı temp->next->next diye de yazabilirisin(sag tarafi)
    free(temp2);

    printf("\n\nİstediginiz veri silinmistir!");
    return head;
}

struct node *ortaya_ekle(struct node *head, int eklenecek_sayi, int sayi_konumu)
{
    struct node *yeni;
    yeni = (struct node*)malloc(sizeof(struct node));

    yeni->data = eklenecek_sayi;
    yeni->next = NULL;

    if(head == NULL)
    {
        free(yeni);
        return head;
    }
    //nexti icin bir sonrakini bir onceki araciligi ile bulacagiz.

    struct node *temp;
    temp = head;

    while(temp->next != NULL && temp->data != sayi_konumu)
    {
        temp = temp->next; //bir oncekini bulana kadar devam ediyor.
    }
    if(temp == NULL)
    {
        free(yeni);
        return head;
    }
    yeni->next = temp->next; //tempimin isaret ettigi yeri artik yeni isaret edecek.
    //yani temp de artik yeniyi isaret etmis olacak onu da alt satirda guncelliyoruz.
    temp->next = yeni;


    printf("\n%d sayisi %d sayisinin sonrasina eklendi!\n",eklenecek_sayi, sayi_konumu);

    return head;
}

int main()
{
    struct node *head;
    head = (struct node*)malloc(sizeof(struct node));
    head->data = 5;
    head->next = NULL;

    int secim;

    while(1)
    {
        printf("\n\nSona eklemek(1)\nBasa eklemek(2)\nRecursive listele(3)\nEleman sayisini goster(4)\nSira bul(5)\nBastan sil(6)\nOrtadan silme(7)\nOrtaya eklemek(8)\n\nSeciniz: ");
        scanf("%d",&secim);
        switch(secim)
        {
            case 1:
            {
                int veri;
                printf("\nVeri giriniz: ");
                scanf("%d",&veri);

                sona_ekle(head, veri);
                listele(head);
                break;
            }
            case 2:
            {
                int veri;
                printf("\nVeri giriniz: ");
                scanf("%d",&veri);

                head = basa_ekle(head, veri);
                listele(head);
                break;
            }
            case 3:
            {
                recursive_listele(head);
                break;
            }
            case 4:
            {
                int sayac = eleman_sayisi(head);
                printf("\neleman sayisi (recursive ile): %d\n",sayac);
                break;
            }
            case 5:
            {
                int aranan,sira = 0;
                printf("aradiginiz sayiyi giriniz: ");
                scanf("%d",&aranan);

                sira = aranan_eleman(head, aranan);

                if(sira < 0 || sira != NULL)
                {
                    printf("\n\n%d elemaninin sirasi -> %d",aranan, sira);
                }
                else
                {
                    printf("\n\nAradiginiz sayi bulunamamistir!\n");
                }
                break;

            }
            case 6:
            {
                head = bastan_sil(head);
                listele(head);
                break;
            }
            case 7:
            {
                int sayi;
                printf("Silmek istediginiz sayiyi giriniz: ");
                scanf("%d",&sayi);

                head = ortadan_sil(head, sayi);
                listele(head);
                break;
            }
            case 8:
            {
                int sayi, sayi_konumu;
                printf("Eklemek istediginiz sayiyi giriniz: ");
                scanf("%d",&sayi);

                printf("Hangi sayidan sonra eklemek istersiniz giriniz: ");
                scanf("%d",&sayi_konumu);

                head = ortaya_ekle(head, sayi, sayi_konumu);
                listele(head);
                break;
            }
        }

    }

    return 0;
}
