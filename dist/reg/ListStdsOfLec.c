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