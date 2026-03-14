#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//23100011052 - Nisanur Cakir

typedef struct Node
{
    int data;
    struct Node *next;
} Node;


Node* node_olustur(int sayi)
{
    Node *node = (Node*)malloc(sizeof(Node));

    node->data = sayi;
    node->next = NULL;

    return node;
}


void adresListele(Node *bas)
{
    Node *temp = bas;

    //printf("%p -> ", (void*)temp);

    while(temp != NULL)
    {
        printf("%p -> ", (void*)temp);
        temp = temp->next;
    }
    printf("NULL\n");
}


void nodeListele(Node *bas) // burada ilk adreslerini de listele ki baslangic gozuksun.
{
    Node *temp = bas;

    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Satırdaki sayıları virgülle ayırıp listeye ekleyecegiz
Node* satirdan_liste_olustur(char *satir)
{
    Node *head = NULL;
    Node *son = NULL;

    char *token = strtok(satir, ",");  // virgule gore ayirdik

    while (token != NULL) //dizi yerine pointer kullandim.
    {
        int sayi = atoi(token);         // stringi sayiya cevirdik.
        Node *yeni = node_olustur(sayi); // nodeumu olusturdum.

        if (head == NULL) //basta eleman yoksa basa ekledim
        {
            head = yeni;
            son = yeni;
        }
        else //varsa da en son dugum hangisi ise onun nextine ekledim.
        {
            son->next = yeni;
            son = yeni;
        }

        token = strtok(NULL, ",");
    }

    return head;
}


Node* bagli_liste1_ekle(Node* head, Node *yeniNode) //yeniNode, liste1 icin yeni oldugu icin.
{
    Node *temp;
    temp = head;

    if (yeniNode->data < head->data)
    {
        yeniNode->next = head; //basta artik datanin kucuk oldugu node var(yeniNode).
        return yeniNode;
    }

    while(temp->next != NULL && temp->next->data < yeniNode->data) //araya ya da sona eklemek icin
    {
        temp = temp->next;
    }//sartlar saglandiginda cikacak

    yeniNode->next = temp->next;
    temp->next = yeniNode;

    return head;
}


Node* listeleri_birlestir(Node* liste1, Node* liste2)
{
    // Siralama kismi (adres degistirerek)
    Node *head = liste1;
    Node *temp;
    Node *onceki;
    int degisti = 1;   // en az 1 kez donguye girmesi icin

    while (degisti)
    {
        degisti = 0;
        temp = head;
        onceki = NULL;

        while (temp != NULL && temp->next != NULL)
        {
            if (temp->data > temp->next->data)
            {
                Node *gecici = temp->next;
                temp->next = gecici->next;
                gecici->next = temp;

                if (onceki == NULL) //onceki demek temp demek eger temp 2.eleman ise onceki->next = temp olur
                {
                    head = gecici; // bas dugum degisti burada
                }
                else
                {
                    onceki->next = gecici;
                }

                onceki = gecici;
                degisti = 1;
            }
            else
            {
                onceki = temp;
                temp = temp->next; //sayiyi surekli bir sonraki ile kiyasliyoruz.
            }
        }
    }

    //buraya kadar liste1'i siralamis olduk.

    Node *temp2 = liste2;    // 2 -> 36 -> 49 -> 9 -> 81 -> NULL
    while(temp2 != NULL)
    {
        Node *sonraki = temp2->next;   // sonraki dugumu kaydet
        temp2->next = NULL;            // temp2 yi kopar
        head = bagli_liste1_ekle(head, temp2);  //head liste1 i tutyordu ve siralanmisti. Sonradan gelenleri ekstra bir fonksiyonla ekledim.
        temp2 = sonraki;               // sonraki nodedan devam edecek
    }

    return head; // yeni head döndürülüyor
}

int main()
{
    Node *liste1;
    Node *liste2;

    int secim;

    while(1)
    {
        printf("\n");
        printf("1-Dosyayi oku\n");
        printf("2-Sirala ve birlestir\n");
        printf("3-Cikis\n");
        printf("Bir secenek giriniz: ");
        scanf("%d",&secim);
        printf("\n");

            switch(secim)
            {
                case 1:
                {
                    FILE *dosya = fopen("veri.txt", "r");

                    if (dosya == NULL)
                    {
                        printf("Dosya açılamadı!\n");
                        return 1;
                    }

                    char satir1[100], satir2[100];

                    fgets(satir1, sizeof(satir1), dosya); //2.kez devam cagirdigimda kaldigi yerden okumaya devam edecek.
                    fgets(satir2, sizeof(satir2), dosya); // burada\n de kaldi ve devam etti -> satir sonuna geldi ve okumayi bitirdi.

                    fclose(dosya);

                    satir1[strcspn(satir1, "\n")] = 0; //bu fonksiyonda sonradan sorun cikmamasi icin strcspn kullandım dolayisiyla \n in bulundugu indisin yerine 0 koyacak ve satir sorunsuz olacak.
                    satir2[strcspn(satir2, "\n")] = 0;

                    liste1 = satirdan_liste_olustur(satir1);
                    liste2 = satirdan_liste_olustur(satir2);

                    printf("___________________________________");

                    printf("\n\n1. bagli liste:\n");
                    nodeListele(liste1);

                    printf("2. bagli liste:\n");
                    nodeListele(liste2);

                    printf("___________________________________\n");

                    //once ilk adresleri listele
                    printf("\n__________________________________________________________________________________________________________\n");
                    printf("1.bagli liste adresleri:\n");
                    adresListele(liste1);

                    printf("\n2.bagli liste adresleri:\n");
                    adresListele(liste2);
                    printf("__________________________________________________________________________________________________________\n\n");

                    break;
                }

                case 2:
                {
                    Node *birlesik_liste = listeleri_birlestir(liste1, liste2);
                    nodeListele(birlesik_liste);
                    adresListele(birlesik_liste); //listeledikten sonra adresler gosterilecek.
                    break;
                }
                case 3:
                {
                    return 0;
                }
            }
    }

    return 0;
}
