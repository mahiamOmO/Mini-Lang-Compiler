// fizzbuzz.ml - MyLang Example: FizzBuzz (1 to 20)

int main() {
    int i = 1;
    while (i <= 20) {
        int r3 = i % 3;
        int r5 = i % 5;
        if (r3 == 0) {
            if (r5 == 0) {
                print(0);   // FizzBuzz placeholder (print 0)
            } else {
                print(3);   // Fizz placeholder
            }
        } else {
            if (r5 == 0) {
                print(5);   // Buzz placeholder
            } else {
                print(i);
            }
        }
        i++;
    }
    return 0;
}
