void dersSil(char *date,struct lect **headP,struct std *headS){
	int i;
	char code[MAX];
	struct lect *p = *headP,*temp;
	struct std *tempS = headS;
	
	//Silinecek dersin kodunu al
	printf("\nSilmek istediginiz ders kodu:");
	scanf("%s",code);
	//Ders listesinin bos olup olmadigini kontrol et
	if(*headP == NULL){
		printf("\nDers listesi bos. Silmek icin oncelikle listeye bir ders ekleyin.\n");
		return;
	}
	//Bos degilse ilk elemani kontrol et
	else if(strcmp(p->code,code) == 0){
		i = 0;
		//Ders icindeki ogrencileri teyit et ve her biri icin gerekli degisiklik ve silme islemlerini yap
		while(i < p->std){
			if(tempS->num == *(p->snums+i)){
				tempS->totCr -= p->cr;
				tempS->totLect--;
				//
				printf("%d No'lu satir degistirildi'\n",tempS->num);
				logKayit(date,"DERS_KAPANDI",p,tempS);
				//
				tempS = tempS->next;
				i++;
			}
			else
				tempS = tempS->next; 
		}
		printf("\n%s Kodlu ders silindi.\n",p->code);
		if(p->snums != NULL)
			free(p->snums);
		p = p->link;
		free(*headP);
		*headP = p;
	}
	//Ilk eleman hedef ders degilse sonraki dersleri teyit et
	else{
		while(p->link != NULL && strcmp(p->link->code,code) != 0)
			p = p->link;
		if(p->link == NULL){
			printf("\nGirdiginiz kod listede bulunamadi.Lutfen var olan gecerli bir kod girin.");
			return;	
		}
		else{
			i = 0;
			temp = p->link;
			while(i < temp->std){
				if(tempS->num == *(temp->snums+i)){
					tempS->totCr -= temp->cr;
					tempS->totLect--;
					//
					printf("%d No'lu satir degistirildi'\n",tempS->num);
					logKayit(date,"DERS_KAPANDI",temp,tempS);
					//
					tempS = tempS->next;
					i++;
				}
				else
					tempS = tempS->next; 
			}
			printf("\n%s Kodlu ders silindi.\n",temp->code);
			p->link = temp->link;
			if(temp->snums != NULL)
				free(temp->snums);
			free(temp);
			temp = NULL;
		}
	}
	dersYaz(*headP);
	stdYaz(headS);
}