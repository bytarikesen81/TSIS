void dersYaz(struct lect *headP){
	struct lect *p = headP;
	FILE *fp = fopen(LectPath,"w+");
	if(fp != NULL){
		while(p != NULL){
			fprintf(fp,"%s %s %d %d\n",p->code,p->name,p->cr,p->cap);
			p = p->link;
		}
	}
	else
		printf("HATA:Ders Listesi Yazilamadi.\n");
	fclose(fp);
}