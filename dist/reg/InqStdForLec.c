int dersStdSorgula(unsigned long int *list,int size,int num){
	int i = 0;
	if(list == NULL || size == 0)
		return 0;
	else{
		while(i<size){
			if(*(list+i) == num)
				return 1;
			else
				i++;
		}
	}
	return 0;
}
