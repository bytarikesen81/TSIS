#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX 32

//Adjust directories
#define LectPath "DB\\Genel\\Dersler.txt"
#define StdPath "DB\\Genel\\Ogrenciler.txt"
#define PathForStdReg "DB\\Genel\\OgrenciDersKayit.txt"

//Used Structures
struct lect{
	char name[MAX],code[MAX];
	int cr,cap,std;
	unsigned long int *snums;
	struct lect *link;
};

struct std{
	char name[MAX],surname[MAX];
	int totLect,totCr;
	long int num;
	struct std *prev,*next;
};

//MAIN FUNCTION
int main(void){
	
	//INITIAL OPERATIONS
	char date[MAX];
	int sel,maxCr,maxLect;
	setlocale(LC_ALL, "Turkish");
	struct lect *headL = NULL;
	struct std *headS = NULL;
	stdOku(&headS);
	dersOku(&headL);
	stdKayitOku(headL,headS);
	
	//PROGRAM MENU
	printf("\n-------------------------ILK-AYAR MENUSU-------------------------\n");
	do{
		printf("\nOgrenci kredi limiti(Max:30,Min:15):");
		scanf("%d",&maxCr);
		printf("Ogrenci ders sayisi limiti(Max:12,Min:1):");
		scanf("%d",&maxLect);
		if((30 < maxCr || maxCr < 15) || (12 < maxLect || maxLect < 1))
			printf("\nUYARI:Girdiginiz degerler uygun araliklarda degil. Lutfen yeniden giris yapin.\n");	
	}while((30 < maxCr || maxCr < 15) || (12 < maxLect || maxLect < 1));
	system("cls");
	printf("\n-------------------------TARIH GIRISI-------------------------\n");
	printf("GG.AA.YYYY:");
	scanf("%s",date);
	do{
		system("cls");
		printf("\n-------------------------ANA MENU-------------------------\n");
		printf("1-Ders Islemleri\n");
		printf("2-Ogrenci Islemleri\n");
		printf("3-Ogrenci Ders Kayit Islemleri\n");
		printf("Cikis icin yukaridakilerden farkli herhangi bir secim numarasi giriniz.\n");
		printf("\n------------------\nIslem:");
		scanf("%d",&sel);
		printf("\n------------------\n");
		switch(sel){
			case 1:
				system("cls");
				do{
					printf("\n-------------------------DERS MENUSU-------------------------\n");	
					printf("1-Ders Ekle\n");
					printf("2-Ders Sil\n");
					printf("3-Ders Listesini Goruntule\n");
					printf("Ana menuye hemen geri donmek icin yukaridakilerden farkli herhangi bir secim numarasi giriniz.\n");
					printf("\n------------------\nIslem:");
					scanf("%d",&sel);
					printf("\n------------------\n");
					switch(sel){
						case 1:
							dersEkle(&headL);
							break;
						case 2:
							dersSil(date,&headL,headS);
							break;
						case 3:
							dersListele(headL);
							break;
					}
				}while(sel == 1 || sel == 2 || sel == 3);	
				sel = 1;
			break;
		case 2:
				system("cls");
				do{
					printf("\n-------------------------OGRENCI MENUSU-------------------------\n");	
					printf("1-Ogrenci Kayit Yaptir\n");
					printf("2-Ogrenci Kayit Sil\n");
					printf("3-Ogrenci Listesini Goruntule\n");
					printf("Ana menuye hemen geri donmek icin yukaridakilerden farkli herhangi bir secim numarasi giriniz.\n");
					printf("\n------------------\nIslem:");
					scanf("%d",&sel);
					printf("\n------------------\n");
					switch(sel){
						case 1:
							stdKayit(&headS);
							break;
						case 2:
							stdSil(date,&headS,headL);
							break;
						case 3:
							stdListele(headS);
							break;
					}
				}while(sel == 1 || sel == 2 || sel == 3);	
				sel = 2;
			break;
		case 3:
				system("cls");
				do{
					printf("\n-------------------------DERS KAYIT ISLEMLERI MENUSU-------------------------\n");	
					printf("1-Ogrenci Ders Kayit Islemi\n");
					printf("2-Ogrenci Ders Silme Islemi\n");
					printf("3-Derse Kayitli Ogrenci Listesini Goruntule\n");
					printf("4-Ogrencinin Aldigi Ders Listesini Goruntule\n");
					printf("5-Derse Kayitli Ogrencilerden Sinif Listesi Olustur\n");
					printf("6-Ogrenci Ders Programi Olustur\n");
					printf("Ana menuye hemen geri donmek icin yukaridakilerden farkli herhangi bir secim numarasi giriniz.\n");
					printf("\n------------------\nIslem:");
					scanf("%d",&sel);
					printf("\n------------------\n");
					switch(sel){
						case 1:
							stdDersKayit(date,headS,headL,maxCr,maxLect);
							break;
						case 2:
							stdDersSil(date,headS,headL);
							break;
						case 3:
							dersStdListele(headS,headL);
							break;
						case 4:
							stdProgListele(headS,headL);
							break;
						case 5:
							dersStdYaz(headS,headL);
							break;
						case 6:
							stdProgYaz(headS,headL);
							break;
					}
				}while(sel == 1 || sel == 2 || sel == 3 || sel == 4 || sel == 5|| sel == 6);	
				sel = 3;
		}	
	}while(sel == 1 || sel == 2 || sel == 3);
	//
    clearLists(&headL,&headS);
    printf("\nProgramdan cikis yapildi.");
	return 0;
}
