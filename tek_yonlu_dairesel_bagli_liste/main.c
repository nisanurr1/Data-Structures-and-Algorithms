#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    int data;
    struct Node *next;
} Node;
/*
Node* dugum_olustur(int sayi)
{
    Node* yeni;
    yeni = (Node*)malloc(sizeof(Node));
    yeni->data= sayi
}
*/
Node* Ekle(struct Node* head, int sayi)
{
    //dugum bos mu
    if(head == NULL)
    {
        head = (Node*)malloc(sizeof(Node));

        head->data = sayi;
        head->next = head; //kendisini isaret etsin.

        return head;
    }
    if(head->data > sayi)//gelen sayiyi basa eklemek icin (kucukten buyuge)
    {
        Node* temp = (Node*)malloc(sizeof(Node));

        temp->data = sayi;
        temp->next = head; //artik temp head oldu birnevi one gecti

        Node* iter = head; //iter butun dugumlerin basini tutsun

        while(iter->next != head) //basa kadar git
        {
            iter = iter->next;
        }
        iter->next = temp;

        return temp;
    }

    //araya eklemek icin ise
    else
    {
        Node* temp = (Node*)malloc(sizeof(Node));

        temp->data = sayi; //peki nexti kim olacak hemen bakalim

        Node* iter = head;
        while(iter->next != head && iter->next->data < sayi)
        {
            iter = iter->next;
        }
        temp->next = iter->next;
        iter->next = temp;

        return head; //baslangic dugumu degismedigi icin head doner.
    }
}

Node* Sil(Node* head, int sayi)
{
    //sayiyi bulmak icin gez.
    if(head == NULL)
    {
        return head;
    }

    if(head->next == head && head->data == sayi) // kendisi ise direkt NULLa cevir
    {
        return NULL;
    }
    //aradan silinecek ise

    Node* iter = head;

    while(iter->next != head) //bastan sona git. Aranan ortada bir yerde ise.
    {
        if(iter->next->data == sayi)
        {
            Node* temp;
            temp = iter->next;
            iter->next = temp->next;
            free(temp);

            return head; //baslangicta bir sey degismedi
        }
        iter = iter->next;
    }

    if(head->data == sayi)
    {
        while(iter->next != head) //butun dugumleri gez.
        {
            iter = iter->next;
        }
        iter->next = head->next;

        return iter->next;
    }
}

void Listele(struct Node* head)
{
    Node* iter = head;

    while(iter->next != head)
    {
        printf("%d -> ",iter->data);
        iter = iter->next;
    }
    printf("%d",iter->data);
}


int main()
{
    int secim;
    int sayi;



    Node *head = NULL;

    while(1)
    {
        printf("\n1-Ekle\n");
        printf("2-Sil\nSeciniz: ");
        scanf("%d",&secim);

        switch(secim)
        {
            case 1:
            {
                printf("\n\nBir sayi giriniz: ");
                printf("\n");
                scanf("%d",&sayi);
                head = Ekle(head, sayi);
                Listele(head);
                break;

            }
            case 2:
            {
                printf("\n\nSilmek istediginiz sayiyi giriniz: ");
                printf("\n");
                scanf("%d",&sayi);
                head = Sil(head, sayi);
                Listele(head);
                break;
            }
        }
    }

    return 0;
}
