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