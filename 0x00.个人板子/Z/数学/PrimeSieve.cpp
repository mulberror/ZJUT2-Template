vector<int> prime;
vector<bool> nprime;
vector<int> minp, maxp, phi, mu;

void sieve(int N) {
    nprime.assign(N + 1, false);
    minp.assign(N + 1, 0), maxp.assign(N + 1, 0), phi.assign(N + 1, 0), mu.assign(N + 1, 0);
    prime.clear();
    maxp[1] = minp[1] = phi[1] = mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!nprime[i]) {
            prime.push_back(i);
            minp[i] = maxp[i] = i;
            phi[i] = i - 1, mu[i] = -1;
        }
        for (auto x : prime) {
            if (i * x > N) {
                break;
            }
            minp[i * x] = minp[x];
            maxp[i * x] = max(x, maxp[i]);
            nprime[i * x] = true;
            if (i % x == 0) {
                phi[i * x] = phi[i] * x;
                mu[i * x] = 0;
                break;
            } else {
                mu[i * x] = -mu[i];
                phi[i * x] = phi[i] * (x - 1);
            }
        }
    }
}

vector<pair<int, int>> div(int n) {
    vector<pair<int, int>> res;
    while (n > 1) {
        int t = minp[n], cnt = 0;
        while (n % t == 0) {
            cnt++;
            n /= t;
        }
        res.push_back({t, cnt});
    }
    return res;
}
