int kodSorgula(struct lect *head,char *code){
	struct lect *p = head;
	while(p != NULL && strcmp(p->code,code) != 0)
		p = p->link;
	if(p == NULL) 
		return 0;
	else 
		return 1;
}
