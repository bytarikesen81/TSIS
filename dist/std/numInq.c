int noSorgula(struct std *head,unsigned long int num){
	struct std *p = head;
	while(p != NULL && p->num != num)
		p = p->next;
	if(p == NULL) 
		return 0;
	else 
		return 1;
}
