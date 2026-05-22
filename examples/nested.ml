// Example 3: Nested if-else with while
int n;
int sum;
n = 1;
sum = 0;
while (n <= 10) {
  if (n % 2 == 0) {
    sum = sum + n;
  } else {
    sum = sum - n;
  }
  n = n + 1;
}
