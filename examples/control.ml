// control.ml - MyLang Example: Control flow + arithmetic

int factorial(int n) {
    int result = 1;
    int i = 2;
    while (i <= n) {
        result = result * i;
        i++;
    }
    return result;
}

int main() {
    // Test constant folding (optimizer will compute 3+4 at compile time)
    int a = 3 + 4;
    int b = a * 2;

    // Test if-else
    if (b > 10) {
        print(b);
    } else {
        print(0);
    }

    // Test for loop
    int sum = 0;
    int j = 1;
    while (j <= 5) {
        sum = sum + j;
        j++;
    }
    print(sum);

    return 0;
}
