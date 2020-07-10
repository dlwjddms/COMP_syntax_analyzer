Readme for semantic analyzer
if success return ACCEPTED

1. exectution(execution file , test file, csv file)
./semantic_analyzer test.out SLR_Parse_Table.csv

2. testcode for test.out
<test.c>
int main(int arg1, char arg2){
	float a;
	float b;
	a = 3.1415926535897932;
	b = -0.014;

	int c;
	c = 7;
	if(a >= b){
		int d= a+b;
	}else{
		a=0;
		if(a >= b){}
	}
	while(c==1){
		arg=arg1+1;
		arg2=arg+1;
	}
	for(arg1=0; arg1<arg2;arg1=arg+1){
		c=c*1;
	}

	return -1;
}
