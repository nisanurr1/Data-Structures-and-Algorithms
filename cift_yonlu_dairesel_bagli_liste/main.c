#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;

}Node;

Node *head = NULL;

void ekle(int sayi)
{
    Node* yeni = (Node*)malloc(sizeof(Node));
    yeni->data = sayi;

    if(head == NULL)
    {
        head = yeni;
        head->prev = head;
        head->next = head;
        return;
    }


    if(sayi < head->data) //kücükse basa gecsin.
    {
        yeni->next = head;
        yeni->prev = head->prev; //eskiden bastaki elemanin previ ne ise onu gostersin.

        //simdi headin baglantilarini guncelleyelim.
        head->prev->next = yeni;
        head->prev = yeni;

        head = yeni; //artik head yeni gelen dugum oldu.
        return;
    }
    Node* temp = head;

    while(temp->next != head && temp->next->data < sayi) //head olana ladar yani dgumun basina gidene kadar cano.
    {
        temp = temp->next;
    }

    yeni->next = temp->next;
    yeni->prev = temp;
    temp->next->prev = yeni;
    temp->next = yeni;
    return;
}

void Yazdir()
{
    Node* temp = head;
    if(head == NULL) return;

    while(1)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
        if(temp == head) break;
    }

}




int main()
{
    int sayi;
    while(1)
    {
        printf("\n\nBir sayi giriniz(cikis =1): ");
        scanf("%d",&sayi);
        ekle(sayi);

        Yazdir();

        if(sayi == 1) return 0;
    }

    return 0;
}
