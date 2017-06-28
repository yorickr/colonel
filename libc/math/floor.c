

int floor (float n) {
    if (n >= 0) {
        return (int)n;
    } else {
        int x = (int) n; // cast to int, so something like -1.1 becomes -1.
        return ((float) x == n) ? x : x - 1;
    }
}
