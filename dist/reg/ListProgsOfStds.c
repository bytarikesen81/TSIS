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