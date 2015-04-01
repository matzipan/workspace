#include <stdio.h>
#include <stdlib.h>

void sort(unsigned int x[1000], unsigned int n) {
	unsigned int i=0, b=0, aux;

	while(b==0) {
		b=1;
		for(i=0; i<n-1; i++) {
			if(x[i] > x[i+1]) {
				aux = x[i];
				x[i] = x[i+1];
				x[i+1] = aux;
				b=0;
			}
		}
	}	
}

// walks the arrays from right to left and increments counter when it 
// decrements on naomi and increments on ken
int wins_war(unsigned int x[2][1000], unsigned int n) {
	int index0=n-1, index1=n-1, current=0, naomi_wins = 0;

	for(; index0>=0; index0--) {
		for(; index1>=0; index1--) {
			if(x[0][index0] < x[1][index1]) {
				current--;
			} else {
				current++;
				break;
			}
		}

		if(current > naomi_wins) {
			naomi_wins = current;
		}
	}	

	return naomi_wins;

}

// walks the arrays from left to right and increments counter when it 
// increments on naomi and decrements on ken
int wins_deceitful_war(unsigned int x[2][1000], unsigned int n) {
	int index0=0, index1=0, current=0, ken_wins = 0;

	for(; index0<n; index0++) {
		for(; index1<n; index1++) {
			if(x[0][index0] < x[1][index1]) {
				current++;
				break;
			} else {
				current--;
			}
		}

		if(current > ken_wins) {
			ken_wins = current;
		}
	}	

	return n-ken_wins;
}

int main() {
	unsigned int n=0, i=0, j=0, pieces_number=0, aux=0, person=0, pieces[2][1000];
	FILE * read_fp, * write_fp;

	read_fp = fopen("input.txt", "r");
	write_fp = fopen("output.txt", "w");


	fscanf(read_fp, "%d", &n);

	for(i=0; i<n; i++) {
		pieces_number = 0;

		fscanf(read_fp, "%d", &pieces_number);

		for(person=0; person<2; person++) {
			for(j=0; j<pieces_number; j++) {
				fscanf(read_fp, "%d.%d", &aux, &aux);

				pieces[person][j] = aux;
			}
		}

		sort(pieces[0], pieces_number); // 0 is naomi
		sort(pieces[1], pieces_number); // 1 is ken

		fprintf(write_fp, "Case #%d: %d %d\n", i+1, wins_deceitful_war(pieces, pieces_number), wins_war(pieces, pieces_number));
	}


	fclose(read_fp);
	fclose(write_fp);

	return 0;
}

