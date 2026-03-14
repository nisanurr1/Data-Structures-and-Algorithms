#include <stdio.h>
#include <stdlib.h>


typedef struct row
{
    int index;
    char name[100];
    struct row *next;
} Row;

typedef struct table
{
    Row rows[16];   //row dizisi olusturduk.
} Table;

Table table;

void initialize_table()
{
    int i;

    for(i = 0; i < 16; i++)
    {
        table.rows[i].index = -1; //her bir index simdilik -1 olsun.
        sprintf(table.rows[i].name, "%s", "$$ BOS $$");
        table.rows[i].next = NULL;

    }
}


int RSHash(char *str, int uzunluk) //deterministiktir (aynı girdi → aynı çıktı)
{
    unsigned int b = 378551;
    unsigned int a = 63689;     // bu carpan kadar ilerleyecek.
    unsigned int hash = 0;

    for(int i = 0; i < uzunluk; i++)
    {
        hash = hash * a + str[i]; // her bir karakterin hash degeri cikartilacak. str[i] degeri aslinde o karakterin ASCII degerini aliyor.
        a = a*b;
    }

    //hoca alttaki ifadeyi kontrol amacli koymus.

    hash = hash & 0x7FFFFFFF; // bu ifade hash her adimda buyuyor dolayisiyla 32 biti asabilir.
    // 01111111 11111111 11111111 11111111
    //burada en soldaki bit tasma olurda 1 olursa sayi negatif anlamina gelir.
    //dolayisiyla hash bir de 16 ile mod alinirsa index negatif bir sayi cikacak.
    //negatif index istenmeyen bir durumdur "lojik AND" ile bunun onune geciyoruz.
    //amac isareti pozitife cevirmek.


    //hash degeri cok buyuk bir deger cikiyor her seferinde carpilarak eklenmis degerlerden olustugu icin.
    //deger bilerek buyuk istenir cunku;
    //benzer stringlerin hash'i uzak olsun
    //dolayisiyla cakisma ihtimali azaltilmis olunur.
    return hash % 16; // tablo boyutuna indirgemis olduk, yani tablodaki max indexin disina cikamaz ( 0 - 15 arasi)

}

void collusion(Row *row, Row *head) //headin, cakisan indexin bulundugu satirin(bagli listenin), basi oluyor
{
    Row *temp = head;

    while(head)
    {
        temp = head;
        head = head->next;
    }

    //sonu bulduk ve sona ekiyoruz yeni row'u
    temp->next = row;
    row->next = NULL;
}

void add_Rows(char *str)
{
    //ekleyecegimiz satir neresi olacak ona karar verecegiz. Bunun icin RSHash fonku gerekiyor.

    int hash_index = RSHash(str, strlen(str)); //hashlenen indexi aldik.

    //eger ki cakisma(collusion) yoksa
    if(table.rows[hash_index].index == -1)
    // hoca burada || strcmp(str, table.rows[hash_index].name) == 0 eklemis fakat
    //gerek yok sadece bos ise eklesin degilse zaten cakisma vardır bu satira girmez!
    {
        table.rows[hash_index].index = hash_index;
        // bu sekilde tasimak yanlis!! table.rows[hash_index].name = str;
        sprintf(table.rows[hash_index].name, "%s", str);
        return;
    }

    //eger ki cakisma var ise liste seklinde devam edecek.
    //cakisan yer: table.rows[hash_index]

    Row *row;
    row = (Row*)malloc(sizeof(Row));
    row->index = hash_index;
    sprintf(row->name, "%s", str);


    collusion(row, &table.rows[hash_index]); //cakistigi icin dugum haline getirdik.
    //dugum olusturdugumuz row ve tabloda cakistigi yeri collusion()'a gonderiyoruz.


}

int Find_row(char *aranan)
{
    int hash_index = RSHash(aranan, strlen(aranan));

    //oyle bir satir yok yani bos
    if(table.rows[hash_index].index == -1)
    {
        return -1;
    }

    //ilk satirda ise
    if(strcmp(table.rows[hash_index].name, aranan) == 0)
    {
        return table.rows[hash_index].index;
    }

    //collision var demektir o halde zinciri dolasacaksin.
    else
    {
        Row *temp = table.rows[hash_index].next;

        while(temp != NULL)
        {
            if(strcmp(temp->name, aranan) == 0)
            {
                return temp->index;
            }
            temp = temp->next;
        }
    }
    return -2; //zincirde de yok demektir.
}


int main()
{
    int i, index;

    char *names[16] = {"bir", "iki", "uc", "dort", "bes", "alti", "yedi", "sekiz",
    "dokuz", "on", "onbir", "oniki", "onuc", "ondort", "onbes", "onalti"};
    //tamamini yazmazsak segmentation fault aliriz burasi onemli
    //ya da daha kucuk degerler kullan: 4, 5 tane


    //ornek degerler.

    initialize_table(); //tablomuzu olusturmus olduk.

    //simdi sirayla rowslara ekleme yapacagiz.

    for(i = 0; i < 16; i++)
    {
        add_Rows(names[i]); //names icindekileri ekleyecegiz yani.
    }

    //ifadeler eklendi (cakisma durumunda da degerlendirildi ve ilgili satira Bagli liste olarak eklenmis oldu)

    char aranan[100];
    printf("\nArama yapilacak kelimeyi giriniz: ");
    scanf("%99s", &aranan);

    //arananin indexini bulmamiz lazim oncelikle.

    index = Find_row(aranan); //hangi indexte oldugu geri donecek.

    if(index != -1)
    {
        printf("\n\n%s kelimesinin bulundugu index: %d\n", aranan, index);
        return 0;
    }
    printf("\n\nindex bulunamadi!\n");


    return 0;
}











/*
//hashin icin tekrar kodu...


//TABLO İCİN VS STRUCTA IHTIYACIMIZ VAR
typedef struct row //her satirin isaretcisi , adi ve indexi bulunacak. index hashlanen kod olacak aslinda
{
    int index;
    char name[100];
    struct row *next;
}Row;

typedef struct table
{
    Row rows[16];
}Table;

Table table;

void tablo_olustur()
{
    int i = 0;

    for (i = 0; i < 16; i++)
    {
        table.rows[i].index = -1;
        sprintf(table.rows[i].name, "%s","bos");
        table.rows[i].next = NULL;
    }

}
int RSHash(char *str, int uzunluk)
{
    //gelen string hashlenecek simdi oan gore de index numarasi geriye donecek.

    unsigned int a = 63689;
    unsigned int b = 378551;
    int hash = 0;
    int i;

    for(i = 0; i < uzunluk; i++) //her harfinin ascii degeri kadar olacak.
    {
        hash = hash*a + str[i];
        a = a*b;
    }
    // cok buyuk degerler cikabilir dolayisiyla bunun onune gecmemiz lazim

    hash = hash & 0x7FFFFFFF; //and kapisi ile tasma engellendi.

    return hash % 16; //mod islemi de indexin dizi sinirindan tasmamasi icin
}

void collusion(Row *new_rowcuk, Row *start_row)
{
    Row *temp = start_row;

    while(start_row)
    {
        temp = start_row;
        start_row = start_row->next;
    }
    temp->next = new_rowcuk;
    new_rowcuk->next = NULL;
}

void add_rows(char *str)
{
    int hash_index;

    hash_index = RSHash(str, strlen(str));

    //bu indexte kimse yoksa stringi yerlestir

    if(table.rows[hash_index].index == -1)
    {
        table.rows[hash_index].index = hash_index;
        sprintf(table.rows[hash_index].name,"%s",str);
        //next yine null o yuzden guncellemedim.
    }

    //eger ki - 1 degil ise doludur demek oluyor yani collusion var demektir.
    //burada artik dugum olusturarak ekleme islemi yapacagiz.

    Row *new_rowcuk;
    new_rowcuk = (Row*)malloc(sizeof(Row));

    new_rowcuk->index = hash_index;
    sprintf(new_rowcuk->name,"%s", str);

    //kimden sonra konulacagina collusion karar veriyor artik
    collusion(new_rowcuk, &table.rows[hash_index]); // bulundugu yerin baslangic adresi gonderildi.

}

int Find_row(char *aranan)
{
    //oncelikle hash kodunu alacagiz
    int hash_index = RSHash(aranan, strlen(aranan));

    //aranan yok ise
    if(table.rows[hash_index].index == -1)
    {
        return -1; //aranan yok. eklenmemis ya da.
    }
    if(strcmp(table.rows[hash_index].name, aranan) == 0)
    {
        return table.rows[hash_index].index;
    }

    //yoksa ya da ilk satirda degilse ilgili satirda liste seklinde gidiyordur ->collusion vardir.
    else
    {
        Row *temp = table.rows[hash_index].next;

        while(temp != NULL)
        {
            if(strcmp(temp->name, aranan) == 0)
            {
                return temp->index;
            }
            temp = temp->next;
        }
    }
    return -2; //zincirde de yok demektir.

}

int main()
{
    char *names[16] = {"bir", "iki", "uc", "dort", "bes", "alti", "yedi", "sekiz",
    "dokuz", "on", "onbir", "oniki", "onuc", "ondort", "onbes", "onalti"};

    //bunlar iicn tablo olsuturmam  gerekiyor oncelikle

    tablo_olustur(); //tablomuz olusturuldu simdi names dizisindeki elemanlari bu tabloya hash koduna gore yerlestirecegiz.

    int i;
    for(i = 0; i < 16; i++)
    {
        add_rows(names[i]); //her bir karakteri add'e gonderiyoruz...
    }

    //artik find_rowu yazabiliriz. index bulacagiz.


    char aranan[100];
    printf("\nArama yapilacak kelimeyi giriniz: ");
    scanf("%99s", &aranan);

    //arananin indexini bulmamiz lazim oncelikle.

    int index = Find_row(aranan); //hangi indexte oldugu geri donecek.

    if(index != -1)
    {
        printf("\n\n%s kelimesinin bulundugu index: %d\n", aranan, index);
        return 0;
    }
    printf("\n\nindex bulunamadi!\n");

    return 0;
}
*/




