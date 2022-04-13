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