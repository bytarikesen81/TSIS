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

//Database reading operations when the execution starts
void dersOku(struct lect **);//Dersleri program basinda veritabanindan okur ve listeye aktarir, yeni haliyle DByi gunceller
void stdOku(struct std **);//Ogrencileri program basinda veritabanindan okur ve listeye aktarir, yeni haliyle DByi gunceller
void stdKayitOku(struct lect *,struct std *);//Program basinda layit veritabanindaki 'KAYITLI' durumdaki satirlari okuyarak ogrencileri derslere aktarir

//Individual Lecture Operations
void dersYaz(struct lect *);//Ders veritabanini gunceller
void dersEkle(struct lect **);//Ders ekleme islemini yapar
void dersSil(char*,struct lect **,struct std *);//Ders silme islemini yapar
void dersListele(struct lect *);//Program icindeki derslerin guncel durumlarini listeler
int kodSorgula(struct lect*,char*);//Girilen kodun listedeki bir derse ait olup olmadigini sorgular


//Individual Student Operations
void stdYaz(struct std *);//Ogrenci veritabanini gunceller
void stdKayit(struct std **);//Ogrenci kayit islemini yapar
void stdSil(char*,struct std **,struct lect*);//Ogrencinin kaydini siler 
void stdListele(struct std *);//Program icindeki ogrencilerin guncel durumlarini listeler
int noSorgula(struct std*,unsigned long int);//Girilen numaranin listedeki bir ogrenciye ait olup olmadigini sorgular


//Register Operations
void stdDersKayit(char*,struct std *,struct lect *,int,int);//Numarasi girilen ogrencinin kaydini kodu girilen derse yapar
void stdDersSil(char*,struct std *,struct lect *);//Numarasi girilen ogrencinin kaydini kodu girilen dersten siler
int dersStdSorgula(unsigned long int *,int,int);//Numarasi girilen ogrencinin secilen derste olup olmadigini sorgulanir
void dersStdListele(struct std *,struct lect *);//Kodu girilen ders icin kayitli ogrencileri listeler
void stdProgListele(struct std *,struct lect *);//Numarasi girilen ogrencinin kayitli oldugu dersleri listeler
void dersStdYaz(struct std *,struct lect *);//Kodu girilen ders icin ozel sinif listesi olusturur
void stdProgYaz(struct std *,struct lect *);//Kodu girilen ders icin ozel ders programi olusturur

//Log Handling and Database Writing Operations
void logKayit(char*,char*,struct lect *,struct std *);//OgrenciDersKayit veritabanini uygun durum icin gunceller

//Dynamic Memory Operations
void clearLists(struct lect **,struct std **);//Bellekteki tüm dinamik tahsis edilmis verileri siler


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


//LECTURE FUNCTIONS
void dersOku(struct lect **headP){
	int size;
	char c;
	struct lect *p,*temp;
	FILE *fp = fopen(LectPath,"r+"),*fpstd;
	//Dosya adresinin varligini,stream ortami icin gerekli bellek alani ve prosedürü kontrol et
	if(fp != NULL){
		//Log dosyasinin boyut bilgisini al
		fseek(fp,0,SEEK_END); 
		size = ftell(fp);
		fseek(fp,0,SEEK_SET);
	}
	//Veritabani olusturma ve guncelleme islemleri icin gerekli sartlar saglanmamis ise
	else{
		printf("\nHATA:Kayit veritabani kontrol edilemedi.\n");
		return;		
	}
	fclose(fp);
	//Dosya bos degil ise
	if(size != 0){
		fp = fopen(LectPath,"r+");
		if(fp != NULL){
			while((c = fgetc(fp)) != EOF){
				// Dosya sonuna gelene kadar her satir icin dugum olustur ve satirda okunan degerleri tiplerine gore bolusturup dugume aktar
				p = *headP;
				temp = (struct lect *)malloc(sizeof(struct lect));
				temp->link = NULL;
				temp->code[0] = c;
				fscanf(fp,"%s %s %d %d\n",&(temp->code[1]),temp->name,&temp->cr,&temp->cap);
				temp->snums = NULL;
				temp->std = 0;
				//Dugumu listeye Bagla
				if(*headP == NULL){//Liste Bossa
					*headP = temp;
				}
				else if(strcmp(temp->code,(*headP)->code) < 0){
						temp->link = *headP;
						*headP = temp;
				}
				else{
					while(p->link != NULL && strcmp(temp->code,p->code) > 0){
						if(strcmp(temp->code,p->link->code) < 0){
								temp->link = p->link;
								p->link = temp;
								p = temp->link;
						}
						else
							p = p->link;
					}
					if(p->link == NULL && strcmp(temp->code,p->code) > 0)
						p->link = temp;
				}
				temp = NULL;
				p = *headP;
			}
			dersYaz(*headP);
		}
		else
			printf("HATA:Ders Listesi Okunamadi.\n");
		fclose(fp);	
	}	
}

void dersYaz(struct lect *headP){
	struct lect *p = headP;
	FILE *fp = fopen(LectPath,"w+");
	if(fp != NULL){
		while(p != NULL){
			fprintf(fp,"%s %s %d %d\n",p->code,p->name,p->cr,p->cap);
			p = p->link;
		}
	}
	else
		printf("HATA:Ders Listesi Yazilamadi.\n");
	fclose(fp);
}

void dersEkle(struct lect **headP){
	//Dugum icin yer olustur
	struct lect *p = *headP,*temp = (struct lect *)malloc(sizeof(struct lect));
	//Eklenecek dugumu yapilandir
	temp->link = NULL;
	printf("\nDers Adi:");
	scanf("%s",temp->name);
	printf("\nDersin kodu(Benzersiz):");
	scanf("%s",temp->code);
	if(kodSorgula(*headP,temp->code)){
		printf("\nHATA:Girilen kod, daha önce baska bir ders tarafindan halihazirda bulunuyor.\nLutfen farkli bir kod girin.\n");
		free(temp);
		return;	
	}
	printf("\nDers Kredisi:");
	scanf("%d",&(temp->cr));
	printf("\nDers icin acilacak kontenjan sayisi:");
	scanf("%d",&(temp->cap));
	printf("\n");
	temp->snums = NULL;
	temp->std = 0;
	//Dugumu listeye Bagla
	if(*headP == NULL)//Liste Bossa
		*headP = temp;
	else if(strcmp(temp->code,p->code) < 0){
			temp->link = *headP;
			*headP = temp;
	}
	else{
		while(p->link != NULL && strcmp(temp->code,p->code) > 0){
			if(strcmp(temp->code,p->link->code) < 0){
					temp->link = p->link;
					p->link = temp;
					p = temp->link;
			}
			else
				p = p->link;
		}
		if(p->link == NULL && strcmp(temp->code,p->code) > 0)
			p->link = temp;
	}
	printf("%s kodlu ders eklendi.",temp->code);
	dersYaz(*headP);
	//Fonk. sonu
}

void dersSil(char *date,struct lect **headP,struct std *headS){
	int i;
	char code[MAX];
	struct lect *p = *headP,*temp;
	struct std *tempS = headS;
	
	//Silinecek dersin kodunu al
	printf("\nSilmek istediginiz ders kodu:");
	scanf("%s",code);
	//Ders listesinin bos olup olmadigini kontrol et
	if(*headP == NULL){
		printf("\nDers listesi bos. Silmek icin oncelikle listeye bir ders ekleyin.\n");
		return;
	}
	//Bos degilse ilk elemani kontrol et
	else if(strcmp(p->code,code) == 0){
		i = 0;
		//Ders icindeki ogrencileri teyit et ve her biri icin gerekli degisiklik ve silme islemlerini yap
		while(i < p->std){
			if(tempS->num == *(p->snums+i)){
				tempS->totCr -= p->cr;
				tempS->totLect--;
				//
				printf("%d No'lu satir degistirildi'\n",tempS->num);
				logKayit(date,"DERS_KAPANDI",p,tempS);
				//
				tempS = tempS->next;
				i++;
			}
			else
				tempS = tempS->next; 
		}
		printf("\n%s Kodlu ders silindi.\n",p->code);
		if(p->snums != NULL)
			free(p->snums);
		p = p->link;
		free(*headP);
		*headP = p;
	}
	//Ilk eleman hedef ders degilse sonraki dersleri teyit et
	else{
		while(p->link != NULL && strcmp(p->link->code,code) != 0)
			p = p->link;
		if(p->link == NULL){
			printf("\nGirdiginiz kod listede bulunamadi.Lutfen var olan gecerli bir kod girin.");
			return;	
		}
		else{
			i = 0;
			temp = p->link;
			while(i < temp->std){
				if(tempS->num == *(temp->snums+i)){
					tempS->totCr -= temp->cr;
					tempS->totLect--;
					//
					printf("%d No'lu satir degistirildi'\n",tempS->num);
					logKayit(date,"DERS_KAPANDI",temp,tempS);
					//
					tempS = tempS->next;
					i++;
				}
				else
					tempS = tempS->next; 
			}
			printf("\n%s Kodlu ders silindi.\n",temp->code);
			p->link = temp->link;
			if(temp->snums != NULL)
				free(temp->snums);
			free(temp);
			temp = NULL;
		}
	}
	dersYaz(*headP);
	stdYaz(headS);
}

void dersListele(struct lect *head){
	struct lect *p = head;
	printf("\n\n-------------------------\nDERS LISTESI\n-------------------------\n");
	if(head == NULL){
		printf("\nUYARI:Ders listesi bos."); 
		printf("\nLutfen oncelikle listeye bir ders ekleyin.\n");
		printf("\n-----------------------------------\n");
		return;
	}
	while(p != NULL){
		printf("%s %s %d %d\n",p->code,p->name,p->cr,p->cap);
		p = p->link;
	}
	printf("\n-----------------------------------\n");
}

int kodSorgula(struct lect *head,char *code){
	struct lect *p = head;
	while(p != NULL && strcmp(p->code,code) != 0)
		p = p->link;
	if(p == NULL) 
		return 0;
	else 
		return 1;
}


//STUDENT FUNCTIONS
void stdOku(struct std **headP){
	int size;
	struct std *p,*temp;
	FILE *fp = fopen(StdPath,"r+");
	//Dosya adresinin varligini,stream ortami icin gerekli bellek alani ve prosedürü kontrol et
	if(fp != NULL){
		//Log dosyasinin boyut bilgisini al
		fseek(fp,0,SEEK_END); 
		size = ftell(fp);
		fseek(fp,0,SEEK_SET);
	}
	//Veritabani olusturma ve guncelleme islemleri icin gerekli sartlar saglanmamis ise
	else{
		printf("\nHATA:Kayit veritabani kontrol edilemedi.\n");
		return;	
	}
	fclose(fp);
	if(size != 0){
		fp = fopen(StdPath,"r+");
		if(fp != NULL){
			while(!feof(fp)){
				// Dosya sonuna gelene kadar her satir icin dugum olustur ve satirda okunan degerleri tiplerine gore bolusturup dugume aktar
				temp = (struct std *)malloc(sizeof(struct std));
				temp->prev = temp->next = NULL;
				fscanf(fp,"%d %s %s %d %d\n",&temp->num,temp->name,temp->surname,&temp->totLect,&temp->totCr);
				//Dugumu listeye Bagla
				if(*headP == NULL){//Liste Bossa
					*headP = temp;
				}
				else if(temp->num < (*headP)->num){
					temp->next = *headP;
					p->prev = temp;
					*headP = temp;
				}
				else{
					while((p->next != NULL) && (temp->num > p->num)){
						if(temp->num < p->next->num){
								temp->next = p->next;
								temp->prev = p;
								p->next = temp;
								temp->next->prev = temp;
						}
						else
							p = p->next;
					}
					if(p->next == NULL && temp->num > p->num)
						p->next = temp;
						temp->prev = p;
				}
				temp = NULL;
				p = *headP;
			}
			stdYaz(*headP);
		}
		else
			printf("HATA:Ogrenci Listesi Okunamadi.\n");
		fclose(fp);	
	}
}

void stdYaz(struct std *headP){
	struct std *p = headP;
	FILE *fp = fopen(StdPath,"w+");
	if(fp != NULL){
		while(p != NULL){
			fprintf(fp,"%d %s %s %d %d\n",p->num,p->name,p->surname,p->totLect,p->totCr);
			p = p->next;
		}
	}
	else
		printf("HATA:Ogrenci Listesi Yazilamadi.\n");
	fclose(fp);
}

void stdKayit(struct std **headP){
	//Dugum icin yer olustur
	struct std *p = *headP,*temp = (struct std *)malloc(sizeof(struct std));
	//Eklenecek dugumu yapilandir
	temp->prev = temp->next = NULL;
	printf("\nOgrenci Adi:");
	scanf("%s",temp->name);
	printf("\nOgrenci Soyadi:");
	scanf("%s",temp->surname);
	printf("\nOgrenci Numarasi(Benzersiz):");
	scanf("%d",&temp->num);
	if(noSorgula(*headP,temp->num)){
		printf("\nHATA:Girilen numara, daha önce baska bir ogrenci tarafindan kullanilmakta.\nLutfen farkli bir numara girin.\n");
		free(temp);
		return;	
	}
	temp->totCr = 0;
	temp->totLect = 0;
	printf("\n");
	//Dugumu listeye Bagla
	if(*headP == NULL)//Liste Bossa
		*headP = temp;
	else if(temp->num < (*headP)->num){
		temp->next = *headP;
		p->prev = temp;
		*headP = temp;
	}
	else{
		while((p->next != NULL) && (temp->num > p->num)){
			if(temp->num < p->next->num){
					temp->next = p->next;
					temp->prev = p;
					p->next = temp;
					temp->next->prev = temp;
			}
			else
				p = p->next;
		}
		if(p->next == NULL && temp->num > p->num)
			p->next = temp;
			temp->prev = p;
	}
	printf("%d no'lu ogrenci eklendi.",temp->num);
	stdYaz(*headP);
}

void stdSil(char *date,struct std **headP,struct lect *headL){
	int i,tempI;
	unsigned long int num,*tempNums;
	struct std *p = *headP,*temp;
	struct lect *tempL = headL;
	//Silmek istenilen ogrencinin numara bilgilerini al
	printf("\nKaydini sildirmek istediginiz ogrenci numarasi:");
	scanf("%d",&num);
	//Ogrenci listesinin bos olup olmadigini kontrol et	
	if(*headP == NULL){
		printf("\nOgrenci listesi bos. Silmek icin oncelikle listeye bir ogrenci ekleyin.\n");
		return;
	}
	//Bos degilse ilk elemani kontrol et ve kendisine bagli olan her bir dersten kendisini cikart
	else if(num == p->num){
		while(tempL != NULL){
			i = 0;
			while((i < tempL->std) && p->num != *(tempL->snums+i))
				i++;
			if(i != tempL->std){
				tempL->cap++;
				while(i<(tempL->std-1)){
					tempI = *(tempL->snums+i+1);
					*(tempL->snums+i+1) = *(tempL->snums+i);
					*(tempL->snums+i) = tempI;
					i++;
				}
				logKayit(date,"SILDI",tempL,p);
				tempNums = realloc(tempL->snums,(tempL->std)*(sizeof(unsigned long int)));
				tempL->std--;
				if(tempNums != NULL)
					tempL->snums = tempNums;
				else{
					printf("\nHATA:Ogrencinin tutulacagi yer tahsis edilemedi.\n");
					return;	
				}
			}
			tempL = tempL->link;
		}
		printf("\n%d No'lu ogrenci silindi.\n",p->num);
		p = p->next;
		free(*headP);
		*headP = p;
		if(p != NULL)
			p->prev = NULL;
	}
	//Ilk eleman degilse digerlerini kontrol et ve kendisine bagli olan her bir dersten kendisini cikart
	else{
		while(p->next != NULL && num != p->next->num)
			p = p->next;
		if(p->next == NULL){
			printf("\nGirdiginiz numara listede bulunamadi.Lutfen var olan gecerli bir numara girin.");
			return;	
		}
		else{
			temp = p->next;
			while(tempL != NULL){
				i = 0;
				while((i < tempL->std) && temp->num != *(tempL->snums+i))
					i++;
				if(i != tempL->std){
					tempL->cap++;
					while(i<(tempL->std-1)){
						tempI = *(tempL->snums+i+1);
						*(tempL->snums+i+1) = *(tempL->snums+i);
						*(tempL->snums+i) = tempI;
						i++;
					}
					logKayit(date,"SILDI",tempL,temp);
					tempNums = realloc(tempL->snums,(tempL->std)*(sizeof(unsigned long int)));
					tempL->std--;
					if(tempNums != NULL)
						tempL->snums = tempNums;
					else{
						printf("\nHATA:Ogrencinin tutulacagi yer tahsis edilemedi.\n");
						return;
					}
				}
				tempL = tempL->link;
			}
			printf("\n%d No'lu ogrenci silindi.\n",temp->num);
			p->next = temp->next;
			temp->next->prev = p;
			free(temp);
			temp = NULL;
		}
	}
	stdYaz(*headP);
	dersYaz(headL);
}

void stdListele(struct std *head){
	struct std *p = head;
	printf("\n\n-------------------------\nOGRENCI LISTESI\n-------------------------\n");
	if(head == NULL){
		printf("\nUYARI:Ogrenci listesi bos."); 
		printf("\nLutfen oncelikle listeye bir ogrenci ekleyin.\n");
		printf("\n-----------------------------------\n");
		return;
	}
	while(p != NULL){
		printf("%d %s %s %d %d\n",p->num,p->name,p->surname,p->totLect,p->totCr);
		p = p->next;
	}
	printf("\n-----------------------------------\n");
}

int noSorgula(struct std *head,unsigned long int num){
	struct std *p = head;
	while(p != NULL && p->num != num)
		p = p->next;
	if(p == NULL) 
		return 0;
	else 
		return 1;
}


//REGISTER FUNCTIONS BASED ON LECTURE-STUDENT RELATIONS
int dersStdSorgula(unsigned long int *list,int size,int num){
	int i = 0;
	if(list == NULL || size == 0)
		return 0;
	else{
		while(i<size){
			if(*(list+i) == num)
				return 1;
			else
				i++;
		}
	}
	return 0;
}

void stdDersKayit(char *date,struct std *headS,struct lect *headL,int maxCr,int maxLect){
	unsigned long int num,*tempNums,tempI;
	int i;
	char code[MAX];
	struct std *tempS = headS;
	struct lect *tempL = headL;
	//Fonksiyon alt menusu
	printf("\n-------------------------OGRENCI DERS KAYIT-------------------------\n");	
	//Ogrenci ve ders listesi bosluk sorgulama
	if(headS == NULL){
		printf("\nOgrenci listesi bos. Kayit islemi icin oncelikle listeye bir ogrenci ekleyin.\n");
		return;
	}
	else if(headL == NULL){
		printf("\nDers listesi bos. Kayit islemi icin oncelikle listeye bir ders ekleyin.\n");
		return;
	}
	else{
		printf("\n\n-------------------------\nOGRENCI SECIMI\n-------------------------\n");
		//Liste bos degilse numara sorgulama ve no bulunursa kaydedilecek ogrenciyi belirleme
		printf("\nDerse kaydetmek istediginiz ogrencinin numarasini giriniz:");
		scanf("%d",&num);
		while(tempS != NULL && tempS->num != num)
			tempS = tempS->next;
		if(tempS == NULL){
			printf("\nGirdiginiz numara ogrenci listede bulunamadi.Lutfen var olan gecerli bir numara girin.\n");
			return;	
		}
		printf("\n\n-------------------------\nDERS SECIMI\n-------------------------\n");
		//Ogrenci bulunursa ders sorgulama ve ders bulunursa kayit islemlerine baslama
		printf("\nOgrenciyi kayit edeceginiz dersin kodu:");
		scanf("%s",code);
		while(tempL != NULL && strcmp(tempL->code,code) != 0)
			tempL = tempL->link;
		if(tempL == NULL){
			printf("\nGirdiginiz koda ait ders listede bulunamadi.Lutfen var olan gecerli bir kod girin.\n");
			return;	
		}
		//Gerekli ogrenci ve ders bulundugunda, islem icin gerekli olan kod ve numarayi alarak sorgulama islemlere basla
		//Kredi limiti sorgusu
		if(tempS->totCr + tempL->cr > maxCr){
			printf("\nHATA: Ogrencinin kredisi azami krediyi asmakta. Lutfen ders silin veya farkli bir ders secin.\n");
			return;
		}
		//Ders sayi limiti sorgusu
		else if(tempS->totLect == maxLect){
			printf("\nHATA: Ogrencinin alabilecegi maksimum ders sayisina ulasildi. Ders kaydi icin oncelikle bir ders silmeniz gerekli.\n");
			return;	
		}
		//Kontenjan limiti sorgusu
		else if(tempL->cap == 0){
			printf("\nHATA: Dersin kontenjani dolu.\n");
			return;
		}
		//Ogrencinin daha once derste olup olmadigini sorgula
		else if(dersStdSorgula(tempL->snums,tempL->std,tempS->num)){
			printf("\nHATA:Bu ders ayni ogrenci tarafindan zaten daha once alinmis.\n");
			return;	
		}
		//Limitlere takilmazsa islemleri baslat
		else{
			printf("Kayit islemi baslatildi...");
			
			//Dersin ogrencisi yoksa
			if(tempL->snums == NULL){
				tempL->snums = malloc(sizeof(unsigned long int));
				if(tempL->snums != NULL)
					*(tempL->snums) = tempS->num;
				else{
					printf("\nHATA:Ogrencinin tutulacagi yer tahsis edilemedi.\n");
					return;
				}
			}
			//Dersin en az 1 ogrencisi varsa siralamaya uygun bir sekilde ekle
			else{
				tempNums = realloc(tempL->snums,(tempL->std+1) * sizeof(unsigned long int));
				if(tempNums != NULL){
					tempL->snums = tempNums;
					*(tempL->snums+tempL->std) = tempS->num;
					i = tempL->std;
					while(i > 0 && *(tempL->snums+i) < *(tempL->snums+(i-1))){
						tempI = *(tempL->snums+(i-1));
						*(tempL->snums+(i-1)) = *(tempL->snums+i);
						*(tempL->snums+i) = tempI;
						i--;
					}	
				}
				else{
					printf("\nHATA:Ogrencinin tutulacagi yer tahsis edilemedi.\n");
					return;
				}
			}
			//Ogrenci kayit olma degisiklikleri
			tempS->totCr += tempL->cr;
			(tempS->totLect)++;
			//Ders kayit olma degisiklikleri
			tempL->cap--;
			tempL->std++;
			//Kayit basarili oldugunda kullaniciyi bilgilendir
			printf("\n%s %s adli ogrenci %s dersine basarili bir sekilde kaydoldu.\n",tempS->name,tempS->surname,tempL->name);
			dersYaz(headL);
			stdYaz(headS);
			logKayit(date,"KAYITLI",tempL,tempS);
		}		
	}
}

void stdDersSil(char *date,struct std *headS,struct lect *headL){
	unsigned long int num,*tempNums,tempI;
	int i = 0;
	char code[MAX];
	struct std *tempS = headS;
	struct lect *tempL = headL;
	//Fonksiyon alt menusu
	printf("\n-------------------------OGRENCI DERS SIL-------------------------\n");
	//Ogrenci ve ders listesi bosluk sorgulama
	if(headS == NULL){
		printf("\nOgrenci listesi bos. Kayit silme islemi icin oncelikle listeye bir ogrenci ekleyin.\n");
		return;
	}
	else if(headL == NULL){
		printf("\nDers listesi bos. Kayit silme islemi icin oncelikle listeye bir ders ekleyin.\n");
		return;
	}
	else{
		printf("\n\n-------------------------\nOGRENCI SECIMI\n-------------------------\n");
		//Liste bos degilse numara sorgulama ve no bulunursa kaydi silinecek ogrenciyi belirleme
		printf("\nDersten kaydini silmek istediginiz ogrencinin numarasini giriniz:");
		scanf("%d",&num);
		while(tempS != NULL && tempS->num != num)
			tempS = tempS->next;
		if(tempS == NULL){
			printf("\nGirdiginiz numara ogrenci listede bulunamadi.Lutfen var olan gecerli bir numara girin.\n");
			return;	
		}
		printf("\n\n-------------------------\nDERS SECIMI\n-------------------------\n");
		//Ogrenci bulunursa ders sorgulama ve ders bulunursa kayit silme islemlerine baslama
		printf("\nOgrencinin kaydini sileceginiz dersin kodu:");
		scanf("%s",code);
		while(tempL != NULL && strcmp(tempL->code,code) != 0)
			tempL = tempL->link;
		if(tempL == NULL){
			printf("\nGirdiginiz koda ait ders listede bulunamadi.Lutfen var olan gecerli bir kod girin.\n");
			return;	
		}
		//Gerekli ogrenci ve ders bulundugunda, islem icin gerekli olan kod ve numarayi alarak sorgulama islemlere basla
		//Ogrencinin derse kayitli olup olmadigina bak,degilse islemi durdur
		if(!dersStdSorgula(tempL->snums,tempL->std,tempS->num)){
			printf("\nOgrencinin derste kaydi bulunamadi.\n");
			return;
		}
		while(i < tempL->std && tempS->num != *(tempL->snums+i))
			i++;
		if(i < tempL->std){
			while(i < tempL->std-1){
				tempI = *(tempL->snums+i+1);
				*(tempL->snums+i+1) = *(tempL->snums+i);
				*(tempL->snums+i) =  tempI;
			}
			tempL->std--;
			if(tempL->std != 0){
				tempNums = realloc(tempL->snums,(tempL->std)*(sizeof(unsigned long int)));
				if(tempNums != NULL)
					tempL->snums = tempNums;
				else{
					printf("\nHATA:Ogrencinin tutulacagi yer tahsis edilemedi.\n");
					return;	
				}
			}
			else{
				free(tempL->snums);
				tempL->snums = NULL;
			}
			//Ogrenci kayit silme degisiklikleri
			tempS->totCr -= tempL->cr;
			(tempS->totLect)--;
			//Ders kayit silme degisiklikleri
			tempL->cap++;
		}
		else{
			printf("\nHATA:Ogrencinin bu derse sistemde kaydi bulunamadi.\n");
			return;	
		}
		//Kayit silme basarili oldugunda kullaniciyi bilgilendir
		printf("\n%s %s adli ogrenci %s dersinden basarili bir sekilde silindi.\n",tempS->name,tempS->surname,tempL->name);
		dersYaz(headL);
		stdYaz(headS);
		logKayit(date,"SILDI",tempL,tempS);
	}
}

void dersStdListele(struct std *headS,struct lect *headL){
	int i = 0;
	char code[MAX];
	struct lect *tempL = headL;
	struct std *tempS = headS;
	if(tempS == NULL){
		printf("\nOgrenci listesi bos. Kayit islemi icin oncelikle listeye bir ogrenci ekleyin.\n");
		return;			
	}
	else if(tempL == NULL){
		printf("\nDers listesi bos. Kayit islemi icin oncelikle listeye bir ders ekleyin.\n");
		return;
	}
	else{
		printf("\nOgrencilerini goruntulemek istediginiz dersin kodunu giriniz:");
		scanf("%s",code);
		while(tempL != NULL && strcmp(code,tempL->code) != 0)
			tempL = tempL->link;
		if(tempL != NULL){
			if(tempL->snums != NULL){
				printf("\nDersi alan ogrenciler:\n");
				while(i < (tempL->std)){
					if(*(tempL->snums+i) == tempS->num){
						printf("%d,%s,%s,%d,%d\n",tempS->num,tempS->name,tempS->surname,tempS->totLect,tempS->totCr);
						i++;	
					}
					else
						tempS = tempS->next;
				}
			}
			else
				printf("\nDerse kayitli ogrenci bulunamadi.\n");
		}
		else
			printf("\nHATA:Girdiginiz koda ait ders bulunamadi.\n");
	}
}

void stdProgListele(struct std *headS,struct lect *headL){
	int i,match = 0;
	unsigned long int num;
	struct std *tempS = headS;
	struct lect *tempL = headL;
	if(tempS == NULL){
		printf("\nOgrenci listesi bos. Kayit islemi icin oncelikle listeye bir ogrenci ekleyin.\n");
		return;			
	}
	else if(tempL == NULL){
		printf("\nDers listesi bos. Kayit islemi icin oncelikle listeye bir ders ekleyin.\n");
		return;
	}
	else{
		//Liste bos degilse numara sorgulama ve no bulunursa listelenecek ogrenciyi belirleme
		printf("\nDers programini listelemek istediginiz ogrencinin numarasini giriniz:");
		scanf("%d",&num);
		while(tempS != NULL && tempS->num != num)
			tempS = tempS->next;
		if(tempS == NULL){
			printf("\nGirdiginiz numara ogrenci listede bulunamadi.Lutfen var olan gecerli bir numara girin.\n");
			return;	
		}
		else{
			while(tempL != NULL){
				i = 0;
				while(i < (tempL->std) && tempS->num != *(tempL->snums+i))
					i++;
				if(i != tempL->std){
					match = 1;
					printf("%s,%s,%d,%d\n",tempL->name,tempL->code,tempL->cr,tempL->cap);
					tempL = tempL->link;
				}
				else tempL = tempL->link;
			}
			if(match == 0)
				printf("\nGirdiginiz ogrencinin kayitli oldugu herhangi bir ders bulunamadi.");
		}
	}
}

void dersStdYaz(struct std *headS,struct lect *headL){
	char code[MAX],dir[MAX]="DB\\DersListesi\\";
	FILE *fp;
	int i = 0;
	struct lect *tempL = headL;
	struct std *tempS = headS;
	if(tempS == NULL){
		printf("\nOgrenci listesi bos. Kayit islemi icin oncelikle listeye bir ogrenci ekleyin.\n");
		return;			
	}
	else if(tempL == NULL){
		printf("\nDers listesi bos. Kayit islemi icin oncelikle listeye bir ders ekleyin.\n");
		return;
	}
	else{
		printf("\nOgrencilerini yazmak istediginiz dersin kodunu giriniz:");
		scanf("%s",code);
		while(tempL != NULL && strcmp(code,tempL->code) != 0)
			tempL = tempL->link;
			
		if(tempL != NULL){		
			if(tempL->snums != NULL){
				//printf("\nDersi alan ogrenciler:\n");
				strcat(code,".txt");
				strcat(dir,code);
				printf("%s",dir);
				fp = fopen(dir,"w+");
				if(fp != NULL){
					while(i < (tempL->std)){
						if(*(tempL->snums+i) == tempS->num){
							fprintf(fp,"%d %s %s %d %d\n",tempS->num,tempS->name,tempS->surname,tempS->totLect,tempS->totCr);
							i++;	
						}
						else
							tempS = tempS->next;
					}	
				}
				else
					printf("HATA:Girilen derse ait sinif listesi Yazilamadi.\n");
				fclose(fp);
			}
			else
				printf("\nDerse kayitli ogrenci bulunamadi.\n");
		}
		else
			printf("\nHATA:Girdiginiz koda ait ders bulunamadi.\n");
	}
}

void stdProgYaz(struct std *headS,struct lect *headL){
	int num;
	char numcode[MAX],dir[MAX]="DB\\OgrenciProgramlari\\";
	FILE *fp;
	int i = 0;
	struct lect *tempL = headL;
	struct std *tempS = headS;
	if(tempS == NULL){
		printf("\nOgrenci listesi bos. Kayit islemi icin oncelikle listeye bir ogrenci ekleyin.\n");
		return;			
	}
	else if(tempL == NULL){
		printf("\nDers listesi bos. Kayit islemi icin oncelikle listeye bir ders ekleyin.\n");
		return;
	}
	else{
		//Liste bos degilse numara sorgulama ve no bulunursa listelenecek ogrenciyi belirleme
		printf("\nDers programini listelemek istediginiz ogrencinin numarasini giriniz:");
		scanf("%d",&num);
		while(tempS != NULL && tempS->num != num)
			tempS = tempS->next;
		if(tempS == NULL){
			printf("\nGirdiginiz numara ogrenci listede bulunamadi.Lutfen var olan gecerli bir numara girin.\n");
			return;	
		}
		else{
			itoa(num,numcode,10);
			strcat(numcode,"_DERSPROGRAMI.txt");
			strcat(dir,numcode);
			fp = fopen(dir,"w+");
			if(fp != NULL){
				while(tempL != NULL){
					i = 0;
					while(i < (tempL->std) && tempS->num != *(tempL->snums+i))
						i++;
					if(i != tempL->std){
						fprintf(fp,"%s %s %d %d\n",tempL->name,tempL->code,tempL->cr,tempL->cap);
						tempL = tempL->link;
					}
					else tempL = tempL->link;
				}
				printf("\n%s\n",dir);	
			}
			else
				printf("HATA:Girilen derse ait sinif listesi Yazilamadi.\n");
			fclose(fp);	
		}
	}
}



//LOG AND FILE FUNCTIONS
void logKayit(char *date,char *status,struct lect *tempL, struct std *tempS){
	int found=0,size,ID,tempNum;
	char tempCode[MAX],tempDate[MAX],tempStatus[MAX];
	FILE *log,*lognew;
	log = fopen(PathForStdReg,"r+");
	//Dosya adreslerinin varligini,stream ortami icin gerekli bellek alani ve prosedürü kontrol et
	if(log != NULL){
		//Log dosyasinin boyut bilgisini al
		fseek(log,0,SEEK_END); 
		size = ftell(log);
		fseek(log,0,SEEK_SET);
	}
	//Veritabani olusturma ve guncelleme islemleri icin gerekli sartlar saglanmamis ise
	else
		printf("\nHATA:Kayit veritabani kontrol edilemedi.\n");
	fclose(log);	
	//Dosya bos ise
	if(size == 0){
		//Dosyanin baslangic satirina kaydi yaz
		ID = 1;
		log = fopen(PathForStdReg,"a+");
		fprintf(log,"%d %s %d %s %s\n",ID,tempL->code,tempS->num,date,status);
		ID++;
		fclose(log);
	}
	//Dosya bos degilse
	else{
		//Ana veritabanini ac ve yeni dokumu olustur
		log = fopen(PathForStdReg,"r+");
		lognew = fopen("templog.txt","w+");
		//Eldeki veritabaninin sonuna kadar git ve daha once ayni ders ve ogrenciyle bir islem yapilip yapilmadigini kontrol et 
		while(!feof(log)){
			//Eldeki veritabanindan satiri oku
			fscanf(log,"%d %s %d %s %s\n",&ID,tempCode,&tempNum,tempDate,tempStatus);
			//Satir islem yapilacak ders-ogrenci ikilisine aitse
			if(strcmp(tempL->code,tempCode) == 0 && tempS->num == tempNum){
				fprintf(lognew,"%d %s %d %s %s\n",ID,tempL->code,tempS->num,date,status);
				found = 1;	
			}
			//Satir islem yapilacak ders-ogrenci ikilisine ait degilse
			else
				fprintf(lognew,"%d %s %d %s %s\n",ID,tempCode,tempNum,tempDate,tempStatus);	
		}
		//Islem yapilacak ders-ogrenci ikilisiyle daha once islem yapilmamissa
		if(found == 0){
			ID++;
			fprintf(lognew,"%d %s %d %s %s\n",ID,tempL->code,tempS->num,date,status);	
		}
		//Veritabanlarini kapat
		fclose(log);
		fclose(lognew);
		//Onceki veritabanini sil ve yenisiyle degistir
		remove(PathForStdReg);
		rename("templog.txt",PathForStdReg);
		//Islem tamamlandiginda kullaniciyi bilgilendir
		printf("\nKayit veritabani guncellendi.\n");
	}
}

void stdKayitOku(struct lect *headL,struct std *headS){
	int i,ID,tempNum;
	unsigned long int tempI;
	char tempCode[MAX],tempDate[MAX],tempStatus[MAX];
	struct lect *tempL = headL;
	struct std *tempS = headS;
	FILE *log = fopen(PathForStdReg,"r+");
	while(!feof(log)){
		fscanf(log,"%d %s %d %s %s\n",&ID,tempCode,&tempNum,tempDate,tempStatus);
		if(strcmp(tempStatus,"KAYITLI") == 0){
			while(tempL != NULL && strcmp(tempL->code,tempCode) != 0)
				tempL = tempL->link;
			i = tempL->std;
			if(i == 0){
				tempL->snums = malloc(sizeof(unsigned long int));
				*(tempL->snums) = tempNum;
			}
			else{
				tempL->snums = realloc(tempL->snums,(i+1)*sizeof(unsigned long int));
				*(tempL->snums+i) = tempNum;
				while(i > 0 && *(tempL->snums+i) < *(tempL->snums+(i-1))){
					tempI = *(tempL->snums+(i-1));
					*(tempL->snums+(i-1)) = *(tempL->snums+i);
					*(tempL->snums+i) = tempI;
					i--;
				}				
			}
			tempL->std++;
		}
		tempL = headL,tempS = headS;
	}
	fclose(log);
}



//DELETE ALL THE DATA ON MEMORY WHEN EXECUTION ENDS
void clearLists(struct lect **headLect,struct std **headStd){
	struct lect *tempL = *headLect;
	struct std *tempS = *headStd;
	
	if(*headLect == NULL)
		printf("Ders listesi zaten bos.\n");
	else{
		while(tempL != NULL){
			if(tempL->snums != NULL)
				free(tempL->snums);
			tempL = tempL->link;
			free(*headLect);	
			*headLect = tempL;
		}
		printf("Ders listesi basariyla temizlendi.\n");
	}
	
	if(*headStd == NULL)
		printf("Ogrenci listesi zaten bos.\n");
	else{
		while(tempS != NULL){
			tempS = tempS->next;
			free(*headStd);	
			*headStd = tempS;
		}
		printf("Ogrenci listesi basariyla temizlendi.\n");
	}
}
//PROGRAM END LINE
