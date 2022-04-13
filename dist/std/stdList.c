void stdListele(struct std *head){
	struct std *p = head;
	printf("\n\n-------------------------\nOGRENCI LISTESI\n-------------------------\n");
	if(head == NULL){
		printf("\nUYARI:Ogrenci listesi bos."); 
		printf("\nLutfen oncelikle listeye bir ogrenci ekleyin.\n");
		printf("\n-----------------------------------\n");
		return;
	}
	while(p != NULL){
		printf("%d %s %s %d %d\n",p->num,p->name,p->surname,p->totLect,p->totCr);
		p = p->next;
	}
	printf("\n-----------------------------------\n");
}