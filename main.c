#include <ctype.h>
#include <stdio.h>
#include "Proje1.h"
//extern int globalBirimCounter;
//extern int globalCalisanCounter;
int main() {
 Calisan**calisanlar=NULL;
 Birim**birimler=NULL;
 char*birimlerFile="Birimler.txt";
 char*calisanlarFile="Calisanlar.txt";
  //  Birim*b=createBirim("Gezi",4,&birimler);
 readBirimlerFile(birimlerFile,&birimler);
 readCalisanlarFile(calisanlarFile,&birimler,&calisanlar);
 Birim * bm= birimler[0];
 Birim*mh= birimler[1];
 //Birim*ik= birimler[2];Birim*pz=createBirim("Pazarlama",4);
 //addBirimToBirimler(&birimler,pz);
 float maas=calculateBirimAverageSalary(bm);
 //printf("18. %.2f",maas);
 //printBirimlerInfo(birimler);
 //Calisan*c1=createCalisan("Dilara","Kuloglu",4,600,2019);
 //addCalisanToBirim(&birimler,c1);
 //addCalisanToCalisanlar(&calisanlar,c1);
 //printBirimlerInfo(birimler);
 printCalisanAboveAverageSalary(maas, mh);
 // Her birimin en yüksek maaşlı çalışanını yazdiran fonksiyon
 printBirimHighIncome(birimler);
 // Parametre olarak bir maaş değeri alıp, 10 yıldan fazla çalışanlar bu maaştan az alıyor ise maaşlarını parametre olarak verilen maaşa eşitleyen fonksiyon
 updateSalary(6000, bm);
 printBirimlerInfo(birimler);
 writeBirimlerToFile(birimlerFile,birimler);
 writeCalisanlarToFile(calisanlarFile,calisanlar);
 //FREELEME
 freeFunction(birimler,calisanlar);
 birimler=NULL;
 calisanlar=NULL;
 return 0;
}