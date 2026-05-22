// Example 5: Sum of even numbers using while and if
int num;
int total;
num = 2;
total = 0;
while (num <= 20) {
  if (num % 2 == 0) {
    total = total + num;
  }
  num = num + 2;
}
