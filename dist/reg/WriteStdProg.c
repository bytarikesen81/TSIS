void stdProgYaz(struct std *headS,struct lect *headL){
	int num;
	char numcode[MAX],dir[MAX]="DB\\OgrenciProgramlari\\";
	FILE *fp;
	int i = 0;
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
			itoa(num,numcode,10);
			strcat(numcode,"_DERSPROGRAMI.txt");
			strcat(dir,numcode);
			fp = fopen(dir,"w+");
			if(fp != NULL){
				while(tempL != NULL){
					i = 0;
					while(i < (tempL->std) && tempS->num != *(tempL->snums+i))
						i++;
					if(i != tempL->std){
						fprintf(fp,"%s %s %d %d\n",tempL->name,tempL->code,tempL->cr,tempL->cap);
						tempL = tempL->link;
					}
					else tempL = tempL->link;
				}
				printf("\n%s\n",dir);	
			}
			else
				printf("HATA:Girilen derse ait sinif listesi Yazilamadi.\n");
			fclose(fp);	
		}
	}
}