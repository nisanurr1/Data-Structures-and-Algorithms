//23100011052 - Nisanur CAKIR

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
}Node;

//silindi mesaji vermek icin kontrol
int silindiMi = 0;


int yukseklik(Node *yeni)
{
    if(yeni == NULL)
    {
        return -1;
    }
    return yeni->height;
}

int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

int dengeHesapla(Node* n)
{
    if (n == NULL)
        return 0;
    return yukseklik(n->left) - yukseklik(n->right);
}

Node* rightRotate(Node* A)
{
    Node* B = A->left; //sol cocuk
    Node* C = B->right; //B nin sag alt agaci

    B->right = A; // b yukari cikacak
    A->left = C; // C de A nin soluna baglanacak

    //yine yukseklik guncellemesi (alttan uste dogru)
    A->height = max(yukseklik(A->left), yukseklik(A->right)) + 1;
    B->height = max(yukseklik(B->left), yukseklik(B->right)) + 1;

    return B;
}


//bunda da tersi kisimlar var.
Node* leftRotate(Node* A)
{
    Node* B = A->right;
    Node* C = B->left;

    B->left = A;
    A->right = C;

    A->height = max(yukseklik(A->left), yukseklik(A->right)) + 1;
    B->height = max(yukseklik(B->left), yukseklik(B->right)) + 1;

    return B;
}



Node *insert(Node *root, int sayi)
{

    if(root == NULL)
    {
        Node *yeni = (Node*)malloc(sizeof(Node));
        yeni->left = NULL;
        yeni->right = NULL;
        yeni->data = sayi;
        yeni->height = 0; //yaprak olarak eklenecek suan.

        return yeni;
    }

    else
    {
        //bos degilse sag sol kontrolu yap
        if(sayi < root->data) //sag koke eklenecek.
        {
            root->left = insert(root->left, sayi);
        }
        if(sayi >= root->data)
        {
            root->right = insert(root->right, sayi);
        }
    }
    //ekledikten sonra yukseklik guncellemesi ve balance kontrolu yapilacak.
    root->height = max(yukseklik(root->left), yukseklik(root->right)) + 1;

    //sonrasinda gerekiyorsa rotation islemi yapilacak. Bunun icin de dengeye yani balance'e bakacagiz.

    int balance = dengeHesapla(root);

    //denge uzerinden rotation islemleri yapilacak

    // LL
    if (balance > 1 && sayi < root->left->data)
        return rightRotate(root);

    // RR
    if (balance < -1 && sayi > root->right->data)
        return leftRotate(root);

    // LR
    if (balance > 1 && sayi > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (balance < -1 && sayi < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;

}

Node* maxValueNode(Node* node)
{
    Node* current = node;

    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

#define BOSLUK 6 //duzenli durmasi icin
void agacYazdir(Node *root, int bosluk)
{
    if (root == NULL)
        return;

    bosluk += BOSLUK;

    // once sag alt agac
    agacYazdir(root->right, bosluk);

    // mevcut dugum
    printf("\n");
    for (int i = BOSLUK; i < bosluk; i++)
        printf(" ");
    printf("%d ", root->data, root->height);
    //printf("%d (h=%d)", root->data, root->height); bu sekilde agirliklarini da gormus oluyoruz kontrol etmek icin eklemistim.

    // sonra sol alt agac
    agacYazdir(root->left, bosluk);
}


Node *deleteNode(Node *root, int sayi)
{
    if(root == NULL)
        return root;

    if(sayi < root->data)
    {
        root->left = deleteNode(root->left, sayi);
    }
    else if(sayi > root->data)
    {
        root->right = deleteNode(root->right, sayi);
    }
    else //silinecek sayinin oldugu dugum bulundu demek oluyor.
    {
        silindiMi = 1;
        // 0 veya 1 cocuk
        if (root->left == NULL || root->right == NULL)
        {
            Node* temp = root->left ? root->left : root->right;

            // cocuk yoksa
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp; // cocugu yukari al
            }


            free(temp);
        }
        else
        {
            // 2 cocuk var ise
            Node* temp = maxValueNode(root->left);
            root->data = temp->data;
            root->left = deleteNode(root->left, temp->data);
        }

    }

    if (root == NULL)
        return root;


    // height guncellenecek.
    root->height = max(yukseklik(root->left), yukseklik(root->right)) + 1;

    // balance kontrolu
    int balance = dengeHesapla(root);

    // LL
    if (balance > 1 && dengeHesapla(root->left) >= 0)
        return rightRotate(root);

    // LR
    if (balance > 1 && dengeHesapla(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && dengeHesapla(root->right) <= 0)
        return leftRotate(root);

    // RL
    if (balance < -1 && dengeHesapla(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

//cikis yapilacaksa da bellek temizlenmeli.
void agacFree(Node *root)
{
    if(root == NULL)
        return;

    agacFree(root->left);
    agacFree(root->right);
    free(root);
}

int main()
{
    Node *root = NULL;

    int sayi,secim;

    while(1)
    {
        printf("\n1-Ekle");
        printf("\n2-Sil");
        printf("\n3-Cikis");
        printf("\nSeciniz: ");
        scanf("%d",&secim);

        switch(secim)
        {
            case 1:
            {
                printf("\nEklemek istediginiz sayiyi giriniz: ");
                scanf("%d",&sayi);

                root = insert(root,sayi);

                printf("\n\nAVL Tree'nin 90 derece yatik sekilde gosterimi:");
                printf("\n----------------------------------------------------");
                agacYazdir(root, 0);
                printf("\n----------------------------------------------------");
                printf("\n");
                break;
            }
            case 2:
            {
                silindiMi = 0;

                printf("\nSilmek istediginiz sayiyi giriniz: ");
                scanf("%d",&sayi);

                root = deleteNode(root, sayi);
                if(silindiMi == 1)
                {
                    printf("\n%d sayisi AVL Tree'den silindi.",sayi);
                }

                else if(silindiMi == 0)
                {
                    printf("\n***Girdiginiz deger AVL Tree'de bulunamadi.***");
                }
                printf("\n\nAVL Tree'nin 90 derece yatik sekilde gosterimi:");
                printf("\n----------------------------------------------------");
                agacYazdir(root, 0);
                printf("\n----------------------------------------------------");
                printf("\n");
                break;
            }
            case 3:
            {
                printf("\nCikis yapiliyor...");
                agacFree(root);
                return 0;
            }
            default:
            {
                printf("\n***Yanlis secim yaptiniz!***\n");
                break;
            }
        }

    }

    return 0;
}
