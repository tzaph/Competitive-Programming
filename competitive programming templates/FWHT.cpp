 1 void FWT_And(int *A, int len) {
 2   if (len == 1) return;
 3   int len2 = len >> 1;
 4   FWT_And(A, len2);
 5   FWT_And(A + len2, len2);
 6   for (int i = 0; i < len2; ++i)
 7     A[i] += A[i + len2];
 8 }
 9 void IFWT_And(int *A, int len) {
10   if (len == 1) return;
11   int len2 = len >> 1;
12   for (int i = 0; i < len2; ++i)
13     A[i] -= A[i + len2];
14   IFWT_And(A, len2);
15   IFWT_And(A + len2, len2);
16 }
17 
18 void FWT_Or(int *A, int len) {
19   if (len == 1) return;
20   int len2 = len >> 1;
21   FWT_Or(A, len2);
22   FWT_Or(A + len2, len2);
23   for (int i = 0; i < len2; ++i)
24     A[i + len2] += A[i];
25 }
26 void IFWT_Or(int *A, int len) {
27   if (len == 1) return;
28   int len2 = len >> 1;
29   for (int i = 0; i < len2; ++i)
30     A[i + len2] -= A[i];
31   IFWT_Or(A, len2);
32   IFWT_Or(A + len2, len2);
33 }
34 
35 void FWT_Xor(int *A, int len) {
36   if (len == 1) return;
37   int len2 = len >> 1;
38   FWT_Xor(A, len2);
39   FWT_Xor(A + len2, len2);
40   for (int i = 0; i < len2; ++i) {
41     int x = A[i], y = A[i + len2];
42     A[i] = x + y;
43     A[i + len2] = x - y;
44   }
45 }
46 void IFWT_Xor(int *A, int len) {
47   if (len == 1) return;
48   int len2 = len >> 1;
49   for (int i = 0; i < len2; ++i) {
50     int x = A[i], y = A[i + len2];
51     A[i] = (x + y) >> 1;
52     A[i + len2] = (x - y) >> 1;
53   }
54   IFWT_Xor(A, len2);
55   IFWT_Xor(A + len2, len2);
56 }