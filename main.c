#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
typedef struct
{
    int id;
    int pin;
    char isim[50];
    float bakiye;
} Hesap;
const char *dosya = "bank_data.dat";
int kGiris();
void KMenu(int id);
void bakiyeGuncelle(int id, float miktar);
void bakiyeKontrol(int id);
void hesapOlustur();
int idUret();
int idVarmi(int testid);

int kGiris()
{
    int id, pin, bulundu = 0;
    Hesap hsp;
    FILE *file = fopen(dosya, "rb");

    if (file == NULL)
    {
        printf("\nSistemde kayitli hesap bulunamadi!\n");
        getch();
        return -1;
    }

    printf("\n*** GUVENLI GIRIS ***\n");
    printf("KART NO (Hesap ID):\n ");
    scanf("%d", &id);
    printf("Sifreniz:\n ");
    scanf("%d", &pin);

    while (fread(&hsp, sizeof(Hesap), 1, file))
    {
        if (hsp.id == id && hsp.pin == pin)
        {
            bulundu = 1;
            printf("\nHosgeldin Sayin %s!\n", hsp.isim);
            break;
        }
    }
    fclose(file);

    if (bulundu)
    {
        printf("Giris basarili. Menuye yonlendiriliyorsunuz...\n");
        sleep(3);
        return id;
    }
    else
    {
        printf("\nHATA: Yanlis ID veya PIN kodu!\n");
        getch();
        return -1;
    }
}

void KMenu(int id)
{
    int secim;
    float miktar;
    do
    {
        system("cls");
        printf("\n*** ISLEM MENUSU ***\n");
        printf("1--> Bakiye Sorgula\n");
        printf("2--> Para Yatir\n");
        printf("3--> Para Cek\n");
        printf("0--> Kart Iade (Cikis)\n");
        printf("\nLUTFEN YAPACAGINIZ ISLEMI SECINIZ: ");
        scanf("%d", &secim);

        switch (secim)
        {
        case 1:
            bakiyeKontrol(id);
            break;
        case 2:
            printf("Yatirilacak Miktar: ");
            scanf("%f", &miktar);
            bakiyeGuncelle(id, miktar);
            break;
        case 3:
            printf("Cekilecek Miktar: ");
            scanf("%f", &miktar);
            bakiyeGuncelle(id, -miktar);
            break;
        case 0:
            printf("\nKartiniz iade ediliyor...\n");
            break;
        default:
            printf("\nGecersiz islem!\n");
            break;
        }
        if (secim != 0)
        {
            printf("\nDevam etmek icin herhangi bir tusa basin...");
            getch();
        }

    } while (secim != 0);
}

void bakiyeGuncelle(int id, float miktar)
{
    Hesap hsp;
    FILE *file = fopen(dosya, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int basari = 0;

    if (!file || !temp)
    {
        printf("\nDosya erisim hatasi!\n");
        return;
    }

    while (fread(&hsp, sizeof(Hesap), 1, file))
    {
        if (hsp.id == id)
        {
            if (miktar < 0 && hsp.bakiye < -miktar)
            {
                printf("\nHATA: Yetersiz bakiye!\n Mevcut bakiye: %.2f TL\n", hsp.bakiye);
            }
            else
            {
                hsp.bakiye += miktar;
                printf("\nIslem basarili. Yeni bakiye: %.2f TL\n", hsp.bakiye);
                basari = 1;
            }
        }
        fwrite(&hsp, sizeof(Hesap), 1, temp);
    }
    fclose(file);
    fclose(temp);

    if (basari)
    {
        remove(dosya);
        rename("temp.dat", dosya);
    }
    else
    {
        remove("temp.dat");
    }
}

void bakiyeKontrol(int id)
{
    Hesap hsp;
    FILE *file = fopen(dosya, "rb");

    if (!file)
        return;

    while (fread(&hsp, sizeof(Hesap), 1, file))
    {
        if (hsp.id == id)
        {
            printf("\n*** HESAP BILGISI ***\n");
            printf("Musteri: %s\n", hsp.isim);
            printf("Bakiye: %.2f TL\n", hsp.bakiye);
            break;
        }
    }
    fclose(file);
}

void hesapOlustur()
{
    Hesap hsp;
    FILE *file = fopen(dosya, "ab");

    if (!file)
    {
        printf("Dosya acilamadi!\n");
        return;
    }

    printf("\n*** YENI MUSTERI KAYDI ***\n");
    hsp.id = idUret();
    printf("Isim (Bosluksuz): ");
    scanf("%s", hsp.isim);
    printf("4 Haneli PIN Giriniz: ");
    scanf("%d", &hsp.pin);

    hsp.bakiye = 0.0;

    fwrite(&hsp, sizeof(Hesap), 1, file);
    fclose(file);
    system("cls");
    printf("\n\nBilgileriniz\n");
    printf("Isim: %s\n", hsp.isim);
    printf("Sifre: %d\n", hsp.pin);
    printf("Kart No & Hesap ID (BU KISMI BILMEDEN GIRIS YAPAMAZSIN!!!)-->  %d\n", hsp.id);
    printf("Bakiye: %.2f\n", hsp.bakiye);
    printf("\nHesabiniz basariyla olusturuldu! Giris yapabilirsiniz.\n");
    getch();
}
int idUret()
{
    int yeniId;
    do
    {
        yeniId = (rand() % 90000) + 10000;
    } while (idVarmi(yeniId));

    return yeniId;
}
int idVarmi(int testid)
{
    Hesap hsp;
    FILE *file = fopen(dosya, "rb");
    if (file == NULL)
    {
        return 0;
    }
    while (fread(&hsp, sizeof(Hesap), 1, file))
    {
        if (hsp.id == testid)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
int main()
{
    srand(time(NULL));
    int secim;
    int oturumD = -1;

    while (1)
    {

        system("cls");
        printf("\n**** ATM SISTEMI ****\n");
        printf("1--> Giris Yapin (Kart Takin) \n");
        printf("2--> Yeni Hesap Olustur\n");
        printf("0--> Cikis\n");
        printf("\nLUTFEN YAPACAGINIZ ISLEMI SECINIZ: ");
        scanf("%d", &secim);

        switch (secim)
        {
        case 1:
            oturumD = kGiris();
            if (oturumD != -1)
            {
                KMenu(oturumD);
            }
            break;
        case 2:
            hesapOlustur();
            break;
        case 0:
            printf("\nLUTFEN KARTINIZI ALINIZ.\n");
            printf("Iyi gunler dileriz...\n");
            exit(0);

        default:
            printf("\nHatali secim! Lutfen gecerli bir secim yapiniz.\n");
            getch();
            break;
        }
    }
    return 0;
}
