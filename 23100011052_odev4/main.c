//23100011052 - Nisanur Cakir

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOYUT 100


typedef struct yiginList
{
    char kelime[BOYUT];
    struct yiginList *next;
    islemTipi tip; // ekleme mi silme mi
} yiginList;

typedef enum { ekleme, silme } islemTipi;

// Gelen listenin sonuna ekleme
yiginList* append(yiginList *appendEdilecekList, const char *kelime, islemTipi tip)
{
    yiginList *yeni = malloc(sizeof(yiginList));
    strcpy(yeni->kelime, kelime);
    yeni->next = NULL;  //tek yonlu liste kullanmayi tercih ettim aslinda dizi de kullanabilirdim.
    yeni->tip = tip;

    if (appendEdilecekList == NULL)
    {
        appendEdilecekList = yeni;
        return appendEdilecekList;
    }

    yiginList *temp = appendEdilecekList;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = yeni;

    return appendEdilecekList;
}


// Listenin sonundan silmek icin
yiginList* pop(yiginList **gelenList)
{
    if (*gelenList == NULL)
    {
        return NULL;
    }
    yiginList *temp = *gelenList;
    yiginList *onceki = NULL;

    while (temp->next != NULL)
    {
        onceki = temp;
        temp = temp->next;
    }

    if (onceki == NULL)
    {
        *gelenList = NULL;
    }
    else
    {
        onceki->next = NULL;
    }
    return temp; // free etmeyecegim(yani sadece char tipindeki kelimesini almayacagim burada, isimize gelmez)
    // cunku islem tipini belirlemem icin nodeun kendisini almam gerekiyor.
}

// Listeyi yazdirmak icin
void printList(yiginList *head)
{
    if (head == NULL)
    {
        printf("Liste bos!\n");
        return;
    }
    while (head != NULL)
    {
        printf("%s ", head->kelime);
        head = head->next;
    }
    printf("\n");
}

// Ozellikle redo kullanimi icin listeyi temizleme + islemler bittiginde bellek temizleme
void temizle(yiginList **headPtr)
{
    yiginList *temp;
    while (*headPtr != NULL)
    {
        temp = *headPtr;
        *headPtr = (*headPtr)->next;
        free(temp);
    }
}

int main()
{
    yiginList *ana_head = NULL;
    yiginList *undoList = NULL;
    yiginList *redoList = NULL;
    int secim;
    char kelime[BOYUT];

    while(1)
    {
        // Hocam burada case olarak eklendiginde anlik olarak islemleri gormek ekstra 1 secim gerektiriyordu, bu sekilde kullanisli oldugunu dusundum.
        printf("\nANLIK METIN: ");
        printList(ana_head);
        printf("\n1- Ekle\n2- Sil (delete)\n3- Undo (Geri Al)\n4- Redo (Yinele)\n5- Cikis\nSecim yapiniz: ");

        while (getchar() != '\n'); // \n temizlemek icin

        switch (secim)
        {
            case 1:  //ekleme kismi
            {
                printf("Kelime gir: ");
                scanf("%s", kelime);

                ana_head = append(ana_head, kelime, ekleme);
                undoList = append(undoList, kelime, ekleme);
                temizle(&redoList); //redonun yeni islem icin sifirlanmasi gerekir. Eski kelimenin anlamsiz yere gelmesini istemiyorum.
                break;
            }

            case 2: // silme kismi
            {
                yiginList *silinen = pop(&ana_head);
                if (!silinen)
                {
                    printf("Silinecek eleman yok.\n");
                }
                else
                {
                    undoList = append(undoList, silinen->kelime, silme);
                    temizle(&redoList);
                    //kendi kontrolum icin
                    //printf("'%s' silindi ve undo icin saklandi.\n", silinen->kelime);
                    free(silinen);
                }
                break;
            }

            case 3: //undo kismi (burada bir karisiklik yasadim enum ile cozulebildigini fark ettim.)
                //sildigim islemi geri al dedigimde ana_headden geri alma islemi yapiyordu, birnevi kontrol eklemis oldum.
            {
                yiginList *sonIslem = pop(&undoList);
                if (!sonIslem)
                {
                    printf("Undo yapilacak islem yok.\n");
                }
                else
                {
                    if (sonIslem->tip == ekleme)
                    {
                        yiginList *sil = pop(&ana_head); // ana listeden eklemeyi sil
                        redoList = append(redoList, sonIslem->kelime, ekleme);
                        if(sil) free(sil);
                    }
                    else
                    { // silme
                        ana_head = append(ana_head, sonIslem->kelime, ekleme);
                        redoList = append(redoList, sonIslem->kelime, silme);
                    }
                    //kendi kontrolum icin
                    //printf("Undo yapildi: '%s'\n", sonIslem->kelime);
                    free(sonIslem);
                }
                break;
            }

            case 4:
            { // Redo
                yiginList *redoIslem = pop(&redoList);
                if (!redoIslem)
                {
                    printf("Redo yapilacak islem yok.\n");
                }
                else
                {
                    if (redoIslem->tip == ekleme)
                    {
                        ana_head = append(ana_head, redoIslem->kelime, ekleme);
                        undoList = append(undoList, redoIslem->kelime, ekleme);
                    }
                    else
                    { // silme
                        yiginList *sil = pop(&ana_head);
                        undoList = append(undoList, redoIslem->kelime, silme);
                        if(sil) free(sil);
                    }
                    //kendi kontrolum icin
                    //printf("Redo yapildi: '%s'\n", redoIslem->kelime);
                    free(redoIslem);
                }
                break;
            }

            case 5:
            {
                printf("Programdan cikiliyor.\n");
                temizle(&ana_head);
                temizle(&undoList);
                temizle(&redoList);
                exit(0);
            }

            /*   // yine de belirtmis olayim.
            case 6:
            {
                printf("\nANLIK METIN: ");
                printList(ana_head);
            }
            */

            default:
                printf("Gecersiz secenek.\n");
        }
    }
    return 0;
}


