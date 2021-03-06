// I haven't run tests to compare the different versions.

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (high + low) / 2;

    while (low <= high && x != v[mid]) {
        if (x < v[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }

        mid = (high + low) / 2;
    }

    if (x == mid) {
        return mid;
    }

    return -1;
}