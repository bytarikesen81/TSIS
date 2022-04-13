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