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