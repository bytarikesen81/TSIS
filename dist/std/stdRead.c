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