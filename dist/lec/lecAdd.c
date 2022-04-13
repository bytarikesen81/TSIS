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