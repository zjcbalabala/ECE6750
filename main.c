/* two-level logic minimazition
*  Jichen Zhang
*  u0841473
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//struct to record all output and input value for each state, number of output and input, all transition start state and end state
// number of transitions, number of state
typedef struct {
	int a[31][31];
	char inputname[31];
	char outputname[31];
	int Tstart[31];
	int Tend[31];
	int inputSize;
	int outputSize;
	int Tsize;
	int statesize;
} State;
//define struct

typedef struct {
	int a[31][31];
	int rowReduced[31];
	int columnReduced[31];
	int reducedRowSize;
	int reducedColumnSize;
} RequiredCube;



typedef struct {
	int x[31];
	int size;
} Variables;



//define variables
FILE* fin;
FILE* fout;
int state[30];

int Output[30];
int rowsize = 0;
int output = 0;
int input = 0;
int Input[64];
char name[31];
int column();
int statesize(State* a);
int getstate(State*a, int b, int c);

void printState(State* a) {
	int c = 10;
	int r = 5;
	fprintf(fout, "  aaa ");
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			
			fprintf(fout, "%2d\n ", a->a[i][j]);
			fprintf(fout, "bbb");
			//fprintf(fout, "%s", );
		fprintf(fout, "%s\n", Input[2]);
			fprintf(fout, "ccc");
		}

	}


}


State* StateNew() {
	State* res = (State*)malloc(sizeof(State));
	memset(res, 0, sizeof(State));
	return res;
}
RequiredCube* RNew() {
	RequiredCube* res = (RequiredCube*)malloc(sizeof(RequiredCube));
	memset(res, 0, sizeof(RequiredCube));
	return res;
}
RequiredCube* RequiredCubecopy(RequiredCube* b) {
	RequiredCube* res = (RequiredCube*)malloc(sizeof(RequiredCube));
	memcpy(res, b, sizeof(RequiredCube));
	return res;
}

Variables* variablesNew() {
	Variables* res = (Variables*)malloc(sizeof(Variables));
	memset(res, 0, sizeof(Variables));
	return res;
}

State* StateCopy(State* a) {
	State* res = (State*)malloc(sizeof(State));
	memcpy(res, a, sizeof(State));
	return res;
}

Variables* variablesCopy(Variables* x) {
	Variables* res = (Variables*)malloc(sizeof(Variables));
	memcpy(res, x, sizeof(Variables));
	return res;
}
void init(State* condition, Variables* out, Variables* in) {

	fopen_s(&fin, "input.txt", "r");

	fopen_s(&fout, "output.txt", "w");



	char temp[64];

	//char tem[11];

	//int a;

	//int b;

	int hash['z' + 1];



	while (1) {

		fgets(temp, 64, fin);

		if (temp[0] == '=') {

			break;

		}
		if (temp[0] != '\n') {
			condition->inputname[input] = temp[0];
			Input[input] = temp[0];
			//fprintf(fout, "%s\n", Input[input]);
			condition->a[0][input] = temp[2] - '0';

			hash[temp[0]] = input;

			++input;
		}
	}

	condition->inputSize = input;



	while (1) {

		fgets(temp, 64, fin);

		if (temp[0] == '=') {

			break;

		}
		if (temp[0] != '\n') {
			condition->outputname[output] = temp[0];

			condition->a[0][input + output] = temp[2] - '0';

			hash[temp[0]] = input + output;

			++output;
		}
		

	}

	condition->outputSize = output;



	condition->Tsize = 0;
	while (1) {
		fgets(temp, 64, fin);

		//fgets(temp, sizeof 64, fin);

		 if (temp[0] == '=') {

			break;

		}
		else if (temp[0] != '\n') {
			condition->Tstart[condition->Tsize] = temp[0] - '0';

			condition->Tend[condition->Tsize] = temp[2] - '0';
			if (temp[0]-'0' >= condition->statesize )
			{
				condition->statesize = temp[0]-'0';
			}
			if(temp[2]-'0' >= condition->statesize)
			{
				condition->statesize = temp[2]-'0';
			}
			++condition->Tsize;

			memcpy_s(condition->a[condition->Tsize], 31 * sizeof(int), condition->a[condition->Tsize - 1], 31 * sizeof(int));

			if (temp[3] == 0) {

				continue;

			}

			int len = strlen(temp);

			for (int i = 4; i < len - 1; i += 3) {

				condition->a[condition->Tsize][hash[temp[i]]] = temp[i + 1] == '+' ? 1 : 0;

			}
		}
	}


}
/*void init(State* condition, Variables* out, Variables* in) {

fopen_s(&fin, "input.txt", "r");
fopen_s(&fout, "output.txt", "w")



char temp[31];
//char tem[11];
//int a;
//int b;

int i = 0;
while (1) {
fgets(temp, 64, fin);
//fscanf_s(fin, "%10s\n", temp, sizeof(char) * 11);
if (temp[0] == '/')
{
break;
}
else if (temp[1]!='n' && temp[0] != '0' && temp[0] != '1') {
condition->outputname[i] = temp[0];
fprintf(fout, "%d\n", condition->inputname[0]);

}
else if (temp[0] == '0' || temp[0] == '1') {
in->x[i] = temp[0] - '0';
condition->a[0][i] = temp[0] - '0';
}





i=i+1;
input = input + 1;
}
in->size = input;
condition->inputSize = input;

int j = 0;
while (1) {
fscanf_s(fin, "%s", temp, sizeof(char) * 11);
if (temp[0] == '/')
{
break;
}
else if (!temp[1]  && temp[0] != '0' && temp[0] != '1') {
condition->inputname[i] = temp[0];
}

else if (temp[0] == '0' || temp[0] == '1') {
out->x[j] = temp[0] - '0';
condition->a[0][j + input] = temp[0] - '0';
}





++output;
++j;
}
out->size = output;
condition->outputSize = output;
i = 0;
int k = 0;
int s = 0;
int e = 0;


do {
fscanf_s(fin, "%10s", temp, sizeof(char) * 11);
if ((temp[0] <= '9') && (k == 0)) {
condition->Tstart[i] = temp[0] - '0';
k = 1;
e = condition->Tstart[i];
if (condition->Tstart[i] >= rowsize) {
rowsize = condition->Tstart[i];
}
}
else if ((temp[0] <= '9') && (k == 1)) {
condition->Tend[i] = temp[0] - '0';
k = 0;
s = condition->Tend[i];
if (condition->Tend[i] >= rowsize) {
rowsize = condition->Tend[i];
}

++i;
}
else if (temp[0] >= '9') {
if (temp[1] == '+') {
for (int j = 0; j <= output + input; ++j)
{
if (temp[0] == name[j]) {
condition->a[s][j] = 1;
}
else if (temp[0] == name[j]) {
condition->a[s][input + j] = 1;
}
}
}
else if (temp[1] == '-') {
for (int j = 0; j <= output + input; ++j)
{
if (temp[0] == name[j]) {
condition->a[s][j] = 0;
}
else if (temp[0] == name[j]) {
condition->a[s][input + j] = 0;
}
}
}
else {
for (int j = 0; j <= output + input; ++j)
{
if (temp[0] == name[j]) {
condition->a[s][j] = getstate(condition, e, j);
}
else if (temp[0] == name[j]) {
condition->a[s][input + j] = getstate(condition, e, j);
}

}
}
}


} while (temp == '/');
condition->Tsize = i;
condition->statesize = rowsize;



}*/
int column() {
	return output + input;
	printf("%d\n", output + input);
}
int getstate(State* a, int b, int c) {
	return a->a[b][b];
	printf("%d\n", a->a[b][c]);
}
int statesize(State* a) {
	return a->statesize;
	printf("%d\n", a->statesize);
}

int Tsize(State* a) {
	return a->Tsize;
	printf("%d\n", a->Tsize);
}
int getstartstate(State* a, int b) {
	return a->Tstart[b];
	printf("%2d\n", a->Tstart);
}
int getendstate(State* a, int b) {
	return a->Tend[b];
	printf("%d\n", a->Tend);
}
int gettype(Variables* a, int b) {
	return a->x[b];
	printf("%d\n", a->x[b]);
}

//if the output of this state is 1, then Stype is 1.
//if 1->1 set ttype to 3
//if 1->0 set Ttype to 2 
//if 0->1 set Ttype to 1
//if 0->0 set Ttype to 0
void Ttype(State* a, Variables* Stype, Variables* Ttype) {
	int row = statesize(a);
	for (int i = 0; i < row; ++i) {
		for (int j = input; j < input + output; ++j) {
			if (a->a[i][j] == 1) {
				Stype->x[i] = 1;
			}
			

		}
	}
	int size = Tsize(a);
	for (int i = 0; i < size; ++i) {
		int k = a->Tstart[i];
		int n = a->Tend[i];
		if ((Stype->x[k] == 1) && (Stype->x[n] == 1)) {
			Ttype->x[i] = 3;
		}
		else if ((Stype->x[k] == 1) && (Stype->x[n] == 0)) {
			Ttype->x[i] = 2;
		}
		else if (Stype->x[k] == 0 && Stype->x[n] == 1) {
			Ttype->x[i] = 1;
		}
		else
			Ttype->x[i] = 0;
	}
	/*
	for (int i = 1; i < row; ++i) {
	int k = Stype->x[i];
	if (k = 1) {
	Ttype->x[i + size - 1] = 3;
	}
	if (k = 0) {
	Ttype->x[i + size - 1] = 0;
	}
	*/
}
void priset(State*a, RequiredCube* b, Variables* Ttype) {
	int row = statesize(a);
	int size = Tsize(a);
	
	int tempa;
	int tempb;
	for (int i = 0; i < size; ++i) {
		tempa = a->Tstart[i];
		tempb = a->Tend[i];
		if (Ttype->x[i] != 0 && Ttype->x[i] !=3) {
			for (int j = 0; j < output + input; ++j) {
				if (a->a[tempa][j] == a->a[tempb][j] && a->a[tempa][j]==0) {
					b->a[i][j] = 0;
				}
				else if (a->a[tempa][j] == a->a[tempb][j] && a->a[tempa][j] == 1) {
					b->a[i][j] = 1;
				}
				else
				{
					b->a[i][j] = 2;

				}
				fprintf(fout, "%2d\n ", b->a[i][j]);
			}
		}
	}

}
/*
*/
void requiredcube(State* a, RequiredCube* b, Variables* Ttype) {
	int row = statesize(a);
	int size = Tsize(a);
	int i = 0;
	int count = 0;
	State* x = StateCopy(a);
	while (i < size) {
		int m = getstartstate(a, i);
		int n = getendstate(a, i);
		if (Ttype->x[i] != 0) {
			for (int j = 0; j < input; ++j) {
				
				if (Ttype->x[i] == 2) {
					if (a->a[m][j] != a->a[n][j]) {
						memcpy_s(b->a[count], 31 * sizeof(int), a->a[m], 31 * sizeof(int));
						b->a[count][j] = 2;
						++count;
						 }
					
				
				}
				else if (Ttype->x[i] == 1) {
					if (a->a[m][j] != a->a[n][j]) {
						memcpy_s(b->a[count], 31 * sizeof(int), a->a[n], 31 * sizeof(int));
						b->a[count][j] = 2;
						++count;
					}
					
				}
				else if(Ttype->x[i] == 3){
					if (a->a[m][j] == a->a[n][j] && a->a[m][j] == 0) {
						b->a[count][j] = 0;
					}
					else if (a->a[m][j] == a->a[n][j] && a->a[m][j] == 1) {
						b->a[count][j] = 1;
					}
					else
					{
						b->a[count][j] = 2;

					}
					++count;
				}
				

				
				//if (Ttype -> x[i] == 2) {

				//}
			}
		}

		++i;
	}
}


int main() {
	State* a = StateNew();
	Variables* x = variablesNew();
	Variables* b = variablesNew();
	Variables* d = variablesNew();
	Variables* e = variablesNew();
	RequiredCube* c = RNew();
	RequiredCube* t = RNew();
	init(a, x, b);
	Ttype(a, d, e);
	requiredcube(a, t, e);
	priset(a, c, e);
	printState(a);
	column();
	
	return 0;
}