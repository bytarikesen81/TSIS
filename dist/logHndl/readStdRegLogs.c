void stdKayitOku(struct lect *headL,struct std *headS){
	int i,ID,tempNum;
	unsigned long int tempI;
	char tempCode[MAX],tempDate[MAX],tempStatus[MAX];
	struct lect *tempL = headL;
	struct std *tempS = headS;
	FILE *log = fopen(PathForStdReg,"r+");
	while(!feof(log)){
		fscanf(log,"%d %s %d %s %s\n",&ID,tempCode,&tempNum,tempDate,tempStatus);
		if(strcmp(tempStatus,"KAYITLI") == 0){
			while(tempL != NULL && strcmp(tempL->code,tempCode) != 0)
				tempL = tempL->link;
			i = tempL->std;
			if(i == 0){
				tempL->snums = malloc(sizeof(unsigned long int));
				*(tempL->snums) = tempNum;
			}
			else{
				tempL->snums = realloc(tempL->snums,(i+1)*sizeof(unsigned long int));
				*(tempL->snums+i) = tempNum;
				while(i > 0 && *(tempL->snums+i) < *(tempL->snums+(i-1))){
					tempI = *(tempL->snums+(i-1));
					*(tempL->snums+(i-1)) = *(tempL->snums+i);
					*(tempL->snums+i) = tempI;
					i--;
				}				
			}
			tempL->std++;
		}
		tempL = headL,tempS = headS;
	}
	fclose(log);
}