//
// Created by hande on 21.12.2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Proje1.h"

int globalBirimCounter=0; //staticti SIZE YAP
int globalCalisanCounter=0;
Birim* createBirim(char *birimAdi, unsigned short int birimKodu)
{
    Birim *newBirim = (Birim *)malloc(sizeof(Birim));
    Calisan **birimCalisanlar = calloc(CALISAN,sizeof(Calisan *));
    if (birimAdi==NULL) {
       newBirim->birimAdi = (char *)malloc(MAX_CHAR*sizeof(char));
    }
    newBirim->birimAdi = strdup(birimAdi);
    newBirim->birimKodu = birimKodu;
    newBirim->calisanSayisi=0;
    newBirim->birimCalisanlar = birimCalisanlar;
    return newBirim;
}

// Calisan olusturan fonksiyon
  Calisan* createCalisan(char *calisanAdi, char *calisanSoyadi, unsigned short int birimKodu, float maas, int girisYili)
{
    Calisan *newCalisan = (Calisan *)malloc(sizeof(Calisan));
    if (newCalisan == NULL)
    {
        printf("Bellek ayrilamadi...\n");
        free(newCalisan);
        return NULL;
    }
    if(calisanAdi == NULL){
      calisanAdi=malloc(MAX_CHAR*sizeof(char));
    }
    newCalisan->calisanAdi = strdup(calisanAdi);
    if(calisanSoyadi == NULL){
      newCalisan->calisanSoyadi = malloc(MAX_CHAR*sizeof(char));
    }
    newCalisan->calisanSoyadi = strdup(calisanSoyadi);
    newCalisan->birimKodu = birimKodu;
    newCalisan->maas = maas;
    newCalisan->girisYili = girisYili;
    return newCalisan;
}
void readBirimlerFile(char *fileName, Birim ***birimler)
{
    FILE *filePtr = fopen(fileName, "r");
    if (filePtr == NULL)
    {
        printf("Dosya bulunamadi...\n");
        free(birimler);
    }
    char *birimAdi =NULL;
    unsigned short int birimKodu=0;
    while (!feof(filePtr)) {
        birimAdi=(char*)malloc(MAX_CHAR * sizeof(char));
        if (birimAdi == NULL) {
            printf("Birim adi icin yer ayrilamadi...\n");
            free(birimAdi);
        }
        if (fscanf(filePtr, " %99[^,], %hu", birimAdi, &birimKodu) != 2) {
            free(birimAdi);
        }
        Birim *birim = createBirim(birimAdi, birimKodu);
        if (birim == NULL){
          printf("Yeni birim olusturulamadi...\n");
          free(birimAdi);
          break;
        }
        addBirimToBirimler(birimler,birim);
    }
    fclose(filePtr);
}

void readCalisanlarFile(char *fileName, Birim ***birimler, Calisan ***calisanlar)
{
    FILE *filePtr = fopen(fileName, "r");
    if (filePtr == NULL)
    {
        printf("Dosya bulunamadi...\n");
        free(calisanlar);
    }

    char *calisanAdi=NULL;
    char *calisanSoyadi=NULL;
    unsigned short int birimKodu=0;
    float maas=0;
    int girisYili=0;
    while (!feof(filePtr)) // dosyanın sonuna gelene kadar oku
    {
        calisanAdi = (char *)malloc(MAX_CHAR * sizeof(char));
        calisanSoyadi = (char *)malloc(MAX_CHAR * sizeof(char));

        if (calisanAdi == NULL || calisanSoyadi == NULL)
        {
            printf("Calisan adi ve soyadi icin yer ayrilamadi...\n");
            free(calisanAdi);
            free(calisanSoyadi);
            break;
        }
        if (fscanf(filePtr, " %[^,], %[^,], %hu, %f, %d",
                            calisanAdi, calisanSoyadi, &birimKodu, &maas, &girisYili) != 5) // 5 deger okunması gerekiyor
        {
            free(calisanAdi);
            free(calisanSoyadi);
        }
        Calisan *calisan = createCalisan(calisanAdi, calisanSoyadi, birimKodu, maas, girisYili); // Yeni çalışan olusturma
        if (calisan == NULL)
        {
            printf("Yeni calisan olusturulamadi...\n");
            free(calisanAdi);
            free(calisanSoyadi);
            break;
        }
        addCalisanToCalisanlar(calisanlar, calisan);
        addCalisanToBirim(*birimler, calisan);
    }
    fclose(filePtr);
}

// Calisani Calisanlar dizisine ekleyen fonksiyon
void addCalisanToCalisanlar(Calisan ***calisanlar, Calisan *calisan)
{
    (*calisanlar) = realloc((*calisanlar), (globalCalisanCounter + 1) * sizeof(Calisan*));
    (*calisanlar)[globalCalisanCounter++]=calisan;
}
void addBirimToBirimler(Birim ***birimler, Birim *birim)
{    // guncellenmis birim listesi
    (*birimler) = realloc((*birimler), (globalBirimCounter + 1) * sizeof(Birim*));
    (*birimler)[globalBirimCounter++]=birim;
}

void addCalisanToBirim(Birim **birimler, Calisan *calisan) {
    if (birimler == NULL || *birimler == NULL || calisan == NULL) {
        printf("Birimler Listesi ,ilk birim veya calisan bos.\n");
        return;
    }
    Birim **tempBirimler = birimler;
    // Birim dizisini gez
    for (int i = 0; i < globalBirimCounter; i++) { //Hangi birimdeyim
        if (tempBirimler[i]->birimKodu == calisan->birimKodu) { // Birim kodu eşleşiyorsa
            // Yeni çalışanı uygun yere
            if (tempBirimler[i]->birimCalisanlar[tempBirimler[i]->calisanSayisi]==NULL) {
                tempBirimler[i]->birimCalisanlar[tempBirimler[i]->calisanSayisi] = calisan;
                tempBirimler[i]->calisanSayisi++;
                printf("Çalışan eklendi: %s %s, Birim: %s\n",calisan->calisanAdi,calisan->calisanSoyadi,tempBirimler[i]->birimAdi);
            }
        }
    }
    tempBirimler=NULL;
}

// Calisan bilgilerini yazdiran fonksiyon
void printCalisanInfo(Calisan *calisan)
{
    printf("Calisan Adi: %s \n", calisan->calisanAdi);
    printf("Calisan Soyadi: %s \n", calisan->calisanSoyadi);
    printf("Calisan Birim Kodu: %d \n", calisan->birimKodu);
    printf("Calisan Maasi: %.2f \n", calisan->maas);
    printf("Calisan Giris Yili: %d \n", calisan->girisYili);
    printf("-------------------------------------------- \n");
}

// Birim bilgilerini yazdiran fonksiyon
void printBirimInfo(Birim *birim)
{
    if (birim == NULL)
    {
        printf("Gecersiz birim bilgisi.\n");
    }
    printf("Birim Adi: %s \n", birim->birimAdi);
    printf("Birim Kodu: %d \n", birim->birimKodu);
    Calisan **calisanPtr = birim->birimCalisanlar;
    printf("Calisanlar:\n");
    for (int i = 0; i < birim->calisanSayisi; i++) {
    printCalisanInfo(calisanPtr[i]);
    }
    printf("-------------------------------------------- \n");
    }

// Birimler dizisini yazdiran fonksiyon
void printBirimlerInfo(Birim **birimler)
{
    if (birimler == NULL)
    {
        printf("Gecersiz birimler dizisi.\n");
    }
    printf("Birimler Bilgisi:\n");
    printf("-------------------------------------------- \n");
   for(int i = 0; i < globalBirimCounter; i++){
        printBirimInfo((birimler)[i]); // Her bir birimi yazdır
    }
    printf("Tum birimler listelendi.\n");
    printf("-------------------------------------------- \n");
}

float calculateBirimAverageSalary(Birim *birim)
{
    Calisan **birimCalisanlar = birim->birimCalisanlar;
    float sumOfSalary = 0;
    float result = 0;
   for (int i = 0; i < birim->calisanSayisi; i++) {
       sumOfSalary += birimCalisanlar[i]->maas;
   }
    result = sumOfSalary / (birim->calisanSayisi);
    birimCalisanlar=NULL;
    return result;
}

// Parametre olarak aldığı birimde ortalama maaş üzerinde maaş alan çalışanları listeleyen bir fonksiyon.
void printCalisanAboveAverageSalary(float maas, Birim *birim) // Iyılestirme yapilabilir
{
    Calisan **birimCalisanlar = birim->birimCalisanlar;
    printf("%s birimindeki ortalama maaş üzerinde maas alan calisanlar\n", birim->birimAdi);
    while (*birimCalisanlar != NULL)
    {
        if ((*birimCalisanlar)->maas > maas)
        {
            printCalisanInfo((*birimCalisanlar));
        }
        birimCalisanlar++;
    }
    birimCalisanlar=NULL;
}

// Her birimin en yüksek maaşlı çalışanını yazdıran fonksiyon
void printBirimHighIncome(Birim **birimler)
{
    printf("Her birimin en yuksek maasli calisanini yazdiriliyor...\n");
    Calisan* cPtr=malloc(sizeof(Calisan));//mallocla yer ayırmıştım
    float maas=0;
    if (birimler == NULL)
    {
        printf("Gecersiz birimler listesi.\n");
    }
        for (int i = 0; i < globalBirimCounter; i++) { //birimler geziliyor
             for (int j = 0; j < birimler[i]->calisanSayisi; j++) { //birimlerin calisan sayisi kadar geziliyor
                 if ((birimler[i]->birimCalisanlar[j]->maas)>(maas)) { //o anki calisanin maasi o anki calisandan yuksekse ccPtr degistiriliyor
                     cPtr=birimler[i]->birimCalisanlar[j];
                 }

             }
            printCalisanInfo(cPtr);
        }
    free(cPtr);
    cPtr=NULL;
}


// Parametre olarak bir maaş değeri alıp, 10 yıldan fazla çalışanlar bu maaştan az alıyor ise maaşlarını parametre olarak verilen maaşa eşitleyen fonksiyon
void updateSalary(float newSalary, Birim *birim)
{
    if (birim == NULL) { // Kontrol: Eğer calisanlar NULL ise
        printf("Calisanlar listesi boş.\n");
    }
      for (int j = 0; j < birim->calisanSayisi; j++) {
          if ((birim->birimCalisanlar[j]->maas < newSalary)&&((2024-(birim->birimCalisanlar[j]->girisYili))>10)){
              birim->birimCalisanlar[j]->maas = newSalary;
          }
    }
}

void writeBirimlerToFile(char *fileName, Birim **birimler) {
    printf("GLOBAL BIRIM%d ALLAH ALLAH",globalBirimCounter);
    if (birimler == NULL)
    {
        printf("Yazilacak birimler bulunamadi.\n");
    }
    FILE *filePtr = fopen(fileName, "w");
    if (filePtr == NULL)
    {
        printf("Dosya olusturulamadi.\n");
    }

  for (int i=0; i<globalBirimCounter; i++) {
      if (birimler[i]!=NULL) {
      //    printf("Yazılıyor: %s\n",birimler[i]->birimAdi);
          fprintf(filePtr, "%s, %hu\n",birimler[i]->birimAdi,birimler[i]->birimKodu);
      }
  }
    fclose(filePtr);
}


void writeCalisanlarToFile(char *fileName, Calisan **calisanlar)
{
    printf("GLOBAL CALISAN %d ALLAH ALLAH",globalCalisanCounter);
    if (calisanlar == NULL)
    {
        printf("Yazilacak calisanlar bulunamadi.\n");
    }
    FILE *filePtr = fopen(fileName, "w");
    if (filePtr == NULL) {
        printf("Dosya olusturulamadi.\n");
    }
    for (int i = 0; i < globalCalisanCounter; i++)
    {
        printf("301  %d",i);
        if (calisanlar[i] != NULL)
        {
            printf("Yazılıyor: %s\n", calisanlar[i]->calisanAdi);
            fprintf(filePtr, "%s, %s, %hu, %.2f, %d\n",
                    calisanlar[i]->calisanAdi,
                    calisanlar[i]->calisanSoyadi,
                    calisanlar[i]->birimKodu,
                    calisanlar[i]->maas,
                    calisanlar[i]->girisYili);
        }
        }
    fclose(filePtr);
    printf("Calisanlar dosyaya yazildi.\n");
}

void freeFunction(Birim **birimler, Calisan **calisanlar) {
    // Birimleri serbest bırak
    for (int i = 0; i < globalBirimCounter; i++) {
        if (birimler[i] != NULL) {
           if (birimler[i]->birimCalisanlar != NULL) {
                free(birimler[i]->birimCalisanlar);
                birimler[i]->birimCalisanlar = NULL;
            }
            free(birimler[i]->birimAdi);
            birimler[i]->birimAdi=NULL;
            free(birimler[i]);
            birimler[i] = NULL;
        }
    }
    free(birimler);
    birimler = NULL;
//CALISANLAR KISMI
   if (calisanlar != NULL) {
        for (int i = 0; i < globalCalisanCounter; i++) {
            if (calisanlar[i] != NULL) {
               free(calisanlar[i]->calisanAdi);
                free(calisanlar[i]->calisanSoyadi);

                calisanlar[i]->calisanAdi=NULL;
                calisanlar[i]->calisanSoyadi=NULL;
                //   free(calisanlar[i]);
                calisanlar[i] = NULL;
            }
        }
        free(calisanlar);
        calisanlar = NULL;
    }
    printf("HER SEY NULL.\n");
}