#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERT 1
#define DISPLAY 2
#define TOTAL 3
#define SEARCH 4
#define UPDATE 5

// struct
typedef struct kost
{
    char nama[20];
    char alamat[30];
    char no_hp[15];
    int jumlah_kamar;
    char fasilitas[5][20];
    int id_kost;

} kost;

void insert();
void display();
void total();
void search();
void update();

int roomCode(int);
int upper = 100;
int lower = 1;

int main()
{

    char mulai = 0;
    do
    {
        system("clear");
        printf("======= MENU =======\n");
        printf("Daftarkan kost ... 1\n");
        printf("Tampilkan kost ... 2\n");
        printf("Jumlah kost ...... 3\n");
        printf("Telusuri kos ......4\n");
        printf("Ubah kost .........5\n");
        printf("KELUAR ............6\n");

        int pilihan;
        printf("\n\nMasukkan pilihan anda : ");
        scanf("%d", &pilihan);
        fflush(stdin);

        switch (pilihan)
        {
        case INSERT:
            insert();
            break;
        case DISPLAY:
            display();
            break;
        case TOTAL:
            total();
            break;
        case SEARCH:
            search();
            break;
        case UPDATE:
            update();
            break;
        default:
            printf("Pilihan anda tidak valid\n");
            break;
        }

        printf("Balik ke Menu? [1/0]");
        scanf("%d", &mulai);
    } while (mulai);
    printf("==== TERIMA KASIH ====\n\n");

    return 0;
}

void insert()
{
    system("clear");
    printf("====== MENAMBAH KOST ======\n\n");

    kost new_kost;
    fflush(stdin);
    printf("Nama :");
    scanf("%[^\n]", new_kost.nama);
    fflush(stdin);
    printf("alamat :");
    scanf("%[^\n]", new_kost.alamat);
    fflush(stdin);
    printf("Nomor HP :");
    scanf("%15s", &new_kost.no_hp);
    fflush(stdin);
    printf("Jumlah kamar :");
    scanf("%d", &new_kost.jumlah_kamar);
    fflush(stdin);
    printf("Fasilitas (5) :\n");
    for (int i = 0; i < 5; i++)
    {
        printf("Fasilitas %d :", i + 1);
        scanf("%[^\n]", &(new_kost.fasilitas[i]));
        fflush(stdin);
    }

    int id;
    id = (rand() % (upper - lower + 1) + lower);
    new_kost.id_kost = roomCode(id);

    system("clear");
    printf("Kost berhasil ditambahkan!!\n\n");

    printf("Nama kost    :%s\n", new_kost.nama);
    printf("alamat kost  :%s\n", new_kost.alamat);
    printf("No HP        :%s\n", new_kost.no_hp);
    printf("Jumlah kamar :%d\n", new_kost.jumlah_kamar);
    printf("Kode kost    :%d\n", new_kost.id_kost);
    printf("Fasilitas :\n");
    for (int i = 0; i < 5; i++)
    {
        printf("\t- %s\n", new_kost.fasilitas[i]);
    }

    FILE *fp = fopen("daftarKost.txt", "a");
    if (fp == NULL)
    {
        fprintf(stderr, "\nError opened file\n");
        exit(1);
    }
    fwrite(&new_kost, sizeof(kost), 1, fp);

    fclose(fp);
}

void display()
{
    FILE *fp;
    kost new_kost;

    fp = fopen("daftarKost.txt", "r");

    if (fp == NULL)
    {
        system("clear");
        printf("Mohon maaf, data tidak dapat diakses!\n");
        exit(1);
    }

    system("clear");
    printf("====== DAFTAR KOST =====\n\n");
    while (fread(&new_kost, sizeof(kost), 1, fp))
    {

        printf("Nama kost    :%s\n", new_kost.nama);
        printf("alamat kost  :%s\n", new_kost.alamat);
        printf("No HP        :%s\n", new_kost.no_hp);
        printf("Jumlah kamar :%d\n", new_kost.jumlah_kamar);
        printf("Kode kost    :%d\n", new_kost.id_kost);
        printf("Fasilitas :\n");
        for (int i = 0; i < 5; i++)
        {
            printf("\t- %s", new_kost.fasilitas[i]);
        }
        printf("\n======================\n");
    }
    fclose(fp);
}

// TODO : Room Code -> memberi kode unik ke setiap obejct lalu ngecek apakah ada yang sama

int roomCode(int num)
{
    int allocated = 0;

    FILE *fp = fopen("daftarKost.txt", "r");
    kost new_kost;
    while (fread(&new_kost, sizeof(kost), 1, fp))
    {
        if (new_kost.id_kost == num)
        {
            allocated = 1;
        }
    }

    if (allocated == 0)
        return num;
    else
        return roomCode((rand() % (upper - lower + 1) + lower));

    fclose(fp);
}

void total()
{
    FILE *fp = fopen("daftarKost.txt", "r");
    kost each_kost;
    fseek(fp, 0, SEEK_END);
    int n = ftell(fp) / sizeof(kost);
    printf("Banyak Kost yang terdaftar : %d\n\n", n);
    fclose(fp);
}

void search()
{
    int kode_input, found = 0;
    printf("Masukkan Kode kost : ");
    scanf("%d", &kode_input);
    FILE *fp;
    kost new_kost;

    fp = fopen("daftarKost.txt", "r");

    if (fp == NULL)
    {
        system("clear");
        printf("Mohon maaf, data tidak dapat diakses!\n");
        exit(1);
    }

    system("clear");
    printf("====== TELUSURI KOST =====\n\n");
    while (fread(&new_kost, sizeof(kost), 1, fp))
    {

        if (new_kost.id_kost == kode_input)
        {
            found = 1;
            printf("Nama kost    :%s\n", new_kost.nama);
            printf("alamat kost  :%s\n", new_kost.alamat);
            printf("No HP        :%s\n", new_kost.no_hp);
            printf("Jumlah kamar :%d\n", new_kost.jumlah_kamar);
            printf("Kode kost    :%d\n", new_kost.id_kost);
            printf("Fasilitas :\n");
            for (int i = 0; i < 5; i++)
            {
                printf("\t- %s", new_kost.fasilitas[i]);
            }
            printf("\n======================\n");
        }
    }
    if (found != 1)
    {
        printf("Mohon maaf, kost tersebut tidak ditemukan!\n");
    }
    fclose(fp);
}

void update()
{
    int kode_input, found = 0;
    printf("Masukkan Kode kost yang ingin diubah : ");
    scanf("%d", &kode_input);
    FILE *fp, *ftemp;
    kost new_kost;

    fp = fopen("daftarKost.txt", "r");
    ftemp = fopen("temp_kost.txt", "w");

    if (fp == NULL || ftemp == NULL)
    {
        system("clear");
        printf("Mohon maaf, data tidak dapat diakses!\n");
        exit(1);
    }

    system("clear");
    printf("====== UBAH KOST =====\n\n");
    while (fread(&new_kost, sizeof(kost), 1, fp))
    {

        if (new_kost.id_kost == kode_input)
        {
            found = 1;
            printf("Melakukan perubahan ...\n\n");
            fflush(stdin);
            printf("Nama :");
            scanf("%[^\n]", new_kost.nama);
            fflush(stdin);
            printf("alamat :");
            scanf("%[^\n]", new_kost.alamat);
            fflush(stdin);
            printf("Nomor HP :");
            scanf("%15s", &new_kost.no_hp);
            fflush(stdin);
            printf("Jumlah kamar :");
            scanf("%d", &new_kost.jumlah_kamar);
            fflush(stdin);
            printf("Fasilitas (5) :\n");
            for (int i = 0; i < 5; i++)
            {
                printf("Fasilitas %d :", i + 1);
                scanf("%[^\n]", &(new_kost.fasilitas[i]));
                fflush(stdin);
            }
            printf("\n======================\n");
        }

        fwrite(&new_kost, sizeof(kost), 1, ftemp);
    }

    fclose(fp);
    fclose(ftemp);

    if (found)
    {
        ftemp = fopen("temp_kost.txt", "r");
        fp = fopen("daftarKost.txt", "w");

        while (fread(&new_kost, sizeof(kost), 1, ftemp))
        {
            fwrite(&new_kost, sizeof(kost), 1, fp);
        }

        fclose(fp);
        fclose(ftemp);
    }
}

