#include <stdio.h>
#include <stdlib.h>

typedef struct dugum
{
    int data;
    struct dugum *next;
} Node;

Node* Node_olustur(int sayi)
{
    //dugum olusturulacak.
    Node *yeni;
    yeni = (Node*)malloc(sizeof(Node));

    yeni->data = sayi;
    yeni->next = NULL;

    return yeni;
}


Node* bagli_listeye_sirali_ekle(Node* head, Node *yeniNode)
{
    Node *temp;

    if(head == NULL) //hic elemani yoksa
    {
        head = yeniNode;

        return yeniNode;
    }

    else if(yeniNode->data < head->data) //2 elemanli ise
    {
        yeniNode->next = head; //head'de bulunanlari bozmadan siraya ekle.
        head = yeniNode; //head artik yeniNode oldu.
        return yeniNode;
    }
    else
    {
        temp = head;
        while(temp->next != NULL && temp->next->data < yeniNode->data)
        {
            temp = temp->next;
        }//sartlar saglandiginda cikacak
        yeniNode->next = temp->next;
        temp->next = yeniNode;
    }

    return head;
}

void yazdir(Node *bagli_liste)
{
    Node *temp;

    temp = bagli_liste;

    while(temp != NULL)
    {
        printf("%d -> ",temp->data);
        temp = temp->next;
    }
    printf("NULL\n\n");
}

int main()
{
    int sayi;
    int liste_boyu;
    int i;

    Node *bagli_liste = NULL;
    Node *yeni_dugum;

    printf("\nListe boyutu giriniz: ");
    scanf("%d",&liste_boyu);


    for(i = 0; i < liste_boyu; i++)
    {
        printf("\n%d.sayiyi giriniz: ",i+1);
        scanf("%d",&sayi);

        yeni_dugum = Node_olustur(sayi);

        bagli_liste = bagli_listeye_sirali_ekle(bagli_liste, yeni_dugum);
    }

    yazdir(bagli_liste);

    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////



