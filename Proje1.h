//
// Created by hande on 21.12.2024.
//

#ifndef PROJE1_H
#define PROJE1_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CALISAN 20
#define MAX_CHAR 30
extern int globalBirimCounter;
extern int globalCalisanCounter;
typedef struct Calisan
{
    char *calisanAdi;
    char *calisanSoyadi;
    unsigned short int birimKodu;
    float maas;
    int girisYili;
} Calisan;

typedef struct Birim
{
    char *birimAdi;
    unsigned short int birimKodu;
    int calisanSayisi; //dongude null olana kadar gez dememek icin ayırdım
    Calisan **birimCalisanlar;
} Birim;


// Calisani Birime ekleyen fonksiyon
void addCalisanToBirim(Birim **birimler, Calisan *calisan);
// Calisanlar dosyasını okuyan fonksiyon
void readCalisanlarFile(char *fileName, Birim ***birimler, Calisan ***calisanlar);
// Birim olusturan fonksiyon
Birim* createBirim(char *birimAdi, unsigned short int birimKodu);
// Calisan olusturan fonksiyon
Calisan* createCalisan(char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili);
// Birimi Birimler dizisine ekleyen fonksiyon
void addBirimToBirimler(Birim ***birimler, Birim *birim);
// Calisani Calisanlar dizisine ekleyen fonksiyon
// Birimler dosyasını okuyan fonksiyon
void readBirimlerFile(char *fileName, Birim ***birimler);
void addCalisanToCalisanlar(Calisan ***calisanlar, Calisan *calisan);
// Calisan bilgilerini yazdiran fonksiyon
void printCalisanInfo(Calisan *calisan);
// Birim bilgilerini yazdiran fonksiyon
void printBirimInfo(Birim *birim);
// Birimler dizisini yazdiran fonksiyon
void printBirimlerInfo(Birim **birimler);
// Parametre olarak aldığı birimin çalışanlarının maaş ortalamasını hesaplayan fonksiyon
float calculateBirimAverageSalary(Birim *birim);
// Parametre olarak aldığı birimde ortalama maaş üzerinde maaş alan çalışanları listeleyen fonksiyon
void printCalisanAboveAverageSalary(float maas, Birim *birim);
// Her birimin en yüksek maaşlı çalışanını yazdiran fonksiyon
void printBirimHighIncome(Birim **birimler);
// Parametre olarak bir maaş değeri alıp, 10 yıldan fazla çalışanlar bu maaştan az alıyor ise maaşlarını parametre olarak verilen maaşa eşitleyen fonksiyon
void updateSalary(float newSalary, Birim *birim);
// Calisanlari dosyaya yazan fonksiyon
void writeCalisanlarToFile(char *fileName, Calisan **calisanlar);
// Birimleri dosyaya yazan fonksiyon
void writeBirimlerToFile(char *fileName, Birim **birimler);
// FREE FONKSIYONLARI
void freeFunction(Birim**birimler,Calisan **calisanlar);
//void freeBirimler(Birim **birimler);
#endif //PROJE1_H
