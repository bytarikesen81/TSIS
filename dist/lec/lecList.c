void dersListele(struct lect *head){
	struct lect *p = head;
	printf("\n\n-------------------------\nDERS LISTESI\n-------------------------\n");
	if(head == NULL){
		printf("\nUYARI:Ders listesi bos."); 
		printf("\nLutfen oncelikle listeye bir ders ekleyin.\n");
		printf("\n-----------------------------------\n");
		return;
	}
	while(p != NULL){
		printf("%s %s %d %d\n",p->code,p->name,p->cr,p->cap);
		p = p->link;
	}
	printf("\n-----------------------------------\n");
}