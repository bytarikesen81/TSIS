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
