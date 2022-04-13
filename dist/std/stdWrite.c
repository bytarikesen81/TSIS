void stdYaz(struct std *headP){
	struct std *p = headP;
	FILE *fp = fopen(StdPath,"w+");
	if(fp != NULL){
		while(p != NULL){
			fprintf(fp,"%d %s %s %d %d\n",p->num,p->name,p->surname,p->totLect,p->totCr);
			p = p->next;
		}
	}
	else
		printf("HATA:Ogrenci Listesi Yazilamadi.\n");
	fclose(fp);
}