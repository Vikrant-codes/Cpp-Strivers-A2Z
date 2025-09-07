#include<iostream>
using namespace std;

void ptrn1(int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			cout << "* ";
		}
		cout << endl;
	}
}
void ptrn2(int n) {
	for(int i=0; i<n; i++) {
		for(int j=0; j<=i; j++) {
			cout << "* ";
		}
		cout << endl;
	}
}
void ptrn3(int n) {
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=i; j++) {
			cout << j << " ";
		}
		cout << endl;
	}
}
void ptrn4(int n) {
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=i; j++) {
			cout << i << " ";
		}
		cout << endl;
	}
}
void ptrn5(int n) {
	for(int i=n; i>0; i--){
		for(int j=1; j<=i; j++){
			cout << "* ";
		}
		cout << endl;
	}
}
void ptrn6(int n) {
	for(int i=n; i>0; i--) {
        for(int j=1; j<=i; j++) {
            cout << j << " ";
        }
        cout << endl;
    }
}
void ptrn7(int n) {
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n-i; j++) {
			cout << " ";
		}
		for(int j=1; j <= 2*i-1; j++) {
			cout << "*";
		}
		cout << "\n";
	}
}
void ptrn8(int n) {
	for(int i=n; i>0; i--) {
		for(int j=1; j<=n-i; j++) {
			cout << " ";
		}
		for(int j=1; j <= 2*i-1; j++) {
			cout << "*";
		}
		cout << "\n";
	}
}
void ptrn9(int n) {
	ptrn7(n);
	ptrn8(n);
}
void ptrn10(int n) {
	/*
	ptrn2(n);
	ptrn5(n-1);
	*/
	for(int i=1; i<=2*n-1; i++) {
		int stars = i <= n ? i : 2*n-i;
		for(int j = 0; j<stars; j++) {
			cout << "*";
		}
		cout << endl;
	}
}
void ptrn11(int n) {
	/*
	for(int i=1; i<=n; i++) {
		for(int j=i; j>0; j--) {
			int x = j%2==0 ? 0 : 1;
			cout << x << " ";
		}
		cout << endl;
	}
	*/
	int start;
	for(int i=0; i<n; i++) {
		start = i%2==0 ? 1 : 0;
		for(int j=0; j<=i; j++) {
			cout << start << " ";
			start = 1 - start; // flips value of start 0 becomes 1 and 1 becomes 0
		}
		cout << endl;
	}
}
void ptrn12(int n) {
	for(int i=1; i<=n; i++) {
        for(int j=1; j<=i; j++) {
            cout << j << " ";
        }
        for(int k=1; k<=2*n-2*i; k++) {
            cout << " " << " ";
        }
        for(int j=i; j>0; j--) {
            cout << j << " ";
        }
        cout << endl;
    }
}
void ptrn13(int n) {
	int st = 1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<=i; j++) {
            cout << st << " ";
            st++;
        }
        cout << endl;
    }
}
void ptrn14(int n) {
	for(int i=0; i<n; i++) {
		for(char ch = 'A'; ch <= 'A'+i; ch++) {
			cout << ch << " ";
		}
		cout << endl;
	}
}
void ptrn15(int n) {
	for(int i=n; i>0; i--) {
        for(char ch='A'; ch < 'A'+i; ch++) {
            cout << ch << " ";
        }
        cout << endl;
    }
}
void ptrn16(int n) {
	for(int i=0; i<n; i++) {
		char ch = 'A' + i;
		for(int j=0; j<=i; j++) {
			cout << ch << " ";
		}
		cout << endl;
	}
}
void ptrn17(int n) {
	for(int i=1; i<=n; i++) {
		for(int j=0; j<n-i; j++) {
			cout << " ";
		}
		char ch = 'A';
		for(int j=1; j<=2*i-1; j++) {
			cout << ch;
			if(j < i) ch++;
			else ch--;
		}
		cout << endl;
	}
}
void ptrn18(int n) {
	for(int i = 1; i<=n; i++) {
		for(char ch = 'A'+n-i; ch < 'A' + n; ch++) {
			cout << ch << " ";
		}
		cout << endl;
	}
}
void ptrn19(int n) {
	// Increasing Void
	for(int i=0;i<n;i++) {
		for(int j=0;j<n-i;j++) {
			cout << "* ";
		}
		for(int j=1;j<=2*i;j++) {
			cout << "  ";
		}
		for(int j=0;j<n-i;j++) {
			cout << "* ";
		}
		cout << endl;
	}
	// Decreasing Void
	for(int i=0;i<n;i++) {
		for(int j=0; j<=i; j++){
			cout << "* ";
		}
		for(int j=0;j<2*(n-i-1);j++) {
			cout << "  ";
		}
		for(int j=0; j<=i; j++){
			cout << "* ";
		}
		cout << endl;
	}
}
void ptrn20(int n) {
	int spaces = 2*n-2;
	for(int i=1; i<=2*n-1; i++) {
		int stars = i<=n ? i : 2*n-i;
		for(int j=0; j<stars; j++) {
			cout << "* ";
		}
		for(int j=0; j<spaces; j++) {
			cout << "  ";
		}
		for(int j=0; j<stars; j++) {
			cout << "* ";
		}
		cout << endl;
		if(i<n) spaces-=2;
		else spaces+=2;
	}
}
void ptrn21(int n) {
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			char ch = (i==1 || i==n || j==1 || j==n) ? '*' : ' ';
			cout << ch << " ";
		}
		cout << endl;
	}
}
void ptrn22(int n) {
	for(int i=0; i<2*n-1; i++) {
		for(int j=0; j<2*n-1; j++) {
			int top = i;
			int left = j;
			int right = 2*n-2-j;
			int bottom = 2*n-2-i;
			cout << n - min(min(top, bottom), min(left, right)) << " ";
		}
		cout << endl;
	}
}

void (*patterns[22])(int) = {ptrn1, ptrn2, ptrn3, ptrn4, ptrn5, ptrn6, ptrn7, ptrn8, ptrn9, ptrn10, ptrn11, ptrn12, ptrn13, ptrn14, ptrn15, ptrn16, ptrn17, ptrn18, ptrn19, ptrn20, ptrn21, ptrn22};

void printall(int n) {
	for(int i=0; i<22; i++) {
		cout << endl << "Pattern " << i+1 << "\n\n";
		patterns[i](n);
	}
}

int main() {
	int choice;
	cout << "1. Print a particular pattern \t\t 2. Print all patterns" << "\n" << "Enter your choice (1 or 2) : ";
	cin >> choice;
	if(choice == 1) {
		int k,n;
		cout << "Enter the Pattern number you want to print : ";
		cin >> k;
    	cout << "Enter value of n : ";
    	cin >> n;
		patterns[k-1](n);
	}
	else if(choice == 2) {
		int n;
		cout << "Enter value of n : ";
    	cin >> n;
		printall(n);
	}
}