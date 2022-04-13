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