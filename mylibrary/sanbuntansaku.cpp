template <class F> ll optimize(int low, int high, const F& f) {
    while (high - low > 2) {
        const int m1 = (low + high) / 2;
        const int m2 = m1 + 1;
        if (f(m1) < f(m2)) {
            low = m1;
        } else {
            high = m2;
        }
    }
    return f(low + 1);
}