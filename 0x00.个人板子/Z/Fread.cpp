#include <bits/stdc++.h>

using namespace std;

struct IO {
    char ibuf[1 << 23], *p1 = ibuf, *p2 = ibuf; // 注意读入空间大小
    char obuf[1 << 23], *op = obuf;             // 注意输出空间大小

#define getchar() (p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
#define putchar(x) (*op++ = (x))

    ~IO() {
        fwrite(obuf, op - obuf, 1, stdout);
    }

    template <typename T>
    void read(T& x) {
        x = 0; char ch = 0; int f = 1;
        for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -1;
        for (; isdigit(ch); ch = getchar()) x = x * 10 + (ch & 15);
        x *= f;
    }

    template <typename T>
    void write(T x) {
        if (x < 0) putchar('-'), x = -x;
        if (x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }

    template <typename T>
    void writeln(T x) {
        write(x), putchar('\n');
    }

#undef getchar
#undef putchar
} io;