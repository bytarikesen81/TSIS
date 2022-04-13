void logKayit(char *date,char *status,struct lect *tempL, struct std *tempS){
	int found=0,size,ID,tempNum;
	char tempCode[MAX],tempDate[MAX],tempStatus[MAX];
	FILE *log,*lognew;
	log = fopen(PathForStdReg,"r+");
	//Dosya adreslerinin varligini,stream ortami icin gerekli bellek alani ve prosedürü kontrol et
	if(log != NULL){
		//Log dosyasinin boyut bilgisini al
		fseek(log,0,SEEK_END); 
		size = ftell(log);
		fseek(log,0,SEEK_SET);
	}
	//Veritabani olusturma ve guncelleme islemleri icin gerekli sartlar saglanmamis ise
	else
		printf("\nHATA:Kayit veritabani kontrol edilemedi.\n");
	fclose(log);	
	//Dosya bos ise
	if(size == 0){
		//Dosyanin baslangic satirina kaydi yaz
		ID = 1;
		log = fopen(PathForStdReg,"a+");
		fprintf(log,"%d %s %d %s %s\n",ID,tempL->code,tempS->num,date,status);
		ID++;
		fclose(log);
	}
	//Dosya bos degilse
	else{
		//Ana veritabanini ac ve yeni dokumu olustur
		log = fopen(PathForStdReg,"r+");
		lognew = fopen("templog.txt","w+");
		//Eldeki veritabaninin sonuna kadar git ve daha once ayni ders ve ogrenciyle bir islem yapilip yapilmadigini kontrol et 
		while(!feof(log)){
			//Eldeki veritabanindan satiri oku
			fscanf(log,"%d %s %d %s %s\n",&ID,tempCode,&tempNum,tempDate,tempStatus);
			//Satir islem yapilacak ders-ogrenci ikilisine aitse
			if(strcmp(tempL->code,tempCode) == 0 && tempS->num == tempNum){
				fprintf(lognew,"%d %s %d %s %s\n",ID,tempL->code,tempS->num,date,status);
				found = 1;	
			}
			//Satir islem yapilacak ders-ogrenci ikilisine ait degilse
			else
				fprintf(lognew,"%d %s %d %s %s\n",ID,tempCode,tempNum,tempDate,tempStatus);	
		}
		//Islem yapilacak ders-ogrenci ikilisiyle daha once islem yapilmamissa
		if(found == 0){
			ID++;
			fprintf(lognew,"%d %s %d %s %s\n",ID,tempL->code,tempS->num,date,status);	
		}
		//Veritabanlarini kapat
		fclose(log);
		fclose(lognew);
		//Onceki veritabanini sil ve yenisiyle degistir
		remove(PathForStdReg);
		rename("templog.txt",PathForStdReg);
		//Islem tamamlandiginda kullaniciyi bilgilendir
		printf("\nKayit veritabani guncellendi.\n");
	}
}
