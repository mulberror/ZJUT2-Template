// 快速读入
int read() {
    int s = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') {
        s = s * 10 + ch - 48;
        ch = getchar();
    }
    return s;
}